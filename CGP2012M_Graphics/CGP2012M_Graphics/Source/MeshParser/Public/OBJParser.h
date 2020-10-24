#pragma once

#include <Mesh/Public/Mesh.h>
#include <vector>

class OBJParser
{
public:

	static Mesh* LoadModel(const char* path);
	static void ParseIndicies(std::string s, std::vector<unsigned int> *location, unsigned int verts);
	static void ParseVerticies(std::string string, std::vector<float> *location);
	static std::vector<float> ParseVerticies(std::string string);
};
