/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:52:41 by ssuchane          #+#    #+#             */
/*   Updated: 2024/03/18 23:04:00 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fix_line(char *line)
{
	char	*holder;
	int		i;

	i = 0;
	holder = NULL;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	holder = ft_substr(line, i + 1, ft_strlen(line) + i);
	if (!holder)
		return (NULL);
	if (holder[0] == '\0')
	{
		free(holder);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (holder);
}

char	*fill_buffer(int fd, char *buffer, char *stash)
{
	int		read_bytes;
	char	*temp;

	read_bytes = 1;
	while (read_bytes)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (NULL);
		buffer[read_bytes] = '\0';
		if (read_bytes == 0)
			break ;
		if (stash == NULL)
			stash = ft_strdup("");
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free (temp);
		temp = NULL;
		if (!stash)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = fill_buffer(fd, buffer, stash);
	free(buffer);
	if (!line)
		return (NULL);
	stash = fix_line(line);
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;
// 	int		i;

// 	i = 0;
// 	fd = open("file.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		printf("Error opening file.\n");
// 		return (1);
// 	}
// 	while((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free (line);
// 	}
// 	// while (i < 6)
// 	// {
// 	// 	line = get_next_line(fd);
// 	// 	if (line == NULL)
// 	// 		return (0);
// 	// 	printf("%s", line);
// 	// 	free(line);
// 	// 	i++;
// 	// }
// 	close(fd);
// 	return (0);
// }
