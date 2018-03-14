#ifndef _SE_MATH_CAABBOX_H_
#define _SE_MATH_CAABBOX_H_

#include "CVector3.h"

namespace se
{
	namespace math
	{		
		class CAABBox
		{
		public:
			CAABBox():m_minVertex(-1, -1, -1), m_maxVertex(1, 1, 1){}
			CAABBox(const CVector3 &minVertex, const CVector3 &maxVertex) :m_minVertex(minVertex), m_maxVertex(maxVertex){}

            const CVector3 &GetMinVertex() const
            {
                return m_minVertex;
            }
            
            const CVector3 &GetMaxVertex() const
            {
                return m_maxVertex;
            }
            
            void Transform(const CMatrix4 &mat)
            {
                mat.TransformVect(m_minVertex);
                mat.TransformVect(m_maxVertex);
            }
            
            void Expand(const CVector3 &vert)
            {
                for (int i = 0; i<3; ++i)
                {
                    if (vert.v[i] < m_minVertex.v[i])
                        m_minVertex.v[i] = vert.v[i];
                    if (vert.v[i] > m_maxVertex.v[i])
                        m_maxVertex.v[i] = vert.v[i];
                }
            }
        private:
			CVector3 m_minVertex;
			CVector3 m_maxVertex;
		};
	}
}

#endif
