#pragma once

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include "../Renderer/Shader.h"
#include "../Renderer/Texture.h"

#include "../Scene/Scene.h"


namespace Core
{

	class Application
	{
		public :
			
			Application();
			~Application();
			void Run();



		private :
			GLFWwindow* m_Window;
			Shader* m_Shader;
			Texture* m_Texture;

			std::shared_ptr<Scene> m_CurrentScene;
	};

}