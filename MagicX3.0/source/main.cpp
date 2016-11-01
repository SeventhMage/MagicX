#include "mx.h"

using namespace mx;

int main(int argc, char *argv[])
{
	IMagicX *mx = CreateMagicX(RDT_OPENGL, 0, 0, 800, 600);
	ISceneManager *sceneManager = mx->GetSceneManager();
	IScene *scene = sceneManager->LoadScene("magic.scene");
	IRenderer *renderer = mx->GetRenderer();
	IDevice *device = mx->GetDevice();

	if (scene)
	{
		ISceneNode *rootNode = scene->GetRootNode();
		if (rootNode)
		{
			rootNode->AddChildNode(nullptr);
		}
	}

	while (device->Run())
	{
		sceneManager->Draw(renderer);
		device->Sleep(100);
	}
	
	return 0;
}