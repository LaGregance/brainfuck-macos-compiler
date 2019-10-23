/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_dispatch_char.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:48:24 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/23 17:29:37 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brainfuck.h"

t_fct_dispatch	write_fcts[8] = {
	{'>', &compiler_write_inc_ptr},
	{'<', &compiler_write_dec_ptr},
	{'+', &compiler_write_inc_value},
	{'-', &compiler_write_dec_value},
	{'[', &compiler_write_open_loop},
	{']', &compiler_write_close_loop},
	{'.', &compiler_write_print},
	{0, NULL}
};

/**
 * Redirect instruction from c to the good function
 * 
 * @param c char corresponding to the target instruction
 * @return SUCCESS or error code
 */
int		compiler_dispatch_char(t_bf *bf, char c)
{
	int	i;

	for (i = 0; write_fcts[i].fct != NULL; i++)
	{
		if (write_fcts[i].c == c)
			return (write_fcts[i].fct(bf));
	}
	return (SUCCESS);
}
