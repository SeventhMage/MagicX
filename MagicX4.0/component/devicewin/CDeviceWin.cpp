#include "CDeviceWin.h"
#include "CKeyEvent.h"
#include "device/CEventManager.h"


namespace mx
{
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
			return 0;
		case WM_ERASEBKGND:
			return 0;

		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
			return 0;
			
		case WM_KEYDOWN:
		{
			CKeyEvent *event = (CKeyEvent *)CEventManager::Instance()->GetEvent(ET_KEYBOARD);
			if (event)
			{
				switch (wParam)
				{
				case VK_SPACE:
				   event->OnPress(KP_KEYBOARD_SPACE);
				   break;
				case VK_ESCAPE:
				   event->OnPress(KP_KEYBOARD_ESC);
				case 'N':
				case 'n':
				   event->OnPress(KP_KEYBOARD_N);
				   break;
				case 'A':
				case 'a':
				   event->OnPress(KP_KEYBOARD_A);
				   break;
				case 'D':
				case 'd':
				   event->OnPress(KP_KEYBOARD_D);
				   break;
				case 'W':
				case 'w':
				   event->OnPress(KP_KEYBOARD_W);
				   break;
				case 'S':
				case 's':
				   event->OnPress(KP_KEYBOARD_S);
				   break;
				}

			}
		}
			return 0;
		case WM_KEYUP:
		{
			CKeyEvent *event = (CKeyEvent *)CEventManager::Instance()->GetEvent(ET_KEYBOARD);
			if (event)
			{
			 switch (wParam)
			 {
			 case VK_SPACE:
				 event->OnUp(KP_KEYBOARD_SPACE);
				 break;
			 case 'N':
			 case 'n':
				 event->OnUp(KP_KEYBOARD_N);
				 break;
			 case 'A':
			 case 'a':
				 event->OnUp(KP_KEYBOARD_A);
				 break;
			 case 'D':
			 case 'd':
				 event->OnUp(KP_KEYBOARD_D);
				 break;
			 case 'W':
			 case 'w':
				 event->OnUp(KP_KEYBOARD_W);
				 break;
			 case 'S':
			 case 's':
				 event->OnUp(KP_KEYBOARD_S);
				 break;
			 }

			}

		}
			return 0;
		case WM_MOUSEWHEEL:
		{
			CKeyEvent *event = (CKeyEvent *)CEventManager::Instance()->GetEvent(ET_KEYBOARD);
			if (event)
			{
				short zDelta = HIWORD(wParam);
				event->OnWheel(zDelta);
			}								   				
		}
			return 0;
		case WM_SIZE:
		{
			CEventManager::Instance()->OnSize(0, 0, LOWORD(lParam), HIWORD(lParam));
		}
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_SYSCOMMAND:
			// prevent screensaver or monitor powersave mode from starting
			if ((wParam & 0xFFF0) == SC_SCREENSAVE ||
				(wParam & 0xFFF0) == SC_MONITORPOWER ||
				(wParam & 0xFFF0) == SC_KEYMENU
				)
				return 0;

			break;

		case WM_ACTIVATE:
			// we need to take care for screen changes, e.g. Alt-Tab

			break;

		case WM_USER:

			return 0;

		case WM_SETCURSOR:
			// because Windows forgot about that in the meantime


		case WM_INPUTLANGCHANGE:
			// get the new codepage used for keyboard input

			return 0;
			
		case WM_LBUTTONDOWN:
		{
			CKeyEvent *event = (CKeyEvent *)CEventManager::Instance()->GetEvent(ET_KEYBOARD);
			if (event)
			{
			   event->OnPress(KP_MOUSE_LBUTTON);
			}
		}

			return 0;
		case WM_LBUTTONUP:
		{
			CKeyEvent *event = (CKeyEvent *)CEventManager::Instance()->GetEvent(ET_KEYBOARD);
			 if (event)
			 {
				 event->OnUp(KP_MOUSE_LBUTTON);
			 }
		}
			return 0;
		case WM_LBUTTONDBLCLK:
			return 0;
		case WM_RBUTTONDOWN:
		{
			CKeyEvent *event = (CKeyEvent *)CEventManager::Instance()->GetEvent(ET_KEYBOARD);
			if (event)
			{
			   event->OnPress(KP_MOUSE_RBUTTON);
			}
		}
			return 0;
		case WM_RBUTTONUP:
		{
			CKeyEvent *event = (CKeyEvent *)CEventManager::Instance()->GetEvent(ET_KEYBOARD);
			if (event)
			{
			 event->OnUp(KP_MOUSE_RBUTTON);
			}
		}
			return 0;
		case WM_MOUSEMOVE:
		{
			CKeyEvent *event = (CKeyEvent *)CEventManager::Instance()->GetEvent(ET_KEYBOARD);
			if (event)
			{
			 int x = LOWORD(lParam);
			 int y = HIWORD(lParam);
			 event->SetMousePosition(x, y);
			}
		}
		
