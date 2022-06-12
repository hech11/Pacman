#include "Input.h"


namespace Core 
{
	static GLFWwindow* s_Handle;
	void Input::Init(GLFWwindow* handle)
	{
		s_Handle = handle;
	}
	bool Input::IsKeyPressed(int keycode)
	{
		return glfwGetKey(s_Handle, keycode) == GLFW_PRESS;
	}
}


