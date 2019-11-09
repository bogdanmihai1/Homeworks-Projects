#ifndef _PARSERS_
#define _PARSERS_

char* get_task(char* response);
char* get_user(char* response);
char* get_pass(char* response);
char* get_cookies(char* response);
char* get_id(char* response);
char* get_token(char* response);
char* make_login(char* user, char* pass);
char* make_answer(char* task, char* id);
char* make_auth(char* token);

#endif
