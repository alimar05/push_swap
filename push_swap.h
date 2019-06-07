/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:06:27 by rymuller          #+#    #+#             */
/*   Updated: 2019/06/07 12:56:24 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <libft.h>
# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct				s_doubly_list
{
	int						value;
	size_t					len_pivot;
	struct s_doubly_list	*prev;
	struct s_doubly_list	*next;
}							t_doubly_list;

typedef struct				s_stack
{
	size_t					len_a;
	t_doubly_list			*top_a;
	t_doubly_list			*btm_a;
	t_doubly_list			*top_b;
	t_doubly_list			*btm_b;
	size_t					size;
}							t_stack;

int							ft_printf(const char *format, ...);
void						sa(t_stack *stack);
void						sb(t_stack *stack);
void						ss(t_stack *stack);
void						pb(t_stack *stack);
void						pa(t_stack *stack);
void						ra(t_stack *stack);
void						rb(t_stack *stack);
void						rr(t_stack *stack);
void						rra(t_stack *stack);
void						rrb(t_stack *stack);
void						rrr(t_stack *stack);
void						print_stack(t_stack *stack);
void						free_doubly_list(t_stack *list);
char						is_sort_stack(t_doubly_list *top);
void						quicksort(int *arr, int low, int high);
char						is_swap_command(t_stack *stack, char *line);
char						is_push_command(t_stack *stack, char *line);
char						is_rotate_command(t_stack *stack, char *line);
char						is_rev_rotate_command(t_stack *stack, char *line);
char						is_placing_argv_stack(t_stack *stack, int argc, char **argv);
t_doubly_list				*ft_list_push_back(t_stack *stack, int value);
#endif
