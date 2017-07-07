#include "CModel.h"
#include "CSoftEngine.h"
#include "resource/IOBJResource.h"

namespace se
{
	namespace scene
	{


		CModel::CModel(const char *filename)
			:m_strName(filename)			
		{
			m_pVertices = new base::Vertices;
			m_pIndices = new base::Indices;

			Load(filename);
		}

		CModel::~CModel()
		{
			SAFE_DEL(m_pVertices->pVertexData);
			SAFE_DEL(m_pVertices);

			SAFE_DEL(m_pIndices->pIndexData);
			SAFE_DEL(m_pIndices);
		}

		void CModel::Load(const char *filename)
		{
			resource::IOBJResource *pOBJResource = dynamic_cast<resource::IOBJResource *>(CSoftEngine::GetResourceManager()->LoadResource(filename));
			if (pOBJResource)
			{
				const std::vector<CVector3> & posList = pOBJResource->GetPositionList();
				const std::vector<CVector3> & norList = pOBJResource->GetNormalList();
				const std::vector<CVector2> & texList = pOBJResource->GetTexCoordList();
				const std::vector<resource::SFaceIndex> & faceList = pOBJResource->GetFaceIndexList();				
				uint posSize = posList.size() * sizeof(CVector3);
				uint norSize = norList.size() * sizeof(CVector3);
				uint texSize = texList.size() * sizeof(CVector2);

				m_pVertices->count = posList.size();
				if (posSize > 0)
					m_pVertices->format.push_back(base::VertexAttrbute(base::VA_POSITION, 0));
				//if (norSize > 0)
				//	m_pVertices->format.push_back(base::VertexAttrbute(base::VA_NORMAL, posSize));
				//if (texSize > 0)
				//	m_pVertices->format.push_back(base::VertexAttrbute(base::VA_TEXCOORD, posSize + norSize));

				m_pVertices->size = posSize;
				m_pVertices->stride = 0;

				SAFE_DEL(m_pVertices->pVertexData);
				m_pVertices->pVertexData = new float[m_pVertices->size];
				memset(m_pVertices->pVertexData, 0, m_pVertices->size);
				
				for (size_t i = 0; i < posList.size(); ++i)
				{					
					memcpy(m_pVertices->pVertexData + i * 3, posList[i].v, sizeof(CVector3));
				}
			//	memcpy(m_pVertices->pVertexData, &posList, posSize);
				//memcpy(m_pVertices->pVertexData + posSize, &norList, norSize);
				//memcpy(m_pVertices->pVertexData + posSize + norSize, &texList, texSize);
				m_pIndices->size = faceList.size() * sizeof(ushort) * 6;
				
				if (m_pIndices->size > 0)
				{
					m_pIndices->pIndexData = new ushort[m_pIndices->size];
					for (uint i = 0; i < faceList.size(); ++i)
					{
						ushort tri[6] = { faceList[i].position[0], faceList[i].position[1], faceList[i].position[2],
							faceList[i].position[0], faceList[i].position[2], faceList[i].position[3] };
						memcpy(m_pIndices->pIndexData + i * sizeof(ushort) * 6, tri, sizeof(tri));
					}
				}
			}
		}

	}
}