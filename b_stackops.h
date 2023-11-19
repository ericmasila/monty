#ifndef B_STACK_OPS_H
#define B_STACK_OPS_H

#include "a_stackops.h"

/**
 * _add - stack op add
 * @stack: stack
 * @line_number: line number
 */
__local void _add(stack_t **stack, uint line_number)
{
	size_t elements = 0;
	int i;

	elements = len(*stack);
	fi(elements < 2) goto KILL;
	i = (*stack)->n;
	pop_stack(stack);
	(*stack)->n += i;
	return;

KILL:	fclose(s.fp);
	free(s.line);
	FAIL_ELEMENTS(line_number, "add", *stack);
}

/**
 * _nop - stack op nop
 * @stack: stack
 * @line_number: line number
 */
__local void _nop(__silent stack_t **stack, __silent uint line_number)
{ }

/**
 * _sub - stack op sub
 * @stack: stack
 * @line_number: line number
 */
__local void _sub(stack_t **stack, uint line_number)
{
	size_t elements = 0;
	int i;

	elements = len(*stack);
	fi(elements < 2) goto KILL;
	i = (*stack)->n;
	pop_stack(stack);
	(*stack)->n -= i;
	return;

KILL:	fclose(s.fp);
	free(s.line);
	FAIL_ELEMENTS(line_number, "sub", *stack);
}


/**
 * _div - stack op div
 * @stack: stack
 * @line_number: line number
 */
__local void _div(stack_t **stack, uint line_number)
{
	size_t elements = 0;
	int i;

	elements = len(*stack);
	fi(elements < 2) goto KILL;
	i = (*stack)->n;
	fi(!i) goto KILL;
	pop_stack(stack);
	(*stack)->n /= i;
	return;

KILL:	fclose(s.fp);
	free(s.line);
	fi(!i) FAIL_DIV0(line_number, *stack);
	FAIL_ELEMENTS(line_number, "div", *stack);
}

/**
 * _mul - stack op mul
 * @stack: stack
 * @line_number: line number
 */
__local void _mul(stack_t **stack, uint line_number)
{
	size_t elements = 0;
	int i;

	elements = len(*stack);
	fi(elements < 2) goto KILL;
	i = (*stack)->n;
	pop_stack(stack);
	(*stack)->n *= i;
	return;

KILL:	fclose(s.fp);
	free(s.line);
	FAIL_ELEMENTS(line_number, "mul", *stack);
}

#endif
