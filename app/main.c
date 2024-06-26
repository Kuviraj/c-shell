#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *get_path_type(char *word) {
  char *temp_path = getenv("PATH");
  if (temp_path == NULL)
    return 0;
  char *p = strtok(word, " ");
  char *path = strdup(temp_path);
  char *iter_path = strtok(path, ":");
  while (iter_path != NULL) {
    // get list of files for each path
    DIR *dir = opendir(iter_path);
    struct dirent *entry;
    if (dir == NULL) {

      iter_path = strtok(NULL, ":");
      continue;
    }
    while ((entry = readdir(dir)) != NULL) {
      if (strcmp(p, (entry->d_name)) == 0) {

        iter_path = strcat(iter_path, "/");
        return strcat(iter_path, p);
      }
    }
    iter_path = strtok(NULL, ":");
  }
  return NULL;
}

int main() {
  /*Uncomment this block to pass the first stage*/
  // Wait for user input
  while (1) {
    printf("$ ");
    system("pwd");
    fflush(stdout);

    char input[100];
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = 0;
    char words[4][10] = {"exit", "echo", "type", "cd"};
    char *full_input = strdup(input);
    if (strcmp(input, "exit 0") == 0)
      break;

    char *p = strtok(input, " ");

    if (strcmp(p, "echo") == 0) {
      printf("%s\n", input + 5);
    } else if (strcmp(p, "type") == 0) {
      int found = 0;
      p = strtok(NULL, " ");
      for (int i = 0; i < 4; i++) {
        if (strcmp(p, words[i]) == 0)
          found = 1;
      }

      if (found) {
        printf("%s is a shell builtin\n", p);
      } else {
        char *new_status = get_path_type(p);
        if (new_status)
          printf("%s is %s\n", p, new_status);
        else
          printf("%s: not found\n", p);
      }
    } else if (strcmp(p, "cd") == 0) {
      full_input += 3;
      if (full_input[0] == '~') {
        char* home_path = getenv("HOME");
        full_input += 1;
        full_input = strcat(home_path, full_input);
      }
      if (chdir(full_input) < 0)
        printf("cd: %s: No such file or directory\n", full_input);
    } else {
      char *command = strtok(input, " ");
      char *new_status = get_path_type(command);
      if (new_status) {
        system(full_input);
      } else
        printf("%s: command not found\n", &input[0]);
    }
  }
  return 0;
}
