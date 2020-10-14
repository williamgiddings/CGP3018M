#pragma once

#include <Mesh/Public/Mesh.h>
#include <vector>

static class OBJParser
{
public:

	Mesh* LoadModel(const char* path);
	void parseIndicies(std::string s, std::vector<unsigned int> *location, unsigned int verts);
	void parseVerticies(std::string string, std::vector<float> *location);
	std::vector<float> parseVerticies(std::string string);
	float formatString(std::string s);
};
