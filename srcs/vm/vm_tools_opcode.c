/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_opcode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:35:15 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/31 20:13:58 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	init_op_funct(int (**t_op_funct)(t_cw*, t_process*))
{
	t_op_funct[0] = &op_alive;
	t_op_funct[1] = &op_load;
	t_op_funct[2] = &op_store;
	t_op_funct[3] = &op_addition;
	t_op_funct[4] = &op_soustraction;
	t_op_funct[5] = &op_and;
	t_op_funct[6] = &op_or;
	t_op_funct[7] = &op_xor;
	t_op_funct[8] = &op_zerojump;
	t_op_funct[9] = &op_load_index;
	t_op_funct[10] = &op_store_index;
	t_op_funct[11] = &op_fork;
	t_op_funct[12] = &op_long_load;
	t_op_funct[13] = &op_long_load_index;
	t_op_funct[14] = &op_long_fork;
	t_op_funct[15] = &op_aff;
}

/*
** Function: is_opcode
** Description:
**	[put some explanations here]
** Return:
**	1: if the byte is an opcode.
**	0: if the byte does not correspond to an opcode.
*/

bool		is_valid_opcode(t_cw *cw, t_process *cur_proc)
{
	u_int8_t	opcode;
	u_int8_t	encoding;
	int			widht;
	t_arg		a;

	opcode = cur_proc->opcode;
	if (opcode_no_encoding(opcode))
		return (true);
	if (opcode >= 1 && opcode <= 16)
	{
		encoding = (u_int8_t)cw->arena[(cur_proc->i + 1) % (int)MEM_SIZE];
		widht = (cur_proc->pc < cur_proc->i) ? MEM_SIZE - cur_proc->i \
			+ cur_proc->pc : cur_proc->pc - cur_proc->i;
		op_arg_init(&a, 0, 0);
		a.widht = widht;
		if (is_valid_encoding(opcode, encoding) == false \
			|| is_valid_reg(cw, cur_proc) == false)
		{
			cw->options->v_lvl & 0b00010000 ? vprint_pcmv(cw, cur_proc, a) : 0;
			return (false);
		}
		return (true);
	}
	return (false);
}

/*
** Function: perform_opcode
** Description:
**	Checks the validity of the encoded byte (if there is one) associated to
**	the opcode in the current process and performs the corresponding
**	instruction if wait_cycles of the process is 0.
** Return:
**	0: No error has been raised by any opcode functions (by return -1)
**	code_error: Can only be an memory allocation issue during process creation
*/

int			perform_opcode(t_cw *cw, t_process *cur_proc)
{
	int				code_error;
	static int		(*op_funct[16])(t_cw*, t_process*) = {NULL};

	code_error = 0;
	if (op_funct[0] == NULL)
		init_op_funct(op_funct);
	if (cur_proc->wait_cycles == 0)
	{
		if (!is_valid_opcode(cw, cur_proc))
			return (0);
		code_error = op_funct[cur_proc->opcode - 1](cw, cur_proc);
	}
	return (code_error);
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

int			arg_size_opcode_no_encode(u_int8_t opcode)
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

bool		opcode_no_encoding(u_int8_t opcode)
{
	if (opcode == 1 || opcode == 9 || opcode == 12 || opcode == 15)
		return (true);
	else
		return (false);
}
