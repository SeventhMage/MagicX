#include "scene/CSphere.h"
#include "mxDef.h"

#include <string.h>

namespace mx
{
	namespace scene
	{

		CSphere::CSphere(float fRadius, int iSlices, int iStacks)
			:m_vertexCount(iStacks * iSlices * 6)
		{
			float drho = (float)(3.141592653589) / (float)iStacks;
			float dtheta = 2.0f * (float)(3.141592653589) / (float)iSlices;
			float ds = 1.0f / (float)iSlices;
			float dt = 1.0f / (float)iStacks;
			float t = 1.0f;
			float s = 0.0f;
			int i, j;     // Looping variables

			m_vertices = new math::CVector3[m_vertexCount];
			m_normals = new math::CVector3[m_vertexCount];
			m_texCoords = new math::CVector2[m_vertexCount];
			int curCount = 0;

			for (i = 0; i < iStacks; i++)
			{
				float rho = (float)i * drho;
				float srho = (float)(sin(rho));
				float crho = (float)(cos(rho));
				float srhodrho = (float)(sin(rho + drho));
				float crhodrho = (float)(cos(rho + drho));

				s = 0.0f;
				math::CVector3 vVertex[4];
				math::CVector3 vNormal[4];
				math::CVector2 vTexture[4];

				for (j = 0; j < iSlices; j++)
				{
					float theta = (j == iSlices) ? 0.0f : j * dtheta;
					float stheta = (float)(-sin(theta));
					float ctheta = (float)(cos(theta));

					float x = stheta * srho;
					float y = ctheta * srho;
					float z = crho;

					vTexture[0].x = s;
					vTexture[0].y = t;
					vNormal[0].x = x;
					vNormal[0].y = y;
					vNormal[0].z = z;
					vVertex[0].x = x * fRadius;
					vVertex[0].y = y * fRadius;
					vVertex[0].z = z * fRadius;

					x = stheta * srhodrho;
					y = ctheta * srhodrho;
					z = crhodrho;

					vTexture[1].x = s;
					vTexture[1].y = t - dt;
					vNormal[1].x = x;
					vNormal[1].y = y;
					vNormal[1].z = z;
					vVertex[1].x = x * fRadius;
					vVertex[1].y = y * fRadius;
					vVertex[1].z = z * fRadius;


					theta = ((j + 1) == iSlices) ? 0.0f : (j + 1) * dtheta;
					stheta = (float)(-sin(theta));
					ctheta = (float)(cos(theta));

					x = stheta * srho;
					y = ctheta * srho;
					z = crho;

					s += ds;
					vTexture[2].x = s;
					vTexture[2].y = t;
					vNormal[2].x = x;
					vNormal[2].y = y;
					vNormal[2].z = z;
					vVertex[2].x = x * fRadius;
					vVertex[2].y = y * fRadius;
					vVertex[2].z = z * fRadius;

					x = stheta * srhodrho;
					y = ctheta * srhodrho;
					z = crhodrho;

					vTexture[3].x = s;
					vTexture[3].y = t - dt;
					vNormal[3].x = x;
					vNormal[3].y = y;
					vNormal[3].z = z;
					vVertex[3].x = x * fRadius;
					vVertex[3].y = y * fRadius;
					vVertex[3].z = z * fRadius;

					for (int i = 0; i < 3; ++i)
					{
						m_vertices[curCount] = vVertex[i];
						m_normals[curCount] = vNormal[i].normalize();
						m_texCoords[curCount] = vTexture[i];
						++curCount;
					}

					// Rearrange for next triangle
					memcpy(vVertex[0].v, vVertex[1].v, sizeof(math::CVector3));
					memcpy(vNormal[0].v, vNormal[1].v, sizeof(math::CVector3));
					memcpy(vTexture[0].v, vTexture[1].v, sizeof(math::CVector2));

					memcpy(vVertex[1].v, vVertex[3].v, sizeof(math::CVector3));
					memcpy(vNormal[1].v, vNormal[3].v, sizeof(math::CVector3));
					memcpy(vTexture[1].v, vTexture[3].v, sizeof(math::CVector2));

					for (int i = 0; i < 3; ++i)
					{
						m_vertices[curCount] = vVertex[i];
						m_normals[curCount] = vNormal[i].normalize();
						m_texCoords[curCount] = vTexture[i];
						++curCount;
					}

				}
				t -= dt;
			}
		}

		CSphere::~CSphere()
		{
			SAFE_DEL_ARRAY(m_vertices);
			SAFE_DEL_ARRAY(m_normals);
			SAFE_DEL_ARRAY(m_texCoords);
		}

	}
}