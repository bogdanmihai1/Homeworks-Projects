#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include "link_emulator/lib.h"
#include "utils.h"

#define HOST "127.0.0.1"
#define PORT 10000

void send_name(char *fisier) {
  msg t, r;

  memset(t.payload, 0, sizeof(t.payload));
  memcpy(t.payload + 4, fisier, strlen(fisier));

  char name_sum = check_sum(t.payload, strlen(fisier) + 4);
  sprintf(t.payload + strlen(fisier) + 5, "%c", name_sum);
  t.len = 6 + strlen(fisier);

  send_message(&t);

  if (recv_message(&r) < 0) {
      perror("receive error");
  } else {
    while (1) {
      if (strcmp(r.payload, "ACK") == 0) {
	  break;
      }
      if (strcmp(r.payload, "NACK") == 0) {
	send_message(&t);
	recv_message(&r);
      }
    }
  }
}

int send_size(char* fisier) {
  msg r, t;
  int fd = open(fisier, O_RDONLY);
  int len = lseek(fd, 0, SEEK_END);
  memset(t.payload, 0, sizeof(t.payload));
  int size = FILE_SIZE;
  int COUNT = len / (MAX_LEN - 9) + 1;

  // trimit dimensiunea fisierului si numarul de pachete
  memcpy(t.payload, &size, 4);
  memcpy(t.payload + 4, &len, 4);
  memcpy(t.payload + 8, &COUNT, 4);

  int size_sum = check_sum(t.payload, 12);
  sprintf(t.payload + 12, "%c", size_sum);
  t.len = 13;

  send_message(&t);

  if (recv_message(&r) < 0) {
    perror("receive error");
  }

  close(fd);
  return COUNT;
}

void send_data(char *fisier, int window_size, int delay, int COUNT) {
  msg r, t;
  int len;
  int fd = open(fisier, O_RDONLY);
  int cnt = 1, cnt_res = 1, res;
  memset(t.payload, 0, sizeof(t.payload));
  int data = FILE_DATA;
  char sum;
  // nack_nums[0] este contorul pachetelor care nu au fost primite corespunzator
  // iar nack_nums[i] reprezinta indicele unui pachet pierdut/corupt
  int nack_nums[COUNT];
  // nack_msg reprezinta mesajele care au primit nack
  msg *nack_msg;
  nack_msg = (msg*)calloc(COUNT + 1, sizeof(msg));
  memset(nack_nums, 0, sizeof(nack_nums));
  nack_nums[0] = 0;

  for (int i = 0; i < window_size; i++) {
    len = read(fd, t.payload + 8, sizeof(t.payload) - 9);
    memcpy(t.payload, &data, 4);
    memcpy(t.payload + 4, &cnt, 4);
    cnt++;
    t.len = 8 + len;
    sum = check_sum(t.payload, t.len);
    sprintf(t.payload + t.len, "%c", sum);
    t.len += sizeof(char);
    send_message(&t);
  }

  for (int i = 0; i < COUNT - window_size; i++) {
    res = recv_message_timeout(&r, delay); 
    
    if (strcmp(r.payload, "NACK") == 0 || res == -1) {
      nack_nums[0]++;
      nack_nums[nack_nums[0]] = cnt_res;
      nack_msg[nack_nums[0]] = t;
    }

    cnt_res++;
    len = read(fd, t.payload + 8, sizeof(t.payload) - 9);
    memcpy(t.payload, &data, 4);
    memcpy(t.payload + 4, &cnt, 4);
    cnt++;
    t.len = 8 + len;
    sum = check_sum(t.payload, t.len);
    sprintf(t.payload + t.len, "%c", sum);
    t.len += sizeof(char);

    send_message(&t);
  }
  for (int i = 0; i < window_size; ++i) {
    res = recv_message_timeout(&r, delay);

    if(strcmp(r.payload, "NACK") == 0 || res == -1) {
      // adaug pachetele corupte/pierdute pentru a le retrimite
      nack_nums[0]++;
      nack_nums[nack_nums[0]] = cnt_res;
      nack_msg[nack_nums[0]] = t;
    }
    cnt_res++;
  }
  // retrimit pachetele care nu au ajuns corect in recv
  while (nack_nums[0] > 0) {
    int pack = nack_nums[nack_nums[0]];
    lseek(fd, (pack-1)*(sizeof(t.payload) - 9), SEEK_SET);
    len = read(fd, t.payload + 8, sizeof(t.payload) - 9);
    memcpy(t.payload, &data, 4);
    memcpy(t.payload + 4, &pack, 4);

    t.len = 8 + len;
    sum = check_sum(t.payload, t.len);
    sprintf(t.payload + t.len, "%c", sum);
    t.len += sizeof(char);
    send_message(&t);

    res = recv_message_timeout(&r, delay);

    if(strcmp(r.payload, "ACK") == 0) {
      nack_nums[0]--;
    }
  }
}

void send_eot() {
  msg t;
  memset(&t, 0, sizeof(msg));
  int type = EOT;
  t.len = 4;
  memcpy(t.payload, &type, 4);

  send_message(&t);
}

void transmit(char *fisier, int window_size, int delay) {
  send_name(fisier);
  int count = send_size(fisier);
  send_data(fisier, window_size, delay, count);
  send_eot();
}


int main(int argc,char** argv) {
  init(HOST,PORT);
  msg r;

  int speed = (int) atoi(argv[2]);
  int delay = (int) atoi(argv[3]);
  int window_size = (speed * delay * 1000) / (8 * sizeof(msg));

  transmit(argv[1], window_size, delay);
  recv_message(&r);
  while (1) {
    if(strcmp(r.payload, "STOP") == 0) {
      return 0;
    }
    else {
      recv_message(&r);
    }
  }

  return 0;
}
