#ifndef _RENDER_C_MATERIAL_H_
#define _RENDER_C_MATERIAL_H_

#include "render/IMaterial.h"

namespace se
{
	namespace render
	{
		class CMaterial : public IMaterial
		{
		public:
			CMaterial(int id);
			virtual ~CMaterial();

			virtual int GetID(){ return m_Id; }
			virtual math::CVector3 GetColor();
			virtual void SetColor(const math::CVector3 &color);
			virtual std::string GetIllumination();
			virtual void SetIllumination(const std::string &illumination);
		private:
			int m_Id;
			math::CVector3 m_vColor;
			std::string m_strIllumination;
		};
	}
}

#endif