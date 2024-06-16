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
    printf("%s: command not found\n", &input[0]);
  }
  return 0;
}
