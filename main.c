/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:45:28 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/04 18:54:08 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	checking_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == '\n')
		i++;
	while (line[i] != '\0')
	{
		if (line[i] == '\n' && line[i + 1] == '\n')
			ft_error("Error: No man's land on the map. Map can't be played.\n");
		i++;
	}
}

char	**stocking_map(char **map, int fd)
{
	int	i;
	char	save[2];
	int		size;
	char	*line;

	i = 0;
	size = read(fd, save, 1);
	save[1] = '\0';
	line = ft_strdup(save);
	size = read(fd, save, 1);
	save[1] = '\0';
	while (size > 0)
	{
		line = ft_strjoin(line, save);
		size = read(fd, save, 1);
		save[1] = '\0';
	}
	checking_map_line(line);
	map = ft_split(line, '\n');
	free(line);
	return (map);
}

int	key_hook(int keycode, t_play *play)
{
	return (gestion_key_input(play, keycode));
}

int	ft_destroy_windows(t_vars *d)
{
	mlx_destroy_window(d->mlx, d->win);
	ft_error("Closed");
	return (1);
}

void	keep_open(t_play *play, char **map)
{
	// printf("keep open\n");
	// system("leaks so_long");
	play->vars->mlx = mlx_init();
	play->vars->win = mlx_new_window(play->vars->mlx, WINDOW_LEN, WINDOW_HEIGHT, "Hello world!");
	put_map(play, map, play->vars);
	mlx_hook(play->vars->win, 17, 0, ft_destroy_windows, play->vars);
	mlx_key_hook(play->vars->win, key_hook, play);
	mlx_loop(play->vars->mlx);
}

void	do_all(t_play *play)
{
	if (checking_map_is_playable(play->map) == 0)
		return ;
	// system("leaks so_long");
	// char c;
	// read(0, &c, 1);
	keep_open(play, play->map);
}

void	puterror(int i)
{
	if (i == 500)
	{
		printf("No map found.\n");
		exit (1);
	}
}

int	main(int ac, char **av)
{
	int			fd;
	t_play		*play;

	fd = 0;
	play = NULL;
	play = malloc(sizeof(t_play));
	play->vars = malloc(sizeof(t_vars));
	play->direct = 0;
	play->img = NULL;
	play->perso = NULL;
	play->width_perso = 0;
	play->height_perso = 0;
	play->exit = NULL;
	play->width_exit = 0;
	play->height_exit = 0;
	play->collec = NULL;
	play->width_collec = 0;
	play->height_collec = 0;
	play->back = NULL;
	play->width_back = 0;
	play->height_back = 0;
	play->walk_perso = NULL;
	play->width_wp = 0;
	play->height_wp = 0;
	play->down_perso = NULL;
	play->width_down = 0;
	play->height_down = 0;
	play->left_perso =  NULL;
	play->width_left = 0;
	play->height_left = 0;
	play->walk_left = NULL;
	play->width_wl = 0;
	play->height_wl = 0;
	play->dust =  NULL;
	play->width_dust = 0;
	play->height_dust = 0;
	play->bott = NULL;
	play->map = NULL;
	play->vars->mlx = NULL;
	play->vars->win = NULL;
	play->direct = 0;
	play->string = NULL;
	if (ac != 2)
	{
		ft_error("No map found.\n");
		return 0;
	}
	else
	{
		if (is_map(av[1]) == 1)
		{
			fd = open(av[1], O_RDONLY);
			if (fd < 0)
				ft_error("File doesn't exist.\n");
			if (open(av[1], O_DIRECTORY) > 0)	
				ft_error("This is a directory.\n");
			play->map = stocking_map(play->map, fd);
			play->player = return_pos(play->map, 'P');
			play->leave = return_pos(play->map, 'E');
			do_all(play);
		}
	}
	return (0);
}