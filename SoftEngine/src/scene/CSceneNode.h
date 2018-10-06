#ifndef _SCENE_C_SCENE_NODE_H_
#define _SCENE_C_SCENE_NODE_H_

#include "scene/ISceneNode.h"
#include "scene/IScene.h"
#include "math/CMatrix4.h"
#include "CEntity.h"

#include <vector>

namespace se
{
	namespace scene
	{
		class CSceneNode : public ISceneNode
		{
		public:
			CSceneNode(IScene *pScene);
			virtual ~CSceneNode();

			virtual void SetParent(ISceneNode *pNode);
			virtual ISceneNode *GetParent() { return m_pParentNode; }
			virtual void AddChildNode(ISceneNode *pNode);
			virtual void RemoveChildNode(ISceneNode *pNode);
			
			virtual void SetPosition(const math::CVector3 &position);
			virtual const math::CVector3 &GetPosition() const;
			CVector3 GetAbslutePosition() const;
			virtual void SetScale(const math::CVector3 &scale);
			virtual const math::CVector3 &GetScale() const;
			virtual void SetRotation(const math::CVector3 &rotation);			
			virtual const math::CVector3 &GetRotation() const;


			virtual void SetVisible(bool bVisible);
			virtual bool IsVisible() const ;


			virtual const math::CMatrix4 &GetAbsluateMatrix() const;
			virtual math::CMatrix4 GetRelativeMatrix() const;
			
			virtual void UpdateRelateMatrix();
			virtual void UpdateAbsluateMatrix();
			virtual void SetNeedUpdateMatrix(bool bNeed);

			virtual void Update(int delta);

		protected:
			IScene *m_pParentScene;			
			
			ISceneNode *m_pParentNode;
			std::vector<ISceneNode *> m_vecChildNode;
			
			//空间位置信息
			math::CMatrix4 m_relativeMatrix;
			math::CMatrix4 m_absluateMatrix;
			math::CVector3 m_relativePosition;
			math::CVector3 m_relativeRotation;
			math::CVector3 m_relativeScale;
			bool m_bNeedUpdate;			

			bool m_bVisible;
		};
	}
}

#endif