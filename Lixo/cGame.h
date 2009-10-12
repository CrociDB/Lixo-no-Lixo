#include <gamespace.h>
#include <windows.h>

#include "cTrash.h"
#include "cMap.h"

#define SPEED_FADES						10

enum GameState
{
	STATE_OPEN,
	STATE_MENU,
	STATE_GAME,
	STATE_END,
	STATE_EXIT
};

class cGame
{
private:
	/* GameSpace Vars... */
	GAMESPACE_VIDEO_HANDLER gsVideo;
    GAMESPACE_INPUT_HANDLER gsInput;
    GAMESPACE_AUDIO_HANDLER gsAudio;

	/* Resources for Menu */
	GS_SPRITE		backMenu;
	GS_SPRITE		trashPointer;

	/* State */
	GameState state;

	/* Points */
	int points;
public:
	cGame();

	void			Init();

	void			Game();

	/* GameState methods */
	void			gameOpen();
	void			gameMenu();
	void			gameMain();
	void			gameEnd();

	void			fadeIn(GS_SPRITE &back, int vel);
	void			fadeOut(GS_SPRITE &back, int vel);
};