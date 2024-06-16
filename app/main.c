#include <stdio.h>
#include <string.h>

int main() {
  /*Uncomment this block to pass the first stage*/
  // Wait for user input
  while (1) {
    printf("$ ");
    fflush(stdout);

    char input[100];
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = 0;
    if (strcmp(input, "exit 0") == 0)
      break;
    char *p = strtok(input, " ");
    if (strcmp(p, "echo") == 0) {
      p = strtok(NULL, " ");
      while (p != NULL) {
        printf("%s ", p);
        p = strtok(NULL, " ");
      }
      printf("\n");
    } else {

      printf("%s: command not found\n", &input[0]);
    }
  }
  return 0;
}
