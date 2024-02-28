#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int my_exit(info_t *info)
{
	int exit_check;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exit_check = err_atoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			err_puts(info->argv[1]);
			err_putchar('\n');
			return (1);
		}
		info->err_num = err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_cd(info_t *info)
{
	char *s, *dir, buffer[BUF_SIZE];
	int chdir_flag;

	s = getcwd(buffer, BUF_SIZE);
	if (!s)
	{
		_puts("Can't get the current working directory\n");
	}
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_flag = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_flag = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_flag = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_flag = chdir(info->argv[1]);
	if (chdir_flag == -1)
	{
		print_error(info, "can't change directory to ");
		err_puts(info->argv[1]), err_putchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, BUF_SIZE));
	}
	return (0);
}

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int my_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}


