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
	monitorinfo = {sizeof(MONITORINFO)};

	
	

	BackBuffer.bitmapinfo.bmiHeader.biSize = sizeof(BackBuffer.bitmapinfo.bmiHeader);
	BackBuffer.bitmapinfo.bmiHeader.biWidth = game_res_width;
	BackBuffer.bitmapinfo.bmiHeader.biHeight = game_res_height;
	BackBuffer.bitmapinfo.bmiHeader.biBitCount = game_bpp;
	BackBuffer.bitmapinfo.bmiHeader.biCompression = BI_RGB;
	BackBuffer.bitmapinfo.bmiHeader.biPlanes = 1;
	BackBuffer.Memory = VirtualAlloc(NULL, game_memory_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	if (BackBuffer.Memory == NULL)
	{
		MessageBox(NULL, "failed to allocation memory", "error!", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	memset(BackBuffer.Memory, 0xff, game_memory_size);

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
		gamerunning = false;
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
	int16_t EscapeKeyIsDown = GetAsyncKeyState(VK_ESCAPE);
	if (EscapeKeyIsDown)
	{
		SendMessageA(GameWindow, WM_CLOSE, 0, 0);
	}

}

void GameEngine::RenderGraphics()
{
	HDC DeviceContext = GetDC(GameWindow);

	StretchDIBits(DeviceContext, 0, 0, 100, 100, 0, 0, 100, 100,
		BackBuffer.Memory, &BackBuffer.bitmapinfo, DIB_RGB_COLORS, SRCCOPY);


	ReleaseDC(GameWindow,DeviceContext);
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
	WindowClass.hbrBackground = CreateSolidBrush(RGB(0, 100, 255));

	if (RegisterClassA(&WindowClass))
	{
		DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME | WS_OVERLAPPEDWINDOW;
		vi2d topleft = Pos;
		//
		//if (fullscreen)
		//{
		//	if (GetMonitorInfoA(MonitorFromWindow(GameWindow, MONITOR_DEFAULTTOPRIMARY), &monitorinfo) == 0)
		//	{
		//		MessageBox(NULL, "window Creation failed", "error!", MB_ICONEXCLAMATION | MB_OK);
		//		return false;
		//	}
		//
		//	dwExStyle = 0;
		//	dwStyle = WS_VISIBLE | WS_POPUP | WS_OVERLAPPEDWINDOW;
		//
		//	Size = { monitorinfo.rcMonitor.right, monitorinfo.rcMonitor.bottom };
		//	topleft = { 0,0 };
		//}
		//int mw = monitorinfo.rcMonitor.right - monitorinfo.rcMonitor.left;
		//int mh = monitorinfo.rcMonitor.bottom - monitorinfo.rcMonitor.top;
		//
		//RECT GameWindowSize = { 0,0, Size.x, Size.y };
		//AdjustWindowRectEx(&GameWindowSize, dwStyle, FALSE, dwExStyle);
		//int width = GameWindowSize.right - GameWindowSize.left;
		//int height = GameWindowSize.bottom - GameWindowSize.top;

		

		GameWindow = CreateWindowExA(
			dwExStyle,
			WindowClass.lpszClassName,
			GAME_NAME,
			dwStyle,
			topleft.x,
			topleft.y,
			Size.x,
			Size.y,
			0,
			0,
			WindowClass.hInstance,
			0);

		if (fullscreen)
		{
			if (GetMonitorInfoA(MonitorFromWindow(GameWindow, MONITOR_DEFAULTTOPRIMARY), &monitorinfo) == 0)
			{
				MessageBox(NULL, "window Creation failed", "error!", MB_ICONEXCLAMATION | MB_OK);
				return false;
			}

			int monitorWidth = monitorinfo.rcMonitor.right - monitorinfo.rcMonitor.left;
			int monitorHeight = monitorinfo.rcMonitor.bottom - monitorinfo.rcMonitor.top;

			SetWindowLongPtrA(GameWindow, GWL_STYLE, (WS_OVERLAPPEDWINDOW | WS_VISIBLE) & ~WS_OVERLAPPEDWINDOW);

			SetWindowPos(GameWindow, HWND_TOPMOST, monitorinfo.rcMonitor.left, monitorinfo.rcMonitor.top,
				monitorWidth, monitorHeight, SWP_FRAMECHANGED);

		}
		

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
	while (PeekMessageA(&message,GameWindow, 0, 0, PM_REMOVE))
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

		RenderGraphics();

		Sleep(0);
	
	
	}
	
	return true;
}









