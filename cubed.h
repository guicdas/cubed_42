/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:51:10 by mneves-l          #+#    #+#             */
/*   Updated: 2024/06/10 21:04:38 by jnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>

#define KEY_W 119
#define KEY_D 100
#define KEY_S 115
#define KEY_A 97
#define KEY_ESC 65307

#define RED 0xE40000
#define GREEN 0x3BFC3B
#define YELLOW 0xF4FF49
#define ORANGE 0xff8000

#define SCREENH 768
#define SCREENW 1024
#define TEXTURE_SIZE 64
#define PLAYER_SPEED 3
#define ROT_SPEED 0.08
#define MINISIZE 32

#define PI 3.14159265359
#define DR 0.0174533

#define HEXA "0123456789ABCDEF"
#define DECA "0123456789"

#define BUFFER_SIZE 20

typedef struct s_img
{
	int	*image;
	int	*addr;

	int	bpp;
	int	linesize;
	int	endian;

}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win_ptr;
	t_img	img;
	int		frames;
	int		screen_height;
	int		screen_width;
	int		**pixels;
	char	**textures;

	void	*wall;
	void	*exit;
	void	*empty;

	char	*map_no;
	char	*map_so;
	char	*map_we;
	char	*map_ea;
	int		map_f;
	int		map_c;
	int		map_x;
	int		map_y;
	int		map_h;
	int		map_w;
	char	**full_map;
	char	**map;

	double	player_x;
	double	player_y;
	double	player_a;
	double	player_dx;
	double	player_dy;
	float	player_speed;

	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		step_x;
	int		step_y;
	double	plane_x;
	double	plane_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;

	int		texture_size;
	double	step;
	double	pos;
	int		texture_x;
	int		texture_y;
	int		texture_index;

}	t_data;

t_data	*d(void);

//	get_next_line.c
char	*get_next_line(int fd);

//	lib_utils.c
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(const char *str);
void	ft_putendl_fd(char *s, int fd);

// utils.c
void	ft_bzero(void *s, size_t n);
void	draw_vertical_line(int x, int start, int end, int color);
int		put_b_nbr(unsigned long long nbr, char *b, size_t bs);
char	*convert(long long n, char *str, int bs, char *b);
char	*ft_itoa(long long n, int bs, char *b);

//	leave.c
void	error(char *s);
int		destroy_hook(void);
int		free_double_char(char **map);
int		free_double_int(int **map);

//	parsing_dir.c
void	parsing(char **av);
void	load_map(int fd, int fd2);
int		check_for_element(char *s);
char	*clean_string(char *s, int i, int flag);

//	debug.c
void	info_print(void);
void	map_print(void);
void	debug_dda(void);

//	parsing_map.c
int		check_char(char c);
void	map_check_matriz(void);
void	map_flood_fill(int x, int y, char **map, int size);

//	moves.c
int		move(int keypress);

//	hooks.c
int		movekey_hook(int keypress);

//	2drays.c
void	draw_map(void);
float	distance(float ax, float ay, float bx, float by);
void	draw_player_direction(int x1, int y1, int color);
//void	draw_horizontal_rays(void);

//	rays.c
void	update_textures(int x);
void	raycaster(void);

//	renders.c
void	render_frame(void);
void	print_minimap(void);

//	init.c
void	init_img(char *path);
void	init_values(void);
void	init_pixels(void);
void	init_dda(int x);

//	colors.c
int		limits_colors(char *s);