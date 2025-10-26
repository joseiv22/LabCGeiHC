/*
Práctica 7: Iluminación 1 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;

Texture lampTexture;
Texture cableTexture;
Texture contornofocoTexture;

Texture octaTexture;

Texture llantaTexture;
Texture cofreTexture;
Texture ojosTexture;
Texture rinTexture;
Texture Prop_Gun1;
Texture equipment;
Texture normalMap;

Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;
Model lamp;


Model carrsincofre;
Model cofre;
Model llantaderfrenobj;
Model llantaizqfrenobj;
Model llantaizqatrasobj;
Model llantaderatrasobj;
Model armazzz;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};
	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 64, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}
void CrearOctaedro()
{
    unsigned int octaedro_indices[] = {
        // 8 triángulos
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10,11,
        12,13,14,
        15,16,17,
        18,19,20,
        21,22,23
    };

    GLfloat octaedro_vertices[] = {
        // Cara 1
        // Izq
		//x,y,z			u	  v			nx	  ny    nz
        -0.5f, 0.0f,  0.5f,  0.04f, 0.38f,    0.0f, 0.0f,  -1.0f,
        // Der
         0.5f, 0.0f,  0.5f,  0.04f, 0.05f,    0.0f,  0.0f,  -1.0f,
        // Altura
         0.0f, 0.75f, 0.0f,  0.333f, 0.21f,   0.0f,  0.0f,  -1.0f,

        // Cara 2
         0.5f, 0.0f,  0.5f,  0.33f, 0.58f,    -1.0f,  0.0f,  0.0f,
         0.5f, 0.0f, -0.5f,  0.04f, 0.41f,    -1.0f,  0.0f,  0.0f,
         0.0f, 0.75f, 0.0f,  0.33f, 0.22f,    -1.0f,  0.0f,  0.0f,

        // Cara 3
         0.5f, 0.0f, -0.5f,  0.65f, 0.4f,     0.0f,  0.0f,  1.0f,
        -0.5f, 0.0f, -0.5f,  0.34f, 0.58f,    0.0f,  0.0f,  1.0f,
         0.0f, 0.75f, 0.0f,  0.34f, 0.22f,    0.0f,  0.0f,  1.0f,

        // Cara 4
        -0.5f, 0.0f, -0.5f,  0.65f, 0.05f,   1.0f,  0.0f, 0.0f,
        -0.5f, 0.0f,  0.5f,  0.65f, 0.38f,   1.0f,  0.0f, 0.0f,
         0.0f, 0.75f, 0.0f,  0.34f, 0.21f,   1.0f,  0.0f, 0.0f,

        // Cara 5 (abajo)
         0.5f, 0.0f,  0.5f,  0.34f, 0.97f,    0.0f, 0.0f,  -1.0f,
        -0.5f, 0.0f,  0.5f,  0.34f, 0.61f,    0.0f, 0.0f,  -1.0f,
         0.0f, -0.75f, 0.0f, 0.66f, 0.79f,    0.0f, 0.0f,  -1.0f,
         
        // Cara 6
         0.5f, 0.0f, -0.5f,  0.36f, 0.605f,   -1.0f, 0.0f,  0.0f,
         0.5f, 0.0f,  0.5f,  0.66f, 0.41f,    -1.0f, 0.0f,  0.0f,
         0.0f, -0.75f, 0.0f, 0.66f, 0.78f,    -1.0f, 0.0f,  0.0f,

        // Cara 7
        -0.5f, 0.0f, -0.5f,  0.7f,  0.44f,    0.0f, 0.0f, 1.0f,
         0.5f, 0.0f, -0.5f,  0.97f, 0.59f,    0.0f, 0.0f, 1.0f,
         0.0f, -0.75f, 0.0f, 0.7f,  0.76f,    0.0f, 0.0f, 1.0f,

        // Cara 8
        -0.5f, 0.0f,  0.5f,  0.97f, 0.63f,   1.0f, 0.0f,  0.0f,
        -0.5f, 0.0f, -0.5f,  0.97f, 0.95f,   1.0f, 0.0f,  0.0f,
         0.0f, -0.75f, 0.0f, 0.7f,  0.8f,    1.0f, 0.0f,  0.0f,
    };

    Mesh* octaedro = new Mesh();
    octaedro->CreateMesh(
        octaedro_vertices,
        octaedro_indices,
        sizeof(octaedro_vertices),
        sizeof(octaedro_indices) / sizeof(unsigned int)
    );
    meshList.push_back(octaedro);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearOctaedro();
	CreateShaders();
	
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();

	//Lampara
	lampTexture = Texture("Textures/foco.tga");
	lampTexture.LoadTextureA();
	contornofocoTexture = Texture("Textures/contorno_foco.tga");
	contornofocoTexture.LoadTextureA();
	cableTexture = Texture("Textures/cable.tga");
	cableTexture.LoadTextureA();
	
	
	octaTexture = Texture("Textures/octa.tga");
	octaTexture.LoadTextureA();

	llantaTexture = Texture("Textures/llantas.tga");
	llantaTexture.LoadTextureA();
	cofreTexture = Texture("Textures/escudo_fi_color.tga");
	cofreTexture.LoadTextureA();
	ojosTexture = Texture("Textures/carro_black.tga");
	ojosTexture.LoadTextureA();
	rinTexture = Texture("Textures/rojo_metalico.tga");
	rinTexture.LoadTextureA();


	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");

	lamp = Model();
	lamp.LoadModel("Models/foco.obj");
	// Arma de zzz
	armazzz = Model();
	armazzz.LoadModel("Models/arma2.obj");
	equipment = Texture("Textures/equipment.png");
	equipment.LoadTextureA();
	Prop_Gun1 = Texture("Textures/Prop_Gun1.png");
	Prop_Gun1.LoadTextureA();
	normalMap = Texture("Textures/normal.png");
	normalMap.LoadTextureA();

	//----------------------------------------------------------
	carrsincofre = Model();
	carrsincofre.LoadModel("Models/carrsincofre.obj");
	cofre = Model();
	cofre.LoadModel("Models/cofre.obj");
	llantaderfrenobj = Model();
	llantaderfrenobj.LoadModel("Models/llantaderfrenobj.obj");

	llantaizqfrenobj = Model();
	llantaizqfrenobj.LoadModel("Models/llantaizqfrenobj.obj");

	llantaizqatrasobj = Model();
	llantaizqatrasobj.LoadModel("Models/llantaizqatrasobj.obj");

	llantaderatrasobj = Model();
	llantaderatrasobj.LoadModel("Models/llantaderatrasobj.obj");
	//+----------------------------------------------

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;

	//Declaración de primer luz puntual
	//pointLights[0] = PointLight(1.0f, 1.0f, 1.0f,
	//	0.0f, 1.0f,
	//	-4.0f, 3.0f, -8.0f,
	//	0.5f, 0.0f, 0.1f);
	//pointLightCount++;

	unsigned int spotLightCount = 0;

	//lampara de techo
	pointLights[0] = PointLight(1.0f, 1.0f, 1.0f,//color 
		0.5f, 5.0f,			//intensidades
		0.0f, 0.0f, 0.0f,  // posicion x,y,z
		0.4f, 0.1f, 0.1f); // con, lin, exp
	pointLightCount++;

	//luz de arma zzz
	pointLights[1] = PointLight(1.0f, 0.647f, 0.0f,//color 
		0.5f, 5.0f,			//intensidades
		0.0f, 0.0f, 0.0f,  // posicion x,y,z
		0.8f, 0.8f, 0.9f); // con, lin, exp
	pointLightCount++;


	spotLights[0] = SpotLight(0.8f, 0.5f, 0.5f,
		1.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		-2.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		25.0f);
	spotLightCount++;

	spotLights[1] = SpotLight(1.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		-2.0f, -2.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		25.0f);
	spotLightCount++;

	spotLights[2] = SpotLight(0.5f, 1.0f, 0.5f,
		1.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		2.0f, -2.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		25.0f);
	spotLightCount++;

	

	////luz helicoptero
	//spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
	//	1.0f, 2.0f,
	//	0.0f, 0.0f, 0.0f,
	//	0.0f, -2.0f, 0.0f,
	//	1.0f, 0.0f, 0.0f,
	//	5.0f);
	//spotLightCount++;
	



	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana

	//Matrices de modelo
	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	

	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		/*glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());*/



		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		//shaderList[0].SetPointLights(pointLights, pointLightCount);
		//shaderList[0].SetSpotLights(spotLights, spotLightCount);
		
		//Funcion para prender lampara y arma de zzz
		if (mainWindow.getPrendida() == GL_TRUE)
 		{
			shaderList[0].SetPointLights(pointLights, pointLightCount-1);
		}
		else if(mainWindow.getarmaprendida() == GL_TRUE)
		{
			shaderList[0].SetPointLights(&pointLights[1], 1);
		}
		else
		{
			shaderList[0].SetPointLights(pointLights, pointLightCount - 2);
		}

		

		//Función para prender luces del coche
		if(mainWindow.getLuzAdelante()== GL_TRUE and mainWindow.getLuzAtras()==GL_FALSE)
		{
			shaderList[0].SetSpotLights(&spotLights[1], spotLightCount - 2);
		}
		else if (mainWindow.getLuzAdelante() == GL_FALSE and mainWindow.getLuzAtras() == GL_TRUE)
		{
			shaderList[0].SetSpotLights(&spotLights[2], spotLightCount - 2);
			// Para activar dos de diferentes posiciones del arreglo
			//SpotLight active[2] = { spotLights[0], spotLights[2] };
			//shaderList[0].SetSpotLights(active, 2);
		}
		else if (mainWindow.getLuzCofre() == GL_TRUE)
		{
			shaderList[0].SetSpotLights(spotLights, spotLightCount-2);
		}
		else
		{
			shaderList[0].SetSpotLights(spotLights, spotLightCount-3);
		}


		//
		//



		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//llantaderatrasobj.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();


		
		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 10.0f, -8.0f));
		modelaux = model;
		pointLights[0].SetPos(glm::vec3(model[3].x, model[3].y - 3.5f, model[3].z));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		
		lamp.RenderModel();
		

		//Instancia del coche 
		model = glm::mat4(1.0);
		
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmuevex(), 0.0f, -3.0f));
		spotLights[1].SetPos(glm::vec3(model[3].x - 4.0f, model[3].y +1.5f, model[3].z));	
		spotLights[2].SetPos(glm::vec3(model[3].x + 4.0f, model[3].y + 1.5f, model[3].z));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		modelaux = model;

		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		carrsincofre.RenderModel();


		//Cofre del coche
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.455f, 0.43f, -0.005f));
		



		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getmuevecofre()), glm::vec3(1.0f, 0.0f, 0.0f));
		const glm::vec3 localFlashPos(0.0f, 0.0f, 0.0f); // ajusta al “borde” del cofre
		const glm::vec3 localFlashDir(0.0f, 0.0f, 1.0f); // “frente” del cofre
		glm::vec3 flashPos = glm::vec3(model * glm::vec4(localFlashPos, 1.0f));
		glm::vec3 flashDir = glm::normalize(glm::mat3(model) * localFlashDir);
		spotLights[0].SetFlash(flashPos, flashDir);

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cofre.RenderModel();

		//Llanta delantera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.62f, 0.14f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getmueval()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaizqfrenobj.RenderModel();

		//Llanta trasera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.62f, 0.14f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getmueval()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaizqatrasobj.RenderModel();

		//Llanta delantera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.62f, 0.14f, -0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getmueval()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaderfrenobj.RenderModel();

		//Llanta trasera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.62f, 0.14f, -0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getmueval()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaderatrasobj.RenderModel();

		//arma de zzz
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, 5.0f, -8.0f));
		pointLights[1].SetPos(glm::vec3(model[3].x-1, model[3].y, model[3].z));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		armazzz.RenderModel();


		
		//blending: transparencia o traslucidez
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//AgaveTexture.UseTexture();
		//Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[3]->RenderMesh();
		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
