/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:37:11 by prafael-          #+#    #+#             */
/*   Updated: 2021/11/15 22:59:12 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	verify_width_map(t_module *module, char *content, int height_now)
{
	if (module->map->width < 4)
		return (error(0, "Width is too small!"));
	if (ft_verify_str(content, "1", module->map->width) == 0)
	{
		if (((int)ft_strlen(content)) != module->map->width && height_now > 0)
			return (error(0, "Wrong construct of the map!"));
		content[module->map->width] = '\0';
		return (0);
	}
	if (ft_verify_str(content, "10ECPJ", module->map->width) == 0)
	{
		if (content[0] != '1' && content [module->map->width - 1] != '1')
			return (error(0, "Wrong construct of the map!"));
		if (((int)ft_strlen(content)) - 1 != module->map->width)
			return (error(0, "Wrong construct of the map!"));
		content[module->map->width] = '\0';
		return (0);
	}
	return (error(0, "Wrong construct of the map this letter is not allowed!"));
}

static int	read_map_while(t_module *module, char **tmp_map, int *a, int b)
{
	tmp_map = (char **)ft_calloc(*a + 2, sizeof(char *));
	if (tmp_map == NULL)
		return (error(14, NULL));
	tmp_map[*a] = get_next_line(module->map->fd);
	if (tmp_map[*a] == NULL)
	{
		free_ptr((void **)&tmp_map);
		return (0);
	}
	if (module->map->width == 0)
		module->map->width = strlen(tmp_map[*a]) - 1;
	if (verify_width_map(module, tmp_map[*a], *a) == 1)
	{
		module->map->height = *a + 1;
		free_ptr((void **)&tmp_map[*a]);
		free_ptr((void **)&tmp_map);
		return (1);
	}
	while (++b < *a)
		tmp_map[b] = module->map->map[b];
	free_ptr((void **)&module->map->map);
	module->map->map = tmp_map;
	return (0);
}

int	read_map(t_module *module)
{
	char	**tmp_map;
	int		a;

	a = 0;
	tmp_map = NULL;
	module->map->width = 0;
	while (module->map->map == NULL
		|| module->map->map[a - 1] != NULL || a == 0)
	{
		if (read_map_while(module, tmp_map, &a, -1) == 1)
			return (1);
		a++;
	}
	if (a - 1 < 4)
		return (error(0, "Height is too small!"));
	module->map->height = a - 1;
	return (0);
}

int	verify_map(char *name_map, t_module *module)
{
	module->map = malloc(1 * sizeof(t_map));
	module->map->map = NULL;
	if (module->map == NULL)
		return (error(14, NULL));
	module->map->fd = open(name_map, O_RDONLY);
	if (module->map->fd == -1)
		return (error(9, NULL));
	if (read_map(module) == 1)
		return (1);
	return (0);
}
