/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:52:01 by adriouic          #+#    #+#             */
/*   Updated: 2022/02/15 01:15:06 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"

int	get_width(char *fname)
{
	int		fd;
	char	*line;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
	{
		perror(NULL);
		close(fd);
		exit(0);
	}
	line = get_next_line(fd);
	close(fd);
	if (!line)
	{
		ft_putstr_fd("No data found.", 2);
		exit(0);
	}
	return (count_elements(line));
}

int	get_heigth(char *fname, int width)
{
	int		fd;
	int		heigth;
	char	*line;

	fd = open(fname, O_RDONLY);
	line = get_next_line(fd);
	heigth = 0;
	while (line)
	{
		if (count_elements(line) != width)
		{
			ft_putstr_fd("Found wrong line length. Exiting.\n", 2);
			exit(0);
		}
		heigth += 1;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (heigth);
}

int	free_previous(t_point **matrix, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(matrix[j]);
	free(matrix);
	return (0);
}

int	verify_extention(char *s)
{
	int		len_s;
	int		i;
	char	*extention;

	i = 3;
	extention = ".fdf";
	len_s = ft_strlen(s);
	if (len_s < 3)
		return (0);
	len_s--;
	while (i >= 0)
	{
		if (s[len_s] != extention[i])
		{
			ft_putstr_fd("File may be wrongly formated.", 2);
			ft_putstr_fd("use the ones with (.fdf) extention!\n", 2);
			return (0);
		}
		len_s--;
		i--;
	}
	return (1);
}
