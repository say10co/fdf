/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:13:16 by adriouic          #+#    #+#             */
/*   Updated: 2022/02/15 00:35:56 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

int	count_elements(char *line)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_split(line, ' ');
	while (str[i])
		free(str[i++]);
	free(str);
	free(line);
	return (i);
}

t_point	**allocate(int h, int w)
{
	t_point	**matrix;
	int		i;

	i = 0;
	matrix = (t_point **)(malloc(sizeof(t_point *) * h + 1));
	if (!matrix)
		return (0);
	while (i < h)
	{
		matrix[i] = (t_point *)(malloc(sizeof(t_point) * w));
		if (!(matrix[i]))
		{
			free_previous(matrix, i);
			return (0);
		}
		i++;
	}
	matrix[i] = 0;
	return (matrix);
}

void	fill_matrix(int y, char *line, t_point **matrix)
{
	char	**s;
	int		i;

	i = 0;
	s = ft_split(line, ' ');
	while (s && s[i])
	{
		matrix[y][i].x = i;
		matrix[y][i].y = y;
		matrix[y][i].z = ft_atoi(s[i]);
		matrix[y][i].color = get_color(s[i]);
		free(s[i]);
		i++;
	}
	free(s);
	free(line);
}

t_point	**alloacte_fill(char *file_name, int *y, int *x)
{
	t_point	**matrix;
	int		i;
	int		fd;
	char	*line;

	*x = get_width(file_name);
	*y = get_heigth(file_name, *x);
	ft_putstr_fd("Allocating memory...\n", 1);
	matrix = allocate(*y, *x);
	if (!matrix)
		return (0);
	i = 0;
	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	ft_putstr_fd("Filling The grid...\n", 1);
	while (line)
	{
		fill_matrix(i, line, matrix);
		i += 1;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (matrix);
}
