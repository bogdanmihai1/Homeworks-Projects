#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"
#include "utils.h"

#define HOST "127.0.0.1"
#define PORT 10001

int main(int argc,char** argv) {

	msg r,t;
  	char received_sum, computed_sum;
  	init(HOST,PORT);
  	int COUNT = 0;
  	msg* content;
  	int type, fd, len = 0;
 	char name[205], name_aux[200];
  	while (1) {
    	if (recv_message(&r) < 0) {
    	  	perror("Receive message");
     	 	return -1;
   	 	}
    	memcpy(&received_sum, r.payload + r.len - sizeof(char), sizeof(char));
  		computed_sum = check_sum(r.payload, r.len - 1);
    
    	// Extrage tipul
    	memcpy(&type, r.payload, 4);
    
    	// In functie de tip, realizeaza o procesare
    	if (type == EOT) {
     		break;
    	}

    	if (type == FILE_NAME) {
			computed_sum = check_sum(r.payload, r.len - 1);
			if (received_sum == computed_sum) {
	 			memset(&t, 0, sizeof(msg));
     			sprintf(t.payload, "ACK");
     			memset(name, 0, sizeof(name));
     			memset(name_aux, 0, sizeof(name_aux));
     			memcpy(name_aux, r.payload + 4, r.len - 6);
     			sprintf(name, "recv_%s", name_aux);
      			fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			} else {
	  			memset(name_aux, 0, sizeof(name_aux));
	 			memset(&t, 0, sizeof(msg));
	 			sprintf(t.payload, "NACK");
			}
   		} else if (type == FILE_SIZE) {
      		len = 0;
      		// initializeaza contorul pt dimensiunea fisierului
      		memcpy(&len, r.payload + 4, 4);
      		memcpy(&COUNT, r.payload + 8, 4);
     		content = (msg*)calloc(COUNT + 1, sizeof(msg));
    	} else if (type == FILE_DATA) {
      		// Am primit un mesaj cu date - scrie le in fisierul recv
      		if(received_sum == computed_sum) {
      			memset(&t, 0, sizeof(msg));
        		sprintf(t.payload, "ACK");
        		int pack_num;
        		memcpy(&pack_num, r.payload + 4, 4);
        		content[pack_num] = r;
        		len -= (r.len - 9);
    		} else {
				memset(&t, 0, sizeof(msg));
				sprintf(t.payload, "NACK");
    		}
  		}
    
    	// Trimite confirmare pt mesajul primit si procesat
    	memset(&t, 0, sizeof(msg));
    	if (received_sum == computed_sum) {
     		sprintf(t.payload, "ACK");
    	} else {
			sprintf(t.payload, "NACK");
    	}
    	t.len = 5;
    	send_message(&t);
	}
  	for (int i = 1; i <= COUNT; i++) {
   		write(fd, content[i].payload + 8, content[i].len - 9);
  	}
  	sprintf(t.payload, "End");
  	send_message(&t);
  	close(fd);
  	return 0;
}
