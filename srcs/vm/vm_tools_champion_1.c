/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_champion_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 13:49:06 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/11 13:38:04 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

/*
** Function: attribut_nb_champ
** Description:
**	Function explores the int table of id, to find an available one.
**	An id is available if id_available[id -1] is equal to 0.
** Return:
**	id: the available id for the new champion.
**	0: otherwise.
*/

static int	attribut_nb_champ(int *id_available)
{
	int		id;

	id = 1;
	while (id < 5 && id_available[id - 1] == 1)
		id++;
	if (id == 5)
		return (0);
	return (id);
}

/*
** Function: is_valid_champ_filename
** Description:
**	Function checks if the filename has the correct format, meaning extension
**	'.cor' is present.
** Return:
**	1: filename is acceptable
**	0: otherwise
*/

int			is_valid_champ_filename(char *filename)
{
	int		len;

	len = ft_strlen(filename);
	return (ft_strequ(filename + len - 4, ".cor"));
}

/*
** Function:
** Description:
**	Set the value of the champion before adding it into the link.
** Return:
**	0: No error occured.
**	CD_ERROR: The code error of a dupplicated champ id or a too long file.
*/

static int	set_champ_value(t_champ *champ, t_parse *p, char *str)
{
	if (p->id_available[p->id_champ - 1] == 1)
		return ((int)CD_DUPL_N);
	if (p->options->n == 1)
	{
		champ->id = p->id_champ;
		p->id_available[champ->id - 1] = 1;
	}
	if (p->options->n == 0)
	{
		champ->id = attribut_nb_champ(p->id_available);
		p->id_available[champ->id - 1] = 1;
	}
	if (ft_strlen(str) >= (int)FILE_BIG)
		return ((int)CD_FILE_BIG);
	champ->champ_file = str;
	champ->name = NULL;
	champ->comment = NULL;
	champ->l_bytecode = 0;
	champ->bytecode = NULL;
	champ->mem_pos = -1;
	return (0);
}

/*
** Function: vm_create_champion
** Description:
**	Function checks if there is the filename in the next argument av,
*/

int			vm_create_champion(t_list **lst_champs, char *av, t_parse *p)
{
	t_list		*nw_link;
	t_champ		champ;
	int			code_error;

	nw_link = NULL;
	if ((code_error = set_champ_value(&champ, p, av)) != 0)
		return (code_error);
	if (!(nw_link = ft_lstnew(&champ, sizeof(champ))))
		return ((int)CD_MEM_CHAMP);
	ft_lstadd(lst_champs, nw_link);
	p->nb_champ++;
	p->options->n = 0;
	p->id_champ = 0;
	return (0);
}

/*
** Function: vm_champion_introduction
** Description:
**	Introduces the different champions before the battle.
*/

void	vm_champion_introduction(t_list *lst_champs, int nb_champ)
{
	t_list	*xplr;
	t_champ	*chp;
	int		id;

	ft_putstr("Introducing contestants...\n");
	// tool_print_short_champ_list(lst_champs);
	if (lst_sort_champion(&lst_champs, nb_champ) == 0)
	{
		ft_printf("erreur dans la fonction de tri des champions.\n");
		return ;
	}
	xplr = lst_champs;
	// tool_print_short_champ_list(lst_champs);
	while (xplr)
	{
		chp = (t_champ *)(xplr->cnt);
		id = chp->id;
		ft_printf("* Player %d, weighing %d bytes,", id, chp->l_bytecode);
		ft_printf(" \"%s\" (\"%s\") !\n", chp->name, chp->comment);
		xplr = xplr->next;
	}
}
