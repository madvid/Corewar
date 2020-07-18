/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:29:46 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/18 22:21:37 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

/*
** Function: is_dump_option
** Description:
**	Function check if the string arg is the option flag -dump. If so, flag for
**	option dump is set to 1 (otherwise 0).
** Return:
**	1: if the str arg is the flag option dump
**	0: if not
*/

static int		is_dump_option(char *arg, t_parse *p)
{
	p->options->dump = (ft_strequ(arg, "-dump") == 1) ? 1 : 0;
	return (p->options->dump);
}

/*
** Function:
** Description:
**	Function checks if the str arg is the flag option to attribute a specific
**	number to the following chafmpion.
** Return:
**	1: if arg is the attribution number flag
**	0: otherwise
*/

static int		is_n_flag(char *arg)
{
	return (ft_strequ(arg, "-n"));
}

/*
** Function: is_valid_nb_champ
** Description:
**	Checks if the number given by the user is a positive int sinfle digit
**	in [1 ; 4].
** Return:
**	1: if the number for the id champion is correct.
**	0: otherwise.
*/

static int		is_valid_nb_champ(char *nb)
{
	if (ft_strlen(nb) > 1)
	{
		ft_putendl("Error: champion number must be 1, 2, 3 or 4.");
		return (0);
	}
	if (!(nb[0] >= '1' && nb[0] <= '4'))
	{
		ft_putendl("Error: champion number must be 1, 2, 3 or 4.");
		return (0);
	}
	return (1);
}

/*
** Function: vm_parsing
** Description:
**	Parsing of the standard inputs of the executable corewar (the VM)
**	the informations are stored in the structure p of type t_parse.
**	Notice that we just verified the validity of the arguments on the stdin
** and not the validity of the bytecode files (which is performed later).
*/

/*
** Remarque:
**	Il faudra tester le retour de ft_atoull, je suspecte que lorsque la str
**	n'est pas correct, ne pas être en mesure de relever qu'il y a une erreur
*/

int				vm_parsing(char **av, t_parse *p)
{
	int		i;

	i = 1;
	if (av[i] && is_dump_option(av[i], p) == 1)
	{
		if (av[++i] && p->options->dump == 1 && ft_is_positive_int(av[i]))
		{
			p->options->dump = 1;
			p->options->nbr_cycle = ft_atoi(av[i++]);
		}
		else
			return (vm_error_manager((int)CD_DUMP, p->error));
	}
	while (av[i] && p->nb_champ < 5)
	{
		if (is_n_flag(av[i]))
		{
			if (av[++i] && is_valid_nb_champ(av[i]))
			{
				p->options->n = 1;
				p->id_champ = (int)(*av[i++] - '0');
			}
			else
				return (vm_error_manager((int)CD_BD_VAL, p->error));
		}
		if (av[i] && !is_valid_champ_filename(av[i]))
			return (vm_error_manager((int)CD_BD_CHAMP_NB, p->error));
		if (av[i] && !vm_create_champion(&(p->lst_champs), av[i++], p))
			return (vm_error_manager((int)CD_MEM_CHAMP, p->error));
	}
	if (p->nb_champ == 0)
		return (vm_error_manager((int)CD_EMPTY_CHP, p->error));
	if (p->nb_champ > (int)MAX_PLAYERS)
		return (vm_error_manager((int)CD_MAX_CHAMP, p->error));
	return (1);
}
