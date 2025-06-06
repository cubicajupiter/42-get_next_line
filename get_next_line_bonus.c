/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:21:44 by jvalkama          #+#    #+#             */
/*   Updated: 2025/06/06 15:38:17 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_buffers		*heads_array[FILDES_MAX];
	int						is_error;

	is_error = 0;
	if (fd < 0 || fd > FILDES_MAX)
		return (NULL);
	if (!heads_array[fd])
		is_error = ft_readtostring(&heads_array[fd], fd);
	else if (!heads_array[fd]->cut_i)
		is_error = ft_readtostring(&heads_array[fd], fd);
	if (is_error)
		return (NULL);
	if (heads_array[fd])
		return (ft_strjoin(&heads_array[fd]));
	return (NULL);
}
