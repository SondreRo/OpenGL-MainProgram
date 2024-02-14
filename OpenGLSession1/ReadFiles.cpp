#include "ReadFiles.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::vector<Vertex> ReadFiles::ReadFileVertexData(const char* path)
{
	std::vector<Vertex> vertices;
	std::ifstream in;
	in.open(path);
	if (in.is_open())
	{
		std::string line;
		std::getline(in,line);
		std::cout << line << '\n';
		int amountOfPoints = std::stoi(line);
		while (std::getline(in,line) )
		{
			glm::vec3 pos;
			glm::vec3 nor;

			Vertex tempVertex;
			pos.x = std::stof(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			pos.y = std::stof(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			pos.z = std::stof(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			nor.x = std::stof(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			nor.y = std::stof(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			nor.z = std::stof(line.substr(0, line.find(',')));
			tempVertex.Position = pos;
			tempVertex.Normal = nor;
			vertices.push_back(tempVertex);
			
		}
		in.close();
	}
	else
	{
		std::cout << "Failed to open file: " << path << std::endl;
	}

	return vertices;
}

void ReadFiles::ReadFileVertexData(const char* path, Line& inLine)
{
	std::vector<Vertex> vertices;
	std::ifstream in;
	in.open(path);
	if (in.is_open())
	{
		std::string line;
		std::getline(in, line);
		std::cout << line << '\n';
		int amountOfPoints = std::stoi(line);
		while (std::getline(in, line))
		{
			glm::vec3 pos;
			glm::vec3 nor;

			Vertex tempVertex;
			pos.x = std::stof(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			pos.y = std::stof(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			pos.z = std::stof(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			nor.x = std::stof(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			nor.y = std::stof(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			nor.z = std::stof(line.substr(0, line.find(',')));
			tempVertex.Position = pos;
			tempVertex.Normal = nor;
			vertices.push_back(tempVertex);

		}
		in.close();
	}
	else
	{
		std::cout << "Failed to open file: " << path << std::endl;
	}
}

std::string ReadFiles::ReadFileString(const char* path)
{
	std::ifstream in;
	in.open(path);
	if (in.is_open())
	{
		std::stringstream buffer;
		buffer << in.rdbuf();
		std::string fileString = buffer.str();
		in.close();
		return fileString;
	}
	else
	{
		std::cout << "Failed to open file: " << path << std::endl;
		return "";
	}
}

void ReadFiles::ReadOBJ(const char* path, Mesh& inMesh)
{
	/*std::ifstream in;
	in.open(path);
	std::string line;
	std::string name;
	if (in.is_open())
	{
		std::cout << "-------------------------------" << std::endl;
		std::cout << "Starting to load model from: " << path << std::endl;
		while (!in.eof())
		{
			char firstChar;
			in >> firstChar;

			switch (firstChar)
			{
			case '#':
				std::getline(in, line);
				std::cout << line << std::endl;
				break;

			case 'v':
				float x, y, z, r, g, b;
				in >> x
				>> y
				>> z
				>> r
				>> g
				>> b;

				Vertex newVertex;
				newVertex.Position = glm::vec3(x, y, z);
				newVertex.Normal = glm::vec3(r, g, b);

				inMesh.vertices.push_back(newVertex);
				break;

			case 'f':
				unsigned int my0, my1, my2;
				in >> my0 >> my1 >> my2;
				inMesh.indices.emplace_back(my0-1,my1-1,my2-1);
				break;

			case 'o':
				std::getline(in, line);
				name = line;
				std::cout << "Name of Model: " << line << std::endl;
				inMesh.SetName(name);
				break;
			default:
				std::getline(in, line);
				break;
			}
		}
		in.close();
		std::cout << "Amount of Vertices: " << inMesh.vertices.size() << std::endl;
		std::cout << "Amount of Triangles: " << inMesh.indices.size() << std::endl;
	}*/
}
