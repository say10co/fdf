/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:12:30 by adriouic          #+#    #+#             */
/*   Updated: 2022/02/14 05:40:37 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

int	get_index(char c)
{
	char	*radi_x;
	char	*radi_x1;
	int		i;

	i = 0;
	radi_x = "0123456789abcedf";
	radi_x1 = "0123456789ABCDEF";
	while (radi_x[i])
	{	
		if (radi_x[i] == c || radi_x1[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

unsigned int	hex_to_int(char *s)
{
	int				i;
	unsigned int	result;

	result = 0;
	i = 2;
	if (!s)
		return (16777215);
	while (s[i])
		result = result * 16 + get_index(s[i++]);
	return (result);
}

int	get_color(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != ',')
		i++;
	if (s[i] == ',')
		return (hex_to_int(s + i +1));
	else
		return (16777215);
}

t_point	**parser(char *file_name, int *y, int *x)
{
	return (alloacte_fill(file_name, y, x));
}
