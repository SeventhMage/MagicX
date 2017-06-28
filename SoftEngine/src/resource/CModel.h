#ifndef _RESOURCE_C_MODEL_H_
#define _RESOURCE_C_MODEL_H_

#include "resource/IModel.h"
#include "COBJLoader.h"

namespace se
{
	namespace resource
	{
		class CModel : public IModel
		{
		public:
			CModel(const char *filename);
			virtual ~CModel();

			virtual std::string GetMaterial();
			virtual std::string GetTexture();
			virtual SPolygon &GetPolygon();

		private:
			COBJLoader *m_pOBJLoader;
		};
	}
}

#endif