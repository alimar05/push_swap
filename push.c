/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:31:13 by rymuller          #+#    #+#             */
/*   Updated: 2019/05/16 18:21:01 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	is_push_command(t_stack *stack, char *line)
{
	if (!ft_strcmp(line, "pb"))
	{
		pb(stack);
		if (stack->print_stack)
		{
			ft_printf(">>>>>> pb\n");
			print_stack(stack);
		}
		return (1);
	}
	else if (!ft_strcmp(line, "pa"))
	{
		pa(stack);
		if (stack->print_stack)
		{
			ft_printf(">>>>>> pa\n");
			print_stack(stack);
		}
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
}

void	pa(t_stack *stack)
{
	if (stack->size - stack->len_a > 0)
	{
		stack->top_a = stack->top_b;
		stack->top_b = stack->top_b->prev;
		stack->len_a++;
	}
}
