#ifndef _MX_RESOURCE_CMESHMANAGER_H_
#define _MX_RESOURCE_CMESHMANAGER_H_

#include "CResourceManager.h"
#include "IResource.h"
#include "render/IGPUBuffer.h"
#include "render/IRenderer.h"

namespace mx
{
	namespace resource
	{
		class CMeshManager : public CResourceManager
		{
		public:
			CMeshManager();
			virtual ~CMeshManager();			

		protected:
			virtual IResource *CreateResource(const char *filename);
		};
	}
}

#endif