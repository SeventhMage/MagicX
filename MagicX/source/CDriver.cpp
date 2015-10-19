#include "CDriver.h"
#include "CDeviceManager.h"
#include "CSceneManager.h"
#include "CGUIManager.h"
#include "driver/CMXRenderDriver.h"

namespace mx
{
	using namespace scene;
	using namespace gui;

	CDriver::CDriver()
	{
		CDeviceManager::NewInstance();
		CSceneManager::NewInstance();
		CGUIManager::NewInstance();
	}

	CDriver::~CDriver()
	{
		CDeviceManager::DeleteInstance();
		CSceneManager::DeleteInstance();
		CGUIManager::DeleteInstance();
	}

	IDevice * CDriver::CreateDevice(uint uWidth, uint uHeight, bool bFullScreen /* = false */, RendererType renderType /* = RT_OPENGL */)
	{
		IDevice *device = CDeviceManager::Instance()->CreateDevice(uWidth, uHeight, bFullScreen);
		IDeviceDriver *deviceDriver = new driver::CMXRenderDriver(renderType);
		device->SetupDriver(deviceDriver);
		return device;
	}

	void CDriver::Run()
	{
		IDevice *device = CDeviceManager::Instance()->GetDevice();
		CSceneManager *sceneManager = CSceneManager::Instance();
		CGUIManager *guiManager = CGUIManager::Instance();

		while (device->Run())
		{
			static long lastTime = device->GetSystemRunTime();
			if (device->GetSystemRunTime() - lastTime > 33)
			{
				sceneManager->Update(0);
				guiManager->Update(0);

				sceneManager->Render();
				guiManager->Render();

				lastTime = device->GetSystemRunTime();
			}		
		}
	}

}