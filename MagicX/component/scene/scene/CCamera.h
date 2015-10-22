#ifndef _C_CAMERA_H_
#define _C_CAMERA_H_

#include "../include/ICamera.h"
#include "CFrustum.h"
#include "common/mxDef.h"

namespace mx
{
	namespace scene
	{
		class CCamera : public ICamera
		{
		public:
			CCamera();
			CCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up);
			virtual ~CCamera();
			virtual void SetPosition(const CVector3 &position);			
			virtual void SetDirection(const CVector3 &direction);			
			virtual void SetUp(const CVector3 &up);
			virtual void SetWidth(uint width);
			virtual void SetHeight(uint height);
			virtual void SetFov(float fov);
			virtual void SetNearClip(float near);
			virtual void SetFarClip(float far);
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
			virtual bool IsOritho()const;

			virtual void Update();
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