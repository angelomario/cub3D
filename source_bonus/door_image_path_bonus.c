/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_image_path_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:59:07 by nmatondo          #+#    #+#             */
/*   Updated: 2025/04/04 14:02:07 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

char	**grade_de_cela(void)
{
	static char	*cela_de_grade_path[13] = {
		"textures/door/grade_de_cela/grade_de_cela_1.xpm",
		"textures/door/grade_de_cela/grade_de_cela_2.xpm",
		"textures/door/grade_de_cela/grade_de_cela_3.xpm",
		"textures/door/grade_de_cela/grade_de_cela_4.xpm",
		"textures/door/grade_de_cela/grade_de_cela_5.xpm",
		"textures/door/grade_de_cela/grade_de_cela_6.xpm",
		"textures/door/grade_de_cela/grade_de_cela_7.xpm",
		"textures/door/grade_de_cela/grade_de_cela_8.xpm",
		"textures/door/grade_de_cela/grade_de_cela_9.xpm",
		"textures/door/grade_de_cela/grade_de_cela_10.xpm",
		"textures/door/grade_de_cela/grade_de_cela_11.xpm",
		"textures/door/grade_de_cela/grade_de_cela_12.xpm",
		NULL};

	return ((char **)cela_de_grade_path);
}

char	**porta_de_dilatacao(void)
{
	static char	*porta_de_dilatacao_path[13] = {
		"textures/door/porta_de_dilatacao/porta_de_dilatacao_1.xpm",
		"textures/door/porta_de_dilatacao/porta_de_dilatacao_2.xpm",
		"textures/door/porta_de_dilatacao/porta_de_dilatacao_3.xpm",
		"textures/door/porta_de_dilatacao/porta_de_dilatacao_4.xpm",
		"textures/door/porta_de_dilatacao/porta_de_dilatacao_5.xpm",
		"textures/door/porta_de_dilatacao/porta_de_dilatacao_6.xpm",
		"textures/door/porta_de_dilatacao/porta_de_dilatacao_7.xpm",
		"textures/door/porta_de_dilatacao/porta_de_dilatacao_8.xpm",
		NULL, NULL, NULL, NULL, NULL};

	return ((char **)porta_de_dilatacao_path);
}

char	**porta_de_madeira(void)
{
	static char	*porta_de_madeira_path[13] = {
		"textures/door/porta_de_madeira/porta_de_madeira_1.xpm",
		"textures/door/porta_de_madeira/porta_de_madeira_2.xpm",
		"textures/door/porta_de_madeira/porta_de_madeira_3.xpm",
		"textures/door/porta_de_madeira/porta_de_madeira_4.xpm",
		"textures/door/porta_de_madeira/porta_de_madeira_5.xpm",
		"textures/door/porta_de_madeira/porta_de_madeira_6.xpm",
		"textures/door/porta_de_madeira/porta_de_madeira_7.xpm",
		"textures/door/porta_de_madeira/porta_de_madeira_8.xpm",
		"textures/door/porta_de_madeira/porta_de_madeira_9.xpm",
		"textures/door/porta_de_madeira/porta_de_madeira_10.xpm",
		NULL, NULL, NULL};

	return ((char **)porta_de_madeira_path);
}
