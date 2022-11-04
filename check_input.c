/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:51:30 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/04 18:55:18 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

t_play	*delete_map(t_play *play)
{
	int	i;

	i = max_len_map(play->map);
	while (i > 0)
	{
		free(play->map[i]);
		i--;
	}
	free(play->map[0]);
	play->map = NULL;
	return (play);
}

int	close_w(int keycode, t_play *play)
{
	(void)keycode;
	mlx_destroy_window(play->vars->mlx, play->vars->win);
	free(play->vars);
	play = delete_map(play);
	free(play);
	exit(0);
}

int	touching_esc(int keycode, t_play *play)
{
	return (close_w(keycode, play));
}

int complet_collect(char **map, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

// int checking_a(char **map, t_point player, char key)
// {
// 	if (key == 'A' && (map[player.x - 1][player.y] == '0'
// 			|| map[player.x - 1][player.y] == 'C'))
// 	{
// 		map[player.x - 1][player.y] = 'P';
// 		map[player.x - 1][player.y] = '0';
// 		return (1);
// 	}
// 	if (key == 'A' && map[player.x][player.y - 1] == 'E')
// 	{
// 		if (complet_collect(map, 'C') == 1)
// 			exit(1);
// 		else
// 		{
// 			map[player.x - 1][player.y] = 'P';
// 			map[player.x - 1][player.y] = '0';
// 		}
// 		return (1);
// 	}
// 	if (key == 'A' && map[player.x - 1][player.y] == '1')
// 		return (0);
// 	return (0);
// }

int	help_checking_moove(t_play *play, t_point save, t_point player)
{
	if (play->map[player.y][player.x] == '1')
		return (0);
	else if (play->map[player.y][player.x] == '0'
		|| play->map[player.y][player.x] == 'C')
	{
		play->map[player.y][player.x] = 'P';
		play->map[save.y][save.x] = '0';
		play->player.y = player.y;
		play->player.x = player.x;
		play->counter = play->counter + 1;
	}
	else if (play->map[player.y][player.x] == 'E')
	{
		if (complet_collect(play->map, 'C') == 1)
		{
			delete_map(play);
			ft_putstr("End's Game!\n");
			system("leaks so_long");
			exit(1);
		}
		else
			return (0);
	}
	return (0);
}

int checking_moove(t_play *play, t_point save, t_point player, char key)
{
	if (key == 'A')
		play->direct = 1;
	else if (key == 'D')
		play->direct = 0;
	if (play->map[player.y][player.x])
		return (help_checking_moove(play, save, player));
	return (1);
}

void	ft_putchar(char c)
{
	write(0, &c, 1);
}

void	ft_putnbr(int nb)
{
	unsigned int	n;

	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	n = (unsigned int)nb;
	if (n / 10)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + '0');
}

int	checking_possibility(t_play *play, t_point player, char key)
{
	t_point	futur_pos;
	int		i;

	i = 0;
	futur_pos.x = player.x;
	futur_pos.y = player.y;
	ft_putnbr(play->counter);
	ft_putchar('\n');
	// printf("checking possibility\n");
	// system("leaks so_long");
	if (key == 'W')
		return (checking_moove(play, player, (t_point){futur_pos.x, futur_pos.y - 1}, key));
	else if (key == 'A')
		return (checking_moove(play, player, (t_point){futur_pos.x - 1, futur_pos.y}, key));
	else if (key == 'S')
		return (checking_moove(play, player, (t_point){futur_pos.x, futur_pos.y + 1}, key));
	else if (key == 'D')
		return (checking_moove(play, player, (t_point){futur_pos.x + 1, futur_pos.y}, key));
	else
		return (0);
}

int	touching_w(int keycode, t_play *play)
{
	t_point		pos;

	pos = play->player;
	// printf("touching_w\n");
	// system("leaks so_long");
	if (keycode == 13 || keycode == 126)
		return (checking_possibility(play, play->player , 'W'));
	else if (keycode == 0 || keycode == 123)
	{
		play->direct = 1;
		return (checking_possibility(play, play->player, 'A'));
	}
	else if (keycode == 1 || keycode == 125)
		return (checking_possibility(play, play->player, 'S'));
	else if (keycode == 2 || keycode == 124)
	{
		play->direct = 0;
		return (checking_possibility(play, play->player, 'D'));
	}
	return (0);
}

