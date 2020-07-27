/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_opcode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:35:15 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/27 16:32:34 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	init_op_funct(int (**t_op_funct)(t_cw*, t_process*, t_op))
{
	t_op_funct[0] = &op_alive;
	// t_op_funct[1] = &op_load;
	// t_op_funct[2] = op_store;
	// t_op_funct[3] = op_addition;
	// t_op_funct[4] = op_soustraction;
	// t_op_funct[5] = op_and;
	// t_op_funct[6] = op_or;
	// t_op_funct[7] = op_xor;
	// t_op_funct[8] = op_zerojump;
	// t_op_funct[9] = op_load_index;
	// t_op_funct[10] = op_store_index;
	// t_op_funct[11] = op_fork;
	// t_op_funct[12] = op_long_load;
	// t_op_funct[13] = op_long_load_index;
	// t_op_funct[14] = op_long_fork;
	// t_op_funct[15] = op_aff;
	// return (t_op_funct[i])
}

/*
** Function: perform_opcode
** Description:
**	[put some explanations here !]
*/

void	perform_opcode(t_cw *cw, t_process *cur_proc)
{
	extern t_op		op_tab[17];
	int				pos;
	static int		(*op_funct[16])(t_cw*, t_process*, t_op) = {NULL};

	
	if (op_funct[0] == NULL)
		init_op_funct(op_funct);
	if (cur_proc->wait_cycles == 0)
	{
		pos = cur_proc->position - (void*)(&(cw->arena[0]));
		if (!is_opcode(cw->arena, pos))
			return ;
		op_funct[0](cw, cur_proc, op_tab[0]);
		// printf("an instruction alive is performed\n");
	}
	// if (i == 0)
	// {
	// 	printf("arena = %s\n", cw->arena);
	// 	printf("process id = %d\n", cur_proc->id);
	// }
	// printf("avant\n");
	// while (++i < 18)
	// 	printf("valeur d op_funct[%d] = %p\n", i, op_funct[i]);
	// printf("apres\n");
	// t_op_funct[(int)cur_proc->opcode](cw, cur_proc, op_tab[(int)cur_proc->opcode])
}

/*
** Function: is_opcode
** Description:
**	[put some explanations here]
** Return:
**	1: if the byte is an opcode.
**	0: if the byte does not correspond to an opcode.
*/

bool	is_opcode(char *arena, int pos)
{
	u_int8_t	opcode;
	u_int8_t	encoding;

	opcode = arena[pos];
	printf("  [is_opcode] valeur de opcode = %d\n", (int)opcode);
	if (opcode_no_encoding(opcode))
	{
		// printf("  [is_opcode] opcode sans byte d'encodage\n");
		return (true);
	}
	encoding = (u_int8_t)arena[(pos + 1) % (int)MEM_SIZE];
	// printf("  [is_opcode] valeur de encoding = %c|(int)%d\n", encoding, (int)encoding);
	if ((int)opcode >= 1 && (int)opcode <= 16)
	{
		if (is_valid_encoding(opcode, encoding) == false)
			return (false);
		return (true);
	}
	return (false);
}

/*
** Function: arg_size_opcode_no_encode
** Description:
**	[put some explanation here]
** Return:
**	4: length of the argument of the instruction live (opcode = 1).
**	1: length of the argument of zjmp/fork/lfork (opcode 9/12/15).
**	-1: if the opcode value is not within (1 ; 9 ; 12 ; 15)
*/

int		arg_size_opcode_no_encode(u_int8_t opcode)
{
	if (opcode == 1)
		return (4);
	if (opcode == 9)
		return (2);
	if (opcode == 12)
		return (2);
	if (opcode == 15)
		return (2);
	return (-1);
}

/*
** Function: opcode_no_encoding
** Description:
**	Checks if the opcode is one of those without encoding byte.
** Return:
**	true: if opcode does not have encoding byte.
**	false: otherwise
*/

bool	opcode_no_encoding(u_int8_t opcode)
{
	if (opcode == 1 || opcode == 9 || opcode == 12 || opcode == 15)
		return (true);
	else
		return (false);
}


/*
** Function: addr_next_opcode
** Description:
**	Gets the address of the next opcode, without distinguish if the opcode is
**	related to the 'current' champion.
** Return:
**	addr: address of the next opcode.
**	NULL: there is no next opcode right after the ongoing one.
*/

void	*addr_next_opcode(char *arena, int mem_pos)
{
	u_int8_t	encoding;
	u_int8_t	opcode;
	int			next_opcode;
	extern t_op	op_tab[17];

	opcode = (u_int8_t)arena[mem_pos];
	// printf(">>[addr_next_opcode] Opcode value = %d\n", opcode);
	if (opcode_no_encoding(opcode))
	{
		// printf(">>  opcode with no encoding byte ...\n");
		// printf(">>[addr_next_opcode] size of the arg of opcode wtht encoded byte : %d\n", arg_size_opcode_no_encode(opcode));
		// printf(">>    adress of the next opcode : %p\n", (void*)(arena + arg_size_opcode_no_encode(opcode) + 1));
		// printf(">>[addr_next_opcode] Code of the next opcode : %d\n", (int)arena[mem_pos + arg_size_opcode_no_encode(opcode) + 1]);
		next_opcode = (mem_pos + arg_size_opcode_no_encode(opcode) + 1) % MEM_SIZE;
		return ((void*)(&arena[next_opcode]));
	}
	// printf("[addr_next] current opcode = %d\n", opcode);
	// printf("[addr_next] current encoding = %d\n", encoding);
	encoding = (u_int8_t)arena[(mem_pos + 1) % MEM_SIZE];
	next_opcode = instruction_width(encoding, op_tab[opcode - 1].direct_size) + 2;
	// printf(">>  opcode with encoding byte ...\n");
	// printf(">>[addr_next_opcode] size of the arg of opcode wth encoded byte : %d\n", instruction_width(encoding, op_tab[opcode - 1].direct_size));
	// printf(">>    adress of the next opcode : %p\n", (void*)(&arena[mem_pos + next_opcode]));
	// printf(">>[addr_next_opcode] Code of the next opcode : %d\n", (int)arena[mem_pos + next_opcode]);
	// if (!is_opcode(arena, mem_pos + next_opcode))
	// 	return (NULL);
	// else
	return ((void*)(&arena[mem_pos + next_opcode]));
}