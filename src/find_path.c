/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 20:11:50 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:35:12 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static char		***paths(char **arr, int ways)
{
	char	***new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < ways)
		if (arr[i])
			j++;
	if (!(new = (char ***)malloc(sizeof(char **) * (j + 1))))
		EXIT("Error. Memory allocation failed.", 16);
	i = -1;
	j = 0;
	while (++i < ways)
		if (arr[i])
		{
			new[j++] = ft_strsplit(arr[i], ';');
			free(arr[i]);
		}
	new[j] = NULL;
	free(arr);
	return (new);
}

static void		set_length(t_graph *head, int i)
{
	t_links	*tmp;

	head->length = i;
	tmp = head->links;
	while (tmp)
	{
		if ((tmp->obj->length > i || tmp->obj->length == 0) &&
			!tmp->obj->is_in_quere)
			set_length(tmp->obj, i + 1);
		tmp = tmp->next;
	}
}

static void		set_nulls(t_graph *head)
{
	while (head)
	{
		head->length = 0;
		head = head->next;
	}
}

static char		*get_path(t_graph *start, char *path)
{
	t_links		*operation;
	t_graph		*tmp;

	operation = get_best_link(start);
	if (operation)
	{
		tmp = operation->obj;
		concat_strings(&path, operation->obj->name);
		if (operation->obj->is_end)
		{
			free(operation);
			return (path);
		}
		free(operation);
		return (get_path(tmp, path));
	}
	free(path);
	return (NULL);
}

char			***simple_ways(t_lem *core)
{
	char	**arr;
	int		i;
	int		ways;

	i = -1;
	if (!core->start->links || !core->end->links)
		EXIT("ERROR. Path not found", 25);
	ways = ft_list_counter((void **)core->start->links);
	arr = init_arr(ways);
	set_length(core->end, 0);
	while ((arr[++i] = get_path(core->start, NULL)))
	{
		set_nulls(core->head);
		set_length(core->end, 0);
	}
	return (paths(arr, ways));
}
