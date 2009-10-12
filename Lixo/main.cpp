#pragma comment (lib, "GameSpace.lib")

#include "cGame.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    cGame game;

	game.Init();
    
    return 0;
}