/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:32:13 by rymuller          #+#    #+#             */
/*   Updated: 2019/05/16 18:26:15 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	is_rotate_command(t_stack *stack, char *line)
{
	if (!ft_strcmp(line, "ra"))
	{
		ra(stack);
		if (stack->print_stack)
		{
			if (stack->color && (stack->len_a > 1))
				stack->btm_a->color = 1;
			ft_printf(">>>>>> ra\n");
			print_stack(stack);
		}
		return (1);
	}
	else if (!ft_strcmp(line, "rb"))
	{
		rb(stack);
		if (stack->print_stack)
		{
			if (stack->color && (stack->size - stack->len_a > 1))
				stack->btm_b->color = 1;
			ft_printf(">>>>>> rb\n");
			print_stack(stack);
		}
		return (1);
	}
	else if (!ft_strcmp(line, "rr"))
	{
		rr(stack);
		if (stack->print_stack)
		{
			if (stack->color && (stack->len_a > 1))
				stack->btm_a->color = 1;
			if (stack->color && (stack->size - stack->len_a > 1))
				stack->btm_b->color = 1;
			ft_printf(">>>>>> rr\n");
			print_stack(stack);
		}
		return (1);
	}
	return (0);
}

void	ra(t_stack *stack)
{
	t_doubly_list	*next;
	t_doubly_list	*prev;

	if (stack->len_a > 1)
	{
		prev = stack->top_a->prev;
		next = stack->top_a->next;
		if (prev != NULL)
			prev->next = next;
		next->prev = prev;
		stack->top_a->prev = stack->btm_a;
		stack->btm_a->next = stack->top_a;
		stack->top_a->next = NULL;
		stack->btm_a = stack->top_a;
		stack->top_a = next;
		if (stack->size == stack->len_a)
			stack->btm_b = stack->top_a;
	}
}

void	rb(t_stack *stack)
{
	t_doubly_list	*next;
	t_doubly_list	*prev;

	if (stack->size - stack->len_a > 1)
	{
		prev = stack->top_b->prev;
		next = stack->top_b->next;
		if (next != NULL)
			next->prev = prev;
		prev->next = next;
		stack->top_b->next = stack->btm_b;
		stack->btm_b->prev = stack->top_b;
		stack->top_b->prev = NULL;
		stack->btm_b = stack->top_b;
		stack->top_b = prev;
		if (stack->len_a == 0)
			stack->btm_a = stack->top_b;
	}
}

void	rr(t_stack *stack)
{
	ra(stack);
	rb(stack);
}
