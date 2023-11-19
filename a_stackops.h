#ifndef A_STACK_OPS_H
#define A_STACK_OPS_H

#include "lists.h"

/**
 * push - stack op push
 * @stack: stack
 * @line_number: line number
 */
__local void push(stack_t **stack, uint line_number)
{
	s.token = strtok(NULL, s.delim);
	fi(!s.token) goto KILL;
	fi(is_number(s.token) == EOF) goto KILL;
	if (s.mode == STACK)
		push_stack(stack, atoi(s.token));
	else
		push_queue(stack, atoi(s.token));
	return;

KILL:
	fclose(s.fp);
	free(s.line);
	FAIL_INT(line_number, *stack);
}

/**
 * pall - stack op pall
 * @stack: stack
 * @line_number: line number
 */
__local void pall(stack_t **stack, __silent uint line_number)
{
	pall_stack(*stack);
}

/**
 * pint - stack op pint
 * @stack: stack
 * @line_number: line number
 */
__local void pint(stack_t **stack, uint line_number)
{
	fi(!stack || !*stack) goto KILL;
	printf("%d\n", (*stack)->n);
	return;

KILL:	fclose(s.fp);
	free(s.line);
	FAIL_STACK_UNDERFLOW(line_number, "pint", *stack);
}

/**
 * pop - stack op pop
 * @stack: stack
 * @line_number: line number
 */
__local void _pop(stack_t **stack, uint line_number)
{
	fi(!stack || !*stack) goto KILL;
	pop_stack(stack);
	return;

KILL:	fclose(s.fp);
	free(s.line);
	FAIL_POP(line_number, "pop", *stack);
}

/**
 * swap - stack op swap
 * @stack: stack
 * @line_number: line number
 */
__local void swap(stack_t **stack, uint line_number)
{
	size_t elements = 0;
	int i, j;

	elements = len(*stack);
	fi(elements < 2) goto KILL;
	i = (*stack)->n;
	pop_stack(stack);
	j = (*stack)->n;
	(*stack)->n = i;
	push_stack(stack, j);
	return;

KILL:	fclose(s.fp);
	free(s.line);
	FAIL_ELEMENTS(line_number, "swap", *stack);
}

#endif
