/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 18:26:48 by rymuller          #+#    #+#             */
/*   Updated: 2019/06/09 18:14:03 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_doubly_list	*ft_list_new(int value)
{
	t_doubly_list	*list;

	if (!(list = (t_doubly_list *)malloc(sizeof(t_doubly_list))))
		return (NULL);
	list->value = value;
	list->prev = NULL;
	list->next = NULL;
	return (list);
}

void					free_doubly_list(t_doubly_list *doubly_list)
{
	t_doubly_list	*buffer;

	if (doubly_list)
	{
		buffer = doubly_list;
		while (buffer->next)
		{
			buffer = buffer->next;
			free(buffer->prev);
		}
		free(buffer);
	}
}

t_doubly_list			*ft_list_push_forw(t_doubly_list *doubly_list, int len)
{
	t_doubly_list	*buffer;

	if (doubly_list)
	{
		if (!(buffer = ft_list_new(len)))
		{
			free_doubly_list(doubly_list);
			exit(EXIT_FAILURE);
		}
		doubly_list->prev = buffer;
		buffer->next = doubly_list;
		return (buffer);
	}
	else
	{
		if (!(buffer = ft_list_new(len)))
			exit(EXIT_FAILURE);
		return (buffer);
	}
}

t_doubly_list			*ft_list_push_back(t_stack *stack, int value)
{
	t_doubly_list	*buffer;

	if (stack->btm_b)
	{
		buffer = stack->btm_b;
		while (buffer->next)
			buffer = buffer->next;
		if (!(buffer->next = ft_list_new(value)))
		{
			free_doubly_list(stack->btm_b);
			exit(EXIT_FAILURE);
		}
		stack->btm_a = buffer->next;
		buffer->next->prev = buffer;
		return (stack->btm_b);
	}
	else
	{
		if (!(buffer = ft_list_new(value)))
			exit(EXIT_FAILURE);
		return (buffer);
	}
}

/*
void					print_stack(t_stack *stack)
{
	t_doubly_list		*buf_a;
	t_doubly_list		*buf_b;

	ft_printf("------------------------\n");
	ft_printf("%d\n", stack->len_a);
	ft_printf("------------------------\n");
	buf_a = stack->top_a;
	while (buf_a)
	{
		ft_printf("%d\n", buf_a->value);
		buf_a = buf_a->next;
	}
	ft_printf("------------------------\n");
	buf_b = stack->top_b;
	while (buf_b)
	{
		ft_printf("%d\n", buf_b->value);
		buf_b = buf_b->prev;
	}
	ft_printf("------------------------\n");
}
*/

void					print_stack(t_stack *stack)
{
	int				i;
	t_doubly_list	*buf_a;
	t_doubly_list	*buf_b;

	if (stack->len_a > stack->size - stack->len_a)
		i = stack->len_a + 1;
	else
		i = stack->size - stack->len_a + 1;
	buf_a = stack->top_a;
	buf_b = stack->top_b;
	ft_printf("------------------------\n");
	while (--i > 0)
	{
		if (i > stack->len_a)
			ft_printf("\t\t");
		else
		{
			ft_printf("%-15d\t", buf_a->value);
			buf_a = buf_a->next;
		}
		if (i > stack->size - stack->len_a)
			ft_printf("\n");
		else
		{
			ft_printf("%-15d\t\n", buf_b->value);
			buf_b = buf_b->prev;
		}
	}
	write(1, "-\t\t-\n", 5);
	write(1, "a\t\tb\n", 5);
	ft_printf("------------------------\n");
}
