#ifndef OTHER_H_
#define OTHER_H_

int removeDir(const char* dirPath);

#define MAX_PASSWORD_LENGTH 16
#define MIN_PASSWORD_LENGTH 6
#define ERROR_PASSWORD "0123456789abcdefghijklmn"
string getPassword();
int getNumber(int down = INT_MIN, int up = INT_MAX);

#define MAX_STRING_LENGTH 30
#define ERROR_STRING "0123456789abcdef0123456789abcdef"
string getString();

#endif // !OTHER_REMOVEDIR_H_