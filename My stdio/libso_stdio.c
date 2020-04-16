// SPDX-License-Identifier: GPL-2.0-or-later

#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#include "so_stdio.h"

#define BUFFER_SIZE 4096
#define NO_OP 0
#define READ_OP 1
#define WRITE_OP 2

struct _so_file {
	int fd;
	long position;
	long size;
	unsigned char *buffer;
	char *command;
	int buffer_start;
	int buffer_len;
	int buffer_op;
	int isAppend;
	int error;
	int eof;
};

SO_FILE *so_fopen(const char *pathname, const char *mode)
{
	SO_FILE *file = malloc(sizeof(SO_FILE));

	int mod, fd;
	mode_t permissions;

	struct stat st;

	/* modul in care deschid fisierul */
	permissions = 0666;
	if (!strcmp(mode, "r")) {
		mod = O_RDONLY;
		file->isAppend = 0;
	} else if (!strcmp(mode, "r+")) {
		mod = O_RDWR;
		file->isAppend = 0;
	} else if (!strcmp(mode, "w")) {
		mod = O_WRONLY | O_CREAT | O_TRUNC;
		file->isAppend = 0;
	} else if (!strcmp(mode, "w+")) {
		mod = O_RDWR | O_CREAT | O_TRUNC;
		file->isAppend = 0;
	} else if (!strcmp(mode, "a")) {
		mod = O_CREAT | O_WRONLY | O_APPEND;
		file->isAppend = 1;
	} else if (!strcmp(mode, "a+")) {
		mod = O_APPEND | O_RDWR | O_CREAT;
		file->isAppend = 1;
	} else {
		free(file);
		return NULL;
	}

	fd = open(pathname, mod, permissions);

	if (fd < 0) {
		free(file);
		return NULL;
	}

	fstat(fd, &st);

	/* initializare date */
	file->fd = fd;
	file->position = 0;
	file->size = (long)st.st_size;
	file->buffer = malloc(BUFFER_SIZE * sizeof(unsigned char));
	file->buffer_start = 0;
	file->buffer_len = 0;
	file->buffer_op = 0;
	file->error = 0;
	file->eof = 0;

	if (file->buffer == NULL) {
		free(file);
		return NULL;
	}
	file->buffer[0] = 0;
	return file;
}

int so_fclose(SO_FILE *stream)
{
	int rc = 0;
	/*
	 * daca ultima operatie a fost de write,
	 * scriu datele din buffer in fisier
	 */
	if (stream->buffer_op == WRITE_OP)
		rc = so_fflush(stream);

	if (close(stream->fd) < 0) {
		stream->error = SO_EOF;
		rc = SO_EOF;
	}
	free(stream->buffer);
	free(stream);
	return rc;
}

int so_fileno(SO_FILE *stream)
{
	return stream->fd;
}

/* so_fflush este singura functie care scrie direct in fisier */
int so_fflush(SO_FILE *stream)
{
	int rc;

	if (stream->fd < 0) {
		stream->error = SO_EOF;
		return SO_EOF;
	}
	if (stream->buffer_len == 0)
		return 0;

	/*
	 * daca fisierul e deschis in modul append,
	 * datele se vor scrie la final
	 */
	if (stream->isAppend)
		lseek(stream->fd, 0, SEEK_END);
	else
		lseek(stream->fd, stream->position, SEEK_SET);

	rc = write(stream->fd, stream->buffer, stream->buffer_len);
	stream->buffer[0] = 0;

	if (rc < 0) {
		stream->error = SO_EOF;
		return SO_EOF;
	}

	/* se face update la membrii structurii */
	stream->buffer_len = 0;
	stream->size += rc;
	stream->position += rc;
	stream->buffer_start = -1;
	stream->buffer_op = NO_OP;
	return 0;
}

int so_fseek(SO_FILE *stream, long offset, int whence)
{
	/* se verifica tipul de date din buffer (scriere/citire) */
	if (stream->buffer_op == READ_OP) {
		stream->buffer[0] = 0;
		stream->buffer_len = 0;
		stream->buffer_op = NO_OP;
	} else if (stream->buffer_op == WRITE_OP) {
		so_fflush(stream);
	}

	switch (whence) {
	case SEEK_SET:
		stream->position = offset;
		break;
	case SEEK_CUR:
		stream->position += offset;
		break;
	case SEEK_END:
		stream->position = stream->size + offset;
		break;
	default:
		stream->error = SO_EOF;
		return SO_EOF;
	}

	if (stream->position < 0 || stream->position > stream->size) {
		stream->error = SO_EOF;
		return SO_EOF;
	}
	return 0;
}

long so_ftell(SO_FILE *stream)
{
	long buffPos;

	if (stream->position < 0 || stream->position > stream->size) {
		stream->error = SO_EOF;
		return SO_EOF;
	}
	/*
	 * daca bufferul este folosit pentru write,
	 * se ia in considerare si dimensiunea acestuia
	 */
	buffPos = stream->buffer_op == WRITE_OP ? stream->buffer_len : 0;
	return stream->position + buffPos;
}

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
	size_t readCnt;
	int c, rc;

	readCnt = 0;
	while (readCnt < size * nmemb) {
		c = so_fgetc(stream);
		if (c >= 0) {
			*(unsigned char *)(ptr + readCnt) = (unsigned char)c;
			readCnt++;
		} else {
			/* so_fgetc a intampinat o eroare */

			/* check for eof */
			lseek(stream->fd, readCnt, SEEK_SET);
			rc = read(stream->fd, stream->buffer,
				BUFFER_SIZE * sizeof(unsigned char));
			if (rc == 0) {
				stream->error = SO_EOF;
				return readCnt;
			}
			/* alta eroare, nu ar trebui sa se ajunga aici */
			stream->error = -2;
			return readCnt;
		}
	}

	return readCnt / size;
}


