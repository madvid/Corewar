/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:58:02 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/05 15:10:13 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

# define NB_ERROR_MSG		12
# define CD_USAGE			0
# define CD_DUMP 			1
# define CD_VERB			11
# define CD_UNIQ			12
# define CD_BD_VAL			2
# define CD_BD_CHAMP_NB		3
# define CD_MEM_CHAMP		4

# define CD_EMPTY_CHP		5
# define CD_MAX_CHAMP		6
# define CD_BD_CODE			7
# define CD_CHP_ERR			8
# define CD_INV_FD			9
# define CD_MAGIC_EXEC		10

# define M_USAGE_1			"Usage: ./corewar [[-dump N1] [-v N2] [-a]]"
# define M_USAGE_2			"[[-n N3] champion1.cor] ...\n"
# define M_USAGE_3			"     * N1 being an positive integer,\n"
# define M_USAGE_4			"     * N2 being an integer in range [0;31],\n"
# define M_USAGE_5			"     * N3 being an integer in range [1;4]."
# define M_USAGE			(M_USAGE_1 M_USAGE_2 M_USAGE_3 M_USAGE_4 M_USAGE_5)
# define M_DUMP_1			"Dump error: [-dump nbr_cycles] nbr_cycles need"
# define M_DUMP_2			" to exist, be non null and positive INT."
# define M_DUMP				(M_DUMP_1 M_DUMP_2)
# define M_VERB				"Error: invalid parameter for verbose option."
# define M_UNIQ				"Error: dupplicate option flag."
# define M_BD_VAL_1			"value error: [-n number], n "
# define M_BD_VAL_2			"must be either 1, 2, 3 or 4."
# define M_BD_VAL			(M_BD_VAL_1 M_BD_VAL_2)
# define M_BD_CHAMP_NB_1	"Champion file error: file must be a bytecode"
# define M_BD_CHAMP_NB_2	" with '.cor' extension."
# define M_BD_CHAMP_NB		(M_BD_CHAMP_NB_1 M_BD_CHAMP_NB_2)
# define M_MEM_CHAMP_1		"Error: memory allocation issue during parsing"
# define M_MEM_CHAMP_2		" process."
# define M_MEM_CHAMP		(M_MEM_CHAMP_1 M_MEM_CHAMP_2)

# define M_EMPTY_CHP		"Error: you must precise 1 champion at least."
# define M_MAX_CHAMP		"Error: a maximum of 4 champions is allowed."
# define M_BD_CODE			"Error: one of champion's file is not bytecode."
# define M_CHP_ERR			"Error: Incorrect bytecode in champion's code."
# define M_INV_FD			"Error: invalid fd, file or path may not exist."
# define M_MAGIC_EXEC		"Error: COREWAR_EXEC_MAGIC number into file."

#endif
