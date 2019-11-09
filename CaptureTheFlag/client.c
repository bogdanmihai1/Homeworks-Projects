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
#include "parsers.h"

int main(int argc, char *argv[])
{
    char *message;
    char *response;
    int sockfd;

    // Task 1
    puts("Task 1");

    // deschid conexiunea
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    char* task1 = "/task1/start";

    // generez mesajul, il trimit catre server si afisez raspunsul
    message = compute_get_request(IP_SERVER, task1, NULL, NULL);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    puts(response);

    // inchid conexiunea
    close_connection(sockfd);

    // Task 2
    puts("\n\nTask 2");

    // deschid conexiunea
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    
    // generez datele necesare primite din taskul anterior
    char* task2 = get_task(response);
    char* user = get_user(response);
    char* pass = get_pass(response);
    char* cookies = get_cookies(response);
    char* aut = make_login(user, pass); // aut = authentication
    free(message);
    free(response);

    // generez mesajul, il trimit catre server si afisez raspunsul
    message = compute_post_request(IP_SERVER, task2, aut, cookies);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    puts(response);

    // inchid conexiunea
    close_connection(sockfd);

    // Task 3
    puts("\n\nTask 3");

    // deschid conexiunea
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);

    // generez datele necesare primite din taskul anterior
    char* token = get_token(response);
    char* id = get_id(response);
    char* task3 = get_task(response);
    char* answer = make_answer(task3, id);
    char* auth = make_auth(token); // auth = authorization
    cookies = get_cookies(response);

    // generez mesajul, il trimit catre server si afisez raspunsul
    message = compute_get_request(IP_SERVER, answer, auth, cookies);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    puts(response);

    // inchid conexiunea
    close_connection(sockfd);

    // Task 4
    puts("\n\nTask 4");

    // deschid conexiunea
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);

    // generez datele necesare primite din taskul anterior
    char* task4 = get_task(response);
    cookies = get_cookies(response);

    // generez mesajul, il trimit catre server si afisez raspunsul
    message = compute_get_request(IP_SERVER, task4, auth, cookies);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    puts(response);

    // inchid conexiunea
    close_connection(sockfd);
    free(message);
    free(response);

    return 0;
}
