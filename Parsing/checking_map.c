/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:34:03 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/04 17:29:28 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	map_is_correct(char **map)
{
	int	hauteur_map;
	int	i;
	int	j;

	i = 0;
	j = 0;
	// printf("tarrives jusque la ?\n");
	hauteur_map = max_len_map(map);
	// printf("hauteur_map == %d\n", hauteur_map);
	while (map[i] != NULL)
	{
		printf("i pour le fun = %d\n", i);
		if (i == 2)
			printf("%s\n", map[i]);
		if (i != 0 && map[i][0] == '\n')
		{
			printf("Error: Map isn't valide. Unknown or missing element inside.\n");
			exit (1);
		}
		if (checking_str(map[i], hauteur_map) == 0)
		{
			printf("Error: Map isn't valide. Unknown or missing element inside.\n");
			exit (1);
		}
		i++;
	}
	return (1);
}

int	wall_top_bott(char **map, int i)
{
	int	j;

	j = 0;
	while (map[i][j] != '\0')
	{	
		if (map[i][j] != '1' && map[i][j] != '\n')
			return (0);
		j++;
	}
	return (1);
}

int	map_is_close(char **map)
{
	int	i;
	int	j;
	int	len_size;

	i = 0;
	j = 0;
	len_size = int_strlen(map[0]);
	i = 0;
	while (map[i] != NULL)
	{
		if (i == 0 || i == max_len_map(map) - 1)
		{
			if (wall_top_bott(map, i) == 0)
				return (0);
			else if (i == max_len_map(map))
				return (1);
		}
		if (map[i][j] != '1' || map[i][int_strlen(map[i]) - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int map_is_oblong(char **map)
{
	int	i;
	int	save;

	i = 1;
	save = int_strlen(map[0]);
	while (map[i])
	{
		if (save != int_strlen(map[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**copy_map(char **map, char **copy)
{
	int	i;
	int	j;
	char **tmp;


	i = 0;
	j = 0;
	tmp = map;
	// tmp[0] = malloc(sizeof(char *) * ft_strlen(map[i]));
	tmp[0] = ft_strdup(map[0]);
	while (map[i] != NULL)
	{
		while (map[i][j] != '\0' && map[i][j] != '\n')
		{
			j++;
		}
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	return (copy);
}

int	checking_map_is_playable(char **map)
{
	t_point	data;
	int		i;
	int		j;

	j = 0;
	i = 0;
	data = return_pos(map, 'E');
	if (map_is_correct(map) == 0)
		return (0);
	if (map_is_oblong(map) == 0)
	{
		printf("Error: Map isn't an oblong. Use Google trad. if you need.\n");
		return (0);
	}
	if (map_is_close(map) == 0)
	{
		printf("Error: Map isn't close.\n");
		return (0);
	}
	if (doublon(map, 'E', return_pos(map, 'E')) == 0)
	{
		printf("Error: WTF. Two or more exit. Don't fool me.\n");
		return (0);
	}
	if (doublon(map, 'P', return_pos(map, 'P')) == 0)
	{
		printf("Error: Stop trying shit. Two or more character(s). Ain't multi here idiots.\n");
		return (0);
	}
	data = return_pos(map, 'E');
	if (data.x == 5000)
	{
		printf("Error: No exit. Can't be finished.\n");
		return (0);
	}
	data = return_pos(map, 'P');
	if (data.x == 5000)
	{
		printf("Error: No player. Can't playing.\n");
		return (0);
	}
	data = return_pos(map, 'C');
	if (data.x == 5000)
	{
		printf("Error: No items. Can't collect all items and finished.\n");
		return (0);
	}
	if (int_strlen(map[0]) - 1 == max_len_map(map))
	{
		printf("Error: Map isn't an oblong. Use Google trad. if you need.\n");
		return (0);
	}
	if (map_is_not_split(map) == 0)
	{
		printf("Error: Map can't be finished.\n");
		return (0);
	}
	return (1);
}
