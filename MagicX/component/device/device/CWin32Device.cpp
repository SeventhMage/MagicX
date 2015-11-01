#include "CWin32Device.h"
#include "../include/CDeviceManager.h"
#include "../include/IDeviceDriver.h"
#include "glew/gl/glew.h"
#include "../include/IKeyEvent.h"
#include "../include/CEventManager.h"

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
				IDevice *device = CDeviceManager::Instance()->GetDevice();
				if (device)
				{
					device->OnSize(0, 0, LOWORD(lParam), HIWORD(lParam));
				}
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

		CWin32Device::CWin32Device(uint uWidth, uint uHeight, bool bFullScreen /*= false*/)
			:IDevice(uWidth, uHeight, bFullScreen)
			, m_uWidth(uWidth)
			, m_uHeight(uHeight)			
		{
			memset(m_deviceDriver, 0, sizeof(m_deviceDriver));

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
			wcex.hCursor =  LoadCursor(NULL, IDC_ARROW);
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

			const int realWidth = clientSize.right - clientSize.left;
			const int realHeight = clientSize.bottom - clientSize.top;

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
			}
		
			// create window
			m_hWnd = CreateWindow(ClassName, __TEXT(""), style, windowLeft, windowTop,
				realWidth, realHeight, NULL, NULL, hInstance, NULL);

			ShowWindow(m_hWnd, SW_SHOWNORMAL);
			UpdateWindow(m_hWnd);

			// fix ugly ATI driver bugs. Thanks to ariaci
			MoveWindow(m_hWnd, windowLeft, windowTop, realWidth, realHeight, TRUE);
		}

		CWin32Device::~CWin32Device()
		{
			for (int i = 0; i < DDT_NUM; ++i)
				SAFE_DEL(m_deviceDriver[i]);
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

		void CWin32Device::SwapBuffers()
		{
			HDC hDC = GetDC(m_hWnd);
			::SwapBuffers(hDC);
			ReleaseDC(m_hWnd, hDC);
		}

		void CWin32Device::OnSize(int iLeft, int iTop, int iWidth, int iHeight)
		{
			if (m_deviceDriver[DDT_RENDERER])
				((CRenderDriver *)m_deviceDriver[DDT_RENDERER])->OnSize(iLeft, iTop, iWidth, iHeight);
		}

		long CWin32Device::GetSystemRunTime()
		{
			return GetTickCount();
		}

		void CWin32Device::Sleep(unsigned long ms)
		{
			::Sleep(ms);
		}

		bool CWin32Device::SetupDriver(IDeviceDriver *driver)
		{
			if (!driver)
				return false;

			bool bRet = false;
			switch (driver->GetDriverType())
			{
			case DDT_RENDERER:
			{
								 HDC hDC = GetDC(m_hWnd);
								 bRet = ((CRenderDriver *)driver)->SetupWin32Renderer(hDC);								 
								 ReleaseDC(m_hWnd, hDC);
			}
				break;
			default:
				break;
			}
			if (bRet)
				m_deviceDriver[driver->GetDriverType()] = driver;
			return bRet;
		}

		IDeviceDriver * CWin32Device::GetDeviceDriver(DeviceDriverType driverType)
		{
			if (driverType >= 0 && driverType < DDT_NUM)
				return m_deviceDriver[driverType];
			return NULL;
		}

	}
}