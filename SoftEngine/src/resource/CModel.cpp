#include "CModel.h"

namespace se
{
	namespace resource
	{


		CModel::CModel(const char *filename)
		{
			m_pOBJLoader = new COBJLoader(filename);
		}

		CModel::~CModel()
		{
			SAFE_DEL(m_pOBJLoader);
		}

	}
}