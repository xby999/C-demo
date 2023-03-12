/*
* Author: binyxia
* Note: Using different way to draw a triangle
* Reference: https://docs.gl/
*/


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	if (glewInit() != GLEW_OK)
		std::cout << "error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	/*
	* binyxia: Generally OpenGL is a state machine, so when OpenGL draw graph, it actually knows already what is need to  
	*          draw the graph. Because it is a part of the state.
	*          So you just need select the buffer and shader, then OpenGL will draw graph.
	*/
	float positions[6] = { // This is a float array buffer
		-1.0f, -0.5f,
		0.0f,   0.5f,
		0.5f,  -0.5f
	};
	unsigned int buffer;
	glGenBuffers(1, &buffer); //Generate a buffer object
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6,positions,GL_STATIC_DRAW);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);//As described above about State Machine.
										 //OpenGL bind buffer in line 49, and this is you selectede buffer.
										 //Then in line 59 OpenGL draw triangle based on selected buffer.

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}