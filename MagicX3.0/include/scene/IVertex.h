/************************************************************************/
/* �����ʽ���û��̳нӿ��Դ�������                                     */
/************************************************************************/

#ifndef _MX_SCENE_S__VERTEX_H_
#define _MX_SCENE_S__VERTEX_H_

namespace mx
{
	namespace scene
	{
		//�����ʽ����
		enum EVertexAttribute
		{
			VF_POSITION					= 0x0001,		//λ��
			VF_COLOR					= 0x0002,		//��ɫ
			VF_TEXCOORD					= 0x0004,		//��������
			VF_NORMAL					= 0x0008,		//����

			VF_COMPLETE = VF_POSITION | VF_COLOR | VF_TEXCOORD | VF_NORMAL,
		};		

		class IVertex
		{		
		public:
			virtual~IVertex(){}

			//���ص�ǰ�����ʽ
			virtual EVertexAttribute GetVertexAttribute() = 0;
			//���ض�������
			virtual void *GetVertexData() = 0;
			//���ض�������
			virtual uint GetVerticeCount() = 0;
			//���ض���ߴ�
			virtual uint GetVerticeSize() = 0;
			//������������
			virtual void *GetIndicesData() = 0;
			//������������
			virtual uint GetIndicesCount() = 0;
			//������������
			virtual void *GetTexCoordData() = 0;
			virtual uint GetTexCoordCount() = 0;
			virtual uint GetTexCoordSize() = 0;
		};

	}
}

#endif