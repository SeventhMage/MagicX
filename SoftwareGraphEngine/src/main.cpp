#include "sge.h"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "LoadShaders.h"


#pragma comment (lib, "glew32s.lib")

enum VAO_IDs
{
	VAO_1,
	NumVAOs,
};

enum Buffer_IDs
{
	ArrayBuffer,
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

static void init()
{
	glClearColor(1, 0, 0, 0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// set function pointer to something
	RGB16Bit = RGB16Bit565;

	VECTOR4D cam_pos = {0, 0, -10};
	VECTOR4D cam_dir = {0, 180, 0};
	VECTOR4D cam_tar = { 0, 0, 0 };

	Init_CAM4DV1(&cam, 0, &cam_pos, &cam_dir, &cam_tar, 1.0f, 500.0f, 90, WINDOW_WIDTH, WINDOW_HEIGHT);

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[VAO_1]);

	VECTOR4D vScale = { 1.0f, 1.0f, 1.0f, 1.0f };
	VECTOR4D vPos = { 0.0f, 0.0f, 0.0f, 0.0f };
	VECTOR4D vRot = { 0.0f, 0.0f, 0.0f, 0.0f };

	Load_OBJECT4DV1_PLG(&obj, "model/cube1.plg", &vScale, &vPos, &vRot);


	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(POINT4D)* obj.num_vertices, obj.vlist_trans, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "shader/common.vert"},
		{ GL_FRAGMENT_SHADER, "shader/common.frag" },
		{GL_NONE, NULL}
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
}

static void resize(int width, int height)
{
	glViewport(0, 0, width, height);
}


static void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAOs[VAO_1]);
	glDrawArrays(GL_TRIANGLES, 0, obj.num_vertices);
	glFlush();
	
	Build_CAM4DV1_Matrix_Euler(&cam, CAM_ROT_SEQ_ZYX);

	Model_To_World_OBJECT4DV1(&obj);
	World_To_Camera_OBJECT4DV1(&cam, &obj);
	Camera_To_Perspective_Screen_OBJECT4DV1(&obj, &cam);

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

	case 'S':
	case 's':
		break;

	case 'N':
	case 'n':break;

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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

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
	getchar();
	return 0;
}