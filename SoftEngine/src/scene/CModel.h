#include "scene/IModel.h"
#include "base/base.h"

namespace se
{
	namespace scene
	{
		class CModel : public IModel
		{
		public:
			CModel(const char *filename);
			virtual ~CModel();		
			virtual std::string GetMaterialName(){ return "material/common.mtl"; }
			virtual base::Vertices *GetVertices(){ return m_pVertices; }
			virtual base::Indices *GetIndices() { return m_pIndices; }
			virtual int GetTextureID(){ return m_textureId; }
		private:
			void Load(const char *filename);
		private:
			std::string m_strName;
			base::Vertices *m_pVertices;
			base::Indices *m_pIndices;
			int m_textureId;
		};
	}
}