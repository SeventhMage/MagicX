#ifndef _MX_CORE_CFRUSTUM_H_
#define _MX_CORE_CFRUSTUM_H_

#include "CPlane3.h"
#include "CVector3.h"
#include "CMatrix4.h"
#include "CAABBox.h"

namespace se
{
	namespace math
	{
		class CFrustum
		{
		public:
			enum FPLANES
			{				
				F_FAR_PLANE = 0,				
				F_NEAR_PLANE,
				F_LEFT_PLANE,
				F_RIGHT_PLANE,
				F_BOTTOM_PLANE,
				F_TOP_PLANE,

				F_PLANE_COUNT
			};
            
            enum FVERTICES
            {
                F_NLB = 0,
                F_NRB,
                F_NRT,
                F_NLT,
                F_FLB,
                F_FRB,
                F_FRT,
                F_FLT,
                
                F_VERTICES_COUNT
            };
            
			CFrustum(){}
			~CFrustum(){}

			void Create(float fFov, float fAspect, float fNear, float fFar)
			{
				float xmin, xmax, ymin, ymax;
				float xFmin, xFmax, yFmin, yFmax;

				fNear = -fNear;
				fFar = -fFar;

				ymax = -fNear * float(tan(fFov * 0.5f));
				ymin = -ymax;
				xmin = ymin * fAspect;
				xmax = -xmin;

				yFmax = -fFar * float(tan(fFov * 0.5f));
				yFmin = -yFmax;
				xFmin = yFmin * fAspect;
				xFmax = -xFmin;

				m_vertices[F_NLB].x = xmin;
				m_vertices[F_NLB].y = ymin;
				m_vertices[F_NLB].z = fNear;

				m_vertices[F_NRB].x = xmax;
				m_vertices[F_NRB].y = ymin;
				m_vertices[F_NRB].z = fNear;

				m_vertices[F_NRT].x = xmax;
				m_vertices[F_NRT].y = ymax;
				m_vertices[F_NRT].z = fNear;

				m_vertices[F_NLT].x = xmin;
				m_vertices[F_NLT].y = ymax;
				m_vertices[F_NLT].z = fNear;


				m_vertices[F_FLB].x = xFmin;
				m_vertices[F_FLB].y = yFmin;
				m_vertices[F_FLB].z = fFar;

				m_vertices[F_FRB].x = xFmax;
				m_vertices[F_FRB].y = yFmin;
				m_vertices[F_FRB].z = fFar;

				m_vertices[F_FRT].x = xFmax;
				m_vertices[F_FRT].y = yFmax;
				m_vertices[F_FRT].z = fFar;

				m_vertices[F_FLT].x = xFmin;
				m_vertices[F_FLT].y = yFmax;
				m_vertices[F_FLT].z = fFar;

				CreatePlane();
			}

			bool Culled(const CAABBox &box) const
			{
                for (int i=0; i<F_PLANE_COUNT; ++i)
                {
                    if ((m_planeClip[i].WitchSide(box.GetMinVertex()) == CPlane3::NEGATIVE)
                        && m_planeClip[i].WitchSide(box.GetMaxVertex()) == CPlane3::NEGATIVE)
                        return true;
                }
				return false;
			}
			
			bool CullSphere(const CVector3 &pos, float radius) const
			{				
/*				if (pos.z + radius < -m_vertices[F_FLB].z || pos.z - radius > -m_vertices[F_NLB].z)
					return true;
				float testX = 0.5f * (m_vertices[F_NRT].x - m_vertices[F_NLT].x) * pos.z / -m_vertices[F_NLT].z;
				if (pos.x - radius > testX || pos.x + radius < -testX)
					return true;
				float testY = 0.5f * (m_vertices[F_NRT].y - m_vertices[F_NRB].y) * pos.z / -m_vertices[F_NLT].z;
				if (pos.y - radius > testY || pos.y + radius < -testY)
					return true;	*/			

				for (uint i = 0; i < F_PLANE_COUNT; ++i)
				{
					float dis = m_planeClip[i].GetDistance(pos);
					if (dis < -radius)
						return true;
				}

				return false;
			}

			void Transform(const CMatrix4 &mat4)
			{				
				for (uint i = 0; i < F_VERTICES_COUNT; ++i)
				{
					mat4.TransformVect(m_vertices[i]);
				}
                CreatePlane();
			}

		private:
			void CreatePlane()
			{
				//right hand
				m_planeClip[F_NEAR_PLANE].SetPlane(m_vertices[F_NRB], m_vertices[F_NLB], m_vertices[F_NRT]);
				m_planeClip[F_FAR_PLANE].SetPlane(m_vertices[F_FLB], m_vertices[F_FRB], m_vertices[F_FRT]);
				m_planeClip[F_LEFT_PLANE].SetPlane(m_vertices[F_NLB], m_vertices[F_FLB], m_vertices[F_NLT]);
				m_planeClip[F_RIGHT_PLANE].SetPlane(m_vertices[F_NRB], m_vertices[F_FRT], m_vertices[F_FRB]);
				m_planeClip[F_TOP_PLANE].SetPlane(m_vertices[F_NLT], m_vertices[F_FRT], m_vertices[F_NRT]);
				m_planeClip[F_BOTTOM_PLANE].SetPlane(m_vertices[F_FRB], m_vertices[F_FLB], m_vertices[F_NLB]);
			}
		private:
            CVector3 m_vertices[F_VERTICES_COUNT];
            
			CPlane3 m_planeClip[F_PLANE_COUNT];;
		};

	}
}

#endif
