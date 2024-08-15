/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 08:15:20 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/15 16:39:40 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_fill(int fd, char *readed, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(readed);
			return (0);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		if (!readed)
			readed = ft_strdup("");
		temp = readed;
		readed = ft_strjoin(temp, buffer);
		free (temp);
		temp = 0;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (readed);
}

char	*ft_set_line(char *line)
{
	char	*readed;
	ssize_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0 || line[1] == 0)
		return (0);
	readed = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*readed == 0)
	{
		free(readed);
		readed = 0;
	}
	line[i + 1] = 0;
	return (readed);
}

char	*get_next_line(int fd)
{
	static char	*readed;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		free(readed);
		readed = 0;
		buffer = 0;
		return (0);
	}
	if (!buffer)
		return (0);
	line = ft_fill(fd, readed, buffer);
	free(buffer);
	buffer = 0;
	if (!line)
		return (0);
	readed = ft_set_line(line);
	return (line);
}
