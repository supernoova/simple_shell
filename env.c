#include "shell.h"

/**
 * _getenv - Gets of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Name of the environment variable.
 *
 * Return: The value of the environment variable.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * new_env_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */
int new_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_at_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
