#include <iostream>
#include <gl\glew.h>
#include <GLFW\glfw3.h>

using namespace std;

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
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        // clear the window with display color
        // can use this to set color for the window
        // glClearColor(r,g,b); the (r,g,b) is scale of 0 - 1.
        glClear(GL_COLOR_BUFFER_BIT);

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