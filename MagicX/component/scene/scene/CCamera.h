#ifndef _C_CAMERA_H_
#define _C_CAMERA_H_

#include "../include/ICameraSceneNode.h"
#include "CFrustum.h"
#include "common/mxDef.h"

namespace mx
{
	namespace scene
	{
		class CCamera : public ICameraSceneNode
		{
		public:
			CCamera();
			CCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up, float fov, float aspect, float near, float far);
			virtual ~CCamera();
			virtual void SetPosition(const CVector3 &position);			
			virtual void SetDirection(const CVector3 &direction);			
			virtual void SetUp(const CVector3 &up);
			virtual void SetWidth(uint width);
			virtual void SetHeight(uint height);
			virtual void SetFov(float fov);
			virtual void SetNearClip(float nearClip);
			virtual void SetFarClip(float farClip);
			virtual void SetAspect(float aspect);
			virtual void SetOritho(bool bOritho);

			virtual const CVector3 &GetPosition() const;
			virtual const CVector3 &GetDirection() const;
			virtual const CVector3 &GetUp() const;
			virtual uint GetWidth() const;
			virtual uint GetHeight() const;
			virtual float GetFov() const;
			virtual float GetNearClip() const;
			virtual float GetFarClip() const;
			virtual float GetAspect() const;
			virtual CMatrix4 &GetViewMatrix()  { return m_matView; }
			virtual CMatrix4 &GetProjectionMatrix() { return m_matProj; }
			virtual const CMatrix4 &GetViewProjectionMatrix() const { return m_matVP; }
			virtual bool IsOritho()const;
			virtual void SetNeedUpdateViewMatrix() { m_bNeedUpdateView = true; }
			virtual void SetNeedUpdateProjectionMatrix() { m_bNeedUpdateProj = true; };

			virtual void UpdateImp(int elapsedTime, const CMatrix4 &mat4MVP, const CMatrix4 &mat4MV);
		protected:
			CMatrix4 m_matView;
			CMatrix4 m_matProj;
			CMatrix4 m_matVP;
			CVector3 m_position;
			CVector3 m_direction;
			CVector3 m_up;

			CFrustum m_frustum;

			uint m_width;
			uint m_height;
			
			float m_farClip;
			float m_nearClip;
			float m_fov;
			float m_aspect;

			bool m_bOrtho;

			bool m_bNeedUpdateView;
			bool m_bNeedUpdateProj;
		};
	}
}

#endif