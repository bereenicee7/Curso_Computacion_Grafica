/*
	Nombre:Domínguez Reyes Cynthia Berenice
	Práctica: Modelo Jerarquico
	Fecha de entrega 06 de septiembre de 2024 
*/

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"
void Inputs(GLFWwindow *window);
const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard (Controlar la vista)
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

// For model, genera la articulacion			
float hombro = 0.0f;
float codo = 0.0f;
float muneca = 0.0f;
float dedo1 = 0.0f; 
float dedo1b = 0.0f;
float dedo2 = 0.0F;	
float dedo2b = 0.0f; 
float pulgar = 0.0f;
float pulgarb = 0.0f; 




int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado jerárquico Cynthia Domínguez :D ", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);

	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	// use with Orthographic Projection

	// use with Perspective Projection
	// Usamos tres parametros (posicion)
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 
		0.5f, -0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		-0.5f,  0.5f, 0.5f, 
		-0.5f, -0.5f, 0.5f, 
		
	    -0.5f, -0.5f,-0.5f, 
		 0.5f, -0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
	    -0.5f,  0.5f,-0.5f, 
	    -0.5f, -0.5f,-0.5f, 
		
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,
      
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		
		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	// Aqui generamos nuestra proyeccion en perspectiva
	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color= glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Aqui dibujamos
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);			// Matriz del modelo
		glm::mat4 view=glm::mat4(1);			// Matriz para la vista
		glm::mat4 modelTemp = glm::mat4(1.0f);	// Controla la informacion de la posición de cada uno
		glm::mat4 modelTemp2 = glm::mat4(1.0f); 
		glm::mat4 modelTemp3 = glm::mat4(1.0f);


		//View set up 
		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		
		// Con esto controlamos el pivote
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	

		glBindVertexArray(VAO);
		
		
		// Bizep del brazo.
		model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f));	// Aplicamos rotacion en la componente Z
		modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));			// Nos sirve para geenerar sensacion de movimiento en articulacion del hombro, nos sirve de pivote
		// el 1.5 es porque movimos el pivote (mitad del tamaño de la caja)
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));							// Escalamos la caja 
		color = glm::vec3(0.0f, 1.0f, 0.0f);											// Aplicamos un color diferente para cada caja
		// Mandamos a dibujar
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));							//mandamos la variable del color 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);// A

		// Model Antebrazo
		model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0f));					// Se modifica la distancia del objeto bizep para dibujar el antebrazo 
		model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 1.0f, 0.0f));	//Se le pasa la variable del codo 
		modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));			// Para llegar al centro de la sig figura
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));							// Escalamos el objeto 	
		color = glm::vec3(1.0f, 0.0f, 0.0f);

		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); //B

		//Nota: Regresamos al valor de la matriz temporal para no inicializar nuevamente la matriz desde el origen
		//Ya solamente se toman los valores del objeto anterior 

	
		// Model Muñeca
		model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(muneca), glm::vec3(1.0f, 0.0f, 0.0f));		//Agregamos la nueva variable de la muñeca
		modelTemp3 = modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));	// Agregamos los dedos desde la mano 
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f); 

		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		
		// Model dedo1
		model = glm::translate(modelTemp, glm::vec3(0.25f, 0.35f, 0.375f));				//Movemos la distancia del objeto
		model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0f, 1.0f)); //Agregamos la nueva variable del dedo
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));						//Escalamos el objeto 
		color = glm::vec3(0.0f, 1.0f, 1.0f);

		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Model dedo1 pt2 
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));					//Movemos la distancia del objeto
		model = glm::rotate(model, glm::radians(dedo1b), glm::vec3(0.0f, 0.0f, 1.0f)); //Agregamos la nueva variable del dedo p2
		model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));						//Escalamos el objeto 
		color = glm::vec3(1.0f, 0.0f, 1.0f);

		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Model Dedo 2 
		model = glm::translate(modelTemp, glm::vec3(-0.5f, 0.01f, -0.375f));
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
	
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Model dedo2 pt2
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo1b), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
	
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Model dedo 3
		model = glm::translate(modelTemp, glm::vec3(-0.5f, 0.01f, -0.375f));
		model = glm::rotate(model, glm::radians(dedo2b), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
	
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Model dedo3 pt2
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo1b), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Model pulgar
		model = glm::translate(modelTemp3, glm::vec3(0.0f, -0.35f, -0.02f));
		model = glm::rotate(model, glm::radians(pulgar), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
	
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Model pulgar pt2
		model = glm::translate(modelTemp, glm::vec3(0.3f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pulgarb), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }


	// Para las entradas del teclado
 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.04f;
	 if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
		 movY += 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY -= 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.04f;
	 // ------------------------ Hombro --------------------------------
	 

	 if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) //con la letra R se va a mover el hombro 
	 {
		 if (90.0f > hombro) //Hacemos los limites del movimiento
			 hombro += 1.5f;
	 }

	 if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && -120.0f < hombro) //Otra forma de hacer los limites del movimiento
		 hombro -= 1.5f; //con la letra F se va a mover el hombro de lado contrario
		 
	 // ------------------------ Antebrazo --------------------------------
	
	 if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	 {
		 if (codo < 0.0f) // Límite de la rotación hacia adentro (90 grados)
			 codo += 1.5f;
	 }

	 // Rota el codo hacia afuera con la letra T
	 if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	 {
		 if (codo > -90.0f) // Límite de la rotación hacia afuera (-90 grados)
			 codo -= 1.5f;
	 }

	 // ------------------------ Muneca --------------------------------
	 if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		 muneca += 0.28f;
	 if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		 muneca -= 0.28f;



	 // ------------------------ Dedo 1 --------------------------------
	 if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) // Flexiona el dedo 1
	 {
		 if (dedo1 < 90.0f) // Límite de la flexión del dedo
			 dedo1 += 1.5f;
	 }
	 if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) // Extiende el dedo 1
	 {
		 if (dedo1 > 0.0f) // Límite de la extensión del dedo
			 dedo1 -= 1.5f;
	 }


	 // ------------------------ Dedo 1b --------------------------------
	 if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		 dedo1b += 0.28f;
	 if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		 dedo1b -= 0.28f;



	 // ------------------------ Pulgar --------------------------------
	 if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) // Flexiona el pulgar
	 {
		 if (pulgar < 90.0f) // Límite de la flexión del pulgar
			 pulgar += 1.5f;
	 }
	 if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) // Extiende el pulgar
	 {
		 if (pulgar > 0.0f) // Límite de la extensión del pulgar
			 pulgar -= 1.5f;
	 }



	 // ------------------------ Pulgar --------------------------------
	 if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) // Flexiona el pulgarb
	 {
		 if (pulgarb < 90.0f) // Límite de la flexión
			 pulgarb += 1.5f;
	 }
	 if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) // Extiende el pulgarb
	 {
		 if (pulgarb > 0.0f) // Límite de la extensión
			 pulgarb -= 1.5f;
	 }
 }


 
