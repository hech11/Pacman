#pragma once

#include <GLFW/glfw3.h>

namespace Core
{
	class Input
	{
		public :
			static void Init(GLFWwindow* handle);


			static bool IsKeyPressed(int keycode);

	};
}