/************************************************************************/
/* ³¡¾°½áµã                                                             */
/************************************************************************/

#ifndef MX_SCENE_C_SCENE_NODE_H_
#define MX_SCENE_C_SCENE_NODE_H_

#include "scene/ISceneNode.h"

#include <list>

namespace mx
{
	namespace scene
	{
		class CSceneNode : public ISceneNode
		{
		public:
			CSceneNode();
			virtual ~CSceneNode();

			virtual void UpdateImp(int delta);

			virtual void Update(uint delta);

			virtual void SetParent(ISceneNode *parent);
			virtual void AddChild(ISceneNode *child);
			
			virtual void Remove();
			virtual void RemoveChild(ISceneNode *child);

			virtual void RemoveAll();

			virtual void SetPosition(const CVector3 &position);

			virtual const CVector3 &GetPosition() const;

			virtual void SetRotation(const CVector3 &rotation);
			virtual const CVector3 &GetRotation() const;

			virtual CVector3 GetAbslutePosition() const;

			virtual void SetScale(const CVector3 &scale);

			virtual const CVector3 &GetScale() const;

			virtual const CMatrix4 &GetAbsluateTransformation() const;
			virtual CMatrix4 GetRelativeTransformation() const;

			virtual void SetVisible(bool visible);

			virtual bool IsVisible()const;

			virtual void SetActive(bool bActive);
			virtual bool IsActive() const;

			virtual const std::string &GetName() const;

			virtual void UpdateAbsluateTransformation();
			virtual void SetNeedUpdateTransformation(bool bNeed);
		protected:
			ISceneNode *m_pNodeParent;
			std::list<ISceneNode *> m_listChild;			

			CMatrix4 m_absluateTransformation;
			CVector3 m_relativePosition;
			CVector3 m_relativeRotation;
			CVector3 m_relativeScale;
			std::string m_name;
			bool m_bVisible;
			bool m_bActive;
			bool m_bNeedUpdate;
		};
	}
}

#endif
