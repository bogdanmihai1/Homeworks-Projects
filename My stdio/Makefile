CC = gcc
SHARED_FLAG = -Wall -shared
fPic_FLAG = -Wall -fpic

build:	libso_stdio.so

libso_stdio.so: libso_stdio.o
	$(CC) $(SHARED_FLAG) libso_stdio.o -o libso_stdio.so

libso_stdio.o: libso_stdio.c
	$(CC) $(fPic_FLAG) -c libso_stdio.c -o libso_stdio.o

clean:
	rm -f *.o  libso_stdio.so
