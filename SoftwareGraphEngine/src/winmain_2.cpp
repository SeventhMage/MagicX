#include <Windows.h>
#include "sge.h"

static const int FRAMES_PER_SECOND = 60;      ///< FPS:50
static const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

static int g_width, g_height;

static bool bFullScreen = false;

static int g_bufferSize = 0;

static HWND hWnd;

static CAM4DV1 cam;


static UINT *buffer = NULL;

static bool keyboard_state[256];

int min_clip_y = 0;
int max_clip_y = WINDOW_HEIGHT;

int min_clip_x = 0;
int max_clip_x = WINDOW_WIDTH;


//////////////////////////
static RENDERLIST4DV2 rend_list; // the render list
static OBJECT4DV2 obj;
BITMAP_IMAGE bitmap_image;

void InitObject();
void InitWindow();
void Run();
void Update(int delta);

int main(int argc, char *argv[])
{
	InitWindow();
	InitObject();
	Run();

	return 0;
}

static void AllocBuffer(int size)
{
	if (buffer)
		delete[]buffer;
	g_bufferSize = size;
	buffer = new UINT[size];
	memset(buffer, 0, sizeof(UINT)* size);
}

static void ClearBuffer()
{
	memset(buffer, 0, sizeof(UINT)* g_bufferSize);
}

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
					   keyboard_state[wParam] = true;

	}
		return 0;
	case WM_KEYUP:
	{
					 keyboard_state[wParam] = false;

	}
		return 0;
	case WM_MOUSEHWHEEL:
	{

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
					g_width = LOWORD(lParam);
					g_height = HIWORD(lParam);
	}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
	{

	}

		return 0;
	case WM_LBUTTONUP:
	{

	}
		return 0;
	case WM_LBUTTONDBLCLK:
		return 0;
	case WM_RBUTTONDOWN:
	{

	}
		return 0;
	case WM_RBUTTONUP:
	{

	}
		return 0;
	case WM_MOUSEMOVE:
	{
						 int x = LOWORD(lParam);
						 int y = HIWORD(lParam);
	}
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void InitWindow()
{
	HINSTANCE hInstance = GetModuleHandle(0);


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
	wcex.hbrBackground = NULL;// (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = "sge";
	wcex.hIconSm = 0;

	// if there is an icon, load it
	wcex.hIcon = (HICON)LoadImage(hInstance, __TEXT(""), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

	RegisterClassEx(&wcex);

	// calculate client size

	RECT clientSize;
	clientSize.top = 0;
	clientSize.left = 0;
	clientSize.right = WINDOW_WIDTH;
	clientSize.bottom = WINDOW_HEIGHT;

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
	hWnd = CreateWindow("sge", __TEXT(""), style, windowLeft, windowTop,
		realWidth, realHeight, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	// fix ugly ATI driver bugs.
	MoveWindow(hWnd, windowLeft, windowTop, realWidth, realHeight, TRUE);

}


void Run()
{
	UINT next_game_tick = GetTickCount();
	int sleep_time = 0;

	bool bQuit = false;
	while (true)
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{

			TranslateMessage(&msg);
			DispatchMessage(&msg);


			if (msg.message == WM_QUIT)
				bQuit = true;
		}
		else
		{
			UINT cur_time = GetTickCount();
			sleep_time = next_game_tick - cur_time;
			if (sleep_time <= 0)
			{
				next_game_tick = GetTickCount() + SKIP_TICKS;
				Update(SKIP_TICKS - sleep_time);
			}
			else
			{
				::Sleep(sleep_time);
			}
		}
		if (bQuit)
			break;
	}
}



void InitObject()
{
	Build_Sin_Cos_Tables();

	AllocBuffer(WINDOW_WIDTH * WINDOW_HEIGHT);

	VECTOR4D cam_pos = { 0, 40, 40, 1 };
	VECTOR4D cam_dir = { 0, 0, 0, 1 };
	VECTOR4D cam_tar = { 0, 0, 0, 1 };

	Init_CAM4DV1(&cam, CAM_MODEL_EULER, &cam_pos, &cam_dir, &cam_tar, 1.0f, 12000.0f, 90, WINDOW_WIDTH, WINDOW_HEIGHT);

	VECTOR4D vscale = { 1.0f, 1.0f, 1.0f, 1.0f };
	VECTOR4D vpos = { 0.0f, 0, -10, 1.0f };
	VECTOR4D vrot = { 0.0f, 180.0f, 0.0f, 1.0f };

	Load_OBJECT4DV2_COB(&obj, "model/tie04.cob", &vscale, &vpos, &vrot);	

	//BITMAP_FILE bitmap_file;
	//Load_Bitmap_File(&bitmap_file, "texture/wall01_256.bmp");

	//Create_Bitmap(&bitmap_image, 0, 0,
	//	bitmap_file.bitmapinfoheader.biWidth,
	//	bitmap_file.bitmapinfoheader.biHeight,
	//	bitmap_file.bitmapinfoheader.biBitCount);

	//// load the bitmap image (later make this 8/16 bit)
	//if (bitmap_image.bpp == 16)
	//	;
	//Load_Image_Bitmap16(&bitmap_image, &bitmap_file, 0, 0, BITMAP_EXTRACT_MODE_ABS);
	//Unload_Bitmap_File(&bitmap_file);


	RGBAV1 ambient;
	ambient.a = 255;
	ambient.r = 128;
	ambient.g = 128;
	ambient.b = 128;

	RGBAV1 diffuse;
	diffuse.a = 255;
	diffuse.r = 200;
	diffuse.g = 200;
	diffuse.b = 200;

	RGBAV1 specular;
	specular.a = 255;
	specular.r = 255;
	specular.g = 255;
	specular.b = 255;


	VECTOR4D lightPos = { 200, 200, 200, 1 };
	VECTOR4D lightDir = { 1, 1, 1, 1 };

	Init_Light_LIGHTV1(0, LIGHTV1_STATE_ON, LIGHTV1_ATTR_AMBIENT, ambient, diffuse, specular, &lightPos, &lightDir, 0, 0, 0, 0, 0, 0);
	Init_Light_LIGHTV1(1, LIGHTV1_STATE_ON, LIGHTV1_ATTR_INFINITE, ambient, diffuse, specular, &lightPos, &lightDir, 0, 0, 0, 0, 0, 0);
	//Init_Light_LIGHTV1(0, LIGHTV1_STATE_ON, LIGHTV1_ATTR_POINT, ambient, diffuse, specular, &lightPos, &lightDir, 1, 0, 0, 0, 0, 0);
	//Init_Light_LIGHTV1(0, LIGHTV1_STATE_ON, LIGHTV1_ATTR_SPOTLIGHT1, ambient, diffuse, specular, &lightPos, &lightDir, 1, 0, 0, 5, 20, 10);
	//Init_Light_LIGHTV1(0, LIGHTV1_STATE_ON, LIGHTV1_ATTR_SPOTLIGHT2, ambient, diffuse, specular, &lightPos, &lightDir, 1, 0, 0, 30, 60, 10);
}


void Update(int delta)
{	
	ClearBuffer();

	Reset_OBJECT4DV2(&obj);
	Reset_RENDERLIST4DV2(&rend_list);

	Rotate_XYZ_OBJECT4DV2(&obj, 0, 1, 0, 1);

	if (!Cull_OBJECT4DV2(&obj, &cam, CULL_OBJECT_XYZ_PLANES))
	{
		Model_To_World_OBJECT4DV2(&obj);
		Insert_OBJECT4DV2_RENDERLIST4DV2(&rend_list, &obj);
	}

	//Remove_Backfaces_RENDERLIST4DV2(&rend_list, &cam);
	
	World_To_Camera_RENDERLIST4DV2(&rend_list, &cam);

	Sort_RENDERLIST4DV2(&rend_list, SORT_POLYLIST_NEARZ);

	Light_RENDERLIST4DV2_World16(&rend_list, &cam, lights, 2);

	Camera_To_Perspective_Screen_RENDERLIST4DV2(&rend_list, &cam);

	//Draw_RENDERLIST4DV2_Wire16(&rend_list, (UCHAR *)buffer, g_width);
	//Draw_RENDERLIST4DV2_Solid16(&rend_list, (UCHAR *)buffer, g_width);
	
	if (obj.texture)
		Draw_RENDERLIST4DV2_Textured16(&rend_list, (UCHAR *)buffer, g_width, obj.texture);
	else
		Draw_RENDERLIST4DV2_Solid16(&rend_list, (UCHAR *)buffer, g_width);

	HDC hdc = GetDC(hWnd);

	HDC mdc = CreateCompatibleDC(hdc);
	CreateCompatibleBitmap(mdc, 0, 0);
	HBITMAP hBitmap = CreateBitmap(g_width, g_height, 1, 32, buffer);
	SelectObject(mdc, hBitmap);

	char buf[256] = { 0 };
	itoa(1000 / delta, buf, 10);
	TextOut(mdc, 0, 0, buf, strlen(buf));

	BitBlt(hdc, 0, 0, g_width, g_height, mdc, 0, 0, SRCCOPY);

	::SwapBuffers(hdc);

	DeleteObject(hBitmap);
	DeleteDC(mdc);
	DeleteDC(hdc);
}