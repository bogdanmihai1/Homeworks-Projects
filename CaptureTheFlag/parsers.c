#include <stdlib.h>
#include <string.h>

char* get_task(char* response)
{
    char* pattern = "url\":\"";
    char* task = NULL;
    char *start, *end;

    start = strstr(response, pattern);
    start += strlen(pattern);
    end = strstr(start, "\"");

    task = (char*)malloc(end - start + 1);
    memcpy(task, start, end - start);
    task[end - start] = '\0';

    return task;
}

char* get_user(char* response)
{
    char* user = NULL;
    char *start, *end;
    char* pattern = "username\":\"";

    start = strstr(response, pattern);
    start += strlen(pattern);
    end = strstr(start, "\"");

    user = (char*)malloc(end - start + 1);
    memcpy(user, start, end - start + 1);
    user[end - start] = '\0';

    return user;
}

char* get_pass(char* response)
{
    char* pass;
    char *start, *end;
    char* pattern = "password\":\"";

    start = strstr(response, pattern);
    start += strlen(pattern);
    end = strstr(start, "\"");

    pass = (char*)malloc(end - start + 1);
    memcpy(pass, start, end - start + 1);
    pass[end - start] = '\0';

    return pass;
}

char* get_cookies(char* response)
{
    char* cookie1 = NULL;
    char* cookie2 = NULL;
    char* cookie = NULL;
    char* pattern1 = "Set-Cookie:";
    char* pattern2 = "httponly";
    char *start, *end;

    start = strstr(response, pattern1);
    start += strlen(pattern1) + 1;
    end = strstr(response, pattern2);
    end += strlen(pattern2);

    cookie1 = (char*)malloc(end - start + 1);
    memcpy(cookie1, start, end - start);
    cookie1[end - start] = '\0';
    
    start = strstr(start, pattern1);
    start += strlen(pattern1) + 1;
    end = strstr(start, pattern2);
    end += strlen(pattern2);

    cookie2 = (char*)malloc(end - start + 1);
    memcpy(cookie2, start, end - start);
    cookie2[end - start] = '\0';

    cookie = (char*)malloc(strlen(cookie1) + strlen(cookie2) + 3);
    strcat(cookie, cookie1);
    strcat(cookie, "; ");
    strcat(cookie, cookie2);

    return cookie;
}

char* get_id(char* response)
{
    char* pattern = "id\":\"";
    char* start = NULL;
    char *end = NULL;
    char* id = NULL;

    start = strstr(response, pattern);
    start += strlen(pattern);
    end = strstr(start, "\"");

    id = (char*) malloc(end - start + 1);
    memcpy(id, start , end - start);
    id[end - start] = '\0';

    return id;
}

char* get_token(char* response)
{
    char* pattern = "token\":\"";
    char* start = NULL;
    char *end = NULL;
    char* token = NULL;

    start = strstr(response, pattern);
    start += strlen(pattern);
    end = strstr(start, "\"");

    token = (char*) malloc(end - start + 1);
    memcpy(token, start , end - start);
    token[end - start] = '\0';

    return token;
}

char* make_login(char* user, char* pass)
{
    char* aut_user = "username=";
    char* aut_pass = "&password=";
    char* aut = NULL;
    
    aut = (char*)malloc(strlen(aut_user) + strlen(user) + strlen(aut_pass) +
          strlen(pass) + 1);
    strcat(aut, aut_user);
    strcat(aut, user);
    strcat(aut, aut_pass);
    strcat(aut, pass);

    return aut;
}

char* make_answer(char* task, char* id)
{
    char* ans = NULL;
    char* str = "?raspuns1=omul&raspuns2=numele&id=";
    ans = (char*)malloc(strlen(task) + strlen(id) + strlen(str) + 1);

    strcpy(ans, task);
    strcat(ans, str);
    strcat(ans, id);

    return ans;
}

char* make_auth(char* token)
{
    char* auth = NULL;
    char* str = "Authorization: Bearer ";
    auth = (char*)malloc(strlen(token) + strlen(str) + 1);

    strcpy(auth, str);
    strcat(auth, token);

    return auth;
}
