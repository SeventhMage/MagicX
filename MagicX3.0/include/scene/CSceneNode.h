/************************************************************************/
/* �������                                                             */
/************************************************************************/

#ifndef MX_SCENE_C_SCENE_NODE_H_
#define MX_SCENE_C_SCENE_NODE_H_

#include "scene/ISceneNode.h"

namespace mx
{
	namespace scene
	{
		class CSceneNode : public ISceneNode
		{
		public:
			CSceneNode();
			virtual ~CSceneNode();

			virtual void AddChildNode(ISceneNode *pChildNode);
			virtual void RemoveChildNode(ISceneNode *pChildNode);
			virtual void AddToParentNode(ISceneNode *pParentNode);

			virtual size_t GetChildCount();
			virtual ISceneNode *GetChildNodeAtIdx(size_t idx);

			//���λ�ò���
			virtual void SetPosition();
			virtual void GetPosition();

			//�ɼ��Լ�������״̬��ֻ�л�Ծ�Ľڵ�Żᱻ��Ⱦ
			virtual void SetActivite();
			virtual bool IsActivite();

			virtual void SetVisible();
			virtual bool IsVisible();

			virtual void Update(int delta);
		};
	}
}

#endif
