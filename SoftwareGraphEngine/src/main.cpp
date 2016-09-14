#include "sge.h"
#include <assert.h>

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

	VECTOR4D cam_pos = {0, 0, 200};
	VECTOR4D cam_dir = {0, 0, 0};
	VECTOR4D cam_tar = { 0, 0, 0 };

	Init_CAM4DV1(&cam, 0, &cam_pos, &cam_dir, &cam_tar, 1.0f, 500.0f, 90, WINDOW_WIDTH, WINDOW_HEIGHT);

	VECTOR4D vScale = { 1.0f, 1.0f, 1.0f, 1.0f };
	VECTOR4D vPos = { 0.0f, 0, 0, 1.0f };
	VECTOR4D vRot = { 0.0f, 0.0f, 0.0f, 1.0f };

	Load_OBJECT4DV1_PLG(&obj, "model/towerg1.plg", &vScale, &vPos, &vRot);


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
	
	//cam.dir.y += 0.05;
	//if (cam.dir.y > 360)
	//	cam.dir.y = 0;
	
	Build_CAM4DV1_Matrix_Euler(&cam, CAM_ROT_SEQ_ZYX);
	Rotate_XYZ_OBJECT4DV1(&obj, 0, 0.5, 0);
	Model_To_World_OBJECT4DV1(&obj);
	Reset_OBJECT4DV1(&obj);
	Cull_OBJECT4DV1(&obj, &cam, CULL_OBJECT_X_PLANE | CULL_OBJECT_Y_PLANE | CULL_OBJECT_Z_PLANE);
	Remove_Backfaces_OBJECT4DV1(&obj, &cam);
	World_To_Camera_OBJECT4DV1(&obj, &cam);
	Camera_To_Perspective_Screen_OBJECT4DV1(&obj, &cam);
	memset(buffer, 0, sizeof(UINT)* WINDOW_WIDTH * WINDOW_HEIGHT);
	for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; ++i)
	{
		buffer[i] = 0xffffffff;
	}
	Draw_OBJECT4DV1_Wire(&obj, (UCHAR *)buffer, WINDOW_WIDTH);
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

	glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_BGRA, GL_UNSIGNED_BYTE, buffer);

	glutSwapBuffers();
}

static void
key(unsigned char key, int x, int y)
{
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
		--cam.pos.z;					
		break;
	case 'S':
	case 's':		
		++cam.pos.z;
		break;
	case 'A':
	case 'a':
		--cam.pos.x;
		break;
	case 'D':
	case 'd':
		++cam.pos.x;
		break;

	default:
		break;
	}

	glutPostRedisplay();
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
	glutKeyboardFunc(key);
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