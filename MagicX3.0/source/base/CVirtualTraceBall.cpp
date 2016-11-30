#include "base/CVirtualTraceBall.h"
#include "mx.h"

namespace mx
{
	namespace base
	{

		CVirtualTraceBall::CVirtualTraceBall()
		{

		}

		CVirtualTraceBall::~CVirtualTraceBall()
		{

		}

		math::CVector3 CVirtualTraceBall::GetSphereCoord(float fScreenX, float fScreenY)
		{
			
			device::IDevice *pDevice = DEVICEMGR->GetDevice();
			if (pDevice)
			{				
				float fx = (2 * fScreenX - pDevice->GetWindowWidth()) / pDevice->GetWindowWidth();
				float fy = (pDevice->GetWindowHeight() - 2 * fScreenY) / pDevice->GetWindowHeight();
				//float fd = sqrt(fx * fx + fy * fy);
				//float fz = cos(PI * 0.5f)  * (fd < 1.f ? fd : 1.f);

				float xy = fx * fx + fy * fy;
				xy = xy < 1.f ? xy : 1.f;
				float fz = sqrt(1 * 1 - xy);
				
				return CVector3(fx, fy, fz);
			}
			return CVector3();
		}

		math::CMatrix4 CVirtualTraceBall::GetRotateMatrix(float fCurScnX, float fCurScnY, float fLastCurScnX, float fLastCurScnY)
		{
			CVector3 vCurCoord = GetSphereCoord(fCurScnX, fCurScnY);
			CVector3 vLastCoord = GetSphereCoord(fLastCurScnX, fLastCurScnY);
					

			CVector3 vRotate = vLastCoord.crossProduct(vCurCoord);
			float fRad = asin((vRotate.getLength()));

			CMatrix4 mRotate;
			vRotate.normalize();
			mRotate.SetRotationRadians(fRad, vRotate);
			m_mRotate = m_mRotate * mRotate;
			return m_mRotate;
		}

	}
}