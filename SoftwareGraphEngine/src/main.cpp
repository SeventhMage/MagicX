#include "sge.h"
#include <assert.h>
#include <time.h>
#include <math.h>
#pragma comment(lib, "glew32s.lib")

enum VAO_IDs
{
	VAO_1,
	NumVAOs,
};

enum Buffer_IDs
{
	ArrayBuffer,
	ElementBuffer,
	NumBuffers,
};

enum Attrib_IDs
{
	vPosition = 0
};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

OBJECT4DV1 obj;

CAM4DV1 cam;

GLuint *indexBuffer = NULL;

UINT *buffer = NULL;

// defines for the game universe
#define UNIVERSE_RADIUS   4000

#define POINT_SIZE        200
#define NUM_POINTS_X      (2*UNIVERSE_RADIUS/POINT_SIZE)
#define NUM_POINTS_Z      (2*UNIVERSE_RADIUS/POINT_SIZE)
#define NUM_POINTS        (NUM_POINTS_X*NUM_POINTS_Z)

#define NUM_TOWERS        96
#define NUM_TANKS         24
#define TANK_SPEED        15


int keyboard_state[256];

OBJECT4DV1     obj_tower,    // used to hold the master tower
obj_tank,     // used to hold the master tank
obj_marker,   // the ground marker
obj_player;   // the player object             

POINT4D        towers[NUM_TOWERS],
tanks[NUM_TANKS];

RENDERLIST4DV1 rend_list; // the render list

int ImageWidth, ImageHeight;

static void LoadBmp()
{
	// 打开文件
	FILE* pFile = fopen("image/grass1.bmp", "rb");
	if (pFile == 0)
		exit(0);
	// 读取图象的大小信息
	fseek(pFile, 0x0012, SEEK_SET);
	
	fread(&ImageWidth, sizeof(ImageWidth), 1, pFile);
	fread(&ImageHeight, sizeof(ImageHeight), 1, pFile);
	// 计算像素数据长度
	int PixelLength = ImageWidth * 3;
	while (PixelLength % 4 != 0)
		++PixelLength;
	PixelLength *= ImageHeight;
	// 读取像素数据
	buffer = (UINT*)malloc(PixelLength);
	if (buffer == 0)
		exit(0);
	fseek(pFile, 54, SEEK_SET);
	fread(buffer, PixelLength, 1, pFile);
	// 关闭文件
	fclose(pFile);
}


static void init()
{
	Build_Sin_Cos_Tables();
	RGB16Bit = RGB16Bit565;

	glClearColor(0, 0, 0, 1);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	VECTOR4D cam_pos = {0, 40, 0, 1};
	VECTOR4D cam_dir = {0, 0, 0, 1};
	VECTOR4D cam_tar = { 0, 0, 0, 1};

	Init_CAM4DV1(&cam, CAM_MODEL_EULER, &cam_pos, &cam_dir, &cam_tar, 1.0f, 12000.0f, 90, WINDOW_WIDTH, WINDOW_HEIGHT);

	VECTOR4D vscale = { 1.0f, 1.0f, 1.0f, 1.0f };
	VECTOR4D vpos = { 0.0f, 0, 0, 1.0f };
	VECTOR4D vrot = { 0.0f, 0.0f, 0.0f, 1.0f };

	//Load_OBJECT4DV1_PLG(&obj, "model/towerg1.plg", &vScale, &vPos, &vRot);

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

	buffer = new UINT[WINDOW_HEIGHT * WINDOW_WIDTH];
	memset(buffer, 0, sizeof(UINT)* WINDOW_HEIGHT * WINDOW_WIDTH);

	//LoadBmp();


	//indexBuffer = new GLuint[obj.num_polys * 3];
	//glGenVertexArrays(NumVAOs, VAOs);
	//glBindVertexArray(VAOs[VAO_1]);

	//glGenBuffers(NumBuffers, Buffers);
	//glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(POINT4D)* obj.num_vertices, NULL, GL_DYNAMIC_DRAW);
	//
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[ElementBuffer]);	

	//glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(vPosition);



	//ShaderInfo shaders[] = {
	//	{ GL_VERTEX_SHADER, "shader/common.vert" },
	//	{ GL_FRAGMENT_SHADER, "shader/common.frag" },
	//	{ GL_NONE, NULL }
	//};

	//GLuint program = LoadShaders(shaders);
	//glUseProgram(program);
}

static void resize(int width, int height)
{
	glViewport(0, 0, width, height);
}


