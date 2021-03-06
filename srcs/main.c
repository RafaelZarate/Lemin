/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarate <rzarate@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 17:56:25 by kmckee            #+#    #+#             */
/*   Updated: 2018/04/13 14:26:52 by rzarate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	You can access to the linked list of paths (list of movements)
**	with lemin->paths
*/

int	main(void)
{
	t_lemin	*lemin;

	lemin = (t_lemin *)ft_memalloc(sizeof(t_lemin));
	parse_input(lemin);
	solve(lemin);
	manage_ants(lemin);
	finalize_lemin(lemin);
	return (0);
}
