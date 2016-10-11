/*
#include <Windows.h>
#include "sge.h"

static const int FRAMES_PER_SECOND = 60;      ///< FPS:50
static const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

static int g_width, g_height;

static bool bFullScreen = false;

static HWND hWnd;

static OBJECT4DV1 obj;

static CAM4DV1 cam;


static UINT *buffer = NULL;

#define UNIVERSE_RADIUS   10000

#define POINT_SIZE        200
#define NUM_POINTS_X      (2*UNIVERSE_RADIUS/POINT_SIZE)
#define NUM_POINTS_Z      (2*UNIVERSE_RADIUS/POINT_SIZE)
#define NUM_POINTS        (NUM_POINTS_X*NUM_POINTS_Z)

#define NUM_TOWERS        96 * 2
#define NUM_TANKS         24 * 2
#define TANK_SPEED        8 * 2
#define TANK_ROTATE_SPEED 1


static bool keyboard_state[256];

static OBJECT4DV1     obj_tower,    // used to hold the master tower
obj_tank,     // used to hold the master tank
obj_marker,   // the ground marker
obj_player;   // the player object             

static POINT4D        towers[NUM_TOWERS],
tanks[NUM_TANKS];

static RENDERLIST4DV1 rend_list; // the render list

int min_clip_y = 0;
int max_clip_y = WINDOW_HEIGHT;

int min_clip_x = 0;
int max_clip_x = WINDOW_WIDTH;

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
	buffer = new UINT[size];
	memset(buffer, 0, sizeof(UINT)* size);

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
	VECTOR4D vpos = { 0.0f, 0, 0, 1.0f };
	VECTOR4D vrot = { 0.0f, 180.0f, 0.0f, 1.0f };
	

	// load the master tank object
	VECTOR4D_INITXYZ(&vscale, 0.75, 0.75, 0.75);
	Load_OBJECT4DV1_PLG(&obj_tank, "model/tank2.plg", &vscale, &vpos, &vrot);

	// load player object for 3rd person view
	VECTOR4D_INITXYZ(&vscale, 0.75, 0.75, 0.75);
	Load_OBJECT4DV1_PLG(&obj_player, "model/tank3.plg", &vscale, &vpos, &vrot);

	// load the master tower object
	VECTOR4D_INITXYZ(&vscale, 1.0, 2.0, 1.0);
	Load_OBJECT4DV1_PLG(&obj_tower, "model/tower1.plg", &vscale, &vpos, &vrot);

	// load the master ground marker
	VECTOR4D_INITXYZ(&vscale, 3.0, 3.0, 3.0);
	Load_OBJECT4DV1_PLG(&obj_marker, "model/marker1.plg", &vscale, &vpos, &vrot);

	// position the tanks
	for (int index = 0; index < NUM_TANKS; index++)
	{
		// randomly position the tanks
		tanks[index].x = RAND_RANGE(-UNIVERSE_RADIUS, UNIVERSE_RADIUS);
		tanks[index].y = 0; // obj_tank.max_radius;
		tanks[index].z = RAND_RANGE(-UNIVERSE_RADIUS, UNIVERSE_RADIUS);
		tanks[index].w = RAND_RANGE(0, 360);
	} // end for


	// position the towers
	for (int index = 0; index < NUM_TOWERS; index++)
	{
		// randomly position the tower
		towers[index].x = RAND_RANGE(-UNIVERSE_RADIUS, UNIVERSE_RADIUS);
		towers[index].y = 0; // obj_tower.max_radius;
		towers[index].z = RAND_RANGE(-UNIVERSE_RADIUS, UNIVERSE_RADIUS);
	} // end for

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
	static float view_angle = 0;
	static float camera_distance = 6000;
	static VECTOR4D pos = { 0, 0, 0, 0 };
	static float tank_speed;
	static float turning = 0;

	if (keyboard_state[VK_SPACE])
		tank_speed = 5 * TANK_SPEED;
	else
		tank_speed = TANK_SPEED;

	// forward/backward
	if (keyboard_state['W'] || keyboard_state['w'])
	{
		// move forward
		cam.pos.x -= tank_speed*Fast_Sin(cam.dir.y);
		cam.pos.z -= tank_speed*Fast_Cos(cam.dir.y);
	} // end if

	if (keyboard_state['S'] || keyboard_state['s'])
	{
		// move backward
		cam.pos.x += tank_speed*Fast_Sin(cam.dir.y);
		cam.pos.z += tank_speed*Fast_Cos(cam.dir.y);
	} // end if

	// rotate
	if (keyboard_state['D'] || keyboard_state['d'])
	{
		cam.dir.y -= TANK_ROTATE_SPEED;

		// add a little turn to object
		if ((turning -= 2) < -15)
			turning = -15;

	} // end if

	if (keyboard_state['a'] || keyboard_state['A'])
	{
		cam.dir.y += TANK_ROTATE_SPEED;

		// add a little turn to object
		if ((turning += 2) > 15)
			turning = 15;

	} // end if
	else // center heading again
	{
		if (turning > 0)
			turning -= 1;
		else
		if (turning < 0)
			turning += 1;

	} // end else

	
	for (int i = 0; i < g_width * g_height; ++i)
	{
		buffer[i] = 0;// 0xffffffff;
	}

	Reset_RENDERLIST4DV1(&rend_list);

	static MATRIX4X4 mrot;   // general rotation matrix

	// generate camera matrix
	Build_CAM4DV1_Matrix_Euler(&cam, CAM_ROT_SEQ_ZYX);

	// insert the tanks in the world
	for (int index = 0; index < NUM_TANKS; index++)
	{
		// reset the object (this only matters for backface and object removal)
		Reset_OBJECT4DV1(&obj_tank);

		// generate rotation matrix around y axis
		Build_XYZ_Rotation_MATRIX4X4(0, tanks[index].y, 0, &mrot);

		// rotate the local coords of the object
		Transform_OBJECT4DV1(&obj_tank, &mrot, TRANSFORM_LOCAL_TO_TRANS, 1);

		// set position of tank
		obj_tank.world_pos.x = tanks[index].x;
		obj_tank.world_pos.y = tanks[index].y;
		obj_tank.world_pos.z = tanks[index].z;

		// attempt to cull object   
		if (!Cull_OBJECT4DV1(&obj_tank, &cam, CULL_OBJECT_XYZ_PLANES))
		{
			// if we get here then the object is visible at this world position
			// so we can insert it into the rendering list
			// perform local/model to world transform
			Model_To_World_OBJECT4DV1(&obj_tank, TRANSFORM_TRANS_ONLY);
			// insert the object into render list
			Insert_OBJECT4DV1_RENDERLIST4DV1(&rend_list, &obj_tank);
		} // end if

	} // end for

	// insert the player into the world
	// reset the object (this only matters for backface and object removal)
	Reset_OBJECT4DV1(&obj_player);

	// set position of tank
	obj_player.world_pos.x = cam.pos.x - 300 * Fast_Sin(cam.dir.y);
	obj_player.world_pos.y = cam.pos.y - 70;
	obj_player.world_pos.z = cam.pos.z - 300 * Fast_Cos(cam.dir.y);

	// generate rotation matrix around y axis
	Build_XYZ_Rotation_MATRIX4X4(0, cam.dir.y + turning, 0, &mrot);


	//static int deg = 0;
	//deg += 1;
	//if (deg > 360)
	//	deg = 0;
	//lights[0].pos.x = 300 * Fast_Sin(deg);	
	//lights[0].pos.z = 300 * Fast_Cos(deg);

	// rotate the local coords of the object
	Transform_OBJECT4DV1(&obj_player, &mrot, TRANSFORM_LOCAL_TO_TRANS, 1);

	// perform world transform
	Model_To_World_OBJECT4DV1(&obj_player, TRANSFORM_TRANS_ONLY);

	Cull_OBJECT4DV1(&obj_player, &cam, CULL_OBJECT_XYZ_PLANES);

	// insert the object into render list
	Insert_OBJECT4DV1_RENDERLIST4DV1(&rend_list, &obj_player);

	// insert the towers in the world
	for (int index = 0; index < NUM_TOWERS; index++)
	{
		// reset the object (this only matters for backface and object removal)
		Reset_OBJECT4DV1(&obj_tower);

		// set position of tower
		obj_tower.world_pos.x = towers[index].x;
		obj_tower.world_pos.y = towers[index].y;
		obj_tower.world_pos.z = towers[index].z;

		// attempt to cull object   
		if (!Cull_OBJECT4DV1(&obj_tower, &cam, CULL_OBJECT_XYZ_PLANES))
		{
			// if we get here then the object is visible at this world position
			// so we can insert it into the rendering list
			// perform local/model to world transform
			Model_To_World_OBJECT4DV1(&obj_tower);

			// insert the object into render list
			Insert_OBJECT4DV1_RENDERLIST4DV1(&rend_list, &obj_tower);
		} // end if

	} // end for

	// seed number generator so that modulation of markers is always the same
	srand(13);

	// insert the ground markers into the world
	for (int index_x = 0; index_x < NUM_POINTS_X; index_x++)
	for (int index_z = 0; index_z < NUM_POINTS_Z; index_z++)
	{
		// reset the object (this only matters for backface and object removal)
		Reset_OBJECT4DV1(&obj_marker);

		// set position of tower
		obj_marker.world_pos.x = RAND_RANGE(-100, 100) - UNIVERSE_RADIUS + index_x*POINT_SIZE;
		obj_marker.world_pos.y = obj_marker.max_radius;
		obj_marker.world_pos.z = RAND_RANGE(-100, 100) - UNIVERSE_RADIUS + index_z*POINT_SIZE;

		// attempt to cull object   
		if (!Cull_OBJECT4DV1(&obj_marker, &cam, CULL_OBJECT_XYZ_PLANES))
		{
			// if we get here then the object is visible at this world position
			// so we can insert it into the rendering list
			// perform local/model to world transform
			Model_To_World_OBJECT4DV1(&obj_marker);

			// insert the object into render list
			Insert_OBJECT4DV1_RENDERLIST4DV1(&rend_list, &obj_marker);
		} // end if

	} // end for

	// remove backfaces
	Remove_Backfaces_RENDERLIST4DV1(&rend_list, &cam);

	// apply world to camera transform
	World_To_Camera_RENDERLIST4DV1(&rend_list, &cam);

	Sort_RENDERLIST4DV1(&rend_list, SORT_POLYLIST_NEARZ);

	Light_RENDERLIST4DV1_World(&rend_list, &cam, lights, 2);

	Camera_To_Perspective_Screen_RENDERLIST4DV1(&rend_list, &cam);

	//Draw_RENDERLIST4DV1_Wire(&rend_list, (UCHAR *)buffer, g_width);
	Draw_RENDERLIST4DV1_Solid(&rend_list, (UCHAR *)buffer, g_width);
	
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

*/