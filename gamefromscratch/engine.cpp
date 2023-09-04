#include "engine.h"

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

bool GameEngine::Construct(vi2d pos, vi2d size)
{
	Pos = pos;
	Size = size;

	return true;
}



LRESULT GameEngine::WindowProc(HWND windowhandle, UINT Message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	switch (Message)
	{
	case WM_CREATE:
	{

	}break;


	case WM_PAINT:
	{


	}break;

	case WM_SIZE:
	{

	}break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
		
	}break;

	case WM_DESTROY:
	{
		
	}break;

	default:
	{
		result = DefWindowProc(windowhandle, Message, wParam, lParam);
	}
	}

	return result;
}

bool GameEngine::gamealreadyrunning()
{
	HANDLE Mutex = NULL;
	Mutex = CreateMutexA(NULL, false, GAME_NAME "gamemutex" );

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void GameEngine::ProcessPlayerInput()
{

}




bool GameEngine::CreateMainWindow()
{
	

	WNDCLASSA WindowClass = {};

	WindowClass.lpfnWndProc = WindowProc;
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.hInstance = GetModuleHandleA(nullptr);
	WindowClass.hIcon = LoadIconA(NULL, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursorA(NULL, IDC_ARROW);
	WindowClass.lpszClassName = GAME_NAME "Window Class";

	if (RegisterClassA(&WindowClass))
	{

		GameWindow = CreateWindowExA(
			0,
			WindowClass.lpszClassName,
			GAME_NAME,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			WindowClass.hInstance,
			0);

		if (GameWindow)
		{
			return true;
		}
		else
		{
			MessageBox(NULL, "window Creation failed", "error!", MB_ICONEXCLAMATION | MB_OK);
		return false;
			
		}
	}
	else
	{
		MessageBox(NULL, "window registeration failed", "error!", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}



	

	
}

void GameEngine::WindowEvent()
{
	MSG message;
	while (PeekMessage(&message, GameWindow, 0, 0, PM_REMOVE))
	{

		TranslateMessage(&message);
		DispatchMessageA(&message);
	}
}

bool GameEngine::Start()
{
	gamerunning = true;
	if (gamealreadyrunning() == true)
	{
		MessageBox(NULL, "window already opened failed", "error!", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}
	
	if (!CreateMainWindow()) return false;
	
	
	while (gamerunning)
	{
		WindowEvent();
		
	
	
		ProcessPlayerInput();


		Sleep(0);
	
	
	}
	
	return true;
}









