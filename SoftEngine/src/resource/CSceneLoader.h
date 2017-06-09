#ifndef _RESOURCE_C_SCENE_LOADER_H_
#define _RESOURCE_C_SCENE_LOADER_H_

#include "resource/IResourceLoader.h"
#include "resource/ISceneResource.h"
#include "math/CVector3.h"
#include <vector>
#include <fstream>


namespace se
{
	namespace resource
	{
		class CSceneLoader : public IResourceLoader
		{
		public:
			CSceneLoader(const char *filename);
			virtual ~CSceneLoader();

			const math::CVector3 &GetCameraPosition(){ return m_camPos; }
			const math::CVector3 &GetCameraDirection() { return m_camDir; }
			const math::CVector3 &GetCameraUp(){ return m_camUp; }
			float GetCameraFov(){ return m_camFov; }
			float GetCameraNearClip(){ return m_camNearClip; }
			float GetCameraFarClip(){ return m_camFarClip; }
			const std::vector<SEntityInfo> &GetEntityInfo(){ return m_vecEntity; }
			int GetEntityCount(){ return m_vecEntity.size(); }

		private:
			bool ReadLine(std::ifstream &in, char *out, int size);
		private:
			//摄像机参数
			math::CVector3 m_camPos;
			math::CVector3 m_camDir;
			math::CVector3 m_camUp;
			float m_camFov;
			float m_camNearClip;
			float m_camFarClip;

			//场景内物体
			std::vector<SEntityInfo> m_vecEntity;
		};
	}
}

#endif