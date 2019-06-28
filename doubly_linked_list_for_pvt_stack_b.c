/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list_for_pvt_stack_b.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:28:24 by rymuller          #+#    #+#             */
/*   Updated: 2019/06/22 17:47:57 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_doubly_list			*ft_list_push_forw(t_stack *stack)
{
	t_doubly_list	*buffer;

	if (stack->len_pvts_b)
	{
		if (!(buffer = ft_list_new(stack->len_less_pvt)))
		{
			free_doubly_list(stack->len_pvts_b);
			exit(EXIT_FAILURE);
		}
		stack->len_pvts_b->prev = buffer;
		buffer->next = stack->len_pvts_b;
		return (buffer);
	}
	else
	{
		if (!(buffer = ft_list_new(stack->len_less_pvt)))
			exit(EXIT_FAILURE);
		return (buffer);
	}
}

t_doubly_list			*del_list_forw(t_stack *stack)
{
	t_doubly_list		*buffer;

	if (stack->len_pvts_b)
	{
		buffer = stack->len_pvts_b->next;
		free(stack->len_pvts_b);
		return (buffer);
	}
	return (NULL);
}

static void				print_stacks_number(t_stack *stack,
		t_doubly_list **buf_a, t_doubly_list **buf_b, size_t *i)
{
	if (*i > stack->len_a)
		ft_printf("\t\t");
	else
	{
		if ((*buf_a)->color)
		{
			ft_printf(C"%-15d\t"C, (*buf_a)->value);
			(*buf_a)->color = 0;
		}
		else
			ft_printf("%-15d\t", (*buf_a)->value);
		(*buf_a) = (*buf_a)->next;
	}
	if (*i > stack->size - stack->len_a)
		ft_printf("\n");
	else
	{
		if ((*buf_b)->color)
		{
			ft_printf(C"%-15d\t"C, (*buf_b)->value);
			(*buf_b)->color = 0;
		}
		else
			ft_printf("%-15d\t\n", (*buf_b)->value);
		(*buf_b) = (*buf_b)->prev;
	}
}

void					print_stack(t_stack *stack)
{
	size_t			i;
	t_doubly_list	*buf_a;
	t_doubly_list	*buf_b;

	buf_a = stack->top_a;
	buf_b = stack->top_b;
	if (stack->len_a > stack->size - stack->len_a)
		i = stack->len_a + 1;
	else
		i = stack->size - stack->len_a + 1;
	while (--i > 0)
		print_stacks_number(stack, &buf_a, &buf_b, &i);
	write(1, "-\t\t-\n", 5);
	write(1, "a\t\tb\n", 5);
}
