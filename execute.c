/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:40:13 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/15 15:12:54 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    **extract_path(char **ev)
{
    int i;
	char	**paths;
	
    i = 0;
    while (ev[i])
    {
        if (ft_strncmp("PATH=", ev[i], 5) == 0)
		{
			paths = find_sign_then_split(ev[i] + 5);
            return (paths);
		}
        i++;
    }
    return (NULL);
}

char    *find_exe_path(char **args, char **ev)
{
    char    *path;
    char    *exe_path;
    char    **ev_path;
    char    *temp;
    int i;

    path = NULL;
    temp = NULL;
    exe_path = NULL;
    ev_path = extract_path(ev);
    if (!ev_path)
        return (NULL);
    i = 0;
    while (ev_path[i])
    {
        temp = ft_strjoin("/", args[0]);
		if (!temp)
		{
			free_split(ev_path);
			return (NULL);
		}
        path = ft_strjoin(ev_path[i], temp);
        free(temp);
        if (path)
        {
            if (access(path, X_OK) == 0)
			{
                exe_path = ft_strdup(path);
				free(path);
				break;
			}
			free(path);
        }
        i++;
    }
    free_split(ev_path);
    return (exe_path);
}

void    exe_cmd(char *cmd, char **args, char **ev)
{
    char    *exe_path;

    exe_path = NULL;
    if (if_slash(cmd) > 1)
    {
        if (access(cmd, X_OK) == 0)        
            exe_path = ft_strdup(cmd);
        else
        {
            perror("Error");
            free_split(args);
            exit(1);
        }
    }
    else
    {
        exe_path = find_exe_path(args, ev);
        if (!exe_path)
        {
            perror("Error");
            free_split(args);
            exit(1);
        }
    }
    execve(exe_path, args, ev);
    perror("No vailable path");
    free(exe_path);
    free_split(args);
    exit(1);
}
