/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:29:38 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/16 21:54:26 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int check_access(char *infile, char *outfile)
{
    if (access(infile, F_OK) == -1)
    {
        perror("Infile does not exist");
        return (-1);
    }
    if (access(infile, R_OK) == -1)
    {
        perror("Infile has not read permission");
        return (-1);
    }
    if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
    {
        perror("Outfile permission denied");
        return (-1);
    }
    return (0);
}

int main(int argc, char *argv[], char **envp)
{    
    if (argc != 5)
        return (1);
    // if (argc < 5)
    // {
    //     perror("Not enough parameters");
    //     return (1);
    // }
    // if (!argv[1] || !argv[argc - 1])
    //     return (1);
    // if (check_access(argv[1], argv[argc - 1]) == -1)
    //     return (1);
    if (!argv[1] || !argv[4])
        return (1);
    if (check_access(argv[1], argv[4]) == -1)
        return (1);
    pipex(argv, envp);
    // pipex(argc, argv, envp);
    return (0);
}