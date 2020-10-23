
#include <MeshParser/Public/OBJParser.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Vertex
{
	float x, y, z;
	Vertex(float X, float Y, float Z) : x(X), y(Y), z(Z) {};
};
struct UV
{
	float x, y;
	UV(float X, float Y) : x(X), y(Y) {};
};
struct Normal
{
	float x, y, z;
	Normal(float X, float Y, float Z) : x(X), y(Y), z(Z) {};
};

Mesh* OBJParser::LoadModel(const char* path)
{
	std::vector<float> tverts;
	std::vector<float> tnorms;
	std::vector<float> tuv;
	std::vector<unsigned int> tindicies;

	std::vector<unsigned int> indicies;

	std::vector<float> verticies;

	std::ifstream myfile = std::ifstream(path);
	std::string line;

	std::vector<float> TVERTEX;
	std::vector<float> TUV;
	std::vector<float> TNORM;

	std::vector<Vertex> _verticies;
	std::vector<UV> _uvcoords;
	std::vector<Normal> _normals;

	std::vector<float> temp;

	while (!myfile.eof())
	{
		std::getline(myfile, line);
		

		if (line.substr(0, 2) == "v ")
		{
			temp = parseVerticies(line.substr(2, line.length() - 1));
			_verticies.push_back(Vertex(temp[0], temp[1], temp[2]));
			temp.clear();
			//parseVerticies(line.substr(2, line.length() - 1), &tverts);
		}
		else if (line.substr(0, 3) == "vt ")
		{
			std::string oooga = line.substr(2, line.length() - 1);
			temp = parseVerticies(line.substr(2, line.length() - 1));
			_uvcoords.push_back(UV(temp[1], temp[2]));
			temp.clear();
			//parseVerticies(line.substr(3, line.length() - 1), &tuv);
		}
		else if (line.substr(0, 3) == "vn ")
		{
			temp = parseVerticies(line.substr(2, line.length() - 1));
			_normals.push_back(Normal(temp[0], temp[1], temp[2]));
			temp.clear();
			//parseVerticies(line.substr(3, line.length() - 1), &tnorms);
		}
		else if (line.substr(0, 2) == "f ")
		{
			parseIndicies(line.substr(2, line.length() - 1), &tindicies, tverts.size() / 3);
		}
	}

	myfile.close();
	
	
	for (int i = 0; i < tindicies.size(); i+=3)
	{
		verticies.push_back(_verticies[tindicies[i]].x);
		verticies.push_back(_verticies[tindicies[i]].y);
		verticies.push_back(_verticies[tindicies[i]].z);
		
		verticies.push_back(_uvcoords[tindicies[i+1]].x);
		verticies.push_back(_uvcoords[tindicies[i+1]].y);

		verticies.push_back(_normals[tindicies[i+2]].x);
		verticies.push_back(_normals[tindicies[i+2]].y);
		verticies.push_back(_normals[tindicies[i+2]].z);
	}

	
	
	return new Mesh( verticies, tindicies, Mesh::VertexLoadingModes::Indexed );
}

void OBJParser::parseIndicies(std::string s, std::vector<unsigned int> *location, unsigned int verts)
{
	std::vector<unsigned int> tiv;
	std::vector<unsigned int> tin;
	std::vector<unsigned int> tiuv;
	std::vector<unsigned int> *curVector;

	std::vector<char> curValue;
	int valueIndex = 0;
	int indexType = 0; //0 for verts, 1 for normals, 2 for UV coords

	for (int i = 0; i < s.length(); i++)
	{
		switch (indexType)
		{
		case 0:
			curVector = &tiv;
			break;
		case 1:
			curVector = &tiuv;
			break;
		case 2:
			curVector = &tin;
			break;
		default:
			break;
		}

		if (s[i] != '/' && s[i] != ' ')
		{
			curValue.push_back(s[i]);
			valueIndex++;
		}
		if (s[i] == '/')
		{
			if (curValue.size() > 0)
			{
				curValue.push_back('\0');
				curVector->push_back(atoi(curValue.data()) - 1);
				
				curValue.clear();
			}
			indexType++;
			valueIndex = 0;
			
		}
		if (s[i] == ' ' || i == s.length() - 1)
		{
			if (curValue.size() > 0)
			{
				curValue.push_back('\0');
				curVector->push_back(atoi(curValue.data()) - 1);
				
				curValue.clear();
			}
			indexType = 0;
			valueIndex = 0;
			
		}

	}

	for (int i = 0; i < tiv.size(); i++)
	{
		location->push_back(tiv[i]);
		location->push_back(tiuv[i]);
		location->push_back(tin[i]);
	}

}


void OBJParser::parseVerticies(std::string s, std::vector<float> *location)
{
	char curValue[9];
	int valueIndex = 0;

	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] != ' ')
		{
			curValue[valueIndex] = s[i];
			valueIndex++;
		}
		if (s[i] == ' ' || i == s.length() - 1)
		{
			curValue[8] = '\0';
			location->push_back(atof(curValue));
			for (auto &v : curValue)
			{
				v = '\0';
			}
			valueIndex = 0;
		}

	}
}

std::vector<float> OBJParser::parseVerticies(std::string s)
{
	char curValue[9];
	int valueIndex = 0;
	std::vector<float> temp;
	
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] != ' ')
		{
			curValue[valueIndex] = s[i];
			valueIndex++;
		}
		if (s[i] == ' ' || i == s.length() - 1)
		{
			curValue[8] = '\0';
			temp.push_back(atof(curValue));
			
			valueIndex = 0;

		}
	}
	return temp;
}


