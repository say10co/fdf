/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:12:30 by adriouic          #+#    #+#             */
/*   Updated: 2022/02/13 19:12:35 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

int	get_index(char c)
{
	char *radi_x;
	char *radi_X;
	int	i;

	i = 0;
	radi_x = "0123456789abcedf";
	radi_X = "0123456789ABCDEF";
	while (radi_x[i])
	{	
		if (radi_x[i] == c || radi_X[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

unsigned int hex_to_int(char *s)
{
	int		i;
       	unsigned int	result;

	result = 0;
	i= 2;
	if (!s)
		return (16777215);
	while (s[i])
		result = result * 16 + get_index(s[i++]);
	return (result);
}
