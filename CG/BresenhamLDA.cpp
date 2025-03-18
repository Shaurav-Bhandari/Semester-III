#include <iostream>
#include <vector>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

void bresenhamAlgorithm(float startX, float startY, float endX, float endY, unsigned int &VAO, unsigned int &VBO)
{
	auto toOpenGlX = [](float x) { return (x / (SCR_WIDTH / 2.0f)) - 1.0f; };
	auto toOpenGlY = [](float y) { return (y / (SCR_HEIGHT / 2.0f)) - 1.0f; };

	int ix1 = static_cast<int>(startX), iy1 = static_cast<int>(startY);
	int ix2 = static_cast<int>(endX), iy2 = static_cast<int>(endY);

	int dx = abs(ix2 - ix1), dy = abs(iy2 - iy1);
	
	int sx = (ix1 < ix2) ? 1 : -1;
	int sy = (iy1 < iy2) ? 1 : -1;

	int err = dx - dy;

	std::vector<float> linePoints;

	int x = ix1, y = iy1;
	while (true)
	{
		linePoints.push_back(toOpenGlX(x));
		linePoints.push_back(toOpenGlY(y));
		linePoints.push_back(0.0f);
		if (x == ix1 && y == iy2)
		{
			break;
		}

		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
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
	if (!glfwInit())
	{
		std::cout << "GLFW initialization Failed." << std::endl;
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Bresenham Line Drawing Algorithm", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD initialization Failed." << std::endl;
		exit(-1);
	}

	unsigned int ShaderProgram = createShaderProgram();
	unsigned int VAO, VBO;

	bresenhamAlgorithm(100.0f, 150.0f, 800.0f, 300.0f, VAO, VBO);

	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(ShaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, VBO);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}