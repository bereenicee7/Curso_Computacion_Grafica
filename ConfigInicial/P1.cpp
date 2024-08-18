/*
	Práctica 1 Dibujo de primitivas
	Cynthia Berenice Domínguez Reyes
	Fecha de entrega: 

*/


#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		0.5f,  0.5f, 0.0f,    1.0f,0.0f,0.0f,  // top right 0
		0.5f, -0.5f, 0.0f,    1.0f,1.0f,0.0f,  // bottom right 1
		-0.5f, -0.5f, 0.0f,   1.0f,0.0f,1.0f,  // bottom left 2
		-0.5f,  0.5f, 0.0f,   1.0f,1.0f,0.0f, // top left 3

	//Figura perrito
	//	X    Y		Z		 R		G	 B      Vertice
	-0.93f, 0.44f, 0.0f,	0.545f, 0.353f, 0.149f,	//A 4
	-0.27f, 0.90f,  0.0f,	0.545f, 0.353f, 0.149f,	//B 5
	-0.72f, -0.25f, 0.0f,	0.545f, 0.353f, 0.149f,	//C 6
	-0.61f, 0.07f, 0.0f,	0.82f, 0.41f, 0.12f,	//D 7
	-0.36f, -0.21f, 0.0f,	0.82f, 0.41f, 0.12f,	//E 8
	-0.0f, 0.2f, 0.0f,		0.76f, 0.60f, 0.42f,	//F 9
	 0.0f, 0.90f, 0.0f,		0.96f, 0.94f, 0.90f,	//G 10
	 0.28f, 0.90f, 0.0f,	0.545f, 0.353f, 0.149f,	//H 11
	 0.39f, -0.23f, 0.0f,	0.82f, 0.41f, 0.12f,	//I 12
	 0.65f, 0.04f, 0.0f,	0.82f, 0.41f, 0.12f,	//J 13
	 0.75f, -0.24f, 0.0f,	0.545f, 0.353f, 0.149f,	//K 14
	 0.95f, 0.43f, 0.0f,	0.545f, 0.353f, 0.149f,	//L 15
	 
	 //Ojos perrito
	-0.30f, 0.49f, 0.0f,	1.0f, 1.0f, 1.0f, // C 16
	-0.25f, 0.49f, 0.0f,	1.0f, 1.0f, 1.0f, // D 17
	-0.30f, 0.34f, 0.0f,	1.0f, 1.0f, 1.0f, // E 18 
	-0.25f, 0.34f, 0.0f,	1.0f, 1.0f, 1.0f, // F 19
	


	};
	unsigned int indices[] = {  // note that we start from 0!
		//3,2,1,// second Triangle
		//0,1,3,
		4, 5, 6,	// ABC
		5, 7, 8,	//BDE
		5, 8, 9,	//BEF
		5, 9, 10,	//BFG
		9, 10, 11,	//FGH
		9, 11, 12,	//FHI
		11, 12, 13,	//HIJ
		11, 14, 15, //HKL
		8, 9, 12, //EFI

	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


        //glPointSize(1);
        //glDrawArrays(GL_POINTS,0,1);
        
        //glDrawArrays(GL_LINES,0,2);
        //glDrawArrays(GL_LINE_LOOP,0,4);
        
       //glDrawArrays(GL_TRIANGLES,4, 3); //desde donde empieza y cuantos se necesitan 

        glDrawElements(GL_TRIANGLES, 27,GL_UNSIGNED_INT,0);

		//Ojos
		glDrawArrays(GL_POLYGON, 16, 4);



        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}