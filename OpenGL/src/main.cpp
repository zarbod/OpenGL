#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

//graphics
#include "graphics/Shader.h"
#include "graphics/texture.h"
#include "graphics/models/cube.hpp"
#include "graphics/models/lamp.hpp"

//Input/Output
#include "io/Keyboard.h"
#include "io/Mouse.h"
#include "io/Joystick.h"

//screen class
#include "io/Screen.h"

// Camera
#include "io/Camera.h"

using namespace std;

void processInput(double dt);


float mixVal = 0.5f;

glm::mat4 mouseTransform = glm::mat4(1.0f);
Joystick mainJ(0);

unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600;

Screen screen;

float radians;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
	cout << "bruh" << endl;
	int success;
	char infoLog[512];

	glfwInit();

	// openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!screen.init()) {
		std::cout << "Could not create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialze GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	screen.setParameters();

	glEnable(GL_DEPTH_TEST);

	// Shaders
	Shader shader("assets/object.vs", "assets/object.fs");
	Shader lampShader("assets/object.vs", "assets/lamp.fs");

	vector<Cube> cubes;

	for (float i = 0.0f; i < 20; i++) {
		int dir;
		if ((int)i % 2 == 0)
			dir = 1;
		else
			dir = -1;

		Cube cube(glm::vec3(5*glm::cos(i)-0.5f, (5*glm::sin(i) * -1.0f) - 0.1f, (0.5f) - 0.7f), glm::vec3(0.75f), Material::white_plastic, true, dir);
		cube.init();
		cubes.push_back(cube);
	}

	Lamp lamp(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(-1.0f, -0.5f, -0.5f), glm::vec3(0.25f));
	lamp.init();

	Lamp lamp2(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f, -0.5f, -0.5f), glm::vec3(0.25f));
	lamp2.init();

	mainJ.update();
	if (mainJ.isPresent()) {
		std::cout << mainJ.getName() << " is present." << std::endl;
	}
	else {
		std::cout <<"Not present." << std::endl;
	}

	while (!screen.shouldClose()) {
		// process input 
		double currenttime = glfwGetTime();
		deltaTime = currenttime - lastFrame;
		lastFrame = currenttime;

		processInput(deltaTime);

		// render
		screen.update();

		shader.activate();
		shader.setFloat3("light.position", lamp.pos);
		shader.setFloat3("viewPos", camera.cameraPos);
		//shader.setFloat("mixVal", mixVal);

		shader.setFloat3("light.ambient", lamp.ambient);
		shader.setFloat3("light.diffuse", lamp.diffuse);
		shader.setFloat3("light.specular", lamp.specular);

	
		// create screen transform

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = camera.getViewMatrix();
		projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		for(Cube cube : cubes)
			cube.render(shader);
		
		lampShader.activate();
		lampShader.setMat4("view", view);
		lampShader.setMat4("projection", projection);
		lamp.render(lampShader);
		// send new frame to window
		screen.newFrame();
	}

	for (Cube cube : cubes)
		cube.cleanup();
	lamp.cleanup();

	glfwTerminate();
	return 0;
}

