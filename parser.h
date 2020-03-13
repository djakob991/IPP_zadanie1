
struct Info {
  int code;
  char *str1;
  char *str2;
  char *beg;
};

void writeInfo(struct Info *dest, int code, char *str1, char *str2, char *beg);
char *readLine();
void whatToDo(char *s, struct Info *dest);
