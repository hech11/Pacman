#pragma once

#include <random>

namespace Core
{


	class Random
	{
		public :
			static uint64_t Generate64()
			{
				static std::random_device device{};
				std::mt19937_64 time(device());

				std::uniform_int_distribution<uint64_t> dist;
				return dist(time);
			}
	};
}