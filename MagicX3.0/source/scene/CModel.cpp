#include "CModel.h"


namespace mx
{
	namespace scene
	{


		CModel::CModel()
			:m_pMesh(nullptr)
			, m_pRenderObject(nullptr)			
		{
			
		}

		CModel::~CModel()
		{

		}

		bool CModel::Load(const char *filename)
		{
			return false;
		}

	}
}