static void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
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
		cam.pos.x += tank_speed*Fast_Sin(cam.dir.y);
		cam.pos.z += tank_speed*Fast_Cos(cam.dir.y);
	} // end if

	if (keyboard_state['S'] || keyboard_state['s'])
	{
		// move backward
		cam.pos.x -= tank_speed*Fast_Sin(cam.dir.y);
		cam.pos.z -= tank_speed*Fast_Cos(cam.dir.y);
	} // end if

	// rotate
	if (keyboard_state['D'] || keyboard_state['d'])
	{
		cam.dir.y += 3;

		// add a little turn to object
		if ((turning += 2) > 15)
			turning = 15;

	} // end if

	if (keyboard_state['a'] || keyboard_state['A'])
	{
		cam.dir.y -= 3;

		// add a little turn to object
		if ((turning -= 2) < -15)
			turning = -15;

	} // end if
	else // center heading again
	{
		if (turning > 0)
			turning -= 1;
		else
		if (turning < 0)
			turning += 1;

	} // end else

	//cam.dir.y += 0.05;
	//if (cam.dir.y > 360)
	//	cam.dir.y = 0;
	
	//Build_CAM4DV1_Matrix_Euler(&cam, CAM_ROT_SEQ_ZYX);
	//Rotate_XYZ_OBJECT4DV1(&obj, 0, 1, 0);
	//Model_To_World_OBJECT4DV1(&obj);
	//Reset_OBJECT4DV1(&obj);
	//Cull_OBJECT4DV1(&obj, &cam, CULL_OBJECT_X_PLANE | CULL_OBJECT_Y_PLANE | CULL_OBJECT_Z_PLANE);
	//Remove_Backfaces_OBJECT4DV1(&obj, &cam);
	//World_To_Camera_OBJECT4DV1(&obj, &cam);
	//Camera_To_Perspective_Screen_OBJECT4DV1(&obj, &cam);
	//memset(buffer, 0, sizeof(UINT)* WINDOW_WIDTH * WINDOW_HEIGHT);
	for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; ++i)
	{
		buffer[i] = 0xffffffff;
	}
	//Draw_OBJECT4DV1_Solid(&obj, (UCHAR *)buffer, WINDOW_WIDTH);
	//Draw_OBJECT4DV1_Wire(&obj, (UCHAR *)buffer, WINDOW_WIDTH);
	//glBindVertexArray(VAOs[VAO_1]);
	//glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(POINT4D)* obj.num_vertices, obj.vlist_trans, GL_DYNAMIC_DRAW);
	////glDrawArrays(GL_TRIANGLES, 0, obj.num_polys);

	//int polys = 0;
	//for (int i = 0, j = 0; i < obj.num_polys; ++i)
	//{Z
	//	if (!(obj.plist[i].state & POLY4DV1_STATE_ACTIVE) || (obj.plist[i].state & POLY4DV1_STATE_CLIPPED)
	//		|| (obj.plist[i].state & POLY4DV1_STATE_BACKFACE))
	//		continue;
	//	indexBuffer[j++] = obj.plist[i].vert[0];
	//	indexBuffer[j++] = obj.plist[i].vert[1];
	//	indexBuffer[j++] = obj.plist[i].vert[2];
	//	++polys;
	//}

	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* 3 * polys, indexBuffer, GL_STATIC_DRAW);

	//glDrawElements(GL_TRIANGLES, polys * 3, GL_UNSIGNED_INT, 0);
	//glFlush();


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
		Build_XYZ_Rotation_MATRIX4X4(0, tanks[index].w, 0, &mrot);

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
			//Insert_OBJECT4DV1_RENDERLIST4DV1(&rend_list, &obj_tank);			
		} // end if

	} // end for

	// insert the player into the world
	// reset the object (this only matters for backface and object removal)
	Reset_OBJECT4DV1(&obj_player);

	// set position of tank
	obj_player.world_pos.x = cam.pos.x + 300 * Fast_Sin(cam.dir.y);
	obj_player.world_pos.y = cam.pos.y - 70;
	obj_player.world_pos.z = cam.pos.z + 300 * Fast_Cos(cam.dir.y);

	// generate rotation matrix around y axis
	Build_XYZ_Rotation_MATRIX4X4(0, cam.dir.y + turning, 0, &mrot);

	// rotate the local coords of the object
	Transform_OBJECT4DV1(&obj_player, &mrot, TRANSFORM_LOCAL_TO_TRANS, 1);

	// perform world transform
	Model_To_World_OBJECT4DV1(&obj_player, TRANSFORM_TRANS_ONLY);

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
			//Insert_OBJECT4DV1_RENDERLIST4DV1(&rend_list, &obj_tower);			
		} // end if

	} // end for

	// seed number generator so that modulation of markers is always the same
	//srand(13);

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
			//Insert_OBJECT4DV1_RENDERLIST4DV1(&rend_list, &obj_marker);		
		} // end if

	} // end for

	// remove backfaces
	Remove_Backfaces_RENDERLIST4DV1(&rend_list, &cam);

	// apply world to camera transform
	World_To_Camera_RENDERLIST4DV1(&rend_list, &cam);

	Camera_To_Perspective_Screen_RENDERLIST4DV1(&rend_list, &cam);

	//Draw_RENDERLIST4DV1_Wire16(&rend_list, (UCHAR *)buffer, WINDOW_WIDTH);

	glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_BGRA, GL_UNSIGNED_BYTE, buffer);

	glutSwapBuffers();
}

static void keyDown(unsigned char key, int x, int y)
{
	keyboard_state[key] = true;
	switch (key)
	{
	case 27:
	case 'Q':
	case 'q': glutLeaveMainLoop();      break;

	case 'I':
	case 'i':        break;

	case '=':
	case '+':                   break;

	case '-':
	case '_': break;

	case ',':
	case '<': break;

	case '.':
	case '>': break;

	case '9':
	case '(': break;

	case '0':
	case ')':break;

	case 'P':
	case 'p':break;

	case 'R':
	case 'r':break;

	case 'N':
	case 'n':break;

	case 'W':
	case 'w':
		
		break;
	case 'S':
	case 's':		
		
		break;
	case 'A':
	case 'a':
		
		break;
	case 'D':
	case 'd':
		
		break;

	default:
		break;
	}

	glutPostRedisplay();
}


static void keyUp(unsigned char key, int x, int y)
{
	keyboard_state[key] = false;
}

static void special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_PAGE_UP:  break;
	case GLUT_KEY_PAGE_DOWN:break;
	case GLUT_KEY_UP:break;
	case GLUT_KEY_DOWN:break;

	case GLUT_KEY_RIGHT: break;
	case GLUT_KEY_LEFT: break;

	default:
		break;
	}
}

static void
idle(void)
{
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	Open_Error_File("ERROR.TXT", stdout);

	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(40, 40);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow("My Window");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(special);
	glutIdleFunc(idle);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);


	if (glewInit())
	{
		exit(-1);
	}

	init();

	glutMainLoop();

	Close_Error_File();

	return 0;
}