			return 0;
		}
		

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
		
	CDeviceWin::CDeviceWin(IRenderer *pRenderer, int x, int y, int width, int height, bool fullScreen)
	{	
		HINSTANCE hInstance = GetModuleHandle(0);

		CEventManager::Instance()->RegisterEvent(new CKeyEvent());
		CEventManager::Instance()->SetDevice(this);

		const char* ClassName = "CWin32Device";

		// Register Class
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadCursor(NULL, IDC_ARROW);
		wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
		wcex.hbrBackground = NULL;// (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = 0;
		wcex.lpszClassName = ClassName;
		wcex.hIconSm = 0;

		// if there is an icon, load it
		wcex.hIcon = (HICON)LoadImage(hInstance, "", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

		RegisterClassEx(&wcex);

		// calculate client size

		RECT clientSize;
		clientSize.top = x;
		clientSize.left = x;
		clientSize.right = width;
		clientSize.bottom = height;

		DWORD style = WS_POPUP;

		if (!fullScreen)
			style = WS_OVERLAPPEDWINDOW;//WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

		AdjustWindowRect(&clientSize, style, FALSE);

		int realWidth = clientSize.right - clientSize.left;
		int realHeight = clientSize.bottom - clientSize.top;

		int windowLeft = (GetSystemMetrics(SM_CXSCREEN) - realWidth) / 2;
		int windowTop = (GetSystemMetrics(SM_CYSCREEN) - realHeight) / 2;

		if (windowLeft < 0)
			windowLeft = 0;
		if (windowTop < 0)
			windowTop = 0;	// make sure window menus are in screen on creation

		if (fullScreen)
		{
			windowLeft = 0;
			windowTop = 0;
			HWND hDesk = GetDesktopWindow();
			RECT rc;
			GetWindowRect(hDesk, &rc);
			realWidth = rc.right;
			realHeight = rc.bottom;;
		}
		m_iWidth = realWidth;
		m_iHeight = realHeight;
		// create window
		m_hWnd = CreateWindow(ClassName, "", style, windowLeft, windowTop,
			realWidth, realHeight, NULL, NULL, hInstance, NULL);

		//初始化渲染器驱动
		m_pRenderer = pRenderer;
		HDC hDC = GetDC(m_hWnd);
		m_pRenderer->InitDriver(hDC);
		ReleaseDC(m_hWnd, hDC);

		ShowWindow(m_hWnd, SW_SHOWNORMAL);
		UpdateWindow(m_hWnd);			

		// fix ugly ATI driver bugs.
		MoveWindow(m_hWnd, windowLeft, windowTop, realWidth, realHeight, TRUE);

		ShowCursor(TRUE);		
	}
	
	CDeviceWin::~CDeviceWin()
	{
		
	}
	
	void CDeviceWin::SwapBuffers()
		{
			HDC hDC = ::GetDC(m_hWnd);
			::SwapBuffers(hDC);
			::ReleaseDC(m_hWnd, hDC);
		}

	int CDeviceWin::GetWindowWidth()const
	{
		return m_iWidth;
	}

	int CDeviceWin::GetWindowHeight()const
	{
		return m_iHeight;
	}

	unsigned long long CDeviceWin::GetSystemRunTime()const
	{
		return GetTickCount64();
	}

	void CDeviceWin::Sleep(unsigned long ms)
	{
		::Sleep(ms);
	}

	void CDeviceWin::OnSize(int x, int y, int width, int height)
	{
		if (m_pRenderer)
			m_pRenderer->OnSize(x, y, width, height);
		m_iWidth = width;
		m_iHeight = height;
	}

	bool CDeviceWin::Run()
	{
		bool bQuit = false;
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				bQuit = true;
		}
		return !bQuit;

	}

}