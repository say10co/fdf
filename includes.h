#ifndef INCLUDES_H
# define INCLUDES_H


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

}t_point;

typedef struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;	
	int		color;
}t_window;

typedef struct s_params
{
	t_point	**matrix;
	t_window window;
	int		x;
	int		y;
	int		t;
}t_params;

t_point **parser(char *file_name, int *y, int *x);
#endif
