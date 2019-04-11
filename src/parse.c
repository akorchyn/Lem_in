/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 20:20:41 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/13 14:21:55 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		links(t_graph *first, t_graph *second)
{
	t_links	*new;
	t_links	*tmp;

	tmp = first->links;
	if (first == second)
		return ;
	while (tmp)
	{
		if (tmp->obj == second)
			return ;
		tmp = tmp->next;
	}
	if (!(new = (t_links *)malloc(sizeof(t_links))))
		EXIT("Error. Memory allocation failed.", 6);
	new->obj = second;
	new->next = first->links;
	first->links = new;
	if (!(new = (t_links *)malloc(sizeof(t_links))))
		EXIT("Error. Memory allocation failed.", 7);
	new->obj = first;
	new->next = second->links;
	second->links = new;
}

static void		create_link(char **first_name, t_graph *tmp)
{
	t_graph *first;
	t_graph	*second;
	char	*second_name;

	first = NULL;
	second = NULL;
	second_name = ft_strchr(*first_name, '-');
	if (!second_name)
		EXIT_PARSE("ERROR. Bad link", *first_name, 4);
	(*first_name)[second_name - *first_name] = '\0';
	while (tmp)
	{
		if (!first && !ft_strcmp(*first_name, tmp->name))
			first = tmp;
		if (!second && !ft_strcmp(second_name + 1, tmp->name))
			second = tmp;
		if (first && second)
			break ;
		tmp = tmp->next;
	}
	(*first_name)[second_name - *first_name] = '-';
	if (!first || !second)
		EXIT_PARSE("ERROR. Node not found.", *first_name, 5);
	links(first, second);
}

static void		insert_element(char **line, t_lem *core)
{
	char	*first_space;
	char	*second_space;
	t_graph	*new;

	if (!(first_space = ft_strchr(*line, ' ')) ||
		!(second_space = ft_strchr(first_space + 1, ' ')) || (*line)[0] == 'L')
		EXIT_PARSE("Error. Bad node.", *line, 2);
	first_space++;
	if (!(new = (t_graph *)malloc(sizeof(t_graph))))
		EXIT("Error. Memory allocation failed.", 3);
	ft_strncpy(new->name, *line, first_space - *line - 1);
	new->name[first_space - *line - 1] = '\0';
	new->x = ft_atoi(first_space);
	new->y = ft_atoi(second_space);
	new->is_in_quere = 0;
	new->next = core->head;
	new->links = NULL;
	new->length = 0;
	if (check_other_nodes(new->name, new->x, new->y, core->head) &&
		ft_isnumeric(first_space, ' ')
		&& ft_isnumeric(second_space + 1, '\0'))
		core->head = new;
	else
		EXIT_PARSE("ERROR. Bad node.", *line, 21);
}

static void		handle_command(t_lem *core, char **line)
{
	if (!ft_strcmp(*line, "##start"))
	{
		if (core->start)
			EXIT("ERROR. Start currently set.", 22);
		*line = get_next_line_save(core);
		insert_element(line, core);
		core->start = core->head;
		core->start->length = 1000;
	}
	else if (!ft_strcmp(*line, "##end"))
	{
		if (core->end)
			EXIT("ERROR. End currently set.", 23);
		*line = get_next_line_save(core);
		insert_element(line, core);
		core->head->is_end = 1;
		core->end = core->head;
	}
	else if (!ft_strcmp(*line, "##turns"))
		core->is_print_turn = 1;
	else if (!ft_strcmp(*line, "##fileoff"))
		core->is_not_print_file = 1;
}

void			parse(t_lem *core)
{
	char	*line;
	int		linking;

	linking = 0;
	if (!(line = get_next_line_save(core)))
		EXIT("ERROR. Parse error, empty input", 26);
	if (!ft_isnumeric(line, 0) || (core->ants = ft_atoi(line)) < 1)
		EXIT_PARSE("ERROR. Amount of ants not valid.", line, 1);
	while ((line = get_next_line_save(core)))
		if (line[0] == '#' && line[1] == '#')
			handle_command(core, &line);
		else if (!linking && ft_strchr(line, ' '))
			insert_element(&line, core);
		else
		{
			linking = 1;
			create_link(&line, core->head);
		}
	if (!core->start || !core->end || core->start == core->end)
		EXIT("ERROR. Haven't start or end location or they are same.", 8);
}
