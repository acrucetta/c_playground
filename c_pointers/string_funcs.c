#include <stdio.h>
#include <stdlib.h>

char *str_cpy(char dest[], const char src[]) {
  int i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  return dest;
}

int str_len(const char str[]) {
  int i = 0;
  while (str[i] != '\0') {
    i++;
  }
  return i;
}

char *str_cat(char str1[], char str2[]) {
  int str1_len = str_len(str1);
  int str2_len = str_len(str2);
  char *result = malloc(str1_len + str2_len + 1);
  str_cpy(result, str1);
  str_cpy(result + str1_len, str2);
  return result;
}

char *str_chr(const char *str, int c) { return 0; }

int main() {

  const char *str = "sample str";
  char *cpy = malloc(str_len(str) + 1);
  printf("%lu", sizeof(cpy));
  str_cpy(cpy, str);
  int len;
  len = str_len(cpy);
  printf("%s", cpy);
  printf("%d", len);
  free(cpy);

  char *str1 = "abc ";
  char *str2 = "def";
  char *result = str_cat(str1, str2);
  printf("%s", result);
}
