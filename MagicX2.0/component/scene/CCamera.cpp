#include "CCamera.h"
#include "scene/ISceneNode.h"

namespace mx
{
	namespace scene
	{
		CCamera::CCamera()
			: m_bNeedUpdateView(true)
			, m_bNeedUpdateProj(true)
			, m_bOrtho(false)
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
		{
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
			if (m_bNeedUpdateView)
			{				
				m_matView.buildCameraLookAtMatrix(m_position, m_direction, m_up);
			}

			if (m_bNeedUpdateProj)
			{
				if (m_bOrtho)
					m_matProj.buildProjectionMatrixOrthoRH(float(m_width), float(m_height), m_nearClip, m_farClip);
				else
					m_matProj.buildProjectionMatrixPerspectiveFovRH(m_fov, m_aspect, m_nearClip, m_farClip);
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

	}
}