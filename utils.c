/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:49:17 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/15 15:04:49 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t  ft_strlen(const char *s)
{
    size_t  len;

    len = 0;
    while(s[len])
        len++;
    return (len);
}

char    **find_sign_then_split(char *str)
{
    int i;
    char    **res;
    char    sep;
    
    sep = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        {
            sep = str[i];
            break;
        }
        else if (str[i] == ':')
        {
            sep = str[i];
            break;
        }
        i++;
    }
    if (sep != 0)
        res = ft_split(str, sep);
    return (res);
}

int if_slash(char *str)
{
    int i;
    int count;
    
    count = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '/')
            count++;
        i++;
    }
    return (count);
}

int ft_strncmp(char *s1, char *s2, size_t n)
{
    size_t  i;

    i = 0;
    while (*s1 && *s2 && i < n)
    {
        if (*s1 != *s2)
            return ((unsigned char)*s1 - (unsigned char)*s2);
        s1++;
        s2++;
        i++;
    }
    if (i < n)
        return ((unsigned char)*s1 - (unsigned char)*s2);
    return (0);
}

void    free_split(char **str)
{
    int i;

    i = 0;
    if (!str)
        return ;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}
