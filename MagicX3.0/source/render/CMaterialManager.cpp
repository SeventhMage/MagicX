#include "CMaterialManager.h"
#include "mxDef.h"
#include "rapidxml.hpp"
#include "CMaterial.h"

#include <fstream>


namespace mx
{
	namespace render
	{

		CMaterialManager::CMaterialManager()
		{
		}

		CMaterialManager::~CMaterialManager()
		{
			for (auto it = m_mapMaterials.begin(); it != m_mapMaterials.end(); ++it)
			{
				SAFE_DEL(it->second);
			}
		}

		void CMaterialManager::LoadMaterial(const char * root)
		{
			char buf[1024] = {0};

			std::ifstream infile(root, std::ios::in);
			if (!infile)
			{
				return;
			}
			infile.read(buf, sizeof(buf));
			rapidxml::xml_document<> doc;
			doc.parse<0>(buf);

			rapidxml::xml_node<> *rootNode = doc.first_node("MaterialRoot");
			if (rootNode)
			{
				for (rapidxml::xml_node<> * node = rootNode->first_node("Material"); node; node = node->next_sibling())
				{
					int id = atoi(node->first_attribute("id")->value());
					char *name = node->first_attribute("name")->value();
					 m_mapMaterials[id] = CreateMaterial(id, name);
					 
				} 
			}
		}

		IMaterial * CMaterialManager::GetMaterial(const char * name)
		{
			return nullptr;
		}

		IMaterial * CMaterialManager::GetMaterial(int id)
		{
			auto it = m_mapMaterials.find(id);
			if (it != m_mapMaterials.end())
			{
				return it->second;
			}
			return nullptr;
		}

		IMaterial * CMaterialManager::CreateMaterial(int id, const char *name)
		{
			char buf[1024] = { 0 };
			std::ifstream infile(name, std::ios::in);
			if (!infile)
			{
				return nullptr;
			}

			IMaterial *pMaterial = new CMaterial(id);

			infile.read(buf, sizeof(buf));
			rapidxml::xml_document<> doc;
			doc.parse<0>(buf);

			rapidxml::xml_node<> *rootNode = doc.first_node("Material");
			if (rootNode)
			{
				rapidxml::xml_node<> * shaderProgramNode = rootNode->first_node("ShaderProgram");
				if (shaderProgramNode)
				{
					const char *vs = shaderProgramNode->first_attribute("vs")->value();
					const char *ps = shaderProgramNode->first_attribute("ps")->value();
					IShaderProgram *pShaderProgram = pMaterial->GetShaderProgram();
					if (pShaderProgram)
					{
						pShaderProgram->Attach(vs, ST_VERTEX);
						pShaderProgram->Attach(ps, ST_FRAGMENT);

						rapidxml::xml_node<> *vertexAttributeNode = shaderProgramNode->first_node("VertexAttribute");
						if (vertexAttributeNode)
						{
							for (rapidxml::xml_node<> * node = vertexAttributeNode->first_node("Location"); node; node = node->next_sibling())
							{
								int index  = atoi(node->first_attribute("index")->value());
								const char *name = node->first_attribute("name")->value();
								pShaderProgram->BindAttributeLocation(index, name);
							}
						}

						pShaderProgram->Link();

						rapidxml::xml_node<> * uniformNode = shaderProgramNode->first_node("Uniform");
						if (uniformNode)
						{
							for (rapidxml::xml_node<> * node = uniformNode->first_node("Property"); node; node = node->next_sibling())
							{
								//char *name = node->first_attribute("name")->value();
								//char *value = node->first_attribute("value")->value();
								//pShaderProgram->SetUniform(name, value);
							}
						}
					}
				}
			}
			return pMaterial;
		}

	}
}