#include "cGame.h"

cGame::cGame()
{
	// Empty! :p
}

void cGame::Init()
{
	if (gsVideo.StartApplication(640, 480, "GameSpace", true))
	{
		state = STATE_OPEN;
		Game();
	}
}

void cGame::Game()
{
	gsInput.RegisterInputDevice(NULL);
	gsAudio.RegisterAudioDevice(NULL);
	gsVideo.HideCursor(false);

	while (state != STATE_EXIT)
	{
		switch(state)
		{
			case STATE_OPEN:
			{
				gameOpen();
				break;
			}
			case STATE_MENU:
			{
				gameMenu();
				break;
			}
			case STATE_GAME:
			{
				gameMain();
				break;
			}
			case STATE_END:
			{
				gameEnd();
				break;
			}
		}
	}
}

void cGame::gameOpen()
{
	gsPlayCutscene(&gsVideo, "media/crocidb.mpg", &gsInput);
	state = STATE_MENU;
}

void cGame::gameMenu()
{
	backMenu.LoadSprite(&gsVideo, "media/menu_back.png", GS_ARGB(255,0,255,0));
	trashPointer.LoadSprite(&gsVideo, "media/trash.png", GS_ARGB(255,0,255,0));

	GS_AUDIO_SAMPLE bgm;
	bgm.LoadSample(&gsAudio, "media/menu.ogg", GSST_SOUNDTRACK);
	bgm.SetVolume(0.5);
	bgm.SetLoop(true);
	bgm.Play();

	GS_AUDIO_SAMPLE effect;
	effect.LoadSample(&gsAudio, "media/menu_effect.ogg", GSST_SOUNDTRACK);

	int op = 0;
	int x = 226;
	int y = 252;

	fadeIn(backMenu, SPEED_FADES);

	while(gsVideo.ManageLoop())
	{
		gsInput.UpdateInputData();

		backMenu.DrawSprite(GS_VECTOR2(0, 0));

		switch(op)
		{
			case 0:
			{
				x = 226;
				y = 252;
				break;
			}

			case 1:
			{
				x = 334;
				y = 344;
				break;
			}
		}

		if (gsInput.KeyDown(GSK_DOWN) && op == 0)
		{
			if (op == 0)
			{
				op = 1;
				effect.Play();
			}
		}
		else if (gsInput.KeyDown(GSK_UP) && op == 1)
		{
			if (op == 1)
			{
				op = 0;
				effect.Play();
			}
		}
		else if (gsInput.KeyDown(GSK_ENTER))
		{
			if (op == 0)
			{
				fadeOut(backMenu, SPEED_FADES);
				state = STATE_GAME;
				break;
			}
			else if (op == 1)
			{
				fadeOut(backMenu, SPEED_FADES);
				exit(0);
			}
		}

		trashPointer.DrawSprite(GS_VECTOR2(x, y));

		if (gsInput.KeyDown(GSK_ESC))
		{
			fadeOut(backMenu, SPEED_FADES);
			exit(0);
			break;
		}
	}
}

void cGame::gameMain()
{
	cTrash trash(&gsVideo, &gsInput, &gsAudio);
	cMap map(&gsVideo, &trash);

	GS_SPRITE background;
	background.LoadSprite(&gsVideo, "media/background.png", GS_ARGB(255,0,255,0));

	GS_SPRITE clock;
	clock.LoadSprite(&gsVideo, "media/clock.png", GS_ARGB(255,0,255,0));

	GS_SPRITE pts;
	pts.LoadSprite(&gsVideo, "media/points.png", GS_ARGB(255,0,255,0));

	GS_AUDIO_SAMPLE bgm;
	bgm.LoadSample(&gsAudio, "media/game.ogg", GSST_SOUNDTRACK);
	bgm.SetVolume(0.5);
	bgm.SetLoop(true);
	bgm.Play();

	int start_time = gsVideo.GetElapsedTime();

	int time;
	
	fadeIn(background, SPEED_FADES);
	while (gsVideo.ManageLoop())
	{
		gsInput.UpdateInputData();
		background.DrawSprite(GS_VECTOR2(0, 0));

		trash.run();
		if (trash.isWalking())
			map.run();

		if (gsInput.KeyDown(GSK_ESC))
		{
			fadeOut(background, SPEED_FADES);
			exit(0);
			break;
		}

		points = trash.getPoints();

		time = (59 - ((gsVideo.GetElapsedTime() - start_time)/1000));

		if (time == -1)
		{
			state = STATE_END;
			fadeOut(background, SPEED_FADES);
			break;
		}

		/* Timeee */
		std::ostringstream strTime;
		strTime << time;

		clock.DrawSprite(GS_VECTOR2(510, 10));
		gsVideo.PrintText(GS_VECTOR2(556, 23), strTime.str().c_str(), "Arial", 50, GS_COLOR(255, 255,255,255));

		/* Points */
		std::ostringstream strPoints;
		strPoints << points;

		pts.DrawSprite(GS_VECTOR2(260, 10));
		gsVideo.PrintText(GS_VECTOR2(315, 23), strPoints.str().c_str(), "Arial", 50, GS_COLOR(255, 255,255,255));
	}
}

void cGame::gameEnd()
{
	GS_SPRITE end_back;
	end_back.LoadSprite(&gsVideo, "media/end.png", GS_ARGB(255,0,255,0));

	fadeIn(end_back, SPEED_FADES);
	while(gsVideo.ManageLoop())
	{
		gsInput.UpdateInputData();

		end_back.DrawSprite(GS_VECTOR2(0,0));

		std::ostringstream strPoints;
		strPoints << points;

		gsVideo.PrintText(GS_VECTOR2((points>9?273:299), 135), strPoints.str().c_str(), "Arial", 96, GS_COLOR(255,61,12,12));

		if (gsInput.KeyDown(GSK_ESC) || gsInput.KeyDown(GSK_ENTER) || gsInput.KeyDown(GSK_SPACE))
		{
			state = STATE_OPEN;
			fadeOut(end_back, SPEED_FADES);
			break;
		}
	}
}

void cGame::fadeIn(GS_SPRITE &back, int vel)
{
	GS_SPRITE color;
	color.LoadSprite(&gsVideo, "media/color.png", GS_ARGB(255,0,255,0));
	int count = 0;

	for (int i = 255; i > 0; i-=vel)
	{
		gsVideo.ManageLoop();
		back.DrawSprite(GS_VECTOR2(0, 0));
		color.DrawSprite(GS_VECTOR2(0, 0), GS_COLOR(i, 255, 255, 255));
	}
}

void cGame::fadeOut(GS_SPRITE &back, int vel)
{
	GS_SPRITE color;
	color.LoadSprite(&gsVideo, "media/color.png", GS_ARGB(255,0,255,0));
	int count = 0;

	for (int i = 0; i < 255; i+=vel)
	{
		gsVideo.ManageLoop();
		back.DrawSprite(GS_VECTOR2(0, 0));
		color.DrawSprite(GS_VECTOR2(0, 0), GS_COLOR(i, 255, 255, 255));
	}
}

