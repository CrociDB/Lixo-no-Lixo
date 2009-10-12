#ifndef _CTRASH_H_
#define _CTRASH_H_

#include <gamespace.h>
#include <windows.h>
#include <math.h>
#include <iostream>
#include <string>
#include <sstream>

#define BAR_X_START					80
#define BAR_X_END					552
#define BAR_MAX_FORCE				12
#define BAR_MIN_FORCE				4

#include "cCan.h"

class cTrash
{
private:
	GAMESPACE_VIDEO_HANDLER *gsVideo;
	GAMESPACE_INPUT_HANDLER *gsInput;
	GAMESPACE_AUDIO_HANDLER *gsAudio;

	GS_SPRITE sprite;
	GS_SPRITE arrow;
	GS_SPRITE bar;
	GS_SPRITE sForce;

	GS_AUDIO_SAMPLE effect;

	cCan *Can;

	float x, y;
	float sx, sy;
	float angle;
	int flag_angle;
	float time;
	float vel;
	float velx;
	float vely;
	float gravity;

	float rot_angle;

	int side;

	int barx;
	int vel_force;

	bool force;
	bool walking;
	bool ver;

	bool flag_space;

	int play;
	int points;
public:
					cTrash(GAMESPACE_VIDEO_HANDLER *video, GAMESPACE_INPUT_HANDLER *input, GAMESPACE_AUDIO_HANDLER *audio);

	void			run();

	void			restart();
	int				getBarForce(int x);

	cCan			*getCan() const;

	int				getX() const;
	int				getY() const;

	int				getPoints() const;

	bool			isWalking() const;
};

#endif