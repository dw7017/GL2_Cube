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


// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
	"out vec4 colour;\n"
	"void main()\n"
	"{\n"
	"colour = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
	"}\n\0";


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

	// get version info
	const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString (GL_VERSION); // version as a string
	std::cout << "Renderer: " << renderer << std::endl;
	std::cout << "OpenGL version: " << version << std::endl;

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	std::cout << "Framebuffer width=" << width << ", height=" << height << std::endl;
	glViewport(0, 0, width, height);

	// Build and compile our shader program
	// Vertex shader
	GLint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertex_shader);
	// Check for compile time errors
	GLint success;
	GLchar log[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, log);
		std::cout << "ERROR: Vertex shader compilation failed\n" << log << std::endl;
	}
	// Fragment shader
	GLint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragment_shader);
	// Check for compile time errors
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, log);
		std::cout << "ERROR: Fragment shader compilation failed\n" << log << std::endl;
	}
	// Link shaders
	GLint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	// Check for linking errors
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, log);
		std::cout << "ERROR: Shader program linking failed\n" << log << std::endl;
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	// Create a Cube
	GLfloat vertices[] = {
		// Front face of cube
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	GLuint vertex_indices[] = {
		// Front face of cube
		0, 1, 3,
		1, 2, 3
	};
	GL2Cube* cube = new GL2Cube();

	// Create VBOs and IBOs
	GLuint vbo, ibo;
	// Depending on GL version you'd create a vertex array object here to
	// allow rebinding of the vertex-index buffer pair with less code
	//GLuint vao;
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);
	// Describe format of vertex array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// The VBO has been enabled to we can unbind it
	// DAN check if we can also unbind element array buffer
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Game loop
	while (!glfwWindowShouldClose(window)) {
		// Check for events like key press, mouse moved, etc.
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		// Rebind VBO/IBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap the screen buffers
		glfwSwapBuffers(window);

	}

	// Delete buffer objects
	//glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}
