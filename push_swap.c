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

void		sort_double(t_stack *stack)
{
	if (stack->len_more_pvt == 2)
	{
		if ((stack->len_pvts_b != NULL && stack->len_pvts_b->value > 1)
			&& (stack->top_a->value > stack->top_a->next->value)
			&& (stack->top_b->value < stack->top_b->next->value))
		{
			ss(stack);
			stack->command_list = ft_command_list(stack, "ss\n");
			stack->iter_count++;
		}
		else if (stack->top_a->value > stack->top_a->next->value)
		{
			sa(stack);
			stack->command_list = ft_command_list(stack, "sa\n");
			stack->iter_count++;
		}
	}
}

void		sort(t_stack *stack)
{
	int				pvt;
	size_t			len;
	size_t			ra_count;
	size_t			rb_count;

	while (stack->len_a > 2)
	{
		stack->len_less_pvt = 0;
		pvt = find_pvt_stack_a(stack, stack->len_a);
		while (is_less_pvt_stack_a(stack, stack->len_a, pvt))
		{
			if (stack->top_a->value < pvt)
			{
				pb(stack);
				stack->command_list = ft_command_list(stack, "pb\n");
				stack->len_less_pvt++;
				stack->iter_count++;
			}
			else
			{
				ra(stack);
				stack->command_list = ft_command_list(stack, "ra\n");
				stack->iter_count++;
			}
		}
		stack->len_pvts_b = ft_list_push_forw(stack);
	}
	if ((stack->len_a == 2)
		&& (stack->top_a->value > stack->top_a->next->value))
	{
		sa(stack);
		stack->command_list = ft_command_list(stack, "sa\n");
		stack->iter_count++;
	}
	ra_count = 0;
	rb_count = 0;
	while (stack->size != stack->len_a)
	{
		if (stack->len_pvts_b->value < 3)
		{
			stack->len_more_pvt = 0;
			while (stack->len_pvts_b->value)
			{
				pa(stack);
				stack->command_list = ft_command_list(stack, "pa\n");
				stack->len_more_pvt++;
				stack->iter_count++;
				stack->len_pvts_b->value--;
			}
			stack->len_pvts_b = del_list_forw(stack);
			sort_double(stack);
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
					pa(stack);
					stack->command_list = ft_command_list(stack, "pa\n");
					stack->len_more_pvt++;
					stack->iter_count++;
				}
				else
				{
					rb(stack);
					stack->command_list = ft_command_list(stack, "rb\n");
					rb_count++;
					stack->iter_count++;
				}
				len--;
			}
			while (rb_count)
			{
				rrb(stack);
				stack->command_list = ft_command_list(stack, "rrb\n");
				rb_count--;
				stack->iter_count++;
			}
			stack->len_pvts_b->value -= stack->len_more_pvt;
			while (stack->len_more_pvt > 2)
			{
				stack->len_less_pvt = 0;
				len = stack->len_more_pvt;
				pvt = find_pvt_stack_a(stack, len);
				while (is_less_pvt_stack_a(stack, len, pvt))
				{
					if (stack->top_a->value < pvt)
					{
						pb(stack);
						stack->command_list = ft_command_list(stack, "pb\n");
						stack->len_less_pvt++;
						stack->iter_count++;
					}
					else
					{
						ra(stack);
						stack->command_list = ft_command_list(stack, "ra\n");
						ra_count++;
						stack->iter_count++;
					}
					len--;
				}
				while (ra_count)
				{
					rra(stack);
					stack->command_list = ft_command_list(stack, "rra\n");
					ra_count--;
					stack->iter_count++;
				}
				stack->len_more_pvt -= stack->len_less_pvt;
				stack->len_pvts_b = ft_list_push_forw(stack);
			}
			sort_double(stack);
		}
	}
}

int			main(int argc, char **argv)
{
	t_stack			stack;

	if (argc > 1)
	{
		stack.iter_count = 0;
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
		optimizing_commands_list(&stack);
		print_commands(&stack);
		ft_printf("%d\n", stack.iter_count);
		free_doubly_list(stack.btm_b);
		free_doubly_list(stack.len_pvts_b);
		free_command_list(stack.command_list);
	}
	return (0);
}
