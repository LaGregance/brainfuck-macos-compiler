/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_write_instructions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:02:31 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/23 18:43:56 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brainfuck.h"

/**
 * Write ASM for '>'
 * @return Always SUCCESS
 */
int		compiler_write_inc_ptr(t_bf *bf)
{
	dprintf(bf->asm_fd, "\tinc r12\n");
	return (SUCCESS);
}

/**
 * Write ASM for '<'
 * @return Always SUCCESS
 */
int		compiler_write_dec_ptr(t_bf *bf)
{
	dprintf(bf->asm_fd, "\tdec r12\n");
	return (SUCCESS);
}

/**
 * Write ASM for '+'
 * @return Always SUCCESS
 */
int		compiler_write_inc_value(t_bf *bf)
{
	dprintf(bf->asm_fd, "\tinc byte[r12]\n");
	return (SUCCESS);
}

/**
 * Write ASM for '-'
 * @return Always SUCCESS
 */
int		compiler_write_dec_value(t_bf *bf)
{
	dprintf(bf->asm_fd, "\tdec byte[r12]\n");
	return (SUCCESS);
}

/**
 * Write ASM for '.'
 * @return Always SUCCESS
 */
int		compiler_write_print(t_bf *bf)
{
	dprintf(bf->asm_fd, "\tmov rdi, 1\n");
	dprintf(bf->asm_fd, "\tmov rdx, 1\n");
	dprintf(bf->asm_fd, "\tmov rsi, r12\n");
	dprintf(bf->asm_fd, "\tmov rax, 0x2000004\n");
	dprintf(bf->asm_fd, "\tsyscall\n");
	return (SUCCESS);
}

/**
 * Write ASM for '['
 * @return Always SUCCESS
 */
int		compiler_write_open_loop(t_bf *bf)
{
	bf->current_loop += 1;
	dprintf(bf->asm_fd, "\tcmp byte[r12], 0\n");
	dprintf(bf->asm_fd, "\tje loop_end_%d\n", bf->current_loop);
	dprintf(bf->asm_fd, "loop_start_%d:\n", bf->current_loop);
	return (SUCCESS);
}

/**
 * Write ASM for ']'
 * @return SUCCESS or ERROR_BAD_LOOP_CLOSE if you trying to close a loop who wasn't opened
 */
int		compiler_write_close_loop(t_bf *bf)
{
	if (bf->current_loop <= 0)
		return (ERROR_BAD_LOOP_CLOSE);
	dprintf(bf->asm_fd, "\tcmp byte[r12], 0\n");
	dprintf(bf->asm_fd, "\tjne loop_start_%d\n", bf->current_loop);
	dprintf(bf->asm_fd, "loop_end_%d:\n", bf->current_loop);
	bf->current_loop -= 1;
	return (SUCCESS);
}
