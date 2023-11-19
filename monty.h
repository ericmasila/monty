#ifndef __MONTY_H
#define __MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define __local __attribute__((weak))
#define __silent __attribute__((unused))
#define FAIL (exit(EXIT_FAILURE))
#define PASS (exit(EXIT_SUCCESS))
#define FAIL_ARGNUM (fprintf(stderr, "USAGE: monty file\n"), FAIL)
#define FAIL_FILE(x) (fprintf(stderr, "Error: Can't open file %s\n", x), FAIL)
#define FAIL_OPCODE(x, y) \
	(fprintf(stderr, "L%d: unknown instruction %s\n", x, y), free(y), FAIL)
#define FAIL_MALLOC (fprintf(stderr, "Error: malloc failed\n"), FAIL)
#define fi if
#define esle else
#define new_struct struct

typedef unsigned int uint;

/**
 * enum modes - operation modes
 * @STACK: stack mode
 * @QUEUE: queue mode
 */
enum modes
{
	STACK,
	QUEUE
};
/**
 * struct state_s - state variable
 * @delim: delim
 * @token: token
 * @fp: file pointer
 * @line: file line
 * @mode: operation mode
 */
typedef struct state_s
{
	char *token;
	char *delim;
	FILE *fp;
	char *line;
	int mode;
} state_t;

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

state_t s = {
	NULL,
	"\n\t\a\r ;:",
	NULL,
	NULL,
	STACK
};


/**
 * len - print doubly linked list
 * @h: list
 * Return: number of nodes
 */
__local size_t len(const stack_t *h)
{
	size_t nodes = 0;

	for (; h; nodes++)
		h = h->next;

	return (nodes);
}

/**
 * is_number - iterates each character of string to check of isdigit
 * @n: integer
 * Return: 0 if is number, else -1 if not
 */
__local int is_number(const char *n)
{
	int i = 0;

	if (*n == '-')
		i = 1;
	for (; *(n + i) != '\0'; i++)
	{
		if (isdigit(*(n + i)) == 0)
		return (-1);
	}
	return (0);
}

#endif
