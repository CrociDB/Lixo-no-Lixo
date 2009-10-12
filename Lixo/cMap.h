#include <gamespace.h>
#include <windows.h>

#include "cTrash.h"

class cMap
{
private:
	GAMESPACE_VIDEO_HANDLER	*gsVideo;

	cTrash					*trash;

	GS_SPRITE				back;
	GS_SPRITE				ball;
	GS_SPRITE				can;
	int						x, y;
public:
							cMap(GAMESPACE_VIDEO_HANDLER *pVideo, cTrash *pTrash);

	void					run();
};