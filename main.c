#include "shell.h"

/**
 * main - entry point
 * @argc: arguments count
 * @argv: argumentss strings
 *
 * Return: 0 on success, 1 on error
 */

int main(int argc, char **argv)
{
	info_t info[] = {INFO_INIT};
	int fd = 2;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				err_puts(argv[0]);
				err_puts(": 0: Can't open ");
				err_puts(argv[1]);
				err_putchar('\n');
				err_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	new_env_list(info);
	shell(info, argv);
	return (EXIT_SUCCESS);
}

int shell(info_t *info, char **argv)
{
	ssize_t read_bytes = 0;
	int builtin_flag = 0;

	while (read_bytes != -1 && builtin_flag != -2)
	{
		clear_info(info);
		if (if_interactive(info))
			_puts("$ ");
		err_putchar(BUF_FLUSH);
		read_bytes = get_input(info);
		if (read_bytes != -1)
		{
			set_info(info, argv);
			builtin_flag = find_builtin(info);
			if (builtin_flag == -1)
				find_cmd(info);
		}
		else if (if_interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	free_info(info, 1);
	if (!if_interactive(info) && info->status)
		exit(info->status);
	if (builtin_flag == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_flag);
}

/**
 * interactive - check if shell in interactive
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int if_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
