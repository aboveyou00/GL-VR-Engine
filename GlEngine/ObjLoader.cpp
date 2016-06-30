#include "stdafx.h"
#include "ObjLoader.h"
#include <sstream>
#include <algorithm>
#include "StringUtils.h"

#include "VboFactory.h"

namespace GlEngine
{
	std::vector<Vector<3>> ObjLoader::positions;
	std::vector<Vector<3>> ObjLoader::normals;
	std::vector<Vector<2>> ObjLoader::texCoords;

	std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>> ObjLoader::glVertices;

	std::vector<int> ObjLoader::triangleIndeces;
	std::vector<int> ObjLoader::quadIndeces;

	bool isWhiteSpace(char c)
	{
		return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v';
	}

	bool isNewLine(char c)
	{
		return c == '\n' || c == '\r';
	}

	GraphicsObject ObjLoader::Load(const char * const filename)
	{
		std::ifstream in;
		in.open(filename, std::ifstream::in);
		auto result = Load(in);
		in.close();
		return result;
	}

	GraphicsObject ObjLoader::Load(std::istream & in)
	{
		std::string line;
		while (std::getline(in, line))
		{
			std::istringstream iss(line);
			
			std::string first;
			iss >> first;
			if (first == "p") //point
			{ } 
			else if (first == "v")
			{
				float x, y, z;
				iss >> x >> y >> z;
				positions.push_back({ x, y, z });
			}
			else if (first == "vt")
			{
				float u, v;
				iss >> u >> v;
				texCoords.push_back({ u, v });
			}
			else if (first == "vn")
			{
				float nx, ny, nz;
				iss >> nx >> ny >> nz;
				normals.push_back({nx, ny ,nz});
			}
			else if (first == "f")
			{
				std::string s0, s1, s2, s3;
				iss >> s0 >> s1 >> s2;
				if (!(iss >> s3))		// tri
				{
					triangleIndeces.push_back(ParseVertex(s0));
					triangleIndeces.push_back(ParseVertex(s1));
					triangleIndeces.push_back(ParseVertex(s2));
				}
				else					// quad
				{
					quadIndeces.push_back(ParseVertex(s0));
					quadIndeces.push_back(ParseVertex(s1));
					quadIndeces.push_back(ParseVertex(s2));
					quadIndeces.push_back(ParseVertex(s3));
				}
			}
		}

		return CreateFromData();
	}

	GraphicsObject ObjLoader::CreateFromData()
	{
		VboFactory<VboType::Float, Vector<3>, Vector<2>, Vector<3>> verticesFactory(BufferMode::Array);
		verticesFactory.Allocate(glVertices.size());
		for (auto vertex : glVertices)
		{
			Vector<3> position; Vector<2> texCoord; Vector<3> normal;
			std::tie(position, texCoord, normal) = vertex;
			verticesFactory.AddVertex(position, texCoord, normal);
		}

		//TODO: dynamically choose VboType based on size
		VboFactory<VboType::UnsignedShort, uint16_t, uint16_t, uint16_t> trianglesFactory(BufferMode::ElementArray);
		trianglesFactory.Allocate(triangleIndeces.size() / 3);
		for (unsigned i = 0; i < triangleIndeces.size(); i += 3)
		{
			trianglesFactory.AddVertex((uint16_t)triangleIndeces[i], (uint16_t)triangleIndeces[i + 1], (uint16_t)triangleIndeces[i + 1]);
		}

		verticesFactory.Compile();
		trianglesFactory.Compile();

		return GraphicsObject();
	}

	int ObjLoader::ParseVertex(std::string faceString)
	{
		Vector<3> position;
		Vector<2> texCoord;
		Vector<3> normal;

		std::string current;
		int idx = 0;
		for (unsigned i = 0; i <= faceString.length(); i++)
		{
			if (faceString[i] == '/' || i == faceString.length())
			{
				idx++;
				if (current.empty())
					continue;

				switch (idx)
				{
				case 0:
					int positionIndex;
					if (!Util::stoi(current.c_str(), positionIndex))
						positionIndex = 0;
					positionIndex += positionIndex < 0 ? positions.size() : -1;
					position = positions[positionIndex];
				case 1:
					int texCoordIndex;
					if (!Util::stoi(current.c_str(), texCoordIndex))
						texCoordIndex = 0;
					texCoordIndex += texCoordIndex < 0 ? texCoords.size() : -1;
					texCoord = texCoords[texCoordIndex];
				case 2:
					int normalIndex;
					if (!Util::stoi(current.c_str(), normalIndex))
						normalIndex = 0;
					normalIndex += normalIndex < 0 ? normals.size() : -1;
					normal = normals[normalIndex];
				}
			}
			else
				current += faceString[i];
		}

		return FindOrAddGlVertex(position, texCoord, normal);
	}

	int ObjLoader::FindOrAddGlVertex(Vector<3> vertex, Vector<2> texCoord, Vector<3> normal)
	{
		std::tuple<Vector<3>, Vector<2>, Vector<3>> glVertex;
		
		auto index = std::find(glVertices.begin(), glVertices.end(), glVertex);
		if (index == glVertices.end())
		{
			glVertices.push_back(glVertex);
			return glVertices.size() - 1;
		}
		else 
		{
			return index - glVertices.begin();
		}
	}
}