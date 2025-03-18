#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

// Screen dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Shader source code for drawing points
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    uniform mat4 projection;
    void main() {
        gl_Position = projection * vec4(aPos.x, aPos.y, 0.0, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    uniform vec3 circleColor;
    void main() {
        FragColor = vec4(circleColor, 1.0);
    }
)";

// Midpoint Circle Drawing Algorithm
void drawCircleMidpoint(std::vector<float>& vertices, float centerX, float centerY, float radius) {
    float x = radius;
    float y = 0;
    float decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0

    while (y <= x) {
        // Add 8-way symmetric points
        vertices.insert(vertices.end(), {
            centerX + x, centerY + y,
            centerX + x, centerY - y,
            centerX - x, centerY + y,
            centerX - x, centerY - y,
            centerX + y, centerY + x,
            centerX + y, centerY - x,
            centerX - y, centerY + x,
            centerX - y, centerY - x
            });

        y++;

        // Midpoint is inside or on the perimeter of the circle
        if (decisionOver2 <= 0) {
            decisionOver2 += 2 * y + 1;   // Change in decision criterion for y
        }
        // Midpoint is outside the perimeter
        else {
            x--;
            decisionOver2 += 2 * (y - x) + 1;
        }
    }
}

// Shader compilation utility function
unsigned int compileShader(unsigned int type, const char* source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Error checking
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "SHADER COMPILATION FAILED: " << infoLog << std::endl;
    }

    return shader;
}

int main() {
    // GLFW initialization
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Midpoint Circle Drawing", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Compile shaders
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // Create shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check program linking
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "SHADER PROGRAM LINKING FAILED: " << infoLog << std::endl;
    }

    // Delete shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Prepare circle vertices
    std::vector<float> circleVertices;
    drawCircleMidpoint(circleVertices, 0, 0, 300);  // Draw circle at (0,0) with radius 300

    // Vertex Buffer Object and Vertex Array Object
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO and VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(float), circleVertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Projection matrix (orthographic)
    glm::mat4 projection = glm::ortho(
        SCR_WIDTH / 2.0f, SCR_WIDTH / 2.0f,
        SCR_HEIGHT / 2.0f, SCR_HEIGHT / 2.0f,
        1.0f, 1.0f
    );

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use shader program
        glUseProgram(shaderProgram);

        // Set uniform color (white)
        int colorLoc = glGetUniformLocation(shaderProgram, "circleColor");
        glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f);

        // Set projection matrix
        int projLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Draw points
        glPointSize(2.0f);
        glDrawArrays(GL_POINTS, 0, circleVertices.size() / 2);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}