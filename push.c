/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:31:13 by rymuller          #+#    #+#             */
/*   Updated: 2019/06/28 14:55:07 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	is_push_command(t_stack *stack, char *line)
{
	if (!ft_strcmp(line, "pb"))
	{
		pb(stack);
		return (1);
	}
	else if (!ft_strcmp(line, "pa"))
	{
		pa(stack);
		return (1);
	}
	return (0);
}

void	pb(t_stack *stack)
{
	if (stack->len_a > 0)
	{
		stack->top_b = stack->top_a;
		stack->top_a = stack->top_a->next;
		stack->len_a--;
	}
	if (stack->print)
	{
		if (stack->color && (stack->len_a > 0))
			stack->top_b->color = 1;
		if (stack->color)
			ft_printf(C">>>>>> pb\n"C);
		else
			ft_printf(N">>>>>> pb\n"N);
		print(stack);
	}
}

void	pa(t_stack *stack)
{
	if (stack->size - stack->len_a > 0)
	{
		stack->top_a = stack->top_b;
		stack->top_b = stack->top_b->prev;
		stack->len_a++;
	}
	if (stack->print)
	{
		if (stack->color && (stack->size - stack->len_a > 0))
			stack->top_a->color = 1;
		if (stack->color)
			ft_printf(C">>>>>> pa\n"C);
		else
			ft_printf(N">>>>>> pa\n"N);
		print(stack);
	}
}
