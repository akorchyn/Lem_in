/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 10:18:29 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/10 21:19:58 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_LEMIN_H
# define LEMIN_LEMIN_H

# include "../libft/includes/libft.h"

# define EXIT_PARSE(s, l, x) if (x != 0) {ft_printf("%s\n%s\n", s, l); exit(x);}
# define EXIT(s, x) if (x != 0) {ft_printf("%s\n", s); exit(x);}

typedef struct			s_links
{
	struct s_links		*next;
	struct s_graph		*obj;
}						t_links;

typedef struct			s_graph
{
	struct s_graph		*next;
	struct s_links		*links;
	char				name[255];
	int					length;
	int					x;
	int					y;
	unsigned char		is_end : 1;
	unsigned char		is_in_quere : 1;
}						t_graph;

typedef struct			s_lem
{
	int					ants;
	t_graph				*head;
	t_graph				*start;
	t_graph				*end;
	char				***paths;
	int					turns;
	unsigned int		is_print_turn : 1;
	unsigned int		is_not_print_file : 1;
	t_list				*file;
}						t_lem;

typedef struct			s_ant
{
	int					pause;
	int					counter;
	char				**path;
}						t_ant;

void					concat_strings(char **current_path, char *new_element);
char					**init_arr(int len);
void					sort_ants(t_ant *array_ants, int ants);
void					print_list(t_list *start);
t_links					*get_best_link(t_graph *element);
char					***simple_ways(t_lem *core);
void					parse(t_lem *core);
char					*get_next_line_save(t_lem *core);
int						check_connection_for_end(t_graph *start);
int						check_other_nodes(char *name, int x, int y,
							t_graph *start);

#endif
