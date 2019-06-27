/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 14:09:35 by rymuller          #+#    #+#             */
/*   Updated: 2019/06/22 17:23:28 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		sort_triple_a(t_stack *stack)
{
	int			a;
	int			b;
	int			c;

	if ((stack->len_a == 2 || stack->len_more_pvt == 2))
	{
		if ((stack->len_pvts_b != NULL && stack->len_pvts_b->value > 1)
			&& (stack->top_a->value > stack->top_a->next->value)
			&& (stack->top_b->value < stack->top_b->next->value))
		{
			SS(stack);
		}
		else if (stack->top_a->value > stack->top_a->next->value)
		{
			SA(stack);
		}

	}
	else if (stack->len_a >= 3)
	{
		a = stack->top_a->value; 
		b = stack->top_a->next->value;
		c = stack->top_a->next->next->value;
		if (stack->len_a == 3)
		{
			if (c > a && b > a && b > c)
			{
				RA(stack);
				SA(stack);
				RRA(stack);
			}
			else if (a > b && a > c && b > c)
			{
				SA(stack);
				RRA(stack);
			}
			else if (c > a && c > b && a > b)
			{
				RA(stack);
			}
			else if (b > a && b > c && a > c)
			{
				RRA(stack);
			}
			else if (a > c && a > b && c > b)
			{
				RA(stack);
			}
		}
		else
		{
			if (c > a && b > a && b > c)
			{
				PB(stack);
				SA(stack);
				PA(stack);
			}
			else if (a > b && a > c && b > c)
			{
				RA(stack);
				SA(stack);
				PB(stack);
				PB(stack);
				RRA(stack);
				PA(stack);
				PA(stack);
			}
			else if (c > a && c > b && a > b)
			{
				SA(stack);
			}
			else if (b > a && b > c && a > c)
			{
				RA(stack);
				RA(stack);
				PB(stack);
				RRA(stack);
				RRA(stack);
				PA(stack);
			}
			else if (a > c && a > b && c > b)
			{
				PB(stack);
				RA(stack);
				RA(stack);
				PA(stack);
				RRA(stack);
				RRA(stack);
			}
		}
	}
}

void		sort(t_stack *stack)
{
	int				pvt;
	size_t			len;
	size_t			ra_count;
	size_t			rb_count;

	while (stack->len_a > 3)
	{
		stack->len_less_pvt = 0;
		pvt = find_pvt_stack_a(stack, stack->len_a);
		while (is_less_pvt_stack_a(stack, stack->len_a, pvt))
		{
			if (stack->top_a->value < pvt)
			{
				PB(stack);
				stack->len_less_pvt++;
			}
			else
			{
				RA(stack);
			}
		}
		stack->len_pvts_b = ft_list_push_forw(stack);
	}
	sort_triple_a(stack);
	ra_count = 0;
	rb_count = 0;
	while (stack->size != stack->len_a)
	{
		if (stack->len_pvts_b->value < 3)
		{
			stack->len_more_pvt = 0;
			while (stack->len_pvts_b->value)
			{
				PA(stack);
				stack->len_more_pvt++;
				stack->len_pvts_b->value--;
			}
			stack->len_pvts_b = del_list_forw(stack);
			sort_triple_a(stack);
		}
		else
		{
			stack->len_more_pvt = 0;
			len = stack->len_pvts_b->value;
			pvt = find_pvt_stack_b(stack, len);
			while (is_more_pvt_stack_b(stack, len, pvt))
			{
				if (stack->top_b->value > pvt)
				{
					PA(stack);
					stack->len_more_pvt++;
				}
				else
				{
					RB(stack);
					rb_count++;
				}
				len--;
			}
			while (rb_count)
			{
				RRB(stack);
				rb_count--;
			}
			stack->len_pvts_b->value -= stack->len_more_pvt;
			while (stack->len_more_pvt > 3)
			{
				stack->len_less_pvt = 0;
				len = stack->len_more_pvt;
				pvt = find_pvt_stack_a(stack, len);
				while (is_less_pvt_stack_a(stack, len, pvt))
				{
					if (stack->top_a->value < pvt)
					{
						PB(stack);
						stack->len_less_pvt++;
					}
					else
					{
						RA(stack);
						ra_count++;
					}
					len--;
				}
				while (ra_count)
				{
					RRA(stack);
					ra_count--;
				}
				stack->len_more_pvt -= stack->len_less_pvt;
				stack->len_pvts_b = ft_list_push_forw(stack);
			}
			sort_triple_a(stack);
		}
	}
}

int			main(int argc, char **argv)
{
	t_stack			stack;

	if (argc > 1)
	{
		stack.len_pvts_b = NULL;
		stack.command_list = NULL;
		if (!is_placing_argv_stack(&stack, argc, argv))
		{
			write(2, "Error\n", 6);
			return (0);
		}
//		print_stack(&stack);
		sort(&stack);
//		print_stack(&stack);
/*
		stack.command_list = ft_command_list(&stack, "rr\n");
		stack.command_list = ft_command_list(&stack, "rr\n");
		stack.command_list = ft_command_list(&stack, "rra\n");
		stack.command_list = ft_command_list(&stack, "rra\n");
		stack.command_list = ft_command_list(&stack, "ra\n");
		stack.command_list = ft_command_list(&stack, "ra\n");
		stack.command_list = ft_command_list(&stack, "ra\n");
*/
//		ft_printf("%d\n", iter_count(&stack));
		optimizing_commands_list(&stack);
//		ft_printf("%d\n", iter_count(&stack));
		print_commands(&stack);
//		print_stack(&stack);
		free_doubly_list(stack.btm_b);
		free_doubly_list(stack.len_pvts_b);
		free_command_list(stack.command_list);
	}
	return (0);
}
