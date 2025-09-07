//práctica 3: Modelado Geométrico y Cámara Sintética.
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include <gtc\random.hpp>
//clases para dar orden y limpieza al còdigo
#include"Mesh.h"
#include"Shader.h"
#include"Sphere.h"
#include"Window.h"
#include"Camera.h"
//tecla E: Rotar sobre el eje X
//tecla R: Rotar sobre el eje Y
//tecla T: Rotar sobre el eje Z


using std::vector;

//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
const float PI = 3.14159265f;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;
Camera camera;
Window mainWindow;
vector<Mesh*> meshList;
vector<Shader>shaderList;
vector<MeshColor*> meshListColor;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
Sphere sp = Sphere(1.0, 20, 20); //recibe radio, slices, stacks

 // Pirámide triangular regular
void CrearPiramideTriangular()
{
	GLfloat v[] = {
		// Base (gris)  y = -0.5
		-0.5f, -0.5f,  0.2887f,   0.6f, 0.6f, 0.6f,
		 0.5f, -0.5f,  0.2887f,   0.6f, 0.6f, 0.6f,
		 0.0f, -0.5f, -0.5774f,   0.6f, 0.6f, 0.6f,

		 // Cara 1 (rojo): V0, V1, V3
		 -0.5f, -0.5f,  0.2887f,   1.0f, 0.0f, 0.0f,
		  0.5f, -0.5f,  0.2887f,   1.0f, 0.0f, 0.0f,
		  0.0f,  0.5f,  0.0f,      1.0f, 0.0f, 0.0f,

		  // Cara 2 (verde): V1, V2, V3
		   0.5f, -0.5f,  0.2887f,   0.0f, 1.0f, 0.0f,
		   0.0f, -0.5f, -0.5774f,   0.0f, 1.0f, 0.0f,
		   0.0f,  0.5f,  0.0f,      0.0f, 1.0f, 0.0f,

		   // Cara 3 (azul): V2, V0, V3
			0.0f, -0.5f, -0.5774f,   0.0f, 0.0f, 1.0f,
		   -0.5f, -0.5f,  0.2887f,   0.0f, 0.0f, 1.0f,
			0.0f,  0.5f,  0.0f,      0.0f, 0.0f, 1.0f
	};



	MeshColor* obj = new MeshColor();
	obj->CreateMeshColor(v, 12 * 6);
	meshListColor.push_back(obj);

	GLfloat v2[] = {
		// Base (blanco)
		-0.5f, -0.5f,  0.2887f,   1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.2887f,   1.0f, 1.0f, 1.0f,
		 0.0f, -0.5f, -0.5774f,   1.0f, 1.0f, 1.0f,

		 // Cara 1 (blanco)
		 -0.5f, -0.5f,  0.2887f,   1.0f, 1.0f, 1.0f,
		  0.5f, -0.5f,  0.2887f,   1.0f, 1.0f, 1.0f,
		  0.0f,  0.5f,  0.0f,      1.0f, 1.0f, 1.0f,

		  // Cara 2 (blanco)
		   0.5f, -0.5f,  0.2887f,   1.0f, 1.0f, 1.0f,
		   0.0f, -0.5f, -0.5774f,   1.0f, 1.0f, 1.0f,
		   0.0f,  0.5f,  0.0f,      1.0f, 1.0f, 1.0f,

		   // Cara 3 (blanco)
			0.0f, -0.5f, -0.5774f,   1.0f, 1.0f, 1.0f,
		   -0.5f, -0.5f,  0.2887f,   1.0f, 1.0f, 1.0f,
			0.0f,  0.5f,  0.0f,      1.0f, 1.0f, 1.0f
	};




	MeshColor* obj2 = new MeshColor();
	obj2->CreateMeshColor(v2, 12 * 6);
	meshListColor.push_back(obj2);

}



void CreateShaders()
{

	Shader* shader2 = new Shader();
	shader2->CreateFromFiles(vShaderColor, fShader);
	shaderList.push_back(*shader2);
}


int main()
{
	mainWindow = Window(1366, 768);
	mainWindow.Initialise();
	//Cilindro y cono reciben resolución (slices, rebanadas) y Radio de circunferencia de la base y tapa
	CrearPiramideTriangular();//índice 1 en MeshList
	CreateShaders();


	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.3f);


	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(-1, 1, -1, 1, 1, 10);

	//Loop mientras no se cierra la ventana
	sp.init(); //inicializar esfera
	sp.load();//enviar la esfera al shader

	glm::mat4 model(1.0);//Inicializar matriz de Modelo 4x4

	//glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f); //inicializar Color para enviar a variable Uniform;

	while (!mainWindow.getShouldClose())
	{

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		//Recibir eventos del usuario
		glfwPollEvents();
		//Cámara
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//-----------------PIRÁMIDE 1------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshListColor[0]->RenderMeshColor();

		//-----------------PIRÁMIDE 2------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, -1.0f, -6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshListColor[0]->RenderMeshColor();

		//-----------------PIRÁMIDE 3------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.0f, -1.0f, -6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshListColor[0]->RenderMeshColor();

		//-----------------PIRÁMIDE 4------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.5f, 0.0f, -6.2887f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshListColor[0]->RenderMeshColor();

		//-----------------PIRÁMIDE 5------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.5f, 0.0f, -6.2887f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshListColor[0]->RenderMeshColor();

		//-----------------PIRÁMIDE 6------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -6.5774f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshListColor[0]->RenderMeshColor();

		//-----------------PIRÁMIDE 7------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.5f, -1.0f, -6.8661f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshListColor[0]->RenderMeshColor();

		//-----------------PIRÁMIDE 8------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -7.7322f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshListColor[0]->RenderMeshColor();

		//-----------------PIRÁMIDE 9------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.5f, -1.0f, -6.8661f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshListColor[0]->RenderMeshColor();

		//-----------------PIRÁMIDE 10------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.0f, 0.0f, -7.1548f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshListColor[0]->RenderMeshColor();

		//-----------------PIRÁMIDE 11------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.5f, -1.05f, -5.9f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 0, 1));
		model = glm::rotate(model, glm::radians(27.0f), glm::vec3(1, 0, 0));
		model = glm::scale(model, glm::vec3(0.8f, 0.9f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshListColor[0]->RenderMeshColor();

		//-----------------PIRÁMIDE 12------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.5f, -1.05f, -5.9f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 0, 1));
		model = glm::rotate(model, glm::radians(27.0f), glm::vec3(1, 0, 0));
		model = glm::scale(model, glm::vec3(0.8f, 0.9f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshListColor[0]->RenderMeshColor();

		//-----------------PIRÁMIDE 13------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -6.1887f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 0, 1));
		model = glm::rotate(model, glm::radians(27.0f), glm::vec3(1, 0, 0));
		model = glm::scale(model, glm::vec3(0.8f, 0.9f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshListColor[0]->RenderMeshColor();

		//-----------------PIRÁMIDE Blanca------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.0f, 0.0f, -6.5774f));
		model = glm::scale(model, glm::vec3(2.9f, 2.9f, 2.9f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshListColor[1]->RenderMeshColor();


		glUseProgram(0);
		mainWindow.swapBuffers();


	}
	return 0;
}