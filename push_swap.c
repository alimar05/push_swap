/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 14:09:35 by rymuller          #+#    #+#             */
/*   Updated: 2019/06/09 18:14:02 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			find_pivot_stack_a(t_stack *stack, int len)
{
	int				i;
	t_doubly_list	*top;
	int				arr[len];

	if (len > 1)
	{
		i = -1;
		top = stack->top_a;
		while (++i < len)
		{
			arr[i] = top->value;
			top = top->next;
		}
		quicksort(arr, 0, len - 1);
		return (arr[len >> 1]);
	}
	return (top->value);
}

int			find_pivot_stack_b(t_stack *stack, int len)
{
	int				i;
	t_doubly_list	*top;
	int				arr[len];

	if (len > 1)
	{
		i = -1;
		top = stack->top_b;
		while (++i < len)
		{
			arr[i] = top->value;
			top = top->prev;
		}
		quicksort(arr, 0, len - 1);
		return (arr[len >> 1]);
	}
	return (top->value);
}

int			find_max_stack_b(t_stack *stack, int len)
{
	int				i;
	int				max;
	t_doubly_list	*top;

	i = -1;
	top = stack->top_b;
	max = stack->top_b->value;
	while (++i < len)
	{
		if (top->value > max)
			max = top->value;
		top = top->prev;
	}
	return (max);
}

char		is_less_pivot_stack_a(t_stack *stack, int len, int pivot)
{
	int				i;
	t_doubly_list	*buff;

	i = -1;
	buff = stack->top_a;
	while (++i < len)
	{
		if (buff->value < pivot)
			return (1);
		buff = buff->next;
	}
	return (0);
}

char		is_more_eq_pvt_stack_b(t_stack *stack, int len, int pivot)
{
	int				i;
	t_doubly_list	*buff;

	i = -1;
	buff = stack->top_b;
	while (++i < len)
	{
		if (buff->value >= pivot)
			return (1);
		buff = buff->prev;
	}
	return (0);
}

void		sort(t_stack *stack)
{
	int				pivot;
	size_t			ra_count;
	size_t			rb_count;
	size_t			iter_count;
	size_t			len_less_pivot;
	size_t			len_more_pivot;
	t_doubly_list	*len_pivots;

	iter_count = 0;
	len_pivots = NULL;
	while (stack->len_a > 3)
	{
		len_less_pivot = 0;
		pivot = find_pivot_stack_a(stack, stack->len_a);
		while (is_less_pivot_stack_a(stack, stack->len_a, pivot))
		{
			if (stack->top_a->value < pivot)
			{
				pb(stack);
//				ft_printf("pb\n");
//				print_stack(stack);
				len_less_pivot++;
				iter_count++;
			}
			else
			{
				ra(stack);
//				ft_printf("ra\n");
//				print_stack(stack);
				iter_count++;
			}
		}
		len_pivots = ft_list_push_forw(len_pivots, len_less_pivot);
		print_stack(stack);
	}
	print_stack(stack);
	len_more_pivot = 0;
	rb_count = 0;
	while (stack->size != stack->len_a)
	{
		if (len_pivots->value < 3)
		{
			while (len_pivots->value)
			{
				pa(stack);
				len_pivots->value--;
				iter_count++;
			}
			len_pivots = len_pivots->next;
			// TO DO sort double
		}
		else
		{
			len_more_pivot = 0;
			pivot = find_pivot_stack_b(stack, len_pivots->value);
			while (is_more_eq_pvt_stack_b(stack, len_pivots->value, pivot))
			{
				if (stack->top_b->value >= pivot)
				{
					pa(stack);
					len_more_pivot++;
					len_pivots->value--;
					iter_count++;
				}
				else
				{
					rb(stack);
					rb_count++:
					iter_count++;
				}
			}
			while (rb_count > 0)
			{
				rrb(stack);
				rb_count--;
				iter_count++;
			}
		}
	}
	free_doubly_list(len_pivots);
	ft_printf("%d\n", iter_count);
}

int			main(int argc, char **argv)
{
	t_stack			stack;

	if (argc > 1)
	{
		if (!is_placing_argv_stack(&stack, argc, argv))
		{
			write(2, "Error\n", 6);
			return (0);
		}
		print_stack(&stack);
		ft_printf("------------------------\n");
		sort(&stack);
		ft_printf("------------------------\n");
//		print_stack(&stack);
		free_doubly_list(stack.btm_b);
	}
	return (0);
}
