#include <Windows.h>
#include <iostream>
#include "utils.h"

#define GAME_NAME "game engine"
static bool gamerunning;

struct GAMEBITMAP
{
	BITMAPINFO bitmapinfo;
	int Width;
	int Height;
	int Pitch;
	void* Memory;
	int bpp;
};

struct Window_Dimension
{
	int width, height;
};

struct Pixel32
{
	uint8_t Blue;
	uint8_t Green;
	uint8_t Red;
	uint8_t Alpha;
};

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
	void RenderGraphics();


	
public:
	vi2d Pos;
	vi2d Size;
	int Width;
	int Height;
	HWND GameWindow = nullptr;
	int game_bpp = 32;
	int game_res_width = 384;
	int game_res_height = 216;
	int game_memory_size = (game_res_width * game_res_height * (game_bpp / 8));
	GAMEBITMAP BackBuffer;
	Pixel32 pixel32;
	
	MONITORINFO monitorinfo;
	bool fullscreen = false;
};