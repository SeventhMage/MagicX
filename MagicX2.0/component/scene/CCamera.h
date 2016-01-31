#ifndef _MX_SCENE_CCAMERA_H_
#define _MX_SCENE_CCAMERA_H_

#include "scene/ICamera.h"
#include "mxType.h"
#include "core/CVector3.h"
#include "core/CMatrix4.h"
#include "core/CFrustum.h"

namespace mx
{
	namespace scene
	{
		using namespace core;
		class CCamera : public ICamera
		{
		public:
			CCamera();
			virtual ~CCamera();
		private:
			uint m_uState;
			uint m_uAttr;	//CAM_MODEL_ELUER,CAM_MODEL_UVN
			CVector3 m_vWorldPos;
			CVector3 m_vDir;			
			CVector3 m_vU;
			CVector3 m_vV;
			CVector3 m_vN;
			CVector3 m_vTarget;
			CFrustum m_frustum;
			float m_fFov;
			float m_fAspectRatio;
			CMatrix4 m_mView;
			CMatrix4 m_mProj;
		};
	}
}

#endif