void	put_map(t_play *play, char **map, t_vars *vars)
{
	int	i;
	int	j;
	int test;
	
	test = 0;
	i = 0;
	j = 0;
	// printf("put_map\n");
	// system("leaks so_long");
	play->img = mlx_xpm_file_to_image(vars->mlx, "Xpm/wall.xpm", &play->img_width, &play->img_height);
	play->perso = mlx_xpm_file_to_image(vars->mlx, "Xpm/Dude_Monster.xpm", &play->width_perso, &play->height_perso);
	play->exit = mlx_xpm_file_to_image(vars->mlx, "Xpm/Door.xpm", &play->width_exit, &play->height_exit);
	play->collec = mlx_xpm_file_to_image(vars->mlx, "Xpm/Monster-Egg.xpm", &play->width_collec, &play->height_collec);
	play->back = mlx_xpm_file_to_image(vars->mlx, "Xpm/Grass.xpm", &play->width_back, &play->height_back);
	play->walk_perso = mlx_xpm_file_to_image(vars->mlx, "Xpm/Monster_walk.xpm", &play->width_wp, &play->height_wp);
	play->down_perso = mlx_xpm_file_to_image(vars->mlx, "Xpm/Monsterdown.xpm", &play->width_down, &play->height_down);
	play->left_perso = mlx_xpm_file_to_image(vars->mlx, "Xpm/Monsterleft.xpm", &play->width_left, &play->height_left);
	play->walk_left = mlx_xpm_file_to_image(vars->mlx, "Xpm/WalkLeft.xpm", &play->width_wl, &play->height_wl);
	play->dust = mlx_xpm_file_to_image(vars->mlx, "Xpm/Dust.xpm", &play->width_dust, &play->height_dust);
	play->bott = mlx_xpm_file_to_image(vars->mlx, "Xpm/Metal.xpm", &play->width_bott, &play->height_bott);
	// system("leaks so_long");

	i = 0;
	j = 0;
	int	start;
	int	start2;
	start = 0;
	start2 = 0;
	if (ft_strlen(map[i]) > WINDOW_LEN / 32)
	{
		if (play->player.x >= (WINDOW_LEN / 32) / 2)
		{
			start = play->player.x - (WINDOW_LEN / 32) / 2;
			start2 = 0;
		}
		if (play->player.y >= (WINDOW_HEIGHT / 32) / 2)
			start2 = play->player.y - (WINDOW_HEIGHT / 32) / 2;
	}
	i = start2;
	int x = 0;
	int y = 0;
	int	g;
	g = 0;
	// printf("milieu put map\n");
	// system("leaks so_long");
	while (map[i])
	{
		j = start;
		x = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				mlx_put_image_to_window(vars->mlx, vars->win, play->back, x, y);
			else if (map[i][j] == '1')
			{
				mlx_put_image_to_window (vars->mlx, vars->win, play->img, x, y);
			}
			else if (map[i][j] == 'C')
			{
				mlx_put_image_to_window(vars->mlx, vars->win, play->back, x, y);
				mlx_put_image_to_window(vars->mlx, vars->win, play->collec, x, y);
			}
			else if (map[i][j] == 'P')
			{
				mlx_put_image_to_window(vars->mlx, vars->win, play->back, x, y);
				if (play->direct == 0)
				{
					if (j % 2 == 0)
						mlx_put_image_to_window(vars->mlx, vars->win, play->perso, x, y);
					else if (i % 2 == 0)
						mlx_put_image_to_window(vars->mlx, vars->win, play->down_perso, x, y);
					else
						mlx_put_image_to_window(vars->mlx, vars->win, play->walk_perso, x, y);
					
					mlx_put_image_to_window(vars->mlx, vars->win, play->dust, x - 12, y);
				}
				else
				{
					if (j % 2 == 0)
						mlx_put_image_to_window(vars->mlx, vars->win, play->left_perso, x, y);
					else
						mlx_put_image_to_window(vars->mlx, vars->win, play->walk_left, x, y);
				
					mlx_put_image_to_window(vars->mlx, vars->win, play->dust, x + 12, y);
				}
			}
			else if (map[i][j] == 'E')
			{
				mlx_put_image_to_window(vars->mlx, vars->win, play->back, x, y);
				mlx_put_image_to_window(vars->mlx, vars->win, play->exit, x, y);
			}
			j++;
			x += 32;
		}
		i++;
		y += 32;
	}
	int z = 0;
	if (int_strlen(map[0]) < WINDOW_LEN / 32)
		z = int_strlen(map[0]);
	else
		z = WINDOW_LEN;
	while (g < z)
	{
		mlx_put_image_to_window(vars->mlx, vars->win, play->bott, g * 32, i * 32);
		g++;
	}
	char *string = NULL;
	string = ft_itoa(play->counter);
	mlx_string_put(vars->mlx, vars->win, z / 2, i * 32,  0xFFAAFFBB, string);
	free(string);
}

int	gestion_key_input(t_play *play, int keycode)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (keycode ==  13 || keycode == 126 || keycode == 0 || keycode == 1
			|| keycode == 2 || keycode == 123 || keycode == 124 || keycode == 125 || keycode == 53)
	{
		if (keycode == 53)
		{
			ft_putstr("End's Game!\n");
			i = (touching_esc(keycode, play));
			exit(1);
		}
		j = (touching_w(keycode, play));
		put_map(play, play->map, play->vars);
	}
	else 
		return (1);
	return (0);
}
