/************************************************************************/
/* �����������ӿ�                                                       */
/************************************************************************/
#ifndef _MX_SCENE_I_SCENE_MANAGER_H_
#define _MX_SCENE_I_SCENE_MANAGER_H_

#include "IScene.h"
#include "render/IRenderer.h"

namespace mx
{
	namespace scene
	{
		class ISceneManager
		{
		public:
			ISceneManager(){};
			virtual ~ISceneManager(){};
			
			//��������
			virtual void Update(int delta) = 0;

			//ͨ���ļ����볡��
			virtual IScene *LoadScene(const char *filename) = 0;

			//���ص�ǰ����
			virtual IScene *GetCurrentScene() = 0;

		};
	}
}

#endif