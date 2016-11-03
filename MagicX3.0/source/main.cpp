#include "mx.h"

using namespace mx;

int main(int argc, char *argv[])
{
	IMagicX *mx = CreateMagicX(RDT_OPENGL, 0, 0, 800, 600);
	ISceneManager *sceneManager = mx->GetSceneManager();
	IScene *scene = sceneManager->LoadScene("magic.scene");
	IDevice *device = mx->GetDevice();

	if (scene)
	{
		ISceneNode *rootNode = scene->GetRootNode();
		if (rootNode)
		{
			CUnit unit;
			unit.LoadModel("test.model");
			rootNode->AddChildNode(&unit);
		}
	}

	while (device->Run())
	{
		sceneManager->Draw();
		device->Sleep(100);
	}
	
	return 0;
}