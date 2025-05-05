/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_image_path_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:29:02 by nmatondo          #+#    #+#             */
/*   Updated: 2025/03/29 17:09:20 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

char	**escopeta(void)
{
	static char	*escopeta_path[][14] = {{"escopeta/disparar/escopeta_1.xpm",
		"escopeta/disparar/escopeta_2.xpm", "escopeta/disparar/escopeta_3.xpm",
		"escopeta/disparar/escopeta_4.xpm", "escopeta/disparar/escopeta_5.xpm",
		"escopeta/disparar/escopeta_6.xpm", "escopeta/disparar/escopeta_7.xpm",
		"escopeta/disparar/escopeta_8.xpm", "escopeta/disparar/escopeta_9.xpm",
		"escopeta/disparar/escopeta_10.xpm", "escopeta/disparar/escopeta_11.xp\
m", "escopeta/disparar/escopeta_12.xpm", "escopeta/disparar/escopeta_13.xpm",
		NULL}, {"escopeta/move/escopeta_1.xpm", "escopeta/move/escopeta_2.xpm",
		"escopeta/move/escopeta_3.xpm", "escopeta/move/escopeta_4.xpm",
		"escopeta/move/escopeta_5.xpm", "escopeta/move/escopeta_6.xpm",
		"escopeta/move/escopeta_7.xpm", "escopeta/move/escopeta_8.xpm",
		"escopeta/move/escopeta_9.xpm", "escopeta/move/escopeta_10.xpm",
		"escopeta/move/escopeta_11.xpm", "escopeta/move/escopeta_12.xpm",
		"escopeta/move/escopeta_13.xpm", NULL}, {"escopeta/parado/mgun_1\
.xpm", "escopeta/parado/mgun_2.xpm", "escopeta/parado/mgun_3.xpm",
		"escopeta/parado/mgun_4.xpm", "escopeta/parado/mgun_5.xpm",
		"escopeta/parado/mgun_6.xpm", "escopeta/parado/mgun_7.xpm",
		"escopeta/parado/mgun_8.xpm", "escopeta/parado/mgun_9.xpm",
		"escopeta/parado/mgun_10.xpm", "escopeta/parado/mgun_11.xpm",
		"escopeta/parado/mgun_12.xpm", "escopeta/parado/mgun_13.xpm",
		NULL}
	};

	return ((char **)escopeta_path);
}

char	**lupara(void)
{
	static char	*lupara_path[][14] = {
	{"lupara/disparar/lupara_1.xpm", "lupara/disparar/lupara_2.xpm",
		"lupara/disparar/lupara_3.xpm", "lupara/disparar/lupara_4.xpm",
		"lupara/disparar/lupara_5.xpm", "lupara/disparar/lupara_6.xpm",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{"lupara/move/lupara_1.xpm", "lupara/move/lupara_2.xpm",
		"lupara/move/lupara_3.xpm", "lupara/move/lupara_4.xpm",
		"lupara/move/lupara_5.xpm", "lupara/move/lupara_6.xpm",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{"lupara/parado/lupara_1.xpm", "lupara/parado/lupara_2.xpm",
		"lupara/parado/lupara_3.xpm", "lupara/parado/lupara_4.xpm",
		"lupara/parado/lupara_5.xpm", "lupara/parado/lupara_6.xpm",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}
	};

	return ((char **)lupara_path);
}

char	**mgun(void)
{
	static char	*mgun_path[][14] = {
	{"mgun/disparar/mgun_1.xpm", "mgun/disparar/mgun_2.xpm",
		"mgun/disparar/mgun_3.xpm", "mgun/disparar/mgun_4.xpm",
		"mgun/disparar/mgun_5.xpm", "mgun/disparar/mgun_6.xpm",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{"mgun/move/mgun_1.xpm", "mgun/move/mgun_2.xpm",
		"mgun/move/mgun_3.xpm", "mgun/move/mgun_4.xpm",
		"mgun/move/mgun_5.xpm", "mgun/move/mgun_6.xpm",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{"mgun/parado/mgun_1.xpm", "mgun/parado/mgun_2.xpm",
		"mgun/parado/mgun_3.xpm", "mgun/parado/mgun_4.xpm",
		"mgun/parado/mgun_5.xpm", "mgun/parado/mgun_6.xpm",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}
	};

	return ((char **)mgun_path);
}

char	**escopeta_dupla(void)
{
	static char	*escopeta_dupla_path[][14] = {{"escopeta_dupla/disparar/escopet\
a_dupla_1.xpm", "escopeta_dupla/disparar/escopeta_dupla_2.xpm", "escopeta_dupla\
/disparar/escopeta_dupla_3.xpm", "escopeta_dupla/disparar/escopeta_dupla_4.xpm\
", "escopeta_dupla/disparar/escopeta_dupla_5.xpm", "escopeta_dupla/disparar/esc\
opeta_dupla_6.xpm", "escopeta_dupla/disparar/escopeta_dupla_7.xpm", "escopeta_d\
upla/disparar/escopeta_dupla_8.xpm", "escopeta_dupla/disparar/escopeta_dupla_9.\
xpm", "escopeta_dupla/disparar/escopeta_dupla_10.xpm", "escopeta_dupla/disparar\
/escopeta_dupla_11.xpm", "escopeta_dupla/disparar/escopeta_dupla_12.xpm", NULL,
		NULL}, {"escopeta_dupla/move/escopeta_dupla_1.xpm", "escopeta_dupla/mov\
e/escopeta_dupla_2.xpm", "escopeta_dupla/move/escopeta_dupla_3.xpm", "escopeta_\
dupla/move/escopeta_dupla_4.xpm", "escopeta_dupla/move/escopeta_dupla_5.xpm", "\
escopeta_dupla/move/escopeta_dupla_6.xpm", "escopeta_dupla/move/escopeta_dupla_\
7.xpm", "escopeta_dupla/move/escopeta_dupla_8.xpm", "escopeta_dupla/move/escopet\
a_dupla_9.xpm", "escopeta_dupla/move/escopeta_dupla_10.xpm", "escopeta_dupla/mo\
ve/escopeta_dupla_11.xpm", "escopeta_dupla/move/escopeta_dupla_12.xpm", NULL,
		NULL}, {"escopeta_dupla/parado/escopeta_dupla_1.xpm", "escopeta_dupla/p\
arado/escopeta_dupla_2.xpm", "escopeta_dupla/parado/escopeta_dupla_3.xpm", "esc\
opeta_dupla/parado/escopeta_dupla_4.xpm", "escopeta_dupla/parado/escopeta_dupla\
_5.xpm", "escopeta_dupla/parado/escopeta_dupla_6.xpm", "escopeta_dupla/parado/e\
scopeta_dupla_7.xpm", "escopeta_dupla/parado/escopeta_dupla_8.xpm", "escopeta_d\
upla/parado/escopeta_dupla_9.xpm", "escopeta_dupla/parado/escopeta_dupla_10.xpm\
", "escopeta_dupla/parado/escopeta_dupla_11.xpm", "escopeta_dupla/parado/escope\
ta_dupla_12.xpm", NULL, NULL}};

	return ((char **)escopeta_dupla_path);
}

char	**pistola(void)
{
	static char	*pistola_path[][14] = {
	{"pistola/disparar/pistola_1.xpm", "pistola/disparar/pistola_2.xpm",
		"pistola/disparar/pistola_3.xpm", "pistola/disparar/pistola_4.xpm",
		"pistola/disparar/pistola_5.xpm", "pistola/disparar/pistola_6.xpm",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{"pistola/move/pistola_1.xpm", "pistola/move/pistola_2.xpm",
		"pistola/move/pistola_3.xpm", "pistola/move/pistola_4.xpm",
		"pistola/move/pistola_5.xpm", "pistola/move/pistola_6.xpm",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{"pistola/parado/pistola_1.xpm", "pistola/parado/pistola_2.xpm",
		"pistola/parado/pistola_3.xpm", "pistola/parado/pistola_4.xpm",
		"pistola/parado/pistola_5.xpm", "pistola/parado/pistola_6.xpm",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}
	};

	return ((char **)pistola_path);
}
