
/*
		Práctica 6: Texturizado
		Nombre: Domínguez Reyes Cynthia Berenice
		Fecha de entrega: 27 de septiembre de 2024

*/

#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"
#include "Camera.h"


// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

// Light attributes
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

							// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Texturizado. Cynthia D. :D ", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);


	// Build and compile our shader program
	//incorparación de shaders y fragmentos 
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");




	// Set up vertex data (and buffer(s)) and attribute pointers

	//Posicion y color de los vertices que van a conformar nuestro plano
	GLfloat vertices[] =
	{
		// Positions            // Colors              // Texture Coords //Coordenada de textura que tienen los vertices 
							//	R	   G	  B		   // U   V	
		//Cara	Frontal 																		Vertices			Indices 
		-0.5f, -0.5f, 0.0f,    1.0f, 1.0f,	1.0f,		0.25f,0.33f, //derecho				//V0				//0
		0.5f, -0.5f, 0.0f,	   1.0f, 1.0f,	1.0f,		0.5f,0.33f,							//V1				//1
		0.5f,  0.5f, 0.0f,     1.0f, 1.0f,	1.0f,	    0.5f,0.66f,							//V2				//2
		-0.5f,  0.5f, 0.0f,    1.0f, 1.0f,	1.0f,		0.25f,0.66f, // izquierdo			//V3				//3

		//Cara Trasera
		
		-0.5f, -0.5f, -1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  0.33f,								// V4				//4
		0.5f, -0.5f, -1.0f,  0.0f, 1.0f, 1.0f,   0.75f, 0.33f,								// V5				//5
		0.5f,  0.5f, -1.0f,  1.0f, 1.0f, 1.0f,  0.75f, 0.66f,								// V7				//6
		-0.5f,  0.5f, -1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  0.66f,								// V6				//7

		//Cara Derecha

		0.5f, -0.5f, 0.0f,		 1.0f, 1.0f,	1.0f,			0.5f,0.33f,					//V1				//8																		
		0.5f,  0.5f, 0.0f,		1.0f, 1.0f,	1.0f,			0.5f, 0.66f,					//V2				//9
		0.5f,  0.5f, -1.0f,	1.0f, 1.0f,	1.0f,		0.75f, 0.66f,							//V7				//10
		0.5f, -0.5f, -1.0f,		1.0f, 1.0f,	1.0f,			0.75f, 0.33f,					//V5				//11

		//Cara izquierda
		-0.5f, -0.5f, 0.0f,    1.0f, 1.0f,	1.0f,		0.25f,0.33f, 						//V0				//12
		-0.5f,  0.5f, 0.0f,    1.0f, 1.0f,	1.0f,		0.25f,0.66f, 						//V3				//13
		-0.5f, -0.5f, -1.0f,  1.0f, 1.0f, 1.0f,			0.0f,  0.33f,						// V4				//14
		-0.5f,  0.5f, -1.0f,  1.0f, 1.0f, 1.0f,			0.0f,  0.66f,						// V6				//15
			
		

		//Cara superior
		0.5f,  0.5f, 0.0f,     1.0f, 1.0f,	1.0f,	    0.5f,0.66f,							//V2				//16
		-0.5f,  0.5f, 0.0f,    1.0f, 1.0f,	1.0f,		0.25f,0.66f, 						//V3				//17
		-0.5f,  0.5f, -1.0f,  1.0f, 1.0f, 1.0f,			0.25f,  1.0f,						// V6				//18
		0.5f,  0.5f, -1.0f,  1.0f, 1.0f, 1.0f,			 0.5f, 1.0f,						// V7				//19

		//Cara inferior
		-0.5f, -0.5f, 0.0f,    1.0f, 1.0f,	1.0f,		0.25f,0.33f, 						//V0				//20
		0.5f, -0.5f, 0.0f,	   1.0f, 1.0f,	1.0f,		0.5f,0.33f,							//V1				//21
		-0.5f, -0.5f, -1.0f,  1.0f, 1.0f, 1.0f,			0.25f,  0.0f,						// V4				//22
		 0.5f, -0.5f, -1.0f,  0.0f, 1.0f, 1.0f,			0.5f, 0.0f,							// V5				//23
	};

	//Indices que implementan el plano 
	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,3,
		1,2,3,
		//Trasera
		 4, 5, 6,   
		4, 7, 6,   
		//derecha
		8, 9, 10,   
		8,10,11,    

		//izquierda
		12, 13, 14,
		14, 13, 15,

		//superior
		16, 17, 19,
		17, 18, 19,

		//inferior 

		20, 21, 22,
		21, 22, 23,
	
	};

	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Texture Coordinate attribute //Buffer donde se manda la información con los ajustes y la información correspondientes (se mandan los indices)
	//(,dimensión del plano, tipo de dato, falso, numero de bits de los atributos, apuntador desplzamiento de los atirbutos) 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0); //inicializa la información en el arreglo 

	// Load textures. Carga de texturas

	GLuint texture1; //genaramos un identificador. 
	glGenTextures(1, &texture1); //lo amndamos a llamar 
	glBindTexture(GL_TEXTURE_2D,texture1); //enlazamos el tipo de textura con el elemento. 
	int textureWidth, textureHeight,nrChannels;
	stbi_set_flip_vertically_on_load(true); 
	unsigned char *image; //funcion que nos ayuda a volteral la coordenada para que aparezca el 0,0 en la parte inferior izquierda 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);


	// Diffuse map
	image = stbi_load("images/dado.jpg", &textureWidth, &textureHeight, &nrChannels,0); //ruta de la textura con su nombre correspondiente. 
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);

	

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lampShader.Use(); //Mandamos a llamar al shader 
		//// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 model(1);

		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lampShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lampShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		// Draw the light object (using light's vertex attributes) DIbujamos nuestros elementos 
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); //agregar el numero de indices que vamos agregando 
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}