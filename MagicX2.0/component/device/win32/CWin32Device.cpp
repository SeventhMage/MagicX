#include "CWin32Device.h"
#include "device/IKeyEvent.h"
#include "../CEventManager.h"
#include "render/IRenderDriver.h"

namespace mx
{
	namespace device
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
							   IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
							   if (event)
							   {
								   switch (wParam)
								   {
								   case VK_SPACE:
									   event->Press(EKP_KEYBOARD_SPACE);
									   break;
								   case VK_ESCAPE:
									   event->Press(EKP_KEYBOARD_ESC);
								   case 'N':
								   case 'n':
									   event->Press(EKP_KEYBOARD_N);
									   break;
								   }

							   }
			}
				return 0;
			case WM_KEYUP:
			{
							 IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
							 if (event)
							 {
								 switch (wParam)
								 {
								 case VK_SPACE:
									 event->Up(EKP_KEYBOARD_SPACE);
									 break;
								 case 'N':
								 case 'n':
									 event->Up(EKP_KEYBOARD_N);
									 break;
								 }

							 }

			}
				return 0;
			case WM_MOUSEHWHEEL:
			{

								   //收不到消息
								   short zDelta = HIWORD(wParam);
								   if (zDelta > 0)
								   {

								   }
								   else
								   {

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
								   IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
								   if (event)
								   {
									   event->Press(EKP_MOUSE_LBUTTON);
								   }
			}

				return 0;
			case WM_LBUTTONUP:
			{
								 IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
								 if (event)
								 {
									 event->Up(EKP_MOUSE_LBUTTON);
								 }
			}
				return 0;
			case WM_LBUTTONDBLCLK:
				return 0;
			case WM_RBUTTONDOWN:
			{
								   IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
								   if (event)
								   {
									   event->Press(EKP_MOUSE_RBUTTON);
								   }
			}
				return 0;
			case WM_RBUTTONUP:
			{
								 IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
								 if (event)
								 {
									 event->Up(EKP_MOUSE_RBUTTON);
								 }
			}
				return 0;
			case WM_MOUSEMOVE:
			{
								 IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
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

		CWin32Device::CWin32Device(uint uPosX, uint uPosY, uint uWidth, uint uHeight, bool bFullScreen /*= false*/)
			:m_uPosX(uPosX), m_uPosY(uPosY), m_uWidth(uWidth), m_uHeight(uHeight)
		{
			CEventManager::Instance()->SetDevice(this);

			memset(m_driverList, 0, sizeof(m_driverList));

			HINSTANCE hInstance = GetModuleHandle(0);

			const wchar_t* ClassName = __TEXT("CWin32Device");

			// Register Class
			WNDCLASSEX wcex;
			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc = WndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = hInstance;
			wcex.hIcon = NULL;
			wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
			wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wcex.lpszMenuName = 0;
			wcex.lpszClassName = ClassName;
			wcex.hIconSm = 0;

			// if there is an icon, load it
			wcex.hIcon = (HICON)LoadImage(hInstance, __TEXT(""), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

			RegisterClassEx(&wcex);

			// calculate client size

			RECT clientSize;
			clientSize.top = 0;
			clientSize.left = 0;
			clientSize.right = uWidth;
			clientSize.bottom = uHeight;

			DWORD style = WS_POPUP;

			if (!bFullScreen)
				style = WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

			AdjustWindowRect(&clientSize, style, FALSE);

			int realWidth = clientSize.right - clientSize.left;
			int realHeight = clientSize.bottom - clientSize.top;

			int windowLeft = (GetSystemMetrics(SM_CXSCREEN) - realWidth) / 2;
			int windowTop = (GetSystemMetrics(SM_CYSCREEN) - realHeight) / 2;

			if (windowLeft < 0)
				windowLeft = 0;
			if (windowTop < 0)
				windowTop = 0;	// make sure window menus are in screen on creation

			if (bFullScreen)
			{
				windowLeft = 0;
				windowTop = 0;
				HWND hDesk = GetDesktopWindow();
				RECT rc;
				GetWindowRect(hDesk, &rc);
				realWidth = rc.right;
				realHeight = rc.bottom;
			}

			// create window
			m_hWnd = CreateWindow(ClassName, __TEXT(""), style, windowLeft, windowTop,
				realWidth, realHeight, NULL, NULL, hInstance, NULL);

			ShowWindow(m_hWnd, SW_SHOWNORMAL);
			UpdateWindow(m_hWnd);

			// fix ugly ATI driver bugs.
			MoveWindow(m_hWnd, windowLeft, windowTop, realWidth, realHeight, TRUE);
		}

		CWin32Device::~CWin32Device()
		{
			for (int i = 0; i < E_DDT_NUM; ++i)
			{
				if (m_driverList[i])
				{
					delete m_driverList[i];
					m_driverList[i] = NULL;
				}
			}
		}

		bool CWin32Device::SetupDriver(IDeviceDriver *driver)
		{
			bool bRet = false;
			if (driver)
			{
				m_driverList[driver->GetDriverType()] = driver;

				HDC hDC = GetDC(m_hWnd);
				bRet = m_driverList[driver->GetDriverType()]->SetupWin32Driver(hDC);
				ReleaseDC(m_hWnd, hDC);				
			}
			return bRet;
		}

		void CWin32Device::SwapBuffers()
		{
			HDC hDC = GetDC(m_hWnd);
			::SwapBuffers(hDC);
			ReleaseDC(m_hWnd, hDC);
		}

		long CWin32Device::GetSystemRunTime()
		{
			return GetTickCount();
		}

		void CWin32Device::Sleep(unsigned long ms)
		{
			::Sleep(ms);
		}

		bool CWin32Device::Run()
		{
			bool bQuit = false;
			MSG msg;
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				//while (GetMessage(&msg, NULL, 0, 0))
			{
				// No message translation because we don't use WM_CHAR and it would conflict with our
				// deadkey handling.
				//if (msg.hwnd == m_hWnd)
				//WndProc(m_hWnd, msg.message, msg.wParam, msg.lParam);
				//else
				TranslateMessage(&msg);
				DispatchMessage(&msg);


				if (msg.message == WM_QUIT)
					bQuit = true;
			}
			return !bQuit;
		}

		void CWin32Device::OnSize(uint uPosX, uint uPosY, uint uWidth, uint uHeight)
		{
			if (m_driverList[E_DDT_RENDERER])
				((render::IRenderDriver *)m_driverList[E_DDT_RENDERER])->OnSize(uPosX, uPosY, uWidth, uHeight);
		}

		render::IRenderer * CWin32Device::GetRenderer()
		{
			if (m_driverList[E_DDT_RENDERER])
				return ((render::IRenderDriver*)m_driverList[E_DDT_RENDERER])->GetRenderer();
			else
				return NULL;
		}

	}
}