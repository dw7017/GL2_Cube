#include <iostream>

// GLEW - Cross-platform GL wrapper
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW - Cross-platform Winsys library
#include <GLFW/glfw3.h>

class GL2Cube {

public:
	GL2Cube();
	~GL2Cube();
};

GL2Cube::GL2Cube() {
}

GL2Cube::~GL2Cube() {
}


// Is called whenever a key is pressed/released via GLFW
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}


// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;


int main(int argc, char* argv[]) {

	std::cout << "Starting GLFW" << std::endl;
	// Init GLFW
	glfwInit();
    // Set required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GL2_Cube", nullptr, nullptr);
	glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, glfwKeyCallback);

	// Init GLEW
    // Set this to true so GLEW uses a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
	glewInit();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

	// Create a Cube
	GL2Cube* cube = new GL2Cube();

	// Game loop
	while (!glfwWindowShouldClose(window)) {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();


	}

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}
