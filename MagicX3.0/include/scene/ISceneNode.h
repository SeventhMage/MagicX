/************************************************************************/
/* 场景结点，场景图基本结构                                             */
/************************************************************************/

#ifndef _MX_SCENE_I_SCENE_NODE_H_
#define _MX_SCENE_I_SCENE_NODE_H_

#include "math/CVector3.h"
#include "math/CMatrix4.h"

#include <list>

namespace mx
{
	namespace scene
	{
		using math::CVector3;
		using math::CMatrix4;
		class IScene;
		class ISceneNode
		{
 		public:
			virtual ~ISceneNode(){}
			virtual void UpdateImp(int delta) = 0;
			virtual void Update(uint delta) = 0;
			virtual void SetParent(ISceneNode *parent) = 0;
			virtual void AddChild(ISceneNode *child) = 0;			

			virtual void Remove() = 0;
			virtual void RemoveChild(ISceneNode *child) = 0;

			virtual void RemoveAll() = 0;

			virtual void SetPosition(const CVector3 &position) = 0;

			virtual const CVector3 &GetPosition() const = 0;

			virtual void SetRotation(const CVector3 &rotation) = 0;

			virtual const CVector3 &GetRotation() const = 0;

			virtual CVector3 GetAbslutePosition() const = 0;

			virtual void SetScale(const CVector3 &scale) = 0;

			virtual const CVector3 &GetScale() const = 0;

			virtual const CMatrix4 &GetAbsluateTransformation() const = 0;
			virtual CMatrix4 GetRelativeTransformation() const = 0;

			virtual void SetVisible(bool visible) = 0;

			virtual bool IsVisible()const = 0;

			//3D检测后，可见为true, 不可见为false
			virtual void SetActive(bool bActive) = 0;
			virtual bool IsActive() const = 0;

			virtual const std::string &GetName() const = 0;

			virtual void UpdateAbsluateTransformation() = 0;
			virtual void SetNeedUpdateTransformation(bool bNeed) = 0;			
		};

	}
}

#endif