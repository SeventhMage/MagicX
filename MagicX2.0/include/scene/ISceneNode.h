#ifndef _H_SCENE_NODE_H_INC_
#define _H_SCENE_NODE_H_INC_

#include <list>
#include "mxType.h"
#include "core/CMatrix4.h"
#include "core/CVector3.h"

namespace mx
{
	namespace scene
	{
		using core::CVector3;
		using core::CMatrix4;
		class ISceneNode
		{
		public:
			ISceneNode()
				:m_pNodeParent(NULL)
				, m_bVisible(true)
			{
			};
			virtual ~ISceneNode(){};
			
			virtual void UpdateImp(int elapsedTime, const CMatrix4 &mat4MVP, const CMatrix4 &mat4MV) = 0;
//			virtual void RenderImp() = 0;

// 			void Render()
// 			{
// 				RenderImp();
// 				std::list<ISceneNode *>::iterator it = m_listChild.begin();
// 				for (; it != m_listChild.end(); ++it)
// 				{
// 					(*it)->Render();
// 				}				
// 			}

			void Update(uint elapsedTime, const CMatrix4 &mat4MVP, const CMatrix4 &mat4MV)
			{
				UpdateImp(elapsedTime, mat4MVP, mat4MV);
				std::list<ISceneNode *>::iterator it = m_listChild.begin();
				for (; it != m_listChild.end(); ++it)
				{
					(*it)->Update(elapsedTime, mat4MVP, mat4MV);
				}
			}



			void SetParent(ISceneNode *parent)
			{
				if (parent)
				{
					Remove();
					parent->AddChild(this);
					m_pNodeParent = parent;
				}
			}
			void AddChild(ISceneNode *child)
			{
				m_listChild.push_back(child);
			}
			void Remove()
			{
				if (m_pNodeParent)
					m_pNodeParent->RemoveChild(this);
			}
			void RemoveChild(ISceneNode *child)
			{
				m_listChild.remove(child);
			}

			void RemoveAll()
			{
				m_listChild.clear();
			}

			void SetPosition(const CVector3 &position)
			{
				m_relativePosition = position;
			}

			const CVector3 &GetPosition() const
			{
				return m_relativePosition;
			}
			
			const CVector3 &GetRotation() const
			{
				return m_relativeRotation;
			}

			CVector3 GetAbslutePosition() const
			{
				return m_absluateTransformation.getTranslation();
			}

			void SetScale(const CVector3 &scale)
			{
				m_relativeScale = scale;
			}

			const CVector3 &GetScale() const
			{
				return m_relativeScale;
			}

			const CMatrix4 &GetAbsluateTransformation() const
			{
				return m_absluateTransformation;
			}
			CMatrix4 GetRelativeTransformation() const
			{
				CMatrix4 mat;

				mat.setTranslation(GetPosition());
				mat.setTranslation(GetRotation());
				if (m_relativeScale != CVector3(1.0f, 1.0f, 1.0f))
				{
					CMatrix4 smat;
					smat.setScale(m_relativeScale);
					mat = mat * smat;
				}
				return mat;
			}

			void SetVisible(bool visible)
			{
				m_bVisible = visible;
			}

			bool GetVisible()const
			{
				return m_bVisible;
			}

			const std::string &GetName() const
			{
				return m_name;
			}

			void UpdateAbsluateTransformation()
			{
				if (m_pNodeParent)
				{
					m_absluateTransformation = m_pNodeParent->GetAbsluateTransformation() * GetRelativeTransformation();
				}
				else
					m_absluateTransformation = GetRelativeTransformation();
			}

		protected:
			ISceneNode *m_pNodeParent;
			std::list<ISceneNode *> m_listChild;

			CMatrix4 m_absluateTransformation;
			CVector3 m_relativePosition;
			CVector3 m_relativeRotation;
			CVector3 m_relativeScale;						
			std::string m_name;
			bool m_bVisible;
		};
	}
}

#endif // !_H_SCENE_NODE_H_INC_
