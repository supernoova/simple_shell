#include "shell.h"

int find_builtin(info_t *info)
{
	int i, built_in_flag = -1;
	builtin_table built_in_cmd[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"cd", my_cd},
		{NULL, NULL}
	};

	for (i = 0; built_in_cmd[i].type; i++)
		if (_strcmp(info->argv[0], built_in_cmd[i].type) == 0)
		{
			info->line_count++;
			built_in_flag = built_in_cmd[i].func(info);
			break;
		}
	return (built_in_flag);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->args[i]; i++)
		if (!is_delim(info->args[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((if_interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->args) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
