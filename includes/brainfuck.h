/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brainfuck.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:38:02 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/23 18:43:08 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAINFUCK_H
#define BRAINFUCK_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <libc.h>

#define BUFFER_SIZE	4096

#define TRUE	1
#define FALSE	0

#define ASM_TMP_FILE "tmp_asm_file_for_brainfuck_compiler.s"
#define OUT_TMP_FILE "tmp_asm_file_for_brainfuck_compiler.o"

#define SUCCESS						0

#define ERROR_OPEN_SRC				-1
#define ERROR_OPEN_TMPASM			-2

#define ERROR_BAD_LOOP_CLOSE		-3
#define ERROR_LOOP_CLOSE_MISSING	-4

typedef struct	s_bf
{
	char	*source_file;
	char	*output_file;
	int		source_fd;
	int		asm_fd;

	int		current_loop;
	int		current_char;
}				t_bf;

typedef struct	s_fct_dispatch
{
	char	c;
	int		(*fct)(t_bf*);
}				t_fct_dispatch;


void	compiler_start(char *source_file, char *output_file);
int		compiler_main(t_bf *bf);

void	compiler_write_header(t_bf *bf);
void	compiler_write_footer(t_bf *bf);
int		compiler_dispatch_char(t_bf *bf, char c);
void	compiler_link(t_bf *bf);

int		compiler_write_inc_ptr(t_bf *bf);
int		compiler_write_dec_ptr(t_bf *bf);
int		compiler_write_inc_value(t_bf *bf);
int		compiler_write_dec_value(t_bf *bf);
int		compiler_write_print(t_bf *bf);
int		compiler_write_open_loop(t_bf *bf);
int		compiler_write_close_loop(t_bf *bf);

#endif
