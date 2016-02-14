#include "CCamera.h"
#include "scene/ISceneNode.h"
#include "mxDef.h"

namespace mx
{
	namespace scene
	{
		CCamera::CCamera()
			: m_bNeedUpdateView(true)
			, m_bNeedUpdateProj(true)
			, m_bOrtho(false)
			, m_pFocus(NULL)
			, m_fov(0)
			, m_aspect(0)
			, m_fDistance(0)
		{

		}

		CCamera::CCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up, float fov, float aspect, float near, float far)
			:m_bNeedUpdateProj(true)
			,m_bNeedUpdateView(true)
			,m_bOrtho(false)
			,m_position(position)
			,m_direction(direction)
			,m_up(up)
			,m_fov(fov)
			,m_aspect(aspect)
			,m_nearClip(near)
			,m_farClip(far)
			, m_pFocus(NULL)
			, m_fDistance(0)
		{
			Update(0);
		}

		CCamera::CCamera(float fDistance, ISceneNode *pFocusNode, const CVector3 &vDirection, const CVector3 &vUp, float fov, float aspect, float nearClip, float farClip)
			:m_bNeedUpdateProj(true)
			, m_bNeedUpdateView(true)
			, m_bOrtho(false)
			, m_direction(vDirection)
			, m_up(vUp)
			, m_fov(fov)
			, m_aspect(aspect)
			, m_nearClip(nearClip)
			, m_farClip(farClip)
			, m_pFocus(pFocusNode)
			, m_fDistance(fDistance)
		{
			CVector3 vDir = -m_direction;
			vDir.normalize();
			if (pFocusNode)
				m_position = pFocusNode->GetPosition() + vDir * fDistance;
			Update(0);
		}

		CCamera::~CCamera()
		{

		}

		void CCamera::SetPosition(const CVector3 &position)
		{
			m_position = position;
			m_bNeedUpdateView = true;
		}

		const CVector3 & CCamera::GetPosition() const
		{
			return m_position;
		}

		void CCamera::SetDirection(const CVector3 &direction)
		{
			m_direction = direction;
			m_bNeedUpdateView = true;
		}


		void CCamera::SetDistance(float fDis)
		{
			m_fDistance = fDis;
			m_bNeedUpdateView = true;
		}


		const CVector3 & CCamera::GetDirection() const
		{
			return m_direction;
		}

		void CCamera::SetUp(const CVector3 &up)
		{
			m_up = up;
			m_bNeedUpdateView = true;
		}

		const CVector3 & CCamera::GetUp() const
		{
			return m_up;
		}

		void CCamera::Update(int elapsedTime)
		{
			if (m_pFocus)
			{
				CVector3 vPos = m_pFocus->GetPosition() + -m_direction * m_fDistance;
				if (vPos != m_position)
				{
					SetPosition(vPos);
				}					
			}

			if (m_bNeedUpdateView)
			{				
				m_matView.BuildCameraLookAtMatrix(m_position, m_direction, m_up);
/*				CMatrix4 mat4;
				BuildFrustumMatrix(mat4);
				m_frustum.Transform(mat4);	*/			
			}

			if (m_bNeedUpdateProj)
			{
				if (m_bOrtho)
				{
					m_matProj.BuildProjectionMatrixOrthoRH(float(m_width), float(m_height), m_nearClip, m_farClip);
				}
				else
				{
					m_matProj.BuildProjectionMatrixPerspectiveFovRH(m_fov, m_aspect, m_nearClip, m_farClip);
					m_frustum.Create(m_fov, m_aspect, m_nearClip, m_farClip);
				}
				
			}

			if (m_bNeedUpdateProj || m_bNeedUpdateView)
			{
				m_matVP = m_matProj * m_matView;
				
				//frustum¸üÐÂ
				

				//


				m_bNeedUpdateProj = false;
				m_bNeedUpdateView = false;
			}
		}

		mx::uint CCamera::GetWidth() const
		{
			return m_width;
		}

		mx::uint CCamera::GetHeight() const
		{
			return m_height;
		}

		float CCamera::GetFov() const
		{
			return m_fov;
		}

		float CCamera::GetNearClip() const
		{
			return m_nearClip;
		}

		float CCamera::GetFarClip() const
		{
			return m_farClip;
		}

		float CCamera::GetAspect() const
		{
			return m_aspect;
		}

		void CCamera::SetWidth(uint width)
		{
			m_width = width;
		}

		void CCamera::SetHeight(uint height)
		{
			m_height = height;
		}

		void CCamera::SetFov(float fov)
		{
			m_fov = fov;
		}

		void CCamera::SetNearClip(float near)
		{
			m_nearClip = near;
		}

		void CCamera::SetFarClip(float far)
		{
			m_farClip = far;
		}

		void CCamera::SetAspect(float aspect)
		{
			m_aspect = aspect;
		}

		void CCamera::SetOritho(bool bOritho)
		{
			m_bOrtho = bOritho;
		}

		bool CCamera::IsOritho() const
		{
			return m_bOrtho;
		}

		void CCamera::BuildFrustumMatrix(CMatrix4 &mat4)
		{
			CVector3 vForward = -m_direction;
			CVector3 vCross = m_up.crossProduct(vForward);
			vCross.normalize();
			mat4[0] = vCross.x;
			mat4[1] = vCross.y;
			mat4[2] = vCross.z;
			mat4[3] = 0;

			mat4[4] = m_up.x;
			mat4[5] = m_up.y;
			mat4[6] = m_up.z;
			mat4[7] = 0;

			mat4[8] = vForward.x;
			mat4[9] = vForward.y;
			mat4[10] = vForward.z;
			mat4[11] = 0;

			mat4[12] = m_position.x;
			mat4[13] = m_position.y;
			mat4[14] = m_position.z;
			mat4[15] = 0;

		}

	}
}