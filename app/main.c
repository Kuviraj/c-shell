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
    char words[3][10] = {"exit", "echo", "type"};

    if (strcmp(input, "exit 0") == 0)
      break;
    char *p = strtok(input, " ");

    if (strcmp(p, "echo") == 0) {
      printf("%s\n", input + 5);
    } else if (strcmp(p, "type") == 0) {
      int found = 0;
      p = strtok(NULL, " ");
      for (int i = 0; i < 3; i++) {
        if (strcmp(p, words[i]) == 0)
          found = 1;
      }
      if (found) {
        printf("%s is a shell builtin\n", p);
      } else {
        printf("%s: not found\n", p);
      }
    } else {
      printf("%s: command not found\n", &input[0]);
    }
  }
  return 0;
}
