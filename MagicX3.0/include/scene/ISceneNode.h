/************************************************************************/
/* 场景结点，场景图基本结构                                             */
/************************************************************************/

#ifndef _MX_SCENE_I_SCENE_NODE_H_
#define _MX_SCENE_I_SCENE_NODE_H_

namespace mx
{
	namespace scene
	{
		class ISceneNode
		{
		public:
			virtual ~ISceneNode(){}

			virtual void AddChildNode(ISceneNode *pChildNode) = 0;
			virtual void RemoveChildNode(ISceneNode *pChildNode) = 0;
			virtual void AddToParentNode(ISceneNode *pParentNode) = 0;
			
			virtual size_t GetChildCount() = 0;
			virtual ISceneNode *GetChildNodeAtIdx(size_t idx) = 0;

			//结点位置操作
			virtual void SetPosition() = 0;
			virtual void GetPosition() = 0;
			
			//可见性检测后设置状态，只有活跃的节点才会被渲染
			virtual void SetActivite() = 0;
			virtual bool IsActivite() = 0;

			virtual void SetVisible() = 0;
			virtual bool IsVisible() = 0;

			virtual void Update(int delta) = 0;

		};
	}
}

#endif