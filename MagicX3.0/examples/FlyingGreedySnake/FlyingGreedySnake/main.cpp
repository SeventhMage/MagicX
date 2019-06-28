#include "CGreedySnake.h"

#include <time.h>

using namespace mx;


int main(int argc, char *argv[])
//int WINAPI WinMain(HINSTANCE h, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
	srand((uint)time(0));

	CGreedySnake::NewInstance();
	
	CGreedySnake::Instance()->InitGame(1280, 720, false);
	CGreedySnake::Instance()->Run();

	CGreedySnake::DeleteInstance();
	return 0;
}