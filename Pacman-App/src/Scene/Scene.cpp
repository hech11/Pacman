#include "Scene.h"

#include "Entity.h"
#include "Component.h"

#include "GL/glew.h"


#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "../Renderer/Renderer.h"

#include <sstream>
#include <fstream>


#include "Prefab.h"
namespace Core
{

	Scene::Scene()
	{
		m_Registry = new EntityRegistry;
	}

	Scene::~Scene()
	{
		delete m_Registry;
	}

	void Scene::LoadLevel(const std::string& filepath)
	{
		std::fstream file(filepath);
		std::string line;
		std::stringstream ss;

		while (getline(file, line))
		{
			ss << line << "\n";
		}


		std::string levelMap = ss.str();

		glm::vec3 position = {0.0f, 0.0f, 0.0f};
		for (int i = 0; i < levelMap.length(); i++)
		{
			if (levelMap[i] == 'b')
			{
				Entity block = Prefab::GetBlockPrefab(this);
				auto& transform = block.GetComponent<TransformComponent>();

				transform = glm::translate(glm::mat4(1.0f), position);

			}

			if (levelMap[i] == 'p')
			{
				Entity pacman = Prefab::GetPacmanPrefab(this);
				auto& transform = pacman.GetComponent<TransformComponent>();
				transform = glm::translate(glm::mat4(1.0f), position);
			}
			if (levelMap[i] == '\n')
			{
				position.y -= 1;
				position.x = 0;
				continue;
			}
			if (levelMap[i] == ' ')
			{
				position.x += 1;
				continue;
			}

			position.x += 1;
		}


	}

	void Scene::OnUpdate(float ts)
	{


		// begin rendering whole scene
		glClear(GL_COLOR_BUFFER_BIT);
		float camZoom = 3.0f;
		glm::vec3 cameraPos = {-8.5f* camZoom, 4.325f* camZoom, 0.0f};
		glm::mat4 projView = glm::ortho(-8.0f * camZoom, 8.0f * camZoom, -4.5f * camZoom, 4.5f * camZoom, 0.0f, 1.0f) * glm::translate(glm::mat4(1.0f),cameraPos);


		Renderer::Begin(projView);
		m_Registry->ForEach<SpriteRenderingComponent>([&](EntityHandle handle, SpriteRenderingComponent& component)
		{

				Entity e = { handle, this };
				Renderer::SumbitSprite(e.GetComponent<TransformComponent>().Transform, component.TexCoords);


		});
		Renderer::End();
	}

	Core::Entity Scene::CreateEntity()
	{
		Entity result(m_Registry->CreateEntity(), this);
		result.AddComponent<TransformComponent>();
		return result;
	}

}