#include "Application3D.h"
#include "Gizmos.h"
#include "Input.h"
#include "MyTexture.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;
using aie::Input;

float vertexData[] =
{
	-5,0,5,1,0,1,
	5,0,5,1,1,1,
	5,0,-5,1,1,0,
	-5,0,-5,1,0,0
};

unsigned int indexData[] =
{
	0,1,2,
	0,2,3
};

Application3D::Application3D() {

	flyCamera = new FlyCamera(m_window, 10, 2.0f);

	//mesh = new Mesh("../Textures/Earth Textures/earth_cloud.jpg");
	rows = 100;
	columns = 100;
	
}

Application3D::~Application3D() {

}

bool Application3D::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);
	// initialise gizmo primitive counts
	Gizmos::create(10000,
		10000, 10000, 10000);
	
	float previousTime = 0;
	float currentTime = (float)glfwGetTime();
	float deltaTime = currentTime - previousTime;
	previousTime = currentTime;
	
	objLoader = new ObjLoader();

	flyCamera->SetLookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	flyCamera->SetPerspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);
	mesh = new Mesh("../Models/soulspear/soulspear/soulspear_diffuse.tga");
	//mesh->LoadAndAttachShaders("vsSourceTexture.vs", "fsSourceTexture.frag");
	//mesh->GenerateGrid(rows, columns);

	return true;
}

void Application3D::shutdown() {

	delete flyCamera;
	delete mesh;
	delete objLoader;

	Gizmos::destroy();
}

void Application3D::update(float deltaTime) {

	// query time since application started
	float time = getTime();

	flyCamera->Update(m_window, deltaTime);

	// wipe the gizmos clean for this frame
	Gizmos::clear();
	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);

	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));
	
	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application3D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	float currentTime = getTime();

	mesh->Draw(flyCamera->GetProjectionView(), flyCamera->GetWorldTransform());

	Gizmos::draw(flyCamera->GetProjectionView());
}