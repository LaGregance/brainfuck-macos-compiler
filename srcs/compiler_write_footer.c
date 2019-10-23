/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_write_footer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:19:28 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/23 18:43:35 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brainfuck.h"

/**
 * Finish writing _main
 */
void	compiler_write_footer(t_bf *bf)
{
	dprintf(bf->asm_fd, "\tleave\n");
	dprintf(bf->asm_fd, "\tret\n");
}
