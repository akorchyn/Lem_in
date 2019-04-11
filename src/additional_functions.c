/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 20:12:41 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/15 19:07:16 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char			**init_arr(int len)
{
	char	**answer;
	int		i;

	i = -1;
	if (!(answer = (char **)malloc(sizeof(char *) * (len + 1))))
		EXIT("Error. Memory allocation failed.", 15);
	len++;
	while (++i < len)
		answer[i] = NULL;
	return (answer);
}

void			concat_strings(char **current_path, char *new_element)
{
	char	*tmp;
	size_t	len;

	len = (*current_path) ?
			ft_strlen(*current_path) + ft_strlen(new_element) + 2
			: ft_strlen(new_element) + 1;
	if (!(tmp = (char *)malloc(sizeof(char) * len)))
		EXIT("Error. Memory allocation failed.", 14);
	if (*current_path)
	{
		tmp = ft_strcpy(tmp, *current_path);
		tmp = ft_strcat(tmp, ";");
		tmp = ft_strcat(tmp, new_element);
	}
	else
		tmp = ft_strcpy(tmp, new_element);
	free(*current_path);
	*current_path = tmp;
}

void			print_list(t_list *start)
{
	(start->next) ? print_list(start->next) : 0;
	(start->content) ? ft_printf("%s\n", (char *)start->content) : 0;
	free(start->content);
	free(start);
}

void			sort_ants(t_ant *array_ants, int const ants)
{
	t_ant	tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < ants - 1)
	{
		j = i;
		while (++j < ants)
		{
			if (array_ants[i].pause > array_ants[j].pause)
			{
				tmp = array_ants[i];
				array_ants[i] = array_ants[j];
				array_ants[j] = tmp;
			}
		}
	}
}

t_links			*get_best_link(t_graph *element)
{
	t_links		*tmp;
	t_links		*best;

	best = NULL;
	tmp = element->links;
	while (tmp)
	{
		if ((!best || best->obj->length > tmp->obj->length
			|| tmp->obj->is_end) && !tmp->obj->is_in_quere)
			best = tmp;
		tmp = tmp->next;
	}
	if (best)
	{
		if (!(tmp = (t_links *)malloc(sizeof(t_links))))
			EXIT("Error. Memory allocation failed.", 18);
		tmp->obj = best->obj;
		(!tmp->obj->is_end) ? tmp->obj->is_in_quere = 1 : 0;
	}
	return (tmp);
}
