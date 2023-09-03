#include <Windows.h>
#include <iostream>
#include "utils.h"

#define GAME_NAME "game engine"
static bool gamerunning;

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	bool Construct(vi2d pos, vi2d size);
	void WindowEvent();
	bool CreateMainWindow();
	bool Start();
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	bool gamealreadyrunning();
	void ProcessPlayerInput();
	
public:
	vi2d Pos;
	vi2d Size;
	HWND GameWindow = nullptr;
	
};