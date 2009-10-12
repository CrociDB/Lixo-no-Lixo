#include "cCan.h"

cCan::cCan(GAMESPACE_VIDEO_HANDLER *video)
{
	gsVideo = video;

	sprite.LoadSprite(gsVideo, "media/can.png", GS_ARGB(255,0,255,0));

	x = 474;
	y = 339;

	setColisionBoxes();
}

void cCan::setColisionBoxes()
{
	box[0].x = 49;
	box[0].y = 11;
	box[0].w = 67;
	box[0].h = 2;

	box[1].x = 89;
	box[1].y = 7;
	box[1].w = 27;
	box[1].h = 3;
}

void cCan::run()
{
	sprite.DrawSprite(GS_VECTOR2(x, y));
}

bool cCan::colision(int cx, int cy, int cw, int ch)
{
	for (int i = 0; i < MAX_COLISION_BOXES; i++)
	{
		if (cx+cw > box[i].x+x && cx < box[i].x+box[i].w+x && cy+ch > box[i].y+y && cy < box[i].y+box[i].h+y)
		{
			return true;
		}
	}

	return false;
}

int	cCan::getX() const
{
	return x;
}

int cCan::getY() const
{
	return y;
}