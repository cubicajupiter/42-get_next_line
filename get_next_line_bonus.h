/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:11:41 by jvalkama          #+#    #+#             */
/*   Updated: 2025/06/06 14:37:08 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# define BUFF_SIZE BUFFER_SIZE

# define COUNT_TOTAL 1
# define IS_NEW_HEAD 1
# define IS_NEW_TAIL 0
# define COUNT_CUTOFF 0
# define NO_LINE_END 0
# define FILDES_MAX 256

#include <stdlib.h>
#include <unistd.h>

typedef struct s_list
{
	char				*str;
	struct s_list		*next;
	int					len;
	int					cut_i;
}	t_buffers;

char		*get_next_line(int fd);
int			ft_readtostring(t_buffers **head, int fd);
char		*ft_strjoin(t_buffers **head);
int			ft_lengths(t_buffers *node, int is_totalcount);
int			ft_appendtail(t_buffers **head, char *str, int len, int is_newhead);
void		ft_freenodes(t_buffers **head);

#endif
