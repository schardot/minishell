/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:58:48 by nataliascha       #+#    #+#             */
/*   Updated: 2024/10/24 18:37:03 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			linelen;

	linelen = 0;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[0] != '\0')
	{
		line = ft_rrealloc(line, (linelen) + BUFFER_SIZE + 1);
		line = append_buffer(buffer, line, &linelen);
	}
	if (line && line[linelen - 1] == '\n')
		return (line);
	line = getmyline(line, buffer, fd, &linelen);
	return (line);
}
