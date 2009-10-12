#include "cMap.h"

cMap::cMap(GAMESPACE_VIDEO_HANDLER *pVideo, cTrash *pTrash)
{
	gsVideo = pVideo;
	trash = pTrash;

	back.LoadSprite(gsVideo, "media/map_back.png", GS_ARGB(255,255,255,255));
	can.LoadSprite(gsVideo, "media/little_can.png", GS_ARGB(255,255,255,255));
	ball.LoadSprite(gsVideo, "media/little_trash.png", GS_ARGB(255,255,255,255));

	x = 6;
	y = 6;
}

void cMap::run()
{
	back.DrawSprite(GS_VECTOR2(x, y), GS_COLOR(140,255,255,255));
	can.DrawSprite(GS_VECTOR2((trash->getCan()->getX()*120/640) + x, 116 + y));
	ball.DrawSprite(GS_VECTOR2((trash->getX()*120/640) + x, (trash->getY()*75/480) + (y + 60)));
}
