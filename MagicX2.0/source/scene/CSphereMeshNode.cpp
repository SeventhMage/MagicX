#include "scene/CSphereMeshNode.h"

namespace mx
{
	namespace scene
	{		
		CShpereMeshNode::CShpereMeshNode(float fRadius, uint uSlices, uint uStacks)
			:m_fRadius(fRadius), m_uSlices(uSlices), m_uStacks(uStacks)
		{
			m_uVertNum = uSlices * uStacks * 6;
			float drho = (float)(3.141592653589) / (float)uSlices;
			float dtheta = 2.0f * (float)(3.141592653589) / (float)uSlices;
			float ds = 1.0f / (float)uSlices;
			float dt = 1.0f / (float)uSlices;
			float t = 1.0f;
			float s = 0.0f;
			uint i, j;     // Looping variables

			for (i = 0; i < uSlices; i++)
			{
				float rho = (float)i * drho;
				float srho = (float)(sin(rho));
				float crho = (float)(cos(rho));
				float srhodrho = (float)(sin(rho + drho));
				float crhodrho = (float)(cos(rho + drho));

				s = 0.0f;
				CVector3 vVertex[4];
				CVector3 vNormal[4];
				CVector2 vTexture[4];

				for (j = 0; j < uSlices; j++)
				{
					float theta = (j == uSlices) ? 0.0f : j * dtheta;
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


					theta = ((j + 1) == uSlices) ? 0.0f : (j + 1) * dtheta;
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

					AddTriangle(vVertex, vNormal, vTexture);

					// Rearrange for next triangle
					memcpy(&vVertex[0], &vVertex[1], sizeof(CVector3));
					memcpy(&vNormal[0], &vNormal[1], sizeof(CVector3));
					memcpy(&vTexture[0], &vTexture[1], sizeof(CVector2));

					memcpy(&vVertex[1], &vVertex[3], sizeof(CVector3));
					memcpy(&vNormal[1], &vNormal[3], sizeof(CVector3));
					memcpy(&vTexture[1], &vTexture[3], sizeof(CVector2));

					AddTriangle(vVertex, vNormal, vTexture);
				}
				t -= dt;
			}
		}

		CShpereMeshNode::~CShpereMeshNode()
		{

		}

		void CShpereMeshNode::AddTriangle(CVector3 verts[3], CVector3 vNorms[3], CVector2 vTexCoords[3])
		{
			vNorms[0].normalize();
			vNorms[1].normalize();
			vNorms[2].normalize();

			for (uint iVertex = 0; iVertex < 3; iVertex++)
			{
				
			}
		}

	}
}