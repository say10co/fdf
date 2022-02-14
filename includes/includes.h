/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 22:12:26 by adriouic          #+#    #+#             */
/*   Updated: 2022/02/14 22:19:40 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

//=-----------=Keys=--------------=//
# define UP_KEY 126
# define C_KEY 8
# define DOWN_KEY 125
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define PLUS_KEY 30
# define MINUS_KEY 44
# define Q_KEY 12
# define X_KEY 7
# define Z_KEY 6
# define W_KEY 13
# define ESCAPE_KEY 53
# define A_KEY 0
# define S_KEY 1
# define ORANGE 14546242
# define DEFAULT_COLOR 13720351

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>

# define BUFFER_SIZE 1

typedef struct s_point
{
	float		x;
	float		y;
	float		z;
	int			color;
}t_point;

typedef struct s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;

}t_img;

typedef struct s_window
{
	double	angle_of_view;
	void	*mlx_ptr;
	void	*win_ptr;	
	int		win_width;
	int		win_higth;
	int		nb_lines;
	int		line_width;
	int		shift_x;
	int		shift_y;
	int		z_scale;
	int		isometric;
	int		zoom;
	int		color_diff;
	int		change_color;
	int		slop;
	int		t;
	t_img	*img;
	t_point	**matrix;
}t_window;

int				my_abs(int a);
int				close_(void *null);
int				key_handler(int k, void *params);
int				get_color(char *s);
int				get_index(char c);
int				switch_(int x);

void			drow(t_point **matrix, t_window *win);
void			set_default(t_window *base_values);
void			zoom_isometric_shift(t_point *p0, t_point *p1, t_window win);

unsigned int	hex_to_int(char *s);

t_point			**parser(char *file_name, int *y, int *x);
t_point			**alloacte_fill(char *file_name, int *y, int *x);

#endif
