/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:29:55 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/16 21:53:56 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

size_t  ft_strlen(const char *s);
int if_slash(char *str);
int if_space(char *str);
int ft_strncmp(char *s1, char *s2, size_t n);
char    *ft_strdup(char *src);
char    *ft_strjoin(char *s1, char *s2);
char    **find_sign_then_split(char *str);
char	**ft_split(char	const *s, char c);
void    free_split(char **str);
void    pipex(char **av, char **ev);
// void    pipex(int ac, char **av, char **ev);
void    exe_cmd(char *cmd, char **args, char **ev);
void    error_exit(char *msg);

#endif