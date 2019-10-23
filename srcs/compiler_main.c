/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:59:46 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/23 18:25:12 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brainfuck.h"

/**
 * Check if c is a brainfuck instruction or a comment
 * 
 * @param c The char to check
 * @return TRUE or FALSE
 */
int		is_bf_char(char c)
{
	return (
		c == '+' || c == '-' ||
		c == '>' || c == '<' ||
		c == '[' || c == ']' ||
		c == '.'
	);
}

/**
 * Read source file and write asm
 * 
 * @return SUCCESS or error code
 */
int		compiler_main(t_bf *bf)
{
	char	c;
	int		fct_res;

	compiler_write_header(bf);
	while (read(bf->source_fd, &c, 1) > 0)
	{
		bf->current_char += 1;
		if (is_bf_char(c))
		{
			if ((fct_res = compiler_dispatch_char(bf, c)) < 0)
				return (fct_res);
		}
	}
	compiler_write_footer(bf);
	return (SUCCESS);
}
