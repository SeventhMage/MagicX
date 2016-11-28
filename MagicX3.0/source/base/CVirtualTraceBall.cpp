#include "base/CVirtualTraceBall.h"
#include "mx.h"

namespace mx
{
	namespace base
	{

		CVirtualTraceBall::CVirtualTraceBall(float fRadius)
			:m_fRadius(fRadius)
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
				float fx = (fScreenX + pDevice->GetWindowWidth()) * 0.5f;
				float fy = (pDevice->GetWindowHeight() - fScreenY) * 0.5f;
				float fz = sqrt(m_fRadius * m_fRadius - fx * fx - fy * fy);
				return CVector3(fx, fy, fz);
			}
			return CVector3();
		}

		math::CMatrix4 CVirtualTraceBall::GetRotateMatrix(float fCurScnX, float fCurScnY, float fLastCurScnX, float fLastCurScnY)
		{
			CVector3 vCurCoord = GetSphereCoord(fCurScnX, fCurScnY);
			vCurCoord.normalize();
			CVector3 vLastCoord = GetSphereCoord(fLastCurScnX, fLastCurScnY);
			vLastCoord.normalize();						

			CVector3 vRotate = vCurCoord.crossProduct(vLastCoord);
			float fRad = asin((vRotate.getLength()));

			CMatrix4 mRotate;
			mRotate.SetRotationRadians(fRad, vRotate);
			return mRotate;
		}

	}
}