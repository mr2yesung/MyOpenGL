#pragma once

#include <string>
#include <vector>

class ModelLoader {
public:
	static bool LoadObjModel(const std::string& filePath, std::vector<float>& outVertex, std::vector<unsigned int>& outIndices);
};