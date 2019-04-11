/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:09:50 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:11:37 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				check_connection_for_end(t_graph *start)
{
	t_links		*tmp;

	tmp = start->links;
	while (tmp)
	{
		if (tmp->obj->is_end)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char			*get_next_line_save(t_lem *core)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) > 0 && line[0] == '#' && line[1] != '#')
		ft_strdel(&line);
	ft_lstadd(&core->file, ft_lstnew(NULL, 0));
	core->file->content = line;
	return (line);
}

int				check_other_nodes(char *name, int x, int y, t_graph *start)
{
	while (start)
	{
		if (!ft_strcmp(name, start->name) || (x == start->x && y == start->y))
			return (0);
		start = start->next;
	}
	return (1);
}
