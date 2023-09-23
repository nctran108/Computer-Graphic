#include <iostream>
#include <gl\glew.h>
#include <GLFW\glfw3.h>

using namespace std;

GLuint VAO, VBO, shader;

// Vertex Shader
static const char* vshader = "                                   \n\
#version 330                                                     \n\
                                                                 \n\
layout (location = 0) in vec3 pos;                               \n\
                                                                 \n\
void main()                                                      \n\
{                                                                \n\
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);    \n\
}";

// Fragment shader
static const char* fshader = "                                   \n\
#version 330                                                     \n\
                                                                 \n\
out vec4 colour;                                                 \n\
                                                                 \n\
void main()                                                      \n\
{                                                                \n\
    colour = vec4(1.0, 0.0, 0.0, 1.0);    \n\
}";

void CreateTriangle() {
    GLfloat vertices[] = {
        -1.0f, -1.0, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // unbind vertex array
    glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        cout << "[ERROR][COMPILE]: " << eLog << endl;
        return;
    }

    glAttachShader(theProgram, theShader);
}

void CompileShaders() {
    shader = glCreateProgram();

    if (!shader) {
        cout << "[ERROR][glCreateProgram] fail to create shader" << endl;
        return;
    }

    AddShader(shader, vshader, GL_VERTEX_SHADER);

    AddShader(shader, fshader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        cout << "[ERROR][LINK]: " << eLog << endl;
        return;
    }

    glValidateProgram(shader);

    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        cout << "[ERROR][VALIDATE]: " << eLog << endl;
        return;
    }
}

int main(int argc, char** argv) {
    cout << "Hello" << endl;

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        cout << "[ERROR][GLFW] fail to init!" << endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Setup GLFW window properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // core profile = no backwards compatobility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        cout << "[ERROR]{GLFW] Fail to create window" << endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // get Buffer size info
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

    /* Make the window's context current */
    // if have multiple window, can switch windows between context
    glfwMakeContextCurrent(window);

    // allow modern extension features
    // access the extention to make alot of thing easier by set it to true
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        cout << "[ERROR][GLEW] glew init fail!" << endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    CreateTriangle();
    CompileShaders();
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        // clear the window with display color
        // can use this to set color for the window
        // glClearColor(r,g,b); the (r,g,b) is scale of 0 - 1.
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);

        /* Swap front and back buffers */
        // swap a new scene to the old scene
        glfwSwapBuffers(window);

        /* Poll for and process events */
        // get and handle user input events
        glfwPollEvents();
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}