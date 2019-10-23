/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_write_header.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:50:34 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/23 18:43:50 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brainfuck.h"

/**
 * Write define, .bss section, .text section and _main begin
 */
void	compiler_write_header(t_bf *bf)
{
	dprintf(bf->asm_fd, "%%define BUFF_SIZE %d\n", BUFFER_SIZE);
	dprintf(bf->asm_fd, "section .bss\n");
	dprintf(bf->asm_fd, "\tbuffer resb BUFF_SIZE\n\n");
	dprintf(bf->asm_fd, "section .text\n\tglobal start, _main\n\n");
	dprintf(bf->asm_fd, "start:\n\tcall _main\n\tret\n\n");

	dprintf(bf->asm_fd, "_main:\n");
	dprintf(bf->asm_fd, "\tpush rbp\n");
	dprintf(bf->asm_fd, "\tmov rbp, rsp\n");
	dprintf(bf->asm_fd, "\tlea r12, [rel buffer]\n");
}
