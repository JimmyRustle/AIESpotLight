#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "gl_core_4_4.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Texture.h"
#include <vector>
#include "..\project3D\ObjLoader.h"
#include "Input.h"

using glm::mat4;
using glm::vec4;
using glm::vec3;
using glm::vec2;
using aie::MyTexture;

struct Vertex
{
	vec4 position;
	vec2 texCoord;
};

class Mesh
{
public:
	Mesh(const char* filename);
	~Mesh();

	void GenerateGrid(int rows, int columns);

	void LoadAndAttachShaders(const char* vsFilename, const char* fsFilename);

	void Draw(mat4 projectionView, mat4 cameraWorld);

	void Draw(mat4 projectionView, float t, float height);

private:
	std::string LoadShader(const char* filename);

	int m_rows;
	int m_columns;

	vec3 lightPosition;

	MyTexture*	m_texture;
	aie::Texture* m_tex;
	unsigned int	m_VAO;
	unsigned int	m_VBO;
	unsigned int	m_IBO;
	//resulting ID of compiled shader
	unsigned int m_programID;
	std::vector<OpenGLInfo> m_glInfo;


};

