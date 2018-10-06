#ifndef _SE_I_SCENE_NODE_H_
#define _SE_I_SCENE_NODE_H_

#include "IEntity.h"
#include "math/CVector3.h"

namespace se
{
	namespace scene
	{
		class ISceneNode
		{
		public:
			virtual ~ISceneNode(){}
			
			virtual void SetParent(ISceneNode *pNode) = 0;
			virtual ISceneNode *GetParent() = 0;
			virtual void AddChildNode(ISceneNode *pNode) = 0;			
			virtual void RemoveChildNode(ISceneNode *pNode) = 0;

			virtual void SetPosition(const math::CVector3 &position) = 0;
			virtual const math::CVector3 &GetPosition() const = 0;
			virtual math::CVector3 GetAbslutePosition() const = 0;
			virtual void SetScale(const math::CVector3 &scale) = 0;
			virtual const math::CVector3 &GetScale() const = 0;
			virtual void SetRotation(const math::CVector3 &rotation) = 0;
			virtual const math::CVector3 &GetRotation() const = 0;
			virtual void SetVisible(bool bVisible) = 0;
			virtual bool IsVisible() const = 0;


			virtual const math::CMatrix4 &GetAbsluateMatrix() const = 0;
			virtual math::CMatrix4 GetRelativeMatrix() const = 0;

			virtual void UpdateRelateMatrix() = 0;
			virtual void UpdateAbsluateMatrix() = 0;
			virtual void SetNeedUpdateMatrix(bool bNeed) = 0;

			virtual void Update(int delta) = 0;
		};
	}
}

#endif