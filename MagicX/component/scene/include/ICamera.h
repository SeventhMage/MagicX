#ifndef _I_CAMERA_H_INC_
#define _I_CAMERA_H_INC_

#include "common/mxDef.h"

namespace mx
{
	namespace scene
	{
		class ICamera
		{
		public:
			ICamera(){};
			virtual ~ICamera(){};

			
			virtual const CVector3 &GetPosition() const  = 0;			
			virtual const CVector3 &GetDirection() const = 0;			
			virtual const CVector3 &GetUp() const = 0;
			virtual uint GetWidth() const = 0;
			virtual uint GetHeight() const = 0;
			virtual float GetFov() const = 0;
			virtual float GetNearClip() const = 0;
			virtual float GetFarClip() const = 0;
			virtual float GetAspect() const = 0;
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


			virtual void Update() = 0;
		};
	}
}

#endif // !_I_CAMERA_H_INC_
