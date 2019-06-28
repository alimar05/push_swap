/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:38:27 by rymuller          #+#    #+#             */
/*   Updated: 2019/05/16 18:31:03 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	is_rev_rotate_command(t_stack *stack, char *line)
{
	if (!ft_strcmp(line, "rra"))
	{
		rra(stack);
		if (stack->print_stack)
		{
			if (stack->color && (stack->len_a > 1))
				stack->top_a->color = 1;
			ft_printf(">>>>>> rra\n");
			print_stack(stack);
		}
		return (1);
	}
	else if (!ft_strcmp(line, "rrb"))
	{
		rrb(stack);
		if (stack->print_stack)
		{
			if (stack->color && (stack->size - stack->len_a > 1))
				stack->top_b->color = 1;
			ft_printf(">>>>>> rrb\n");
			print_stack(stack);
		}
		return (1);
	}
	else if (!ft_strcmp(line, "rrr"))
	{
		rrr(stack);
		if (stack->print_stack)
		{
			if (stack->color && (stack->len_a > 1))
				stack->top_a->color = 1;
			if (stack->color && (stack->size - stack->len_a > 1))
				stack->top_b->color = 1;
			ft_printf(">>>>>> rrr\n");
			print_stack(stack);
		}
		return (1);
	}
	return (0);
}

void	rra(t_stack *stack)
{
	t_doubly_list	*btm_a_buff;

	if (stack->len_a > 1)
	{
		btm_a_buff = stack->btm_a->prev;
		btm_a_buff->next = NULL;
		stack->btm_a->next = stack->top_a;
		stack->btm_a->prev = stack->top_a->prev;
		if (stack->top_a->prev)
			stack->top_a->prev->next = stack->btm_a;
		stack->top_a->prev = stack->btm_a;
		stack->top_a = stack->btm_a;
		stack->btm_a = btm_a_buff;
		if (stack->size == stack->len_a)
			stack->btm_b = stack->top_a;
	}
}

void	rrb(t_stack *stack)
{
	t_doubly_list	*btm_b_buff;

	if (stack->size - stack->len_a > 1)
	{
		btm_b_buff = stack->btm_b->next;
		btm_b_buff->prev = NULL;
		stack->btm_b->next = stack->top_b->next;
		stack->btm_b->prev = stack->top_b;
		if (stack->top_b->next)
			stack->top_b->next->prev = stack->btm_b;
		stack->top_b->next = stack->btm_b;
		stack->top_b = stack->btm_b;
		stack->btm_b = btm_b_buff;
		if (stack->len_a == 0)
			stack->btm_a = stack->top_b;
	}
}

void	rrr(t_stack *stack)
{
	rra(stack);
	rrb(stack);
}
