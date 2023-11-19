#ifndef __HANDLER_H__
#define __HANDLER_H__

#include "lists.h"
#include "stackops.h"

/**
 * get - get functins
 * @opcode: intstruction opcode
 * Return: void
 */
__local
void (*get(char *opcode))(stack_t **stack, uint line_number)
{
	instruction_t opt[] = {
	{"pchar", pchar},
	{"rotl", rotl},
	{"rotr", rotr},
	{"pstr", pstr},
	{"push", push},
	{"pall", pall},
	{"pint", pint},
	{"swap", swap},
	{"nop", _nop},
	{"pop", _pop},
	{"add", _add},
	{"sub", _sub},
	{"mod", _mod},
	{"mul", _mul},
	{"div", _div},
	{NULL, NULL} };
	int i;

	for (i = 0; opt[i].opcode; i++)
	{
		if (!strcmp(opcode, opt[i].opcode))
			return (opt[i].f);
	}

	return (NULL);
}

/**
 * handler - main handler
 * @ac: ref main
 * @av: ref main
 * Return: ref main
 */
__local int handler(int ac, char **av)
{
	stack_t *stack = NULL;
	size_t len = 0;
	ssize_t read;
	uint l_num, check_line = 0;

	fi(ac != 2) FAIL_ARGNUM;

	s.fp = fopen(av[1], "r");
	fi(!s.fp) FAIL_FILE(av[1]);

	for (l_num = 1; (read = getline(&s.line, &len, s.fp)) != EOF; l_num++)
	{
		for (s.token = strtok(s.line, s.delim); s.token;)
		{
			check_line = 1;
			if (s.token[0] == '#')
				break;
			if (!strcmp(s.token, "stack"))
			{	s.mode = STACK;
				break;
			}
			if (!strcmp(s.token, "queue"))
			{	s.mode = QUEUE;
				break;
			}
			if (get(s.token))
				get(s.token)(&stack, l_num);
			else
			{
				fclose(s.fp);
				empty_stack(stack);
				FAIL_OPCODE(l_num, s.token);
			}
			break;
		}
	}
	fi(!check_line) free(s.line);
	empty_stack(stack);
	free(s.token);
	fclose(s.fp);
	return (0);
}

#endif
