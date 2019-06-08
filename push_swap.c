/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 14:09:35 by rymuller          #+#    #+#             */
/*   Updated: 2019/06/08 18:41:57 by rymuller         ###   ########.fr       */
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

char		is_more_pivot_stack_b(t_stack *stack, int len, int pivot)
{
	int				i;
	t_doubly_list	*buff;

	i = -1;
	buff = stack->top_b;
	while (++i < len)
	{
		if (buff->value > pivot)
			return (1);
		buff = buff->prev;
	}
	return (0);
}

void		sort(t_stack *stack)
{
//	int				max;
	int				pivot;
	size_t			ra_count;
	size_t			rb_count;
	size_t			iter_count;
	size_t			len_less_pivot;
	size_t			len_more_pivot;
	size_t			len_temp;
	size_t			origin_len_pivot;

	iter_count = 0;
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
				iter_count++;
				len_less_pivot++;
			}
			else
			{
				ra(stack);
//				ft_printf("ra\n");
//				print_stack(stack);
				iter_count++;
			}
		}
		print_stack(stack);
		stack->top_b->len_pivot = len_less_pivot;
	}
	print_stack(stack);
	rb_count = 0;
	origin_len_pivot = 0;
	while (stack->size - stack->len_a > 0)
	{
		if (stack->top_b->len_pivot < 2)
		{
			pa(stack);
			iter_count++;
		}
		else if (stack->top_b->len_pivot < 3)
		{
			pa(stack);
			pa(stack);
			iter_count += 2;
		}
		else
		{
			print_stack(stack);

			len_more_pivot = 0;
			origin_len_pivot = stack->top_b->len_pivot;
			len_temp = origin_len_pivot;
			pivot = find_pivot_stack_b(stack, origin_len_pivot);
			while (is_more_pivot_stack_b(stack, len_temp, pivot))
			{
				if (stack->top_b->value > pivot)
				{
					pa(stack);
//					ft_printf("pa\n");
//					print_stack(stack);
					iter_count++;
					len_more_pivot++;
				}
				else
				{
					rb(stack);
//					ft_printf("rb\n");
//					print_stack(stack);
					iter_count++;
					rb_count++;
				}
				len_temp--;
			}
			while (rb_count > 0)
			{
				rrb(stack);
				rb_count--;
				iter_count++;
			}
			print_stack(stack);

			len_less_pivot = 0;
			while (len_more_pivot > 3)
			{
				len_temp = len_more_pivot;
				pivot = find_pivot_stack_a(stack, len_more_pivot);
				while (is_less_pivot_stack_a(stack, len_temp, pivot))
				{
					if (stack->top_b->value > pivot)
					{
						pb(stack);
//						ft_printf("pa\n");
//						print_stack(stack);
						iter_count++;
						len_more_pivot--;
						len_less_pivot++;
					}
					else
					{
						ra(stack);
//						ft_printf("rb\n");
//						print_stack(stack);
						iter_count++;
						ra_count++;
					}
					len_temp--;
				}
				while (ra_count > 0)
				{
					rra(stack);
					ra_count--;
					iter_count++;
				}
				print_stack(stack);
			}
			origin_len_pivot += len_less_pivot;
		}
	}
//	ft_printf("top_b = %d, len = %d, max stack_b = %d\n", stack->top_b->value, stack->top_b->triple, find_max_stack_b(stack, len));*/
		
	print_stack(stack);
	ft_printf("%d\n", iter_count);
/*
	while (stack->size - stack->len_a != 0)
	{
		max = find_max_stack_b(stack, stack->top_b->len);
		len = stack->top_b->len;
		rb_count = 0;
		while (stack->top_b->value != max)
		{
			rb(stack);
//			ft_printf("rb\n");
			iter_count++;
			rb_count++;
		}
		if (stack->top_b->value == max)
		{
			pa(stack);
//			ft_printf("pa\n");
			iter_count++;
			len--;
		}
		while (rb_count != 0)
		{
			rrb(stack);
//			ft_printf("rrb\n");
			iter_count++;
			rb_count--;
		}
		if (len > 0)
			stack->top_b->len = len;
	}
	ft_printf("%d\n", iter_count);
*/
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
		free_doubly_list(&stack);
	}
	return (0);
}
