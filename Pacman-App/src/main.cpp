#include <iostream>

#include "Core/Application.h"

#include <glm/glm.hpp>



int main()
{
	using namespace Core;


	Application* app = new Application;
	app->Run();
	delete app;
}