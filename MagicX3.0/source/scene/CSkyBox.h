#ifndef _C_SKY_BOX_H_
#define _C_SKY_BOX_H_

#include <string>

#include "scene/IScene.h"
#include "scene/ISkyBox.h"
#include "render/IVertexArrayObject.h"
#include "render/ITexture.h"
#include "math/CMatrix4.h"
#include "mxType.h"
#include "render/IShaderProgram.h"
#include "scene/CEntity.h"



namespace mx
{
	namespace scene
	{
		class CSkyBox : public ISkyBox, public CEntity
		{
		public:
			CSkyBox(IScene *pScene, float radius);
			virtual ~CSkyBox();

			virtual bool Create(const char *filename);
			virtual bool Create(const char *right, const char *left, const char *top, const char *bottom, const char *front, const char *back);
			virtual render::ITexture *GetTexture() { return m_pTexture; }
			virtual const CMatrix4 &GetModelMatrix() { return m_modelMatr4; }
			virtual void UpdateImp(int delta);			
		private:
			std::string m_filename;
			math::CMatrix4 m_viewMat4;
			math::CMatrix4 m_modelMatr4;
			render::ITexture *m_pTexture;
			IScene *m_pParentScene;
			float *m_pBoxData;			
			float m_fRadius;
		};
	}
}

#endif