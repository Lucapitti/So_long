/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittigl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:23:38 by lpittigl          #+#    #+#             */
/*   Updated: 2024/03/08 19:43:15 by lpittigl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	recover_mem(char **s, char **mem)
{
	int	i;

	i = 0;
	*s = (char *)malloc(len(*mem) + 1);
	if (!s)
		return (1);
	if (!s)
		return (0);
	ft_strlcpy(*s, *mem, BUFFER_SIZE);
	free (*mem);
	while ((*s)[i] != 0)
	{
		if ((*s)[i] == '\n' || (*s)[i] == -1)
		{
			*mem = ft_substr(*s, i + 1, len(*s) - (i), 0);
			*s = ft_substr(*s, 0, i + 1, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	read_form_file(char **s, int fd, ssize_t i)
{
	int		bytes_read;
	char	*c;

	bytes_read = 1;
	while (bytes_read)
	{
		i = 0;
		c = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!c)
			return (-1);
		bytes_read = read(fd, c, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(c);
			break ;
		}
		c[bytes_read] = 0;
		*s = ft_strjoin(*s, c, 0, 0);
		while (i < bytes_read)
			if (c[i++] == '\n')
				bytes_read = 0;
		free(c);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*mem;
	char		*s;
	size_t		check;

	s = NULL;
	if (fd < 0 || fd >= 1000 || BUFFER_SIZE <= 0)
		return (NULL);
	if (mem)
	{
		if (*mem == '\0')
			free(mem);
		else if (recover_mem(&s, &mem))
			return (s);
	}
	read_form_file(&s, fd, 0);
	check = 0;
	while (s != NULL && *(s + check) != 0
		&& *(s + check) != '\n' && *(s + check) != -1)
		check++;
	mem = ft_substr(s, check + 1, len(s) - (check), 0);
	return (ft_substr(s, 0, check + 1, 1));
}
