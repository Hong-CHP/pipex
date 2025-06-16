/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:49:16 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/16 21:52:22 by hporta-c         ###   ########.fr       */
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
		// int i = 0;
		// while (args[i])
		// 	fprintf(stderr, "args cmd1 are : %s\n", args[i++]);
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
		// int i = 0;
		// while (args[i])
		// 	fprintf(stderr, "args cmd2 are : %s\n", args[i++]);
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
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

// void	close_childs_fd(int *prev_pipe, int pipefd[], int i, int nb_cmds)
// {
// 	if (*prev_pipe != -1)
// 		close(*prev_pipe);
// 	if (i != nb_cmds - 1)
// 	{
// 		close (pipefd[0]);
// 		close(pipefd[1]);
// 	}
// }

// void	close_parents_fd(int *prev_pipe, int pipefd[], int i, int nb_cmds)
// {
// 	if (*prev_pipe != -1)
// 		close(*prev_pipe);
// 	if (i != nb_cmds - 1)
// 	{
// 		close(pipefd[1]);
// 		*prev_pipe = pipefd[0];
// 	}
// }

// void	pipe_in_childs(int files[], int pipefd[], int i, int *prev_pipe)
// {
// 	if (i == 0)
// 	{
// 		dup2(files[0], 0);
// 		close(files[0]);
// 	}
// 	else
// 		dup2(*prev_pipe, 0);
// }

// void	pipe_out_childs(int files[], int pipefd[], int i, int nb_cmds)
// {
// 	if (i != nb_cmds - 1)
// 		dup2(pipefd[1], 1);
// 	else
// 	{
// 		dup2(files[1], 1);
// 		close(files[1]);
// 	}
// }

// void	creat_pipe(int files[], int ac, char **av, char **ev)
// {
// 	int	pipefd[2];
// 	int	prev_pipe;
// 	int	i;
// 	pid_t	pid;
// 	// char	**args;
	
// 	prev_pipe = -1;
// 	i = 0;
// 	while (i < ac - 3)
// 	{
// 		if (i != ac - 4 && pipe(pipefd) == -1)
// 			error_exit("Pipe error", files[0], files[1]);	
// 		pid = fork();
// 		if (pid < 0)
// 			error_exit("Fork error", files[0], files[1]);
// 		if (pid == 0)
// 		{
// 			pipe_in_childs(files, pipefd, i, &prev_pipe);
// 			pipe_out_childs(files, pipefd, i, ac - 3);
// 			close_childs_fd(&prev_pipe, pipefd, i, ac - 3);
// 			// args = find_sign_then_split(av[i + 2]);
// 			exe_cmd(av[i + 2], find_sign_then_split(av[i + 2]), ev);
// 		}
// 		close_parents_fd(&prev_pipe, pipefd, i, ac - 3);
// 		i++;
// 	}
// }

// void    pipex(int ac, char **av, char **ev)
// {
// 	int	infile;
// 	int	outfile;
// 	int files[2];
	
// 	infile = open(av[1], O_RDONLY);
// 	outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (infile < 0 || outfile < 0)
// 		error_exit("Display file error", infile, outfile);
// 	files[0] = infile;
// 	files[1] = outfile;
// 	creat_pipe(files, ac, av, ev);
// 	while (wait(NULL) > 0)
// 		;
// 	close(files[0]);
// 	close(files[1]);	
// 	close(infile);
// 	close(outfile);
// }

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
