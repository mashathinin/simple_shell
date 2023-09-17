#include "main.h"
/**
 * get_path_dirs - Gets the value from environmental variable PATH.
 *
 * @en: Environmental variables pointer.
 *
 * Return: Pathway for commands in directories.
 */
char **get_path_dirs(char **en)
{
char **path_dirs = NULL, *path_value = NULL;
unsigned int i = 0;
path_value = strtok(en[i], "=");
while (en[i])
{
if (string_compare(path_value, "PATH"))
{
path_value = strtok(NULL, "\n");
path_dirs = tokenizer(path_value, ":");
return (path_dirs);
}
i++;
path_value = strtok(en[i], "=");
}
return (NULL);
}
/**
 * execute_cmd - Executes a command.
 *
 * @cmd: Command pointer of strings.
 * @name: Name of the shell.
 * @env: Environmental variables pointer.
 * @cycles: Number of executed cycles.
 *
 * Return: Nothing.
 */
void execute_cmd(char **cmd, char *name, char **env, int cycles)
{
char **path_dirs = NULL, *fullpath = NULL;
struct stat pr;
unsigned int i = 0;
if (string_compare(cmd[0], "env") != 0)
print_environ(env);
if (stat(cmd[0], &pr) == 0)
{
if (execve(cmd[0], cmd, env) < 0)
{
perror(name);
free_mem_exit(cmd);
}
}
else
{
path_dirs = get_path_dirs(env);
while (path_dirs[i])
{
fullpath = string_con(path_dirs[i], cmd[0]);
i++;
if (stat(fullpath, &pr) == 0)
{
if (execve(fullpath, cmd, env) < 0)
{
perror(name);
free_memory(path_dirs);
free_mem_exit(cmd);
}
return;
}
}
message_error(name, cycles, cmd);
free_memory(path_dirs);
}
}
/**
 * message_error - Prints "not found" error message.
 *
 * @name: Shell name.
 * @cycles: Number of cycles.
 * @cmd: Tokenized command.
 *
 * Return: Nothing.
 */
void message_error(char *name, int cycles, char **cmd)
{
char cycle_char;
cycle_char = cycles + '0';
write(STDOUT_FILENO, name, string_len(name));
write(STDOUT_FILENO, ": ", 2);
write(STDOUT_FILENO, &cycle_char, 1);
write(STDOUT_FILENO, ": ", 2);
write(STDOUT_FILENO, cmd[0], string_len(cmd[0]));
write(STDOUT_FILENO, ": not found\n", 12);
}
/**
 * print_environ - Prints all environmental variables.
 *
 * @env: Environmental variables pointer.
 *
 * Return: Nothing.
 */
void print_environ(char **env)
{
size_t i = 0, len = 0;
while (env[i])
{
len = string_len(env[i]);
write(STDOUT_FILENO, env[i], len);
write(STDOUT_FILENO, "\n", 1);
i++;
}
}

