/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:49:02 by aquissan          #+#    #+#             */
/*   Updated: 2025/05/09 15:08:03 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	check_sound(t_sound *sound)
{
	if (!sound->background)
		return (printerror("Failed to load Background audio file"), 1);
	if (!sound->pistol)
		return (printerror("Failed to load Pistol audio file"), 1);
	if (!sound->revolver)
		return (printerror("Failed to load Revolver audio file"), 1);
	if (!sound->shotgun)
		return (printerror("Failed to load Shotgun audio file"), 1);
	if (!sound->run)
		return (printerror("Failed to load Run audio file"), 1);
	if (!sound->door_open)
		return (printerror("Failed to load Door open audio file"), 1);
	if (!sound->door_close)
		return (printerror("Failed to load Door close audio file"), 1);
	if (!sound->revolver_3)
		return (printerror("Failed to load Revolver 3 audio file"), 1);
	if (!sound->shotgun_frst)
		return (printerror("Failed to load first Shotgun audio file"), 1);
	return (0);
}

int	play_sound(HSTREAM sound, int vol, BOOL restart)
{
	float	volume;

	if (vol >= 0 && vol <= 100)
		volume = (float)vol / 100.0f;
	else
		volume = 1.0f;
	if (sound)
	{
		BASS_ChannelSetAttribute(sound, BASS_ATTRIB_VOL, volume);
		BASS_ChannelPlay(sound, restart);
	}
	return (0);
}

int	sound_init(t_sound *sounds, BOOL *bass)
{
	*sounds = (t_sound){0, 0, 0, 0, 0, 0, 0, 0, 0};
	*bass = BASS_Init(-1, 44100, 0, 0, 0);
	if (!(*bass))
		return (printerror("Error to init the BASS"), 1);
	sounds->background = BASS_StreamCreateFile(FALSE, "./sound/back6.mp3", 0, 0,
			BASS_SAMPLE_LOOP);
	sounds->run = BASS_StreamCreateFile(FALSE, "./sound/run/run.mp3", 0, 0, 0);
	sounds->revolver = BASS_StreamCreateFile(FALSE,
			"./sound/weapon/revolver.mp3", 0, 0, 0);
	sounds->shotgun = BASS_StreamCreateFile(FALSE,
			"./sound/weapon/shotgun-frst.mp3", 0, 0, 0);
	sounds->pistol = BASS_StreamCreateFile(FALSE, "./sound/weapon/pistol.mp3",
			0, 0, 0);
	sounds->door_open = BASS_StreamCreateFile(FALSE, "./sound/door/door_3.mp3",
			0, 0, 0);
	sounds->door_close = BASS_StreamCreateFile(FALSE, "./sound/door/door_3.mp3",
			0, 0, 0);
	sounds->revolver_3 = BASS_StreamCreateFile(FALSE,
			"./sound/weapon/science.mp3", 0, 0, 0);
	sounds->shotgun_frst = BASS_StreamCreateFile(FALSE,
			"./sound/weapon/shotgun-frst.mp3", 0, 0, 0);
	check_sound(sounds);
	return (0);
}

int	set_weapon(t_master *master, int index)
{
	if (index == 0)
		master->weapon = master->sounds.shotgun_frst;
	if (index == 1)
		master->weapon = master->sounds.revolver;
	if (index == 2)
		master->weapon = master->sounds.revolver_3;
	if (index == 3)
		master->weapon = master->sounds.shotgun;
	if (index == 4)
		master->weapon = master->sounds.pistol;
	return (0);
}

int	clear_sounds(t_sound sounds, BOOL bass)
{
	if (bass)
	{
		BASS_ChannelStop(sounds.background);
		BASS_StreamFree(sounds.background);
		BASS_ChannelStop(sounds.revolver);
		BASS_StreamFree(sounds.revolver);
		BASS_ChannelStop(sounds.pistol);
		BASS_StreamFree(sounds.pistol);
		BASS_ChannelStop(sounds.revolver_3);
		BASS_StreamFree(sounds.revolver_3);
		BASS_ChannelStop(sounds.shotgun);
		BASS_StreamFree(sounds.shotgun);
		BASS_ChannelStop(sounds.shotgun_frst);
		BASS_StreamFree(sounds.shotgun_frst);
		BASS_ChannelStop(sounds.run);
		BASS_StreamFree(sounds.run);
		BASS_ChannelStop(sounds.door_close);
		BASS_StreamFree(sounds.door_close);
		BASS_ChannelStop(sounds.door_open);
		BASS_StreamFree(sounds.door_open);
		BASS_Stop();
		BASS_Free();
		return (0);
	}
	return (1);
}
