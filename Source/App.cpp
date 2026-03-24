#include "App.h"

#include <glad/glad.h>

#include <iostream>


#include "OpenGLObjects/VAO.h"
#include "OpenGLObjects/VBO.h"
#include "OpenGLObjects/EBO.h"
#include "OpenGLObjects/Shader.h"
#include "OpenGLObjects/Texture2D.h"


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

	Shader defaultShader("Shaders/simple.vert", "Shaders/simple.frag");

	VAO TriangleVAO;
	TriangleVAO.Bind();

	VBO TriangleVBO;
	TriangleVBO.Bind();

	EBO TriangleEBO;
	TriangleEBO.Bind();

	TriangleVBO.SetData(vertices, sizeof(vertices), GL_STATIC_DRAW);
	TriangleEBO.SetData(indices, sizeof(indices), GL_STATIC_DRAW);

	TriangleVAO.linkAttrib(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	TriangleVAO.linkAttrib(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	TriangleVAO.linkAttrib(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	TriangleVBO.Unbind();
	TriangleVAO.Unbind();

	Texture2D brick = Texture2D("Textures/wall.jpg");
	Texture2D face = Texture2D("Textures/awesomeface.png");

	defaultShader.Use();

	defaultShader.setInt("texture1", 0);
	defaultShader.setInt("texture2", 1);


	while (!glfwWindowShouldClose(m_Window))
	{
		glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		defaultShader.Use();
		TriangleVAO.Bind();
		brick.Bind(0);
		face.Bind(1);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		brick.Unbind();
		face.Unbind();
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}