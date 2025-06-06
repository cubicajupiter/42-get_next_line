/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:25:47 by jvalkama          #+#    #+#             */
/*   Updated: 2025/06/04 11:55:37 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_readtostring(t_buffers **head, int fd)
{
	char			*string;
	int				len;
	int				i;
	int				cutoff;

	cutoff = NO_LINE_END;
	while (!cutoff)
	{
		i = 0;
		string = malloc((BUFF_SIZE + 1) * sizeof(char));
		if (!string)
			return (1);
		while (i <= BUFF_SIZE)
			string[i++] = 0;
		len = read(fd, string, BUFF_SIZE);
		if (len < 0)
		{
			free(string);
			return (1);
		}
		else if (len == 0)
		{
			free(string);
			break;
		}
		cutoff = ft_appendtail(head, string, len, IS_NEW_TAIL);
		//if (cutoff < 0)
		//	return (1);
	}
	return (0);
}

int		ft_appendtail(t_buffers **head, char *str, int len, int is_newhead)
{
	t_buffers	*new_node;
	t_buffers	*tmp;

	new_node = malloc(sizeof(t_buffers));
	if (!new_node)
		return (-1); //different handling maybe
	new_node->str = str;
	new_node->len = len;
	new_node->cut_i = ft_lengths(new_node, COUNT_CUTOFF);
	new_node->next = NULL;
	if (*head == NULL || is_newhead)
		*head = new_node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (new_node->cut_i);
}

char	*ft_strjoin(t_buffers **head)
{
	char			*newstr;
	t_buffers		*tmp;
	int				total_len;
	int				i;
	int				j;

	total_len = ft_lengths(*head, COUNT_TOTAL);
	newstr = malloc((total_len + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	j = 0;
	tmp = *head;
	while (tmp)
	{
		i = 0;
		while ((!tmp->cut_i && i < tmp->len) || (tmp->cut_i && i < tmp->cut_i))
			newstr[j++] = tmp->str[i++];
		tmp = tmp->next;
	}
	newstr[j] = '\0';
	ft_freenodes(head);
	return (newstr);
}

int	ft_lengths(t_buffers *node, int is_totalcount)
{
	int			cutoff_i;
	int			total_len;

	if (!is_totalcount)
	{
		cutoff_i = 0;
		while (cutoff_i < node->len)
		{
				if (node->str[cutoff_i] == '\n' || node->str[cutoff_i] == '\0')
					return (cutoff_i + 1);
				cutoff_i++;
		}
		return (NO_LINE_END);
	}
	total_len = 0;
	while (node)
	{
		if (node->cut_i)
			total_len += node->cut_i;
		else
			total_len += node->len;
		node = node->next;
	}
	return (total_len);
}

void	ft_freenodes(t_buffers **head)
{
	t_buffers	*tmp;
	char		*new_headstr;
	int			new_len;
	int			i;

	while (*head)
	{
		tmp = *head;
		if ((*head)->cut_i && (*head)->cut_i < (*head)->len) // this used to be ((*head)->cut_i < BUFF_SIZE)
		{
			i = 0;
			new_len = (*head)->len - (*head)->cut_i;
			new_headstr = malloc((new_len + 1) * sizeof(char));
			while (i < new_len)
				new_headstr[i++] = (*head)->str[(*head)->cut_i++];
			ft_appendtail(head, new_headstr, new_len, IS_NEW_HEAD);
			free(tmp->str);
			free(tmp);
			break;
		}
		*head = (*head)->next;
		free(tmp->str);
		free(tmp);
	}
}
