/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_link.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 18:09:13 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/23 18:46:57 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brainfuck.h"
#include <errno.h>

static pid_t	fork_exit()
{
	pid_t	child_pid;
	
	if ((child_pid = fork()) < 0)
	{
		perror("Fork failure during linkage\n");
		exit(1);
	}
	return (child_pid);
}

/**
 * Fork the process 2 time to exec nasm and ld
 * Print error on stderr or success on stdin
 */
void	compiler_link(t_bf *bf)
{
	int		status = 0;
	pid_t	child_pid = fork_exit();

	if(child_pid == 0)
	{		
		child_pid = fork_exit();
		if(child_pid == 0)
		{
			if (execl("/usr/bin/nasm", "/usr/bin/nasm", "-f", "macho64", ASM_TMP_FILE, "-o", OUT_TMP_FILE, NULL) == -1)
				dprintf(STDERR_FILENO, "NASM failure (errno : %d)\n", errno);
			exit(0);
		}
		else
		{
			wait(&status);
			if (execl("/usr/bin/ld", "/usr/bin/ld", OUT_TMP_FILE, "-o", bf->output_file, "-macosx_version_min", "10.8", "-lSystem", NULL) == -1)
				dprintf(STDERR_FILENO, "Linkage failure (errno : %d)\n", errno);
			exit(0);
		}
	}
	wait(&status);
	unlink(ASM_TMP_FILE);
	unlink(OUT_TMP_FILE);
	printf("Writing binary file %s\n", bf->output_file);
}
