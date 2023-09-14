#include <stdio.h>
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>
#include "util.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

float quad[] = {
	0.0,0.0,1.0,0.0,0.0,
	0.0,0.5,0.0,1.0,0.0,
	0.5,0.0,0.0,0.0,1.0
};
void updateUI()
{
	bool imguiactive = true;
	ImGui::NewFrame();
	ImGui::Begin("information", &imguiactive, ImGuiWindowFlags_MenuBar);
	ImGui::SetWindowPos(ImVec2(2, 2));
	ImGui::SetWindowSize(ImVec2(400, 200));
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* renderer = glGetString(GL_RENDER);
	const GLubyte* version = glGetString(GL_VERSION);
	ImGui::Text("vendor:%s,renderer:%s,version:%s", vendor, renderer,version);
	ImGui::End();
	ImGui::Render();
}
int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}




	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * 5, quad, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);




	Shader shader("test.vert", "test.frag");
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();


	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	while (!glfwWindowShouldClose(window))
	{

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		updateUI();
		processInput(window);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
