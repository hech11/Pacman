#pragma once

#include <string>


namespace Core
{

	class Texture
	{
		public :
			Texture(const std::string& filepath);
			~Texture();


			void Bind(uint32_t slot = 0);
			void Unbind();


			int32_t GetWidth() { return m_Width; }
			int32_t GetHeight() { return m_Height; }


		private :
			int32_t m_Width, m_Height, m_BPP;
			uint32_t m_TextureID;
	};

}