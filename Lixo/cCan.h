#ifndef _CCAN_H_
#define _CCAN_H_

#include <gamespace.h>
#include <windows.h>

#define MAX_COLISION_BOXES			2

struct ColBoxes
{
	int x, y;
	int w, h;
};

class cCan
{
private:
	GAMESPACE_VIDEO_HANDLER *gsVideo;

	GS_SPRITE sprite;

	ColBoxes box[MAX_COLISION_BOXES];

	int x, y;
public:
				cCan(GAMESPACE_VIDEO_HANDLER *video);
	void		setColisionBoxes();


	void		run();

	bool		colision(int cx, int cy, int cw, int ch);

	int			getX() const;
	int			getY() const;

};

#endif