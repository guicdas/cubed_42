/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:51:10 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/01 21:52:51 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <X11/X.h>

# include "minilibx-linux/mlx.h"
# include "defs_and_structs.h"

typedef struct s_img
{
	void	*image;
	int		*addr;

	int		bpp;
	int		linesize;
	int		endian;

}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win_ptr;
	t_header file_header[6];
	//int		last_mouse_x;
	char	*map_no;
	char	*map_so;
	char	*map_we;
	char	*map_ea;
	char	*map_f;
	char	*map_c;
	int		hex_floor;
	int		hex_ceiling;
	int		settings_flag;

	int		moves;
	int		screen_height;
	int		screen_width;
	int		**pixels;
	int		**textures;
	int		info_count;
	int		n_player;
	int		n_info;
	int		mmap_s_h;
	int		mmap_s_w;
	t_img	wall;
	t_img	exit;
	t_img	floor;
	int		map_x;
	int		map_y;
	int		map_h;
	int		map_w;
	char	**full_map;
	char	**map;
	int		max_x;
	int		init_map_flag;

	double	player_x;
	double	player_y;
	double	player_a;
	double	player_dx;
	double	player_dy;
	double	p_speed;

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
	double	line_height;
	int		draw_start;
	int		draw_end;

	int		texture_w;
	int		texture_h;
	double	step;
	double	pos;
	int		texture_x;
	int		texture_y;
	int		texture_index;

}	t_data;

t_data	*d(void);
void	parse_map(char **av);
int		get_color_rgb(char *str);
int		verify_map_header(char *s);
void	error(char *s);
void	leave(void);
void	initialize_data(void);
int		mouse_move(int x, int y, void *param);
void	free_double(void **map);
void	rotate(int keypress);
void	move(int keypress);
void	move_sideways(int keypress);
int		movekey_hook(int keypress);
int		destroy_hook(void);
void	load_map_body(void);

//	ft_utils.c
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_strlen_array(char **str);
void	ft_putendl_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
char	*get_next_line(int fd);


char	**ft_split(char const *s, char *c);
char	*ft_itoa(long long n, int bs, char *b);
char	*clean_string(char *s, int i, int flag);

//	DEBUG
void	info_print(void);
void	map_print(void);
void	debug_dda(void);

//	utils.c
void	draw_vertical_line(int x, int start, int end, int color);
void	max_map(void);
void	init_map(int width, int i);
void	get_index(void);
void	init_texture(t_img *img);
//	leave.c
void	free_image(void);
//	parsing_map.c
void	map_flood_fill(int x, int y, char **map, int size);
//	2drays.c
void	put_image(void *img, int h, int w);
void	draw_map(void);
void	draw_player_direction(int x1, int y1, int color);
//	rays.c
void	raycaster(void);
//	renders.c
void	render_frame(void);
//	init.c
void	init_image(t_img *img, char *path, int i);
void	init_dda(int x);
void	init_values(void);
