/************************************************************************/
/* 场景结点                                                             */
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

			//结点位置操作
			virtual void SetPosition();
			virtual void GetPosition();

			//可见性检测后设置状态，只有活跃的节点才会被渲染
			virtual void SetActivite();
			virtual bool IsActivite();

			virtual void SetVisible();
			virtual bool IsVisible();

			virtual void Update(int delta);
		};
	}
}

#endif
