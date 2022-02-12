#ifndef INCLUDES_H
# define INCLUDES_H

//=-----------=Keys=--------------=//
# define up 126
# define down 125
# define left 123
# define right 124
# define zoom_in 44
# define zoom_out 30
# define reset 12
# define z_up 7
# define z_down 6
# define tow_d 13
# define escap 53
# define rotate_left 0
# define rotate_right 1

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
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
    double		angle;
    int			xshift;
    int			yshift;
    int			depth;
    int			z_z;
    int			iso;
    int			sizex;
    int			sizey;
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
	void	*mlx_ptr;
	void	*win_ptr;	
	int		color;
	int			width;
	int			higth;
	t_img		*img;

}t_window;

typedef struct s_params
{
	t_point	**matrix;
	t_window window;
	int		x;
	int		y;
	int		t;
	t_point		*v;
}t_params;


int    		my_abs(int a);
int		close_(void     *null);
int		key_handler(int k, void *params);
void		drow(t_point **matrix, t_window win, int y, int x, t_point *p_base);
void    	set_default(t_point *p_base);
void    	zoom_isometric_shift(t_point *p0, t_point *p1,t_point *p_base);
unsigned int 	hex_to_int(char *s);
int     	get_index(char c);
t_point 	**parser(char *file_name, int *y, int *x);
#endif
