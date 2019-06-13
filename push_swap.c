/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 14:09:35 by rymuller          #+#    #+#             */
/*   Updated: 2019/06/13 14:43:24 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			find_pvt_stack_a(t_stack *stack, int len)
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
	return (stack->top_a->value);
}

int			find_pvt_stack_b(t_stack *stack, int len)
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
	return (stack->top_b->value);
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

char		is_less_pvt_stack_a(t_stack *stack, int len, int pvt)
{
	int				i;
	t_doubly_list	*buff;

	i = -1;
	buff = stack->top_a;
	while (++i < len)
	{
		if (buff->value < pvt)
			return (1);
		buff = buff->next;
	}
	return (0);
}

char		is_more_eq_pvt_stack_b(t_stack *stack, int len, int pvt)
{
	int				i;
	t_doubly_list	*buff;

	i = -1;
	buff = stack->top_b;
	while (++i < len)
	{
		if (buff->value >= pvt)
			return (1);
		buff = buff->prev;
	}
	return (0);
}

void		sort(t_stack *stack)
{
	int				pvt;
	size_t			ra_count;
	size_t			rb_count;
	size_t			iter_count;
	size_t			len_less_pvt;
	size_t			len_mr_eq_pvt;
	t_doubly_list	*len_pvts_b;

	iter_count = 0;
	len_pvts_b = NULL;
	while (stack->len_a > 3)
	{
		len_less_pvt = 0;
		pvt = find_pvt_stack_a(stack, stack->len_a);
/*		ft_printf("------------------------------\n");
		ft_printf("pvt_stack_a = %d\n", pvt);
		ft_printf("------------------------------\n");*/
		while (is_less_pvt_stack_a(stack, stack->len_a, pvt))
		{
			if (stack->top_a->value < pvt)
			{
				pb(stack);
				len_less_pvt++;
				iter_count++;
			}
			else
			{
				ra(stack);
				iter_count++;
			}
		}
		len_pvts_b = ft_list_push_forw(len_pvts_b, len_less_pvt);
		ft_printf("------------------------------\n");
		ft_printf("%d\n", len_less_pvt);
		ft_printf("------------------------------\n");
	}
	print_stack(stack);
	ra_count = 0;
	rb_count = 0;
	len_mr_eq_pvt = 0;
	while (stack->size != stack->len_a)
	{
		len_mr_eq_pvt = 0;
		pvt = find_pvt_stack_b(stack, len_pvts_b->value);
		ft_printf("------------------------------\n");
		ft_printf("pvt_stack_b = %d, len_pvts_b->value = %d\n", pvt, len_pvts_b->value);
		ft_printf("------------------------------\n");
		ft_printf("------------------------------\n");
		while (is_more_eq_pvt_stack_b(stack, len_pvts_b->value, pvt))
		{
			if (stack->top_b->value >= pvt)
			{
				pa(stack);
				len_mr_eq_pvt++;
				iter_count++;
			}
			else
			{
				rb(stack);
				rb_count++;
				iter_count++;
			}
			print_stack(stack);
			len_pvts_b->value--;
		}
		while (rb_count > 0)
		{
			rrb(stack);
			rb_count--;
			iter_count++;
			len_pvts_b->value++;
		}
		print_stack(stack);
		while (len_mr_eq_pvt > 3)
		{
			pvt = find_pvt_stack_a(stack, len_mr_eq_pvt);
			ft_printf("------------------------------\n");
			ft_printf("pvt_stack_a = %d, len_mr_eq_pvt = %d\n", pvt, len_mr_eq_pvt);
			ft_printf("------------------------------\n");
			ft_printf("------------------------------\n");
			while (is_less_pvt_stack_a(stack, len_mr_eq_pvt, pvt))
			{
				if (stack->top_a->value < pvt)
				{
					pb(stack);
					len_pvts_b->value++;
					iter_count++;
				}
				else
				{
					ra(stack);
					ra_count++;
					iter_count++;
				}
				print_stack(stack);
				len_mr_eq_pvt--;
			}
			while (ra_count > 0)
			{
				rra(stack);
				ra_count--;
				iter_count++;
				len_mr_eq_pvt++;
			}
			print_stack(stack);
		}
		if (len_pvts_b->value == 0)
			len_pvts_b = len_pvts_b->next;
	}
	print_stack(stack);
	free_doubly_list(len_pvts_b);
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
