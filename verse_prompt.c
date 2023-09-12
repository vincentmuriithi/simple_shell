#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_INPUT_LENGTH 1024
/**
 * main - entry of program
 * Return: 0 upon success
 */
int main(void)
{
char input[MAX_INPUT_LENGTH];
while (1)
{
printf("($) ");
if (fgets(input, sizeof(input), stdin) == NULL)
{
printf("\n");
break;
}
input[strcspn(input, "\n")] = '\0';
pid_t pid = fork();
if (pid == -1)
{
perror("Fork failed");
exit(1);
}
else if (pid == 0)
{
if (execlp(input, input, (char *)NULL) == -1)
{
perror("Exec failed");
exit(1);
}
}
else
{
int status;
waitpid(pid, &status, 0);
if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
{
printf("Command not found: %s\n", input);
}
}
}

return (0);
}
