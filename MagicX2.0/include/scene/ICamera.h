#ifndef _I_SCENE_ICAMERA_H_
#define _I_SCENE_ICAMERA_H_

#include "mxType.h"
#include "core/CVector3.h"
#include "core/CMatrix4.h"
#include "core/CFrustum.h"
#include "scene/ISceneNode.h"

namespace mx
{
	namespace scene
	{
		using core::CVector3;
		using core::CMatrix4;
		using core::CFrustum;
		class ICamera
		{
		public:
			virtual ~ICamera(){};

			virtual void Update(int elapsedTime) = 0;
			
			virtual const CVector3 &GetPosition() const  = 0;			
			virtual const CVector3 &GetDirection() const = 0;			
			virtual const CVector3 &GetUp() const = 0;
			virtual uint GetWidth() const = 0;
			virtual uint GetHeight() const = 0;
			virtual float GetFov() const = 0;
			virtual float GetNearClip() const = 0;
			virtual float GetFarClip() const = 0;
			virtual float GetAspect() const = 0;
			virtual CMatrix4 &GetViewMatrix()  = 0;
			virtual CMatrix4 &GetProjectionMatrix() = 0;
			virtual const CMatrix4 &GetViewProjectionMatrix() const = 0;
			virtual const CFrustum &GetFrustum() const = 0;
			virtual float GetDistance() const = 0;
			virtual bool IsOritho() const = 0;

			virtual void SetPosition(const CVector3 &position) = 0;
			virtual void SetDirection(const CVector3 &direction) = 0;
			virtual void SetUp(const CVector3 &up) = 0;
			virtual void SetWidth(uint width) = 0;
			virtual void SetHeight(uint height) = 0;
			virtual void SetFov(float fov) = 0;
			virtual void SetNearClip(float near) = 0;
			virtual void SetFarClip(float far) = 0;
			virtual void SetAspect(float aspect) = 0;
			virtual void SetOritho(bool bOritho) = 0;
			virtual void SetNeedUpdateViewMatrix() = 0;
			virtual void SetNeedUpdateProjectionMatrix() = 0;
			virtual void SetDistance(float fDis) = 0;
			virtual ISceneNode *GetFocus() = 0;
		};
	}
}

#endif // !_I_SCENE_ICAMERA_H_
