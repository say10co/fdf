#ifndef INCLUDES_H
# define INCLUDES_H

//=-----------=Keys=--------------=//
# define up_key 126
# define c_key 8
# define down_key 125
# define left_key 123
# define right_key 124
# define plus_key 30
# define minus_key 44
# define q_key 12
# define x_key 7
# define z_key 6
# define w_key 13
# define escap_key 53
# define a_key 0
# define s_key 1

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

typedef struct	s_img
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
	t_img	*img;
	t_point	**matrix;


}t_window;


unsigned int 	hex_to_int(char *s);
int    			my_abs(int a);
int				close_(void     *null);
int				key_handler(int k, void *params);
int				get_color(char *s);
void			drow(t_point **matrix, t_window *win);
void    		set_default(t_window *base_values);
void    		zoom_isometric_shift(t_point *p0, t_point *p1, t_window win);
int     		get_index(char c);
t_point 		**parser(char *file_name, int *y, int *x);
t_point			**alloacte_fill(char *file_name, int *y, int *x);
#endif
