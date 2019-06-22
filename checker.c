/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:52:58 by rymuller          #+#    #+#             */
/*   Updated: 2019/06/22 17:47:27 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char			is_sort_stack(t_doubly_list *top)
{
	while (top->next)
	{
		if (top->value > top->next->value)
			return (0);
		top = top->next;
	}
	return (1);
}

static char		is_read_command_and_sort(t_stack *stack, char *line)
{
	while (get_next_line(0, &line))
		if (is_swap_command(stack, line))
			print_stack(stack);
		else if (is_push_command(stack, line))
			print_stack(stack);
		else if (is_rotate_command(stack, line))
			print_stack(stack);
		else if (is_rev_rotate_command(stack, line))
			print_stack(stack);
		else
		{
			write(2, "Error\n", 6);
			free_doubly_list(stack->btm_b);
			exit(EXIT_FAILURE);
		}
	if (stack->size != stack->len_a)
		return (0);
	return (is_sort_stack(stack->btm_b));
}

int				main(int argc, char **argv)
{
	char			*line;
	t_stack			stack;

	line = NULL;
	if (argc > 1)
	{
		if (!is_placing_argv_stack(&stack, argc, argv))
		{
			write(2, "Error\n", 6);
			return (0);
		}
		if (!is_read_command_and_sort(&stack, line))
		{
			write(1, "KO\n", 3);
			free_doubly_list(stack.btm_b);
			return (0);
		}
		else
			write(1, "OK\n", 3);
		free(line);
		free_doubly_list(stack.btm_b);
	}
	return (0);
}
