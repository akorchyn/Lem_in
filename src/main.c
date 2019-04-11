/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 20:17:14 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/10 22:35:27 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		*count_path_length(char ***paths, int const ways)
{
	int		i;
	int		*path_len;

	i = -1;
	if (!(path_len = (int *)malloc(sizeof(int) * ways)))
		EXIT("Error. Memory allocation failed.", 17);
	while (paths[++i])
		path_len[i] = ft_len(paths[i], sizeof(paths[i])) + 1;
	return (path_len);
}

void	print_ways(t_ant *ants, t_lem *core)
{
	int		finish;
	int		i;
	int		k;

	finish = 0;
	sort_ants(ants, core->ants);
	while (finish != core->ants && !(k = 0))
	{
		i = -1;
		finish = 0;
		while (++i < core->ants)
			if (!ants[i].path)
				finish++;
			else if (ants[i].pause > 0)
				ants[i].pause--;
			else
			{
				(k == 1) ? write(1, " ", 1) : 0;
				ft_printf("L%i-%s", i + 1, ants[i].path[ants[i].counter++]);
				if (ants[i].path[ants[i].counter] == NULL)
					ants[i].path = NULL;
				k = 1;
			}
		(finish != core->ants && ++core->turns) ? write(1, "\n", 1) : 0;
	}
}

void	distribute_ants(t_lem *core, int ways, int const *paths_len, int i)
{
	t_ant	ants[core->ants];
	int		pause;
	int		ant;

	pause = 0;
	ant = 0;
	while (ant < core->ants && !(i = 0))
	{
		while (i < ways && paths_len[i] == paths_len[0] && ant < core->ants)
		{
			ants[ant].counter = 0;
			ants[ant].pause = pause;
			ants[ant++].path = core->paths[i++];
		}
		while (i < ways && paths_len[i] <= paths_len[0] + pause &&
				ant < core->ants)
		{
			ants[ant].counter = 0;
			ants[ant].path = core->paths[i];
			ants[ant++].pause = (paths_len[0] + pause) - paths_len[i++] - 1;
		}
		pause++;
	}
	print_ways(ants, core);
}

void	path_from_start_to_end(t_lem *core)
{
	int i;

	i = 1;
	(!core->is_not_print_file) ? print_list(core->file) : 0;
	(!core->is_not_print_file) ? write(1, "\n", 1) : 0;
	ft_printf("L%i-%s", i, core->end->name);
	while (++i <= core->ants)
		ft_printf(" L%i-%s", i, core->end->name);
	write(1, "\n", 1);
	(core->is_print_turn) ? ft_printf("Turns: 1") : 0;
	exit(0);
}

int		main(void)
{
	t_lem		core;
	int			*paths_len;
	int			ways;

	core.head = NULL;
	core.end = NULL;
	core.file = NULL;
	core.turns = 0;
	parse(&core);
	(check_connection_for_end(core.start)) ? path_from_start_to_end(&core) : 0;
	core.paths = simple_ways(&core);
	if (!(ways = ft_len(core.paths, sizeof(core.paths))))
		EXIT("ERROR. Path not found", 20);
	(!core.is_not_print_file) ? print_list(core.file) : 0;
	(!core.is_not_print_file) ? write(1, "\n", 1) : 0;
	paths_len = count_path_length(core.paths, ways);
	distribute_ants(&core, ways, paths_len, 0);
	(core.is_print_turn) ? ft_printf("Turns : %d\n", core.turns) : 0;
	free(paths_len);
	return (0);
}
