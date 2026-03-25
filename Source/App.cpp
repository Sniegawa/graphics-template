#include "App.h"

#include <glad/glad.h>

#include <iostream>


#include "OpenGLObjects/VAO.h"
#include "OpenGLObjects/VBO.h"
#include "OpenGLObjects/EBO.h"
#include "OpenGLObjects/Shader.h"
#include "OpenGLObjects/Texture2D.h"
#include "ExampleObjects/CubeObject.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

App::App()
{
	m_WindowSize = glm::vec2(800, 600);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	m_Window = glfwCreateWindow(m_WindowSize.x, m_WindowSize.y, "LearnOpenGL", NULL, NULL);
	if (m_Window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return; // Make an exception or sth idc
	}

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return; // Make an exception or sth idc
	}

	glViewport(0, 0, m_WindowSize.x, m_WindowSize.y);

	glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);



}

App::~App()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void App::Run()
{
	float vertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f    // top left 
	};

	unsigned int indices[] = {  
		0, 1, 3,   
		1, 2, 3   
	};
	

	std::shared_ptr<Shader> CubeShader = std::make_shared<Shader>("Shaders/cube.vert", "Shaders/cube.frag");
	std::shared_ptr<Texture2D> CubeTexture = std::make_shared<Texture2D>("Textures/wall.jpg");

	CubeObject cube;

	cube.SetShader(CubeShader);
	cube.SetTexture(CubeTexture);

	cube.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	while (!glfwWindowShouldClose(m_Window))
	{
		glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cube.SetRotation({ (float)glfwGetTime() * - 5.0f, (float)glfwGetTime()*50, (float)glfwGetTime() * 15.0f });
		cube.Draw();

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}