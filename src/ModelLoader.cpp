#include "ModelLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <glm.hpp>
#include <unordered_map>

bool ModelLoader::LoadObjModel(const std::string& filePath, std::vector<float>& outVertex, std::vector<unsigned int>& outIndices)
{
	std::cout << "Loading .obj model from " << filePath << std::endl;

	std::ifstream stream(filePath);

	if (!stream.is_open())
	{
		std::cout << "Failed to open file " << filePath << std::endl;
		return false;
	}

	std::vector<glm::vec3> vertexPosition;
	std::vector<glm::vec3> vertexNormal;
	std::vector<glm::vec2> vertexTexture;

	std::unordered_map<std::string, unsigned int> indicesMap;

	std::string line;

	while (getline(stream, line))
	{
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		if (prefix == "v")
		{
			glm::vec3 position;
			iss >> position.x >> position.y >> position.z;
			vertexPosition.push_back(position);
		}
		else if (prefix == "vn")
		{
			glm::vec3 normal;
			iss >> normal.x >> normal.y >> normal.z;
			vertexNormal.push_back(normal);
		}
		else if (prefix == "vt")
		{
			glm::vec2 texture;
			iss >> texture.x >> texture.y;
			vertexTexture.push_back(texture);
		}
		else if (prefix == "f")
		{
			std::vector<unsigned int> positionIndices;
			std::vector<unsigned int> normalIndices;
			std::vector<unsigned int> textureIndices;

			std::string vertexData;
			
			while (iss >> vertexData)
			{
				std::istringstream fiss(vertexData);

				unsigned int positionIndex, textureIndex, normalIndex;
				char slash;
				fiss >> positionIndex >> slash >> textureIndex >> slash >> normalIndex;

				// indices in obj format start from 1
				positionIndices.push_back(positionIndex - 1);
				textureIndices.push_back(textureIndex - 1);
				normalIndices.push_back(normalIndex - 1);
			}

			// obj file prefix f row can be 4 vertexs (quad, not triangle)
			for (unsigned int i = 1; i < positionIndices.size() - 1; ++i)
			{
				// create fan shaped triangles
				unsigned int indices[3] = { 0, i, i + 1 };

				// loop for each vertex
				for (unsigned int j = 0; j < 3; ++j)
				{
					unsigned int positionIndex = positionIndices[indices[j]];
					unsigned int textureIndex = textureIndices[indices[j]];
					unsigned int normalIndex = normalIndices[indices[j]];

					// same position, same vertex
					std::string key = std::to_string(positionIndex);

					// store the vertex data if no match
					if (indicesMap.find(key) == indicesMap.end())
					{
						indicesMap[key] = outVertex.size() / 8;

						const auto& v = vertexPosition[positionIndex];
						const auto& vn = vertexNormal[normalIndex];
						const auto& vt = vertexTexture[textureIndex];

						// 8 elements for 1 vertex
						outVertex.insert(outVertex.end(), { v.x, v.y, v.z, vn.x, vn.y, vn.z, vt.x, vt.y });
					}

					// store index data
					outIndices.push_back(indicesMap[key]);
				}
			}
		}

	}

	return true;
}