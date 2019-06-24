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
		}
		else if (stack->top_a->value > stack->top_a->next->value)
		{
			sa(stack);
			stack->command_list = ft_command_list(stack, "sa\n");
		}
	}
}

void		sort_triple(t_stack *stack)
{
	int			a;
	int			b;
	int			c;

	if ((stack->len_a == 2)
		&& (stack->top_a->value > stack->top_a->next->value))
	{
		sa(stack);
		stack->command_list = ft_command_list(stack, "sa\n");
	}
	else if (stack->len_a == 3)
	{
		a = stack->top_a->value; 
		b = stack->top_a->next->value;
		c = stack->top_a->next->next->value;
		if (c > a && b > a && b > c)
		{
			ra(stack);
			stack->command_list = ft_command_list(stack, "ra\n");
			sa(stack);
			stack->command_list = ft_command_list(stack, "sa\n");
			rra(stack);
			stack->command_list = ft_command_list(stack, "rra\n");
		}
		else if (a > b && a > c && b > c)
		{
			sa(stack);
			stack->command_list = ft_command_list(stack, "sa\n");
			rra(stack);
			stack->command_list = ft_command_list(stack, "rra\n");
		}
		else if (c > a && c > b && a > b)
		{
			sa(stack);
			stack->command_list = ft_command_list(stack, "sa\n");
		}
		else if (b > a && b > c && a > c)
		{
			rra(stack);
			stack->command_list = ft_command_list(stack, "rra\n");
		}
		else if (a > c && a > b && c > b)
		{
			ra(stack);
			stack->command_list = ft_command_list(stack, "ra\n");
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
				pb(stack);
				stack->command_list = ft_command_list(stack, "pb\n");
				stack->len_less_pvt++;
			}
			else
			{
				ra(stack);
				stack->command_list = ft_command_list(stack, "ra\n");
			}
		}
		stack->len_pvts_b = ft_list_push_forw(stack);
	}
	sort_triple(stack);
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
				}
				else
				{
					rb(stack);
					stack->command_list = ft_command_list(stack, "rb\n");
					rb_count++;
				}
				len--;
			}
			while (rb_count)
			{
				rrb(stack);
				stack->command_list = ft_command_list(stack, "rrb\n");
				rb_count--;
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
					}
					else
					{
						ra(stack);
						stack->command_list = ft_command_list(stack, "ra\n");
						ra_count++;
					}
					len--;
				}
				while (ra_count)
				{
					rra(stack);
					stack->command_list = ft_command_list(stack, "rra\n");
					ra_count--;
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
		ft_printf("%d\n", iter_count(&stack));
		optimizing_commands_list(&stack);
		ft_printf("%d\n", iter_count(&stack));
//		print_commands(&stack);
		free_doubly_list(stack.btm_b);
		free_doubly_list(stack.len_pvts_b);
		free_command_list(stack.command_list);
	}
	return (0);
}
