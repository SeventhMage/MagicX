/************************************************************************/
/* ��Ⱦ�б�ӿ�                                                         */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDER_LIST_H_
#define _MX_RENDER_I_RENDER_LIST_H_


namespace mx
{
	namespace render
	{
		class IRenderable;
		class IShaderProgram;
		class IRenderList
		{
		public:			
			virtual ~IRenderList(){}
			
			//�����Ⱦʵ�嵽��Ⱦ�б�
			virtual void AddRenderable(IRenderable *pRenderable) = 0;
			//�Ƴ���Ⱦʵ��
			virtual void RemoveRenderable(IRenderable *pRenderable) = 0;
			
			virtual void Clear() = 0;

			virtual void SetShaderProgram(IShaderProgram *) = 0;

			//ִ����Ⱦ
			virtual void Render() = 0;

		};
	}
}

#endif