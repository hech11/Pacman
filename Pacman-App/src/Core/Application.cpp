#include "Application.h"

#include "../Renderer/Renderer.h"
#include "Input.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

#include "../Scene/Entity.h"
namespace Core
{

	Application::Application()
	{

		glfwInit();

		m_Window = glfwCreateWindow(1600, 900, "Pacman", nullptr, nullptr);

		glfwMakeContextCurrent(m_Window);
		glewInit();
		glfwSwapInterval(1);

		Input::Init(m_Window);

		Renderer::Init();

		m_CurrentScene = std::make_shared<Scene>();
	}

	Application::~Application()
	{
		Renderer::Shutdown();

		glfwDestroyWindow(m_Window);
	}

	void Application::Run()
	{

		m_CurrentScene->LoadLevel("assets/levels/testmap.txt");

		while (!glfwWindowShouldClose(m_Window))
		{
			glClear(GL_COLOR_BUFFER_BIT);


			m_CurrentScene->OnUpdate();

			glfwSwapBuffers(m_Window);
			glfwPollEvents();

		}

		delete m_Shader;
	}

}