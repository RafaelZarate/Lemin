/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarate <rzarate@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 17:13:56 by rzarate           #+#    #+#             */
/*   Updated: 2018/04/05 09:25:15 by rzarate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	Parses # of ants and stores it in graph_data
*/

static	void	get_number_of_ants(t_lemin *lemin)
{
	char	*line;

	lemin->graph_data = (t_graph *)ft_memalloc(sizeof(t_graph));
	get_next_line(0, &line);
	lemin->graph_data->ants = ft_atoi(line);
	if (lemin->graph_data->ants == 0)
		error();
	ft_strdel(&line);
}

/*
**	Rooms always come in with the following format
**	[string:Name]->[space]->[int:coord[0]]->space->[int:coord[1]]
**	NOTE: Remember to check for comments after ##start or ##end
*/

static	void	create_room(char *line, t_lemin *lemin, int start_end)
{
	char	**splitted_line;
	char	*name;
	int		coords[2];
	int		room_number;

	splitted_line = ft_strsplit(line, ' ');
	name = ft_strdup(splitted_line[0]);
	only_digits(splitted_line[1]);
	only_digits(splitted_line[2]);
	coords[0] = ft_atoi(splitted_line[1]);
	coords[1] = ft_atoi(splitted_line[2]);
	// This might be changed with a ft_2d_strdel
	ft_strdel(&splitted_line[0]);
	ft_strdel(&splitted_line[1]);
	ft_strdel(&splitted_line[2]);
	free(splitted_line);
	room_number = lemin->graph_data->rooms;
	lemin->graph_data->rooms++;
	add_room(&lemin->rooms, new_room(name, start_end, coords, room_number));
	ft_putstr(line);
	ft_putchar('\n');
}

/*
**	Adds new node to room linked list is valid
*/

static	void	get_rooms(char **line, t_lemin *lemin)
{
	int		start_end;

	while (get_next_line(0, line))
	{
		if (ft_strlen(*line) > 4 && (*line)[0] == '#' && (*line)[1] == '#')
		{
			start_end = get_start_end(*line, lemin);
			ft_putstr(*line);
			ft_putchar('\n');
			ft_strdel(line);
			get_next_line(0, line);
			create_room(*line, lemin, start_end);
		}
		else if (ft_strlen(*line) > 1 && (*line)[0] == '#')
		{
			ft_putstr((*line));
			ft_putchar('\n');
		}
		else if (ft_wordcount(*line) == 3)
			create_room(*line, lemin, 0);
		else if (ft_strchr(*line, '-'))
			break ;
		else
			error();
		ft_strdel(line);
	}
}

/*
**	1.- Parse # of ants
**	2.- Parse rooms
**	3.- Parse tunnels
*/

void			parse_input(t_lemin *lemin)
{
	char	*line;

	lemin->rooms = NULL;
	get_number_of_ants(lemin);
	ft_putstr("Number of ants: ");
	ft_putnbr(lemin->graph_data->ants);
	ft_putchar('\n');
	get_rooms(&line, lemin);
	if (lemin->graph_data->rooms == 0 || lemin->graph_data->end == 0
			|| lemin->graph_data->start == 0)
		error();
	get_tunnels(&line, lemin);
	if (!lemin->adj_list)
		error();
}