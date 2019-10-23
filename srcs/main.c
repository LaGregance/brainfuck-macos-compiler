/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:38:41 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/23 18:44:24 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brainfuck.h"

/**
 * Show usage if need
 * 
 * @return Return TRUE if usage need to be shown
 */
int		usage(int argc, char **argv)
{
	if (argc == 2 || (argc == 4 && strcmp(argv[3], "-o") == 0))
		return (FALSE);
	printf("Usage: ./bfc <brainfuck source file> [-o <output file>\n");
	return (TRUE);
}

/**
 * @param source_file The source file path
 * @return source_file remplacing extension by .bf
 */
char	*get_output_file(char *source_file)
{
	char	*output;
	char	*ext;

	output = malloc(strlen(source_file) + 5);
	strcpy(output, source_file);

	ext = strrchr(output, '.');
	if (ext == NULL || strcmp(ext, ".out") == 0)
		ext = output + strlen(output);
	strcpy(ext, ".out");
	return (output);
}

int		main(int argc, char **argv)
{
	char	*source_file;
	char	*output_file;

	if (usage(argc, argv))
		return (0);
	source_file = argv[1];
	output_file = argc == 2 ? get_output_file(source_file) : strdup(argv[3]);
	compiler_start(source_file, output_file);
	free(output_file);
	return (0);
}
