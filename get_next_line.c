/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangchpa <sangchpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:50:05 by sangchpa          #+#    #+#             */
/*   Updated: 2021/02/05 16:40:45 by sangchpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		find_nidx(char *backup_buf)
{
	int			idx;

	idx = 0;
	while (backup_buf[idx] != '\0')
	{
		if (backup_buf[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}

static int		give_line(char **backup_buf, char **line, int n_idx)
{
	char		*temp;

	(*backup_buf)[n_idx] = '\0';
	*line = ft_strdup(*backup_buf);
	if (*(*backup_buf + n_idx + 1) != '\0')
	{
		temp = ft_strdup(*backup_buf + n_idx + 1);
		free(*backup_buf);
		*backup_buf = temp;
	}
	else
	{
		free(*backup_buf);
		*backup_buf = 0;
	}
	return (1);
}

static int		last_backup_buf(char **backup_buf, char **line, int read_byte)
{
	int			n_idx;

	if (read_byte < 0)
		return (-1);
	if (*backup_buf)
	{
		if ((n_idx = find_nidx(*backup_buf)) >= 0)
			return (give_line(backup_buf, line, n_idx));
		else
		{
			*line = ft_strdup(*backup_buf);
			free(*backup_buf);
			*backup_buf = 0;
			return (0);
		}
	}
	else
		*line = ft_strdup("");
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static char	*backup_buf[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	int			read_byte;
	int			n_idx;

	if ((fd < 0) || !line || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (-1);
	while ((read_byte = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_byte] = '\0';
		if (backup_buf[fd] == 0)
			backup_buf[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(backup_buf[fd], buf);
			free(backup_buf[fd]);
			backup_buf[fd] = tmp;
		}
		if ((n_idx = find_nidx(backup_buf[fd])) >= 0)
			return (give_line(&backup_buf[fd], line, n_idx));
	}
	return (last_backup_buf(&backup_buf[fd], line, read_byte));
}
