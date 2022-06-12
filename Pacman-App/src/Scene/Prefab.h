#pragma once


#include "Entity.h"
namespace Core
{

	class Prefab
	{
		public :
			static Entity GetBlockPrefab(Scene* context);
			static Entity GetPacmanPrefab(Scene* context);
	};

}