void processInput(double dt)
{	
	//cout << "input works" << endl;
	if (Keyboard::keyWentUp(GLFW_KEY_ESCAPE) || mainJ.buttonState(GLFW_JOYSTICK_BTN_RIGHT)) {
		cout << "test" << endl;
		screen.setShouldClose(true);
	}

	// change mix val
	//std::cout << mainJ.buttonState(GLFW_JOYSTICK_DPAD_UP) << std::endl;

	if (Keyboard::key(GLFW_KEY_UP) || mainJ.buttonState(GLFW_JOYSTICK_DPAD_UP)) {
		mixVal += 0.05f;
		if (mixVal > 1)
			mixVal = 1.0f;
	}
	if (Keyboard::key(GLFW_KEY_DOWN) || mainJ.buttonState(GLFW_JOYSTICK_DPAD_DOWN)) {
		mixVal -= 0.05f;
		if (mixVal < 1)
			mixVal = 0.0f;
	}
	if (Keyboard::key(GLFW_KEY_RIGHT) || mainJ.buttonState(GLFW_JOYSTICK_DPAD_RIGHT)) {
		mixVal = 0.5f;
	}

	// Keyboard Movement Input 

	if (Keyboard::key(GLFW_KEY_W)) {
		camera.updateCameraPos(CameraDirection::FORWARD, dt);
	}
	if (Keyboard::key(GLFW_KEY_S)) {
		camera.updateCameraPos(CameraDirection::BACKWARD, dt);
	}
	if (Keyboard::key(GLFW_KEY_A)) {
		camera.updateCameraPos(CameraDirection::LEFT, dt);
	}
	if (Keyboard::key(GLFW_KEY_D)) {
		camera.updateCameraPos(CameraDirection::RIGHT, dt);
	}
	if (Keyboard::key(GLFW_KEY_SPACE)) {
		camera.updateCameraPos(CameraDirection::UP, dt);
	}
	if (Keyboard::key(GLFW_KEY_LEFT_SHIFT)) {
		camera.updateCameraPos(CameraDirection::DOWN, dt);
	}

	// Mouse input

	double dx = Mouse::getDX() / 50.0, dy = Mouse::getDY() / 50.0f;
	if (dx != 0 || dy != 0) {
		camera.updateCameraDirection(dx, dy);
	}

	double scrollDy = Mouse::getScrollDY();
	if (scrollDy != 0) {
		camera.updateCameraZoom(scrollDy);
	}

	// Joystick Input

	mainJ.update();

	float lx = mainJ.axesState(GLFW_JOYSTICK_AXES_LEFT_STICK_X);
	float ly = -mainJ.axesState(GLFW_JOYSTICK_AXES_LEFT_STICK_Y);
	if (ly > 0.5f) {
		camera.updateCameraPos(CameraDirection::FORWARD, dt);
	}
	if (ly < -0.5f) {
		camera.updateCameraPos(CameraDirection::BACKWARD, dt);
	}
	if (lx > 0.5f) {
		camera.updateCameraPos(CameraDirection::RIGHT, dt);
	} 
	if (lx < -0.5) {
		camera.updateCameraPos(CameraDirection::LEFT, dt);
	}
	if (mainJ.buttonState(GLFW_JOYSTICK_BTN_DOWN)) {
		camera.updateCameraPos(CameraDirection::UP, dt);
	}
	if (mainJ.buttonState(GLFW_JOYSTICK_BTN_LEFT)) {
		camera.updateCameraPos(CameraDirection::DOWN, dt);
	}

	float rx = mainJ.axesState(GLFW_JOYSTICK_AXES_RIGHT_STICK_X);
	float ry = -mainJ.axesState(GLFW_JOYSTICK_AXES_RIGHT_STICK_Y);
	//std::cout << rx << ' ' << ry << std::endl;
	
	if(abs(ry) > 0.05f && abs(rx) > 0.05f)
		camera.updateCameraDirection(rx/20.0, ry/20.0);
	else if (abs(ry) > 0.05 && !abs(rx) > 0.05f)
		camera.updateCameraDirection(0, ry/20.0);
	else if (!abs(ry) > 0.05 && abs(rx) > 0.05f)
		camera.updateCameraDirection(rx/20.0, 0);
	
	float rt = mainJ.axesState(GLFW_JOYSTICK_AXES_RIGHT_TRIGGER);

	if (rt >= 0.05f) {
		camera.sprint = true;
	}
	else {
		camera.sprint = false;
	}
	float lt = mainJ.axesState(GLFW_JOYSTICK_AXES_LEFT_TRIGGER);
	//std::cout << rt << ' ' << lt << std::endl;
	if (lt > 0.0f) {
		camera.updateCameraZoom(-lt);
	}
}
