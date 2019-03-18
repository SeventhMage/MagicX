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
		bool rayTriangleIntersect(const math::CRay &ray, const math::CVector3 &v0, const math::CVector3 &v1, const math::CVector3 &v2, float &t, float &u, float &v)
		{
			CVector3 v0v1 = v1 - v0;
			CVector3 v0v2 = v2 - v0;
			CVector3 dir = ray.GetDirection();
			CVector3 pvec = dir.crossProduct(v0v2);
			float det = v0v1.dotProduct(pvec);

			// ray and triangle are parallel if det is close to 0
			if (fabs(det) < ROUNDING_ERROR_FLOAT) return false;

			float invDet = 1 / det;

			CVector3 tvec = ray.GetOrigin() - v0;
			u = tvec.dotProduct(pvec) * invDet;
			if (u < 0 || u > 1) return false;

			CVector3 qvec = tvec.crossProduct(v0v1);
			v = dir.dotProduct(qvec) * invDet;
			if (v < 0 || u + v > 1) return false;

			t = v0v2.dotProduct(qvec) * invDet;

			return (t > 0) ? true : false;
		}

		bool CSphere::Intersect(const math::CRay &ray, const math::CMatrix4 &transform, float *distance /*= nullptr*/, math::CVector3 *hitPoint /*= nullptr*/, math::CVector2 *uv /*= nullptr*/, uint *triIndex /*= nullptr*/)
		{
			uint numTris = m_vertexCount / 3;
			uint j = 0;
			float tNear = INFINITY;
			bool bOnlyInsetTest = (distance == nullptr) && (hitPoint == nullptr) && (uv == nullptr) && (triIndex == nullptr);
			bool isect = false;
			for (uint i = 0; i < numTris; ++i) {
				CVector3 v0;
				transform.TransformVect(v0, m_vertices[i]);
				CVector3 v1;
				transform.TransformVect(v1, m_vertices[i]);
				CVector3 v2;
				transform.TransformVect(v2, m_vertices[i]);


				float t = INFINITY, u, v;
				if (rayTriangleIntersect(ray, v0, v1, v2, t, u, v) && t < tNear)
				{
					if (bOnlyInsetTest)
						break;
					tNear = t;
					if (uv)
					{
						uv->x = u;
						uv->y = v;
					}
					if (triIndex)
						*triIndex = i;
					isect = true;
				}
				j += 3;
			}
			if (distance)
				*distance = tNear;
			if (hitPoint)
				*hitPoint = ray.GetOrigin() + ray.GetDirection() * tNear;
			return isect;
		}

		void CSphere::GetSurfaceData(const uint &triIndex, const math::CVector2 &uv, math::CVector3 &hitNormal, base::Color &hitColor)
		{
			const math::CVector3 &n0 = m_normals[triIndex * 3];
			const math::CVector3 &n1 = m_normals[triIndex * 3 + 1];
			const math::CVector3 &n2 = m_normals[triIndex * 3 + 2];
			hitNormal = (1 - uv.x - uv.y) * n0 + uv.x * n1 + uv.y * n2;

			// doesn't need to be normalized as the N's are normalized but just for safety
			hitNormal.normalize();

			// texture coordinates
			const math::CVector2 &st0 = m_texCoords[triIndex * 3];
			const math::CVector2 &st1 = m_texCoords[triIndex * 3 + 1];
			const math::CVector2 &st2 = m_texCoords[triIndex * 3 + 2];
			math::CVector2 hitTextureCoordinates = (1 - uv.x - uv.y) * st0 + uv.x * st1 + uv.y * st2;
			hitColor = base::Color(.1f, 0.1f, 0.2f, .4f);
		}

	}
}