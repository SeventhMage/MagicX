/************************************************************************/
/* �����ṹ�ӿ�                                                         */
/************************************************************************/

#ifndef _MX_SCENE_I_SCENE_H_
#define _MX_SCENE_I_SCENE_H_

#include "ISceneNode.h"

namespace mx
{
	namespace scene
	{
		class IScene
		{
		public:
			IScene(){};
			virtual~IScene(){};

			//ÿ��������Ψһ����㣬����ͼ�ĸ�
			virtual ISceneNode *GetRootNode() = 0;
		};
	}
}

#endif