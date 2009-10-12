#include "cTrash.h"

cTrash::cTrash(GAMESPACE_VIDEO_HANDLER *video, GAMESPACE_INPUT_HANDLER *input, GAMESPACE_AUDIO_HANDLER *audio)
{
	gsVideo = video;
	gsInput = input;
	gsAudio = audio;

	x = sx = 95;
	y = sy = 415;
	angle = 5;
	flag_angle = 0;

	rot_angle = 0;

	time = 0;
	velx = vel = 2.0;
	gravity = -9.0;

	ver = false;

	play = points = 0;

	vely = 0;

	walking = false;
	force = false;
	barx = 80;
	vel_force = 7;

	flag_space = false;

	side = 1;

	Can = new cCan(gsVideo);

	sprite.LoadSprite(gsVideo, "media/trash.png", GS_ARGB(255,0,255,0));
	sprite.SetSpriteOrigin(GSSO_CENTER);
	arrow.LoadSprite(gsVideo, "media/arrow.png", GS_ARGB(255,0,255,0));
	arrow.SetSpriteOrigin(GSSO_CENTER_BOTTOM);

	bar.LoadSprite(gsVideo, "media/bar.png", GS_ARGB(255,0,255,0));
	sForce.LoadSprite(gsVideo, "media/force.png", GS_ARGB(255,0,255,0));

	effect.LoadSample(gsAudio, "media/effect.ogg", GSST_SOUNDTRACK);
}

void cTrash::run()
{
	Can->run();

	if (walking == true)
	{
		rot_angle -= (((vely<0?-vely:vely)*3) + 2.0) * side;

		time += 1.0;
			
		x += (velx);
		vely = ((vel * sin(gsDegreeToRadian(angle))) + (gravity * (time/100)));
		y -= vely;
	}
	else
	{
		if (force == true)
		{
			if (flag_angle == 0)
			{
				angle += 1;

				if (angle > 85)
				{
					flag_angle = 1;
				}
			}
			else if (flag_angle == 1)
			{
				angle -= 1;

				if (angle < 5)
				{
					flag_angle = 0;
				}
			}
			arrow.DrawSprite(GS_VECTOR2(110, 395), GS_COLOR(130,255,255,255), (angle-90));
		}
		else
		{
			if (flag_angle == 0)
			{
				barx += vel_force;

				if (barx > BAR_X_END-2*vel_force)
				{
					flag_angle = 1;
				}
			}
			else if (flag_angle == 1)
			{
				barx -= vel_force;

				if (barx < BAR_X_START+2*vel_force)
				{
					flag_angle = 0;
				}
			}
		}

		bar.DrawSprite(GS_VECTOR2(78, 436), GS_COLOR(130,255,255,255));
		sForce.DrawSprite(GS_VECTOR2(barx, 446));
	}

	if (gsInput->KeyDown(GSK_SPACE) && walking == false && flag_space == false)
	{
		flag_space = true;
		if (force == false)
		{
			force = true;
			flag_angle = 1;
		}
		else
		{
			walking = true;
			velx = (vel * cos(gsDegreeToRadian(angle)));
			play++;
			vel = getBarForce(barx);
		}
	}
	else if (!gsInput->KeyDown(GSK_SPACE))
	{
		flag_space = false;
	}

	/*if (gsInput->KeyDown(GSK_ADD) && walking == false)
	{
		vel += 0.1;
	}
	else if (gsInput->KeyDown(GSK_SUBTRACT) && walking == false)
	{
		vel -= 0.1;
	}*/

	if (x > 630 && ver == false)
	{
		velx = -(velx) + velx/2;
		ver = true;
		side = -side;
	}

	if (y > 480 || x < 0 || (y < 0 && x > 640))
	{
		restart();
	}

	if (Can->colision(x, y, 20, 20))
	{
		restart();
		points++;
		effect.Play();
	}

	/*std::ostringstream str;
	str << "Força: " << vel;
	gsVideo->PrintText(GS_VECTOR2(10, 10), str.str().c_str(), "Arial", 20.0, GS_COLOR(255, 255,255,255));*/
	
	/*std::ostringstream str2;
	str2 << "Você fez " << points << " pontos em " << play << " jogadas.";
	gsVideo->PrintText(GS_VECTOR2(150, 10), str2.str().c_str(), "Arial", 20.0, GS_COLOR(255, 255,255,255));*/

	sprite.DrawSprite(GS_VECTOR2(x, y), GS_COLOR(255,255,255,255), rot_angle);
}

void cTrash::restart()
{
	walking = false;
	x = sx;
	y = sy;
	vely = 0;
	time = 0;
	ver = false;
	side = 1;
	barx = BAR_X_START;
	force = false;
	flag_angle = 0;
}

int cTrash::getBarForce(int x)
{
	int abs;
	abs = (BAR_X_END - BAR_X_START) / 2;

	int force = 0;

	if (x >= 640/2)
	{
		force = (640 - x) - (640 - BAR_X_END);
	}
	else
	{
		force = x - BAR_X_START;
	}

	force = ((force * (BAR_MAX_FORCE - BAR_MIN_FORCE)) / abs) +  BAR_MIN_FORCE;

	return force;
}

cCan *cTrash::getCan() const
{
	return Can;
}

int cTrash::getX() const
{
	return x;
}
int cTrash::getY() const
{
	return y;
}

int cTrash::getPoints() const
{
	return points;
}

bool cTrash::isWalking() const
{
	return walking;
}
