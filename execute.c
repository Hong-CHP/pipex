/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:40:13 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/12 17:30:09 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    **extract_path(char **ev)
{
    int i;

    i = 0;
    while (ev[i])
    {
        if (ft_strcmp("PATH=", ev[i]) == 0)
            return (find_sign_then_split(ev[i] + 5));
        i++;
    }
    return (NULL);
}

//split is allocated, need to be free after
//strjoin is allocated, need to be free after
//malloc
char    *find_exe_path(char *cmd, char **args, char **ev)
{
    char    *path;
    char    *exe_path;
    char    **ev_path;
    char    *temp;
    int i;

    ev_path = extract_path(ev);
    i = 0;
    while (ev_path[i])
    {
        if (if_slash(cmd) < 1)
        {
            temp = ft_strjoin("/", args[0]);
            path = ft_strjoin(ev_path[i], temp);
            free(temp);
        }
        else
            path = ft_strjoin(ev_path[i], args[0]);
        if (access(path, X_OK) == 0)
        {
            exe_path = ft_strdup(path);
            free(path);
            free_split(ev_path);
            return (exe_path);
        }
        free(path);
        i++;
    }
    free_split(ev_path);
    return (NULL);
}

void    exe_cmd(char *cmd, char **args, char **ev)
{
    char    *exe_path;

    if (if_slash(cmd) > 1)
    {
        if (access(cmd, X_OK) == 0)        
            exe_path = ft_strdup(cmd);
        else
        {
            perror("Error");
            exit(1);
        }
    }
    else
    {
        exe_path = find_exe_path(cmd, args, ev);
        if (!exe_path)
        {
            perror("Error");
            exit(1);
        }
    }
    execve(exe_path, args, ev);
    perror("No vailable path");
    free(exe_path);
    free(args);
    exit(1);
}
