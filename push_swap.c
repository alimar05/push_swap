/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 14:09:35 by rymuller          #+#    #+#             */
/*   Updated: 2019/06/21 19:54:09 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		sort(t_stack *stack)
{
	int				pvt;
	size_t			len;
	size_t			ra_count;
	size_t			rb_count;
	size_t			len_less_pvt;
	size_t			len_more_pvt;
	t_doubly_list	*len_pvts_b;

	len_pvts_b = NULL;
	stack->iter_count = 0;
	while (stack->len_a > 2)
	{
		len_less_pvt = 0;
		pvt = find_pvt_stack_a(stack, stack->len_a);
		while (is_less_pvt_stack_a(stack, stack->len_a, pvt))
		{
			if (stack->top_a->value < pvt)
			{
				pb(stack);
				len_less_pvt++;
				stack->iter_count++;
			}
			else
			{
				ra(stack);
				stack->iter_count++;
			}
		}
		len_pvts_b = ft_list_push_forw(len_pvts_b, len_less_pvt);
	}
	// TO DO sorted function for double and triple
/*	if ((stack->len_a == 2)
			&& (stack->top_a->value > stack->top_a->next->value)
			&& (stack->top_b->value < stack->top_b->next->value))
	{
		ss(stack);
		stack->iter_count++;
	}
	else*/ if (stack->top_a->value > stack->top_a->next->value)
	{
		sa(stack);
		stack->iter_count++;
	}
/*
	while (len_pvts_b)
	{
		ft_printf("%d\n", len_pvts_b->value);
		len_pvts_b = len_pvts_b->next;
	}
*/
	print_stack(stack);
	ra_count = 0;
	rb_count = 0;
	while (stack->size != stack->len_a)
	{
		if (len_pvts_b->value < 3)
		{
			len_more_pvt = 0;
			while (len_pvts_b->value)
			{
				pa(stack);
//				print_stack(stack);
				len_more_pvt++;
				stack->iter_count++;
				len_pvts_b->value--;
			}
			len_pvts_b = del_list_forw(len_pvts_b);
			if (len_more_pvt == 2)
			{
				if ((stack->size - stack->len_a > 1)
						&& (stack->top_a->value > stack->top_a->next->value)
						&& (stack->top_b->value < stack->top_b->next->value))
				{
					ss(stack);
					stack->iter_count++;
				}
				else if (stack->top_a->value > stack->top_a->next->value)
				{
					sa(stack);
					stack->iter_count++;
				}
			}
		}
		else
		{
			len_more_pvt = 0;
			len = len_pvts_b->value;
			pvt = find_pvt_stack_b(stack, len);
//			ft_printf("------------------------------\n");
//			ft_printf("pvt_stack_b = %d, len_pvts_b->value = %d\n", pvt, len);
//			ft_printf("------------------------------\n");
//			ft_printf("------------------------------\n");
			while (is_more_pvt_stack_b(stack, len, pvt))
			{
				if (stack->top_b->value > pvt)
				{
					pa(stack);
					len_more_pvt++;
					stack->iter_count++;
				}
				else
				{
					rb(stack);
					rb_count++;
					stack->iter_count++;
				}
				len--;
//				print_stack(stack);
			}
			while (rb_count)
			{
				rrb(stack);
				rb_count--;
				stack->iter_count++;
			}
			len_pvts_b->value -= len_more_pvt;
//			print_stack(stack);
			while (len_more_pvt > 2)
			{
				len_less_pvt = 0;
				len = len_more_pvt;
				pvt = find_pvt_stack_a(stack, len);
//				ft_printf("------------------------------\n");
//				ft_printf("pvt_stack_a = %d, len_more_pvt = %d\n", pvt, len);
//				ft_printf("------------------------------\n");
//				ft_printf("------------------------------\n");
				while (is_less_pvt_stack_a(stack, len, pvt))
				{
					if (stack->top_a->value < pvt)
					{
						pb(stack);
						len_less_pvt++;
						stack->iter_count++;
					}
					else
					{
						ra(stack);
						ra_count++;
						stack->iter_count++;
					}
					len--;
//					print_stack(stack);
				}
				while (ra_count)
				{
					rra(stack);
					ra_count--;
					stack->iter_count++;
				}
				len_more_pvt -= len_less_pvt;
//				print_stack(stack);
				len_pvts_b = ft_list_push_forw(len_pvts_b, len_less_pvt);
			}
			// TO DO sorted function for double and triple
			if (len_more_pvt == 2)
			{
/*				if ((stack->size - stack->len_a > 1)
						&& (stack->top_a->value > stack->top_a->next->value)
						&& (stack->top_b->value < stack->top_b->next->value))
				{
					ss(stack);
					stack->iter_count++;
				}
				else*/ if (stack->top_a->value > stack->top_a->next->value)
				{
					sa(stack);
					stack->iter_count++;
				}
			}
		}
	}
	print_stack(stack);
	free_doubly_list(len_pvts_b);
	ft_printf("%d\n", stack->iter_count);
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
//		print_stack(&stack);
		ft_printf("------------------------\n");
		sort(&stack);
		ft_printf("------------------------\n");
//		print_stack(&stack);
		free_doubly_list(stack.btm_b);
	}
	return (0);
}
