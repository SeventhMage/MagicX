#ifndef _I_SCENE_H_INC_
#define _I_SCENE_H_INC_

#include "ISceneNode.h"
#include "ISkyBox.h"
#include "ICamera.h"
#include "ITerrainSceneNode.h"

namespace mx
{
	namespace scene
	{
		class IScene
		{
		public:
			IScene(){}
			virtual ~IScene(){}

			virtual void AddSceneNode(ISceneNode *pSceneNode) = 0;
			virtual void RemoveSceneNode(ISceneNode * pSceneNode) = 0;	
			virtual void RemoveAll() = 0;
			
			virtual bool LoadScene(const char *filename) = 0;

			virtual ISkyBox *CreateSkyBox(const char *filename) = 0;
			virtual ISkyBox *CreateSkyBox(const char *front, const char *back, const char * left, const char *right, const char *top, const char *bottom) = 0;

			virtual ICamera *SetupCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up, float fov, float aspect, float near, float far) = 0;

			virtual void Update(int elapsedTime) = 0;
			virtual void Render() = 0;
		};
	}
}

#endif