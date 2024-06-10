/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:31:05 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/10 21:05:04 by jnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"
#include "../minilibx-linux/mlx.h"	

t_data	*d(void)
{
	static t_data	data;

	return (&data);
}

void	valid_entry(int ac, char *str)
{
	if (ac != 2)
		error("Error\nWrong input -> ./cub3d [path_to_map]\n");
	if (ft_strlen(str) <= 4)
		error("Error\nEmpty map name\n");
	while (*str && *str != '.')
		str++;
	if (ft_strcmp(str, ".cub") != 0)
		error("Error\nWrong file format -> [map.cub]\n");
}

static char	*xpm_to_img(char *path)
{
	char	*buffer;
	int		x;
	int		y;

	init_img(path);
	buffer = ft_calloc(d()->texture_size * d()->texture_size + 1, sizeof(char));
	if (!buffer)
		error("error!\nCouldn't allocate buffer!\n");
	y = 0;
	while (y < d()->texture_size)
	{
		x = 0;
		while (x < d()->texture_size)
		{
			buffer[y * d()->texture_size + x] = d()->img.addr[y \
				* d()->texture_size + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(d()->mlx, d()->img.image); //indirect leak
	return (buffer);
}

static void	assets(void)
{
	char	**tmp;
	void	*tmp1;
	void	*tmp2;
	void	*tmp3;
	void	*tmp4;	

	d()->texture_size = TEXTURE_SIZE;
	d()->player_speed = PLAYER_SPEED;
	d()->screen_height = SCREENH;
	d()->screen_width = SCREENH;
	d()->mlx = mlx_init();
	tmp1 = mlx_new_window(d()->mlx, d()->screen_width, \
		d()->screen_height, "CUBED");
	if (!d()->mlx || !tmp1)
		error("Error!\n Cub3d coudn't be initialized!\n");
	d()->win_ptr = tmp1;
	tmp = ft_calloc(5, sizeof(int *));
	if (!tmp)
		error("error!\n Couldn't allocate textures\n");
	d()->textures = tmp;
	info_print();
	printf("map_no = \"%s\"", d()->map_no);
	d()->textures[0] = xpm_to_img(d()->map_no);
	d()->textures[1] = xpm_to_img(d()->map_so);
	d()->textures[2] = xpm_to_img(d()->map_ea);	//verificar se ta na boa ordem
	d()->textures[3] = xpm_to_img(d()->map_we);
	tmp2 = mlx_xpm_file_to_image(d()->mlx, "textures/wall.xpm", \
		&d()->texture_size, &d()->texture_size);
	d()->wall = tmp2;
	tmp3 = mlx_xpm_file_to_image(d()->mlx, "textures/exit.xpm", \
		&d()->texture_size, &d()->texture_size);
	d()->exit = tmp3;
	tmp4 = mlx_xpm_file_to_image(d()->mlx, "textures/floor.xpm", \
		&d()->texture_size, &d()->texture_size);
	d()->empty = tmp4;
	init_pixels();
	max_map();
	d()->player_a = ROT_SPEED;
}

int	main(int ac, char **av)
{
	valid_entry(ac, av[1]);
	parsing(av);
	assets();
	raycaster();
	render_frame();
	print_minimap();
	mlx_hook(d()->win_ptr, 17, 0, destroy_hook, d);
	mlx_hook(d()->win_ptr, 2, 1L << 0, movekey_hook, d);
	mlx_loop(d()->mlx);
}
