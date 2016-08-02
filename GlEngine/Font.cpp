#include "stdafx.h"
#include "Font.h"

//#include "freetype-gl\freetype-gl.h"
#include <fstream>

namespace GlEngine
{
	Font::Font(const char * const filename, int size)
	{
		filename;
		this->size = size;
		//auto atlas = texture_atlas_new(100, 100, 8);
		//auto font = texture_font_new_from_file(atlas, 16, "font.ttf");
	}
	Font::~Font()
	{
	}

	void Font::Use()
	{
	}

	//float Font::StringWidth(const char * const str)
	//{
	//	str;
	//	Use();
	//}
	//
	//float Font::StringHeight(const char * const str)
	//{
	//	str;
	//	Use();
	//}

	//void Font::Render(const char * const str)
	//{
	//	str;
	//	Use();
	//}
}