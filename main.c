/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:29:38 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/15 14:26:49 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// char    *extract_dir(char *file)
// {
//     char    *ext_name;
//     int    slash;
//     int i;

//     slash = ft_strlen(file) - 1;
//     while(slash >= 0 && file[slash] != '/')
//         slash--;
//     if (slash < 0)
//         return (ft_strdup("."));
//     else if (slash == 0)
//         return (ft_strdup("/"));
//     else
//     {
//         ext_name = malloc(sizeof(char) * (slash + 1));
//         if (!ext_name)
//             return (NULL);
//         i = 0;
//         while (i < slash)
//         {
//             ext_name[i] = file[i];
//             i++;
//         }
//         ext_name[i] = '\0';
//     }
//     return (ext_name);
// }

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
    // if (access(outfile, F_OK) == -1)
    // {
    //     if ((access(extract_dir(outfile), W_OK) == -1))
    //     {
    //         free(extract_dir(outfile));
    //         perror("Cannot creat outfile in current directory");
    //         return (-1);
    //     }
    // }
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
    if (!argv[1] || !argv[4])
        return (1);
    if (check_access(argv[1], argv[4]) == -1)
        return (1);
    // if (check_cmd(argv[2]) == 0 || check_cmd(argv[3]) == 0)
    //     return (1);
    pipex(argv, envp);
    return (0);
}