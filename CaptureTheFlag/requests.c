#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

char *compute_get_request(char *host, char *url, char* auth, char* cookies)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    // Scriem numele metodei, calea si tipul protocolului
    sprintf(line, "GET %s HTTP/1.1", url);
    compute_message(message, line);
  
    // Adaugam host-ul
    sprintf(line, "HOST: %s", host);
    compute_message(message, line);

    // Adaugam headere si/ sau cookies, respectand forma protocolului
    if (cookies == NULL)
    {
        sprintf(line, "Cookie: isLogged=true");
        compute_message(message, line);
    } else
    {
        sprintf(line, "Cookie: %s", cookies);
        compute_message(message, line);
    }

    if (auth != NULL)
    {
        sprintf(line, "%s", auth);
        compute_message(message, line);
    }

    // Adaugam linia de final
    memset(line, 0, LINELEN);
    compute_message(message, line);

    free(line);
    return message;
}
char *compute_post_request(char *host, char *url, char *form_data, char* cookies)
{

    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    
    // Scriem numele metodei, calea si tipul protocolului
    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);
   
    // Adaugam host-ul
    sprintf(line, "HOST: %s", host);
    compute_message(message, line);

    // Adaugam headere si/ sau cookies, respectand forma protocolului
    strcpy(line, "Content-Type: application/x-www-form-urlencoded");
    compute_message(message, line);

    sprintf(line, "Content-Length: %ld", strlen(form_data));
    compute_message(message, line);
    
    sprintf(line, "Cookie: %s", cookies);
    compute_message(message, line);

    // Adaugam linia de final de antent
    strcpy(line, "\r\n");
    strcat(message, line);
    
    // Adaugam data
    strcpy(line, form_data);
    compute_message(message, line);

    free(line);
    return message;
}
