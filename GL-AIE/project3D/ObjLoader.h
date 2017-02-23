#pragma once
#include  "..\bootstrap\gl_core_4_4.h"
#include "tiny_obj_loader.h"
#include <vector>

struct OpenGLInfo { 
	unsigned int m_VAO; 
	unsigned int m_VBO; 
	unsigned int m_faceCount; 
};

struct OBJVertex
{
	float x, y, z;
	float nx, ny, nz;
	float u, v;
};

class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	std::vector<OpenGLInfo> CreateOpenGLBuffers(tinyobj::attrib_t &attribs, std::vector<tinyobj::shape_t>& shapes);

	void Render();

private:
	std::vector<OpenGLInfo> m_glInfo;
};

