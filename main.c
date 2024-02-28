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

