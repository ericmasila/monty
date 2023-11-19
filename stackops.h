#ifndef _STACK_OPS_H
#define _STACK_OPS_H

#include "b_stackops.h"

/**
 * _mod - stack op mod
 * @stack: stack
 * @line_number: line number
 */
__local void _mod(stack_t **stack, uint line_number)
{
	size_t elements = 0;
	int i;

	elements = len(*stack);
	fi(elements < 2) goto KILL;
	i = (*stack)->n;
	fi(!i) goto KILL;
	pop_stack(stack);
	(*stack)->n %= i;
	return;

KILL:	fclose(s.fp);
	free(s.line);
	fi(!i) FAIL_DIV0(line_number, *stack);
	FAIL_ELEMENTS(line_number, "mod", *stack);
}

/**
 * pchar - stack op pchar
 * @stack: stack
 * @line_number: line number
 */
__local void pchar(stack_t **stack, uint line_number)
{
	int i = 48;

	fi(!stack || !*stack) goto KILL;
	i = (*stack)->n;
	fi(!isascii(i)) goto KILL;

	putchar(i);
	putchar('\n');
	return;

KILL:	fclose(s.fp);
	free(s.line);
	fi(!isascii(i)) FAIL_RANGE(line_number, *stack);
	FAIL_STACK_UNDERFLOW(line_number, "pchar", *stack);
}

/**
 * pstr - stack op pstr
 * @stack: stack
 * @line_number: line number
 */
__local void pstr(stack_t **stack, __silent uint line_number)
{
	int i;
	stack_t *temp = *stack;

	for (; temp;)
	{
		i = temp->n;
		if (isascii(i) && i)
		{
			putchar(i);
			temp = temp->next;
		}
		else
			break;
	}
	putchar('\n');
}

/**
 * rotl - stack op rotl
 * @stack: stack
 * @line_number: line number
 */
__local void rotl(stack_t **stack, __silent uint line_number)
{
	int i;
	size_t _len = 0;

	_len = len(*stack);

	if (_len < 2)
		return;

	i = (*stack)->n;
	pop_stack(stack);
	push_queue(stack, i);
}

/**
 * rotr - stack op rotr
 * @stack: stack
 * @line_number: line number
 */
__local void rotr(stack_t **stack, __silent uint line_number)
{
	size_t _len = 0;
	stack_t *temp = *stack;

	_len = len(*stack);
	if (_len < 2)
		return;

	for (; temp->next;)
		temp = temp->next;
	(*stack)->prev = temp;
	temp->next = *stack;
	temp->prev->next = NULL;
	temp->prev = NULL;
	*stack = (*stack)->prev;
}
#endif
