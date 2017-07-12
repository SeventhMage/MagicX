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
				if (norSize > 0)
					m_pVertices->format.push_back(base::VertexAttrbute(base::VA_NORMAL, posSize));
				//if (texSize > 0)
				//	m_pVertices->format.push_back(base::VertexAttrbute(base::VA_TEXCOORD, posSize + norSize));

				m_pVertices->size = posSize + posSize;
				m_pVertices->stride = 0;

				SAFE_DEL(m_pVertices->pVertexData);
				m_pVertices->pVertexData = new ubyte[m_pVertices->size];
				memset(m_pVertices->pVertexData, 0, m_pVertices->size);
				
				for (size_t i = 0; i < posList.size(); ++i)
				{					
					memcpy(m_pVertices->pVertexData + i * sizeof(CVector3), posList[i].v, sizeof(CVector3));
				}

				std::vector<CVector3> normalList(posList.size(), CVector3());

				for (size_t i = 0; i < faceList.size(); ++i)
				{			

					for (int j = 0; j < faceList[i].indicesCount; ++j)
					{
						int last = j - 1 < 0 ? faceList[i].indicesCount - 1 : j - 1;
						int next = j + 1 >= faceList[i].indicesCount ? 0 : j + 1;
						CVector3 v0 = posList[faceList[i].position[last]] - posList[faceList[i].position[j]];
						CVector3 v1 = posList[faceList[i].position[next]] - posList[faceList[i].position[j]];

						normalList[faceList[i].position[j]] += v1.crossProduct(v0);
						
					}					
				}

				for (uint i = 0; i < normalList.size(); ++i)
				{
					normalList[i].normalize();
					memcpy(m_pVertices->pVertexData + posSize + i * sizeof(CVector3), normalList[i].v, sizeof(CVector3));
				}				
				
				uint count = 0;
				for (uint i = 0; i<faceList.size(); ++i)
				{
					if (faceList[i].indicesCount == 3)
						count += 3;
					else
						count += 6;
				}

				m_pIndices->size = count * sizeof(ushort);
				
				if (m_pIndices->size > 0)
				{
					m_pIndices->pIndexData = new ushort[count];
					ushort *pDataAddr = m_pIndices->pIndexData;
					for (uint i = 0; i < faceList.size(); ++i)
					{
						if (faceList[i].indicesCount == 3)
						{
							memcpy(pDataAddr, faceList[i].position, sizeof(ushort)* 3);
							pDataAddr += 3;
						}
						else
						{
							ushort tri[6] = { faceList[i].position[0], faceList[i].position[1], faceList[i].position[2],
								faceList[i].position[0], faceList[i].position[2], faceList[i].position[3] };
							memcpy(pDataAddr, tri, sizeof(tri));
							pDataAddr += 6;
						}
					}
				}
			}
		}

	}
}