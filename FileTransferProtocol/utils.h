#define FILE_NAME 0
#define FILE_SIZE 1
#define FILE_DATA 2
#define EOT 3
#define MAX_LEN 1400

char check_sum(char data[MAX_LEN], int len) {
    char res = data[0];
    for (int i = 1; i < len; i++) {
	res = res ^ data[i];
    }
    return res;
}
