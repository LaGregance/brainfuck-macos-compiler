/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:59:46 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/23 21:51:45 by gtaja            ###   ########.fr       */
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
 * Check if c is an optimizable brainfuck instruction (+-<>)
 * 
 * @param c The char to check
 * @return TRUE or FALSE
 */
int		is_stackable(char c)
{
	return (
		c == '+' || c == '-' ||
		c == '>' || c == '<'
	);
}

/**
 * 
 */
int		flush_stackable(t_bf *bf)
{
	int fct_res;

	if (bf->stack_instruction != 0)
	{
		if ((fct_res = compiler_dispatch_char(bf, bf->stack_instruction)) < 0)
			return (fct_res);
		bf->stack_instruction = 0;
		bf->stack_number = 0;
	}
	return (SUCCESS);
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
			if (c == bf->stack_instruction)
				bf->stack_number += 1;
			else
			{
				if ((fct_res = flush_stackable(bf)) < 0)
					return (fct_res);
				if (is_stackable(c))
				{
					bf->stack_instruction = c;
					bf->stack_number += 1;
				}
				else if ((fct_res = compiler_dispatch_char(bf, c)) < 0)
					return (fct_res);
			}
		}
	}
	if ((fct_res = flush_stackable(bf)) < 0)
		return (fct_res);
	compiler_write_footer(bf);
	return (SUCCESS);
}
