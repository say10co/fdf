/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:13:16 by adriouic          #+#    #+#             */
/*   Updated: 2022/02/14 20:23:53 by adriouic         ###   ########.fr       */
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
	return (i);
}

int	*get_heigth_width(char *fname)
{
	int		fd;
	int		*h_w;
	char	*line;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
	{	
		ft_putstr_fd("[Error]:Cant open file\n", 2);
		exit(0);
	}
	h_w = (int *)malloc(sizeof(int) * 2);
	line = get_next_line(fd);
	h_w[0] = count_elements(line);
	h_w[1] = 0;
	while (line)
	{
		h_w[1] += 1;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (h_w);
}

t_point	**allocate(int	*h_w)
{
	t_point	**matrix;
	int		i;

	i = 0;
	matrix = (t_point **)(malloc(sizeof(t_point *) * h_w[1] + 1));
	while (i < h_w[1])
	{
		matrix[i] = (t_point *)(malloc(sizeof(t_point) * h_w[0]));
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
	while (s[i])
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
	int		*h_w;
	int		fd;
	char	*line;

	h_w = get_heigth_width(file_name);
	matrix = allocate(h_w);
	*x = h_w[0];
	h_w[0] = 0;
	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		fill_matrix(h_w[0], line, matrix);
		h_w[0] += 1;
		line = get_next_line(fd);
	}
	*y = h_w[0];
	free(h_w);
	close(fd);
	return (matrix);
}
