/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:29:32 by rymuller          #+#    #+#             */
/*   Updated: 2019/05/16 18:16:47 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	is_swap_command(t_stack *stack, char *line)
{
	if (!ft_strcmp(line, "sa"))
	{
		sa(stack);
		if (stack->print_stack)
		{
			if (stack->color && (stack->len_a > 1))
				stack->top_a->next->color = 1;
			ft_printf(">>>>>> sa\n");
			print_stack(stack);
		}
		return (1);
	}
	else if (!ft_strcmp(line, "sb"))
	{
		sb(stack);
		if (stack->print_stack)
		{
			if (stack->color && (stack->size - stack->len_a > 1))
				stack->top_b->next->color = 1;
			ft_printf(">>>>>> sb\n");
			print_stack(stack);
		}
		return (1);
	}
	else if (!ft_strcmp(line, "ss"))
	{
		ss(stack);
		if (stack->print_stack)
		{
			if (stack->color && (stack->len_a > 1))
				stack->top_a->next->color = 1;
			if (stack->color && (stack->size - stack->len_a > 1))
				stack->top_b->next->color = 1;
			ft_printf(">>>>>> ss\n");
			print_stack(stack);
		}
		return (1);
	}
	return (0);
}

void	sa(t_stack *stack)
{
	int		value;

	if (stack->len_a > 1)
	{
		value = stack->top_a->value;
		stack->top_a->value = stack->top_a->next->value;
		stack->top_a->next->value = value;
	}
}

void	sb(t_stack *stack)
{
	int		value;

	if (stack->size - stack->len_a > 1)
	{
		value = stack->top_b->value;
		stack->top_b->value = stack->top_b->prev->value;
		stack->top_b->prev->value = value;
	}
}

void	ss(t_stack *stack)
{
	sa(stack);
	sb(stack);
}
