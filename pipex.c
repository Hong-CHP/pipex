/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:49:16 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/13 11:35:00 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	make_pipe_child1(int infile, char *cmd1, char **ev, int pipefd[])
{
	pid_t	pid;
	char	**args;
	
	pid = fork();
	if (pid < 0)
		error_exit("Fork error");
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(infile, 0);
		close(infile);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		args = find_sign_then_split(cmd1);
		if (!args || !args[0])
		{
			fprintf(stderr, "Invalid command: %s\n", cmd1);
			exit(127);
		}
		fprintf(stderr, "Executing cmd1: %s\n", cmd1);
		exe_cmd(cmd1, args, ev);
	}
	return (pid);
}

pid_t	make_pipe_child2(int outfile, char *cmd2, char **ev, int pipefd[])
{
	pid_t	pid;
	char	**args;
	
	pid = fork();
	if (pid < 0)
		error_exit("Fork error");
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		dup2(outfile, 1);
		close(outfile);
		args = find_sign_then_split(cmd2);
			if (!args || !args[0])
		{
			fprintf(stderr, "Invalid command: %s\n", cmd2);
			exit(127);
		}
		fprintf(stderr, "Executing cmd2: %s\n", cmd2);
		exe_cmd(cmd2, args, ev);
	}
	return (pid);
}

void	creat_pipe(int infile, int outfile, char **av, char **ev)
{
	int	pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
	{
		close(infile);
		close(outfile);
		error_exit("Pipe error");
	}
	pid1 = make_pipe_child1(infile, av[2], ev, pipefd);
	pid2 = make_pipe_child2(outfile, av[3], ev, pipefd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	close(pipefd[0]);
	close(pipefd[1]);
}

void    pipex(char **av, char **ev)
{
	int	infile;
	int	outfile;

	infile = open(av[1], O_RDONLY);
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
		error_exit("Display file error");
	creat_pipe(infile, outfile, av, ev);
	close(infile);
	close(outfile);
}
