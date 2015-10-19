#ifndef _I_TEXTURE_H_INC
#define _I_TEXTURE_H_INC


namespace mx
{
	namespace render
	{
		enum TexType
		{
			TT_1D,
			TT_2D,
			TT_3D,
			TT_CUBE,
		};
		class ITexture
		{
		public:
			ITexture(){};
			ITexture(TexType texType):m_texType(texType){};
			virtual ~ITexture(){};

			virtual bool Create() = 0;
		protected:
			void *m_texData;
			TexType m_texType;

		};
	}
}

#endif // !_I_TEXTURE_H_INC
