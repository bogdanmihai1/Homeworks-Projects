#ifndef _REQUESTS_
#define _REQUESTS_

char *compute_get_request(char *host, char *url, char *auth, char *cookies);
char *compute_post_request(char *host, char *url, char *form_data, char *cookies);

#endif
