/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:29:55 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/12 17:41:35 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

size_t  ft_strlen(const char *s);
int if_slash(char *str);
int ft_strcmp(char *s1, char *s2);
char    *ft_strdup(char *src);
char    *ft_strjoin(char *s1, char *s2);
char    **find_sign_then_split(char *str);
char	**ft_split(char	const *s, char c);
void    free_split(char **str);
void    error_exit(char *msg);

#endif