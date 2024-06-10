/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:31:05 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/10 19:23:04 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"
#include "../minilibx-linux/mlx.h"	

t_data  *d(void)
{
	static t_data data;
	return (&data);
}

void valid_entry(int ac, char *str)
{
	if (ac != 2)
		error("Error\nWrong input -> ./cub3d [path_to_map]\n");
	if (ft_strlen(str) <= 4 )
		error("Error\nEmpty map name\n");
	while(*str && *str != '.')
		str++;
	if (ft_strcmp(str, ".cub") != 0)
		error("Error\nWrong file format -> [map.cub]\n");
}

static int	*xpm_to_img(char *path)
{
	t_img	img;
	int		*buffer;
	int		x;
	int		y;

	init_image(&img, path, 0);
	buffer = ft_calloc(d()->texture_size * d()->texture_size, sizeof(int));
	if (!buffer)
		error("Error\nCouldn't allocate buffer!\n");
	y = 0;
	while (y < d()->texture_size)
	{
		x = 0;
		while (x < d()->texture_size)
		{
			buffer[y * d()->texture_size + x] = img.addr[y * d()->texture_size + x];
			x++;
		}
		y++;
	}	
	mlx_destroy_image(d()->mlx, img.image);
	return (buffer);
}

static void	assets()
{
	d()->mlx = mlx_init();
	d()->win_ptr = mlx_new_window(d()->mlx, d()->screen_width, d()->screen_height, "CUBED");
	if (!d()->mlx || !d()->win_ptr)
		error("Error\n Cub3d coudn't be initialized!\n");
	d()->textures = ft_calloc(5, sizeof(int *));
	if (!d()->textures)
		error("Error\n Couldn't allocate textures\n");
	d()->textures[0] = xpm_to_img(d()->map_no);
	d()->textures[1] = xpm_to_img(d()->map_so);
	d()->textures[2] = xpm_to_img(d()->map_ea);
	d()->textures[3] = xpm_to_img(d()->map_we);
	init_image(&d()->wall, "/home/gcatarin/Documents/cub3d/textures/image_1_.xpm", 1);
	init_image(&d()->exit, "/home/gcatarin/Documents/cub3d/textures/exit.xpm", 1);
	init_image(&d()->floor, "/home/gcatarin/Documents/cub3d/textures/wall.xpm", 1);
	init_image(&d()->empty, "/home/gcatarin/Documents/cub3d/textures/black.xpm", 1);
	init_image(&d()->player, "/home/gcatarin/Documents/cub3d/textures/player.xpm", 1);
	init_pixels();
	max_map();
}

int main(int ac, char **av)
{
	valid_entry(ac, av[1]);
	initialize_everything();
	parsing(av);

	assets();
	raycaster();
	render_frame();
	print_minimap();

	mlx_hook(d()->win_ptr, 17, 0, destroy_hook, d);
	mlx_hook(d()->win_ptr,  2, 1L << 0, movekey_hook, d);
	mlx_loop(d()->mlx);
}

/*
The map must be closed/surrounded by walls.

Spaces are a valid part of the map and are up to you to handle.
You must be able to parse any kind of map, as long as it respects 
the rules of the map.

	erros possiveis
		single digits (0, 1..)
		+ se a linha F ou C tiver mal escrita
	
*/