size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
	size_t writeCnt = 0;
	unsigned char c;

	while (writeCnt < size * nmemb) {
		c = *(unsigned char *)(ptr + writeCnt);
		writeCnt++;
		so_fputc(c, stream);
	}

	return writeCnt / size;
}

int so_fgetc(SO_FILE *stream)
{
	/*
	 * pos este pozitia din buffer din care se va lua caracterul
	 * newStart este folosit pentru a determina daca elementul
	 *	este in buffer sau nu
	 * newStart * BUFFER_SIZE + pos = position
	 */
	size_t cnt;
	int pos = stream->position % BUFFER_SIZE;
	int newStart = (int) (stream->position / BUFFER_SIZE);

	if (so_feof(stream))
		return SO_EOF;

	/* s-a folosit bufferul pt scriere */
	if (stream->buffer_op == WRITE_OP)
		so_fseek(stream, 0, SEEK_CUR);

	/* se populeaza bufferul daca este nevoie */
	if (stream->buffer_len == 0 || newStart != stream->buffer_start) {
		stream->buffer_start = newStart;
		stream->buffer[0] = 0;
		lseek(stream->fd, BUFFER_SIZE * stream->buffer_start, SEEK_SET);
		cnt = read(stream->fd, stream->buffer,
			BUFFER_SIZE * sizeof(unsigned char));
		stream->buffer_len = cnt;

		if (cnt < 0 || pos >= cnt) {
			stream->eof = 1;
			stream->error = SO_EOF;
			stream->buffer[0] = 0;
			stream->buffer_len = 0;
			return SO_EOF;
		}
	}

	/* s-a ajuns la eof */
	if (stream->buffer_len <= pos) {
		stream->eof = 1;
		return SO_EOF;
	}

	stream->buffer_op = READ_OP;
	stream->position = stream->position + 1;
	return (int)stream->buffer[pos];
}

int so_fputc(int c, SO_FILE *stream)
{
	int len;

	if (c < 0) {
		stream->error = SO_EOF;
		return SO_EOF;
	}

	/* daca s-a folosit bufferul pt citire, il golesc */
	if (stream->buffer_op == READ_OP)
		so_fseek(stream, 0, SEEK_CUR);

	/* daca bufferul e plin, dau flush */
	if (stream->buffer_len >= BUFFER_SIZE - 1) {
		so_fflush(stream);
		len = 0;
	} else
		len = stream->buffer_len;

	/* adaug elementul pe urmatoarea pozitie libera din buffer */
	stream->buffer[len] = (unsigned char) c;
	stream->buffer[len + 1] = '\0';
	stream->buffer_op = WRITE_OP;
	stream->buffer_len += 1;

	return c;
}

int so_feof(SO_FILE *stream)
{
	return stream->eof;
}

int so_ferror(SO_FILE *stream)
{
	return stream->error;
}

SO_FILE *so_popen(const char *command, const char *type)
{
	pid_t pid;
	int rc;
	int fds[2];
	char *argp[4] = {"sh", "-c", NULL, NULL};

	SO_FILE *file = malloc(sizeof(SO_FILE));

	if (file == NULL)
		return NULL;

	struct stat st;

	rc = pipe(fds);
	if (rc)
		return NULL;

	pid = fork();
	switch (pid) {
	case -1:
	/* Fork failed */
		free(file);
		close(fds[0]);
		close(fds[1]);
		return NULL;
	case 0:
		/* Child process */
		if (strcmp(type, "r") == 0) {
			close(fds[0]);
			if (fds[1] != STDOUT_FILENO) {
				dup2(fds[1], STDOUT_FILENO);
				close(fds[1]);
			}
		} else {
			return NULL;
		}
		file->command = malloc((strlen(command) + 1) * sizeof(char));
		if (file->command == NULL)
			return NULL;

		strcpy(file->command, command);
		argp[2] = file->command;
		execvp("/bin/sh", argp);
		return NULL;
	default:
		/* Parent process */
		if (strcmp(type, "r") == 0) {
			file->fd = fds[0];
			close(fds[1]);
		} else {
			return NULL;
		}

		/* initializare date */
		fstat(file->fd, &st);
		file->position = 0;
		file->size = (long)st.st_size;
		file->buffer = malloc(BUFFER_SIZE * sizeof(unsigned char));
		file->buffer_start = 0;
		file->buffer_len = 0;
		file->buffer_op = 0;
		file->error = 0;
		file->eof = 0;
		file->isAppend = 0;

		if (file->buffer == NULL) {
			free(file);
			return NULL;
		}
		file->buffer[0] = 0;
		return file;
	}
}

int so_pclose(SO_FILE *stream)
{
	/* wait for child to finish */
	wait(NULL);
	close(stream->fd);
	free(stream->buffer);
	free(stream);
	return 0;
}

int main(void)
{
	return 0;
}
