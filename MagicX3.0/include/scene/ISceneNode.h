/************************************************************************/
/* ������㣬����ͼ�����ṹ                                             */
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

			//���λ�ò���
			virtual void SetPosition();
			virtual void GetPosition();
			
			//�ɼ��Լ�������״̬��ֻ�л�Ծ�Ľڵ�Żᱻ��Ⱦ
			virtual void SetActivite();
			virtual bool IsActivite();

			virtual void SetVisible() = 0;
			virtual bool IsVisible() = 0;
			
			//�ڵ����
			virtual void Update(int delta) = 0;
		};
	}
}

#endif