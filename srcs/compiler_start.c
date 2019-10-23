/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:59:27 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/23 21:19:08 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brainfuck.h"

/**
 * Open source / asm / output files
 * 
 * @return On success return 0 else return an error code
 */
static int	open_files(t_bf *bf)
{
	if ((bf->source_fd = open(bf->source_file, O_RDONLY)) <= 0)
		return (ERROR_OPEN_SRC);
	if ((bf->asm_fd = open(ASM_TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0666)) <= 0)
		return (ERROR_OPEN_TMPASM);
	return (SUCCESS);
}

/**
 * Write error message in stderr
 * 
 * @param code The error code
 */
/*
#define ERROR_OPEN_SRC			-1
#define ERROR_OPEN_OUTPUT		-2
#define ERROR_OPEN_TMPASM		-3

#define ERROR_BAD_LOOP_CLOSE	-4
*/
static void print_error(t_bf *bf, int code)
{
	if (code == ERROR_OPEN_SRC)
		dprintf(STDERR_FILENO, "Can't open file %s\n", bf->source_file);
	else if (code == ERROR_OPEN_TMPASM)
		dprintf(STDERR_FILENO, "Can't create temporary file %s\n", ASM_TMP_FILE);
	else if (code == ERROR_BAD_LOOP_CLOSE)
		dprintf(STDERR_FILENO, "Syntax error at char %d - You are trying to close a loop who wasn't opened\n", bf->current_char);
	else if (code == ERROR_LOOP_CLOSE_MISSING)
		dprintf(STDERR_FILENO, "Error - Missing loop close\n");
}

/**
 * Initialise variables and
 * start the compilation process
 * Write success in stdout or failure in stderr
 * 
 * @param source_file Name of brainfuck source to compile
 * @param output_file Name of executable file to target
 */
void	compiler_start(char *source_file, char *output_file)
{
	t_bf		bf;
	int			fct_res;

	bzero(&bf, sizeof(t_bf));
	bf.source_file = source_file;
	bf.output_file = output_file;
	if ((fct_res = open_files(&bf)) == SUCCESS)
		fct_res = compiler_main(&bf);
	if (bf.current_loop != 0)
		fct_res = ERROR_LOOP_CLOSE_MISSING;
	if (fct_res < 0)
		print_error(&bf, fct_res);
	else
		compiler_link(&bf);
}
