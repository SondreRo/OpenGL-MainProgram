#pragma once
#include <string>
#include "Vertex.h"
#include "triangle.h"
#include <vector>

#include "Line.h"
#include "Mesh.h"
class ReadFiles
{
public:
	static std::vector<Vertex>  ReadFileVertexData(const char* path);
	static void ReadFileVertexData(const char* path, Line& inLine);

	static std::string ReadFileString(const char* path);
	static void ReadOBJ(const char* path, Mesh& inMesh);
};