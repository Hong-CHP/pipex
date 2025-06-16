/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:59:50 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/16 21:52:54 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int if_space(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
                return (1);
        i++;
    }
    return (0);
}

void    error_exit(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

char    *ft_strjoin(char *s1, char *s2)
{
    char    *res;
    int i;
    int j;
    
    if (!s1 || !s2)
        return (NULL);
    res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!res)
        return (NULL);
    i = 0;
    while (s1[i])
    {
        res[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
    {
        res[i] = s2[j];
        i++;
        j++;
    }
    res[i] = '\0';
    return (res);
}

char    *ft_strdup(char *src)
{
    int i;
    char    *dst;

    dst = malloc(sizeof(char) * (ft_strlen(src) + 1));
    if (!dst)
        return (NULL);
    i = 0;
    while (src[i])
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}