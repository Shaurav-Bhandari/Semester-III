#include <iostream>
#include <glad/glad.h>
#include <gl/GL.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector> 

using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = R"(
   #version 330 core
   layout (location = 0) in vec3 aPos;
   void main() {
       gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   }
)";

const char* fragmentShaderSource = R"(
	#version 330 core
	out vec4 FragColor;
	void main() {
		FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	}
)";

void DrawLine(float startX, float startY, float endX, float endY, unsigned int& VBO, unsigned int& VAO)
{
	float dx = endX - startX, dy = endY - startY;
	int steps = max(abs(static_cast<int>(dx)), abs(static_cast<int>(dy)));
	float x_inc = dx / static_cast<float>(steps);
	float y_inc = dy / static_cast<float>(steps);
	float x = startX, y = startY;
	vector<float> linePoints;

	// Ensure we only generate points along the line
	for (int i = 0; i <= steps; i++)
	{
		// Normalize coordinates to OpenGL's coordinate system (-1 to 1)
		linePoints.push_back((x / (SCR_WIDTH / 2.0f)) - 1.0f);
		linePoints.push_back((y / (SCR_HEIGHT / 2.0f)) - 1.0f);
		linePoints.push_back(0.0f);

		x += x_inc;
		y += y_inc;
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, linePoints.size() * sizeof(float), linePoints.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

unsigned int createShaderProgram()
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}

void frameBuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	glfwInit();
	if (!glfwInit())
	{
		cout << "GLFW failed to initialize" << endl;
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "DDA Line Drawing Algorithm", NULL, NULL);
	if (!window)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "GLAD initialization Failed" << endl;
		exit(-1);
	}

	unsigned int ShaderProgram = createShaderProgram();
	unsigned int VBO, VAO;
	DrawLine(100, 100, 700, 500, VBO, VAO);

	while (!glfwWindowShouldClose(window))
	{
		// Input
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw line
		glUseProgram(ShaderProgram);
		glBindVertexArray(VAO);
		GLint bufferSize;
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
		glDrawArrays(GL_LINE_STRIP, 0, bufferSize / (3 * sizeof(float)));

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(ShaderProgram);

	glfwTerminate();
	return 0;
}