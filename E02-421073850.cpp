//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
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
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá

float angulo = 0.0f;


void CreateShaders()
{
	// solo se ocupa 1 por que los colores se asignan en el VAO
	Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader1);


}
// Notas prioriza el color de los shaders sobre el color del VAO
// Si quieres que se vea el color del VAO usa un shader que no tenga color fijo
//El mesh color list es para pintar figuras con color por vértice
// El mesh list es para pintar figuras con un color fijo desde el shader y usando índices

void CrearLetrasyFiguras()
{
    // ------------------ TRIÁNGULO AZUL ------------------
    GLfloat vertices_trianguloazul[] = {
        //X      Y       Z       R    G    B
        -1.0f, -1.0f, 0.5f,   0.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 0.5f,   0.0f, 0.0f, 1.0f,
         0.0f,  1.0f, 0.5f,   0.0f, 0.0f, 1.0f,
    };
    MeshColor* trianguloazul = new MeshColor();
    trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
    meshColorList.push_back(trianguloazul);

    // ------------------ TRIÁNGULO VERDE (1) ------------------
    GLfloat vertices_trianguloverde1[] = {
        -1.0f, -1.0f, 0.5f,   0.0f, 0.5f, 0.0f,
         1.0f, -1.0f, 0.5f,   0.0f, 0.5f, 0.0f,
         0.0f,  1.0f, 0.5f,   0.0f, 0.5f, 0.0f,
    };
    MeshColor* trianguloverde1 = new MeshColor();
    trianguloverde1->CreateMeshColor(vertices_trianguloverde1, 18);
    meshColorList.push_back(trianguloverde1);

    // ------------------ TRIÁNGULO VERDE (2) ------------------
    GLfloat vertices_trianguloverde2[] = {
        -1.0f, -1.0f, 0.5f,   0.0f, 0.5f, 0.0f,
         1.0f, -1.0f, 0.5f,   0.0f, 0.5f, 0.0f,
         0.0f,  1.0f, 0.5f,   0.0f, 0.5f, 0.0f,
    };
    MeshColor* trianguloverde2 = new MeshColor();
    trianguloverde2->CreateMeshColor(vertices_trianguloverde2, 18);
    meshColorList.push_back(trianguloverde2);

    // ------------------ CUADRADO ROJO ------------------
    GLfloat vertices_cuadradorojo[] = {
        -0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,
    };
    MeshColor* cuadradorojo = new MeshColor();
    cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
    meshColorList.push_back(cuadradorojo);

    // ------------------ CUADRADO VERDE (1) ------------------
    GLfloat vertices_cuadradoverde1[] = {
        -0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
    };
    MeshColor* cuadradoverde1 = new MeshColor();
    cuadradoverde1->CreateMeshColor(vertices_cuadradoverde1, 36);
    meshColorList.push_back(cuadradoverde1);

    // ------------------ CUADRADO VERDE (2) ------------------
    GLfloat vertices_cuadradoverde2[] = {
        -0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
    };
    MeshColor* cuadradoverde2 = new MeshColor();
    cuadradoverde2->CreateMeshColor(vertices_cuadradoverde2, 36);
    meshColorList.push_back(cuadradoverde2);

    // ------------------ CUADRADO VERDE (3) ------------------
    GLfloat vertices_cuadradoverde3[] = {
        -0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
    };
    MeshColor* cuadradoverde3 = new MeshColor();
    cuadradoverde3->CreateMeshColor(vertices_cuadradoverde3, 36);
    meshColorList.push_back(cuadradoverde3);

    // ------------------ CUADRADO CAFÉ (1) ------------------
    GLfloat vertices_cuadradocafe1[] = {
        -0.5f, -0.5f, 0.5f,   0.478f, 0.255f, 0.067f,
         0.5f, -0.5f, 0.5f,   0.478f, 0.255f, 0.067f,
         0.5f,  0.5f, 0.5f,   0.478f, 0.255f, 0.067f,
        -0.5f, -0.5f, 0.5f,   0.478f, 0.255f, 0.067f,
         0.5f,  0.5f, 0.5f,   0.478f, 0.255f, 0.067f,
        -0.5f,  0.5f, 0.5f,   0.478f, 0.255f, 0.067f,
    };
    MeshColor* cuadradocafe1 = new MeshColor();
    cuadradocafe1->CreateMeshColor(vertices_cuadradocafe1, 36);
    meshColorList.push_back(cuadradocafe1);

    // ------------------ CUADRADO CAFÉ (2) ------------------
    GLfloat vertices_cuadradocafe2[] = {
        -0.5f, -0.5f, 0.5f,   0.478f, 0.255f, 0.067f,
         0.5f, -0.5f, 0.5f,   0.478f, 0.255f, 0.067f,
         0.5f,  0.5f, 0.5f,   0.478f, 0.255f, 0.067f,
        -0.5f, -0.5f, 0.5f,   0.478f, 0.255f, 0.067f,
         0.5f,  0.5f, 0.5f,   0.478f, 0.255f, 0.067f,
        -0.5f,  0.5f, 0.5f,   0.478f, 0.255f, 0.067f,
    };
    MeshColor* cuadradocafe2 = new MeshColor();
    cuadradocafe2->CreateMeshColor(vertices_cuadradocafe2, 36);
    meshColorList.push_back(cuadradocafe2);





}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();

	CrearLetrasyFiguras();
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);	
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
		//Para las letras hay que usar el segundo set de shaders con índice 0 en ShaderList 
		// solo ocupo 1 shader por que los colores se asignan en el VAO 
        shaderList[0].useShader();
        uniformModel = shaderList[0].getModelLocation();
        uniformProjection = shaderList[0].getProjectLocation();

        // 0: Triángulo azul
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.7f, -1.1f));
        model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.4f));
        
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshColorList[0]->RenderMeshColor();

        // 1: Triángulo verde
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.7f, -0.425f, -1.6f));
        model = glm::scale(model, glm::vec3(0.16f, 0.25f, 0.4f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshColorList[1]->RenderMeshColor();

        // 2: Triángulo verde
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.7f, -0.425f, -1.6f));
        model = glm::scale(model, glm::vec3(0.16f, 0.25f, 0.4f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshColorList[2]->RenderMeshColor();

        // 3: Cuadrado rojo
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.25f, -1.5f));
        model = glm::scale(model, glm::vec3(0.9f, 1.3f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshColorList[3]->RenderMeshColor();

        // 4: Cuadrado verde
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.2f, 0.0f, -1.0f));
        model = glm::scale(model, glm::vec3(0.25f, 0.3f, 0.3f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshColorList[4]->RenderMeshColor();

        // 5: Cuadrado verde
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.2f, 0.0f, -1.0f));
        model = glm::scale(model, glm::vec3(0.25f, 0.3f, 0.3f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
       
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshColorList[5]->RenderMeshColor();

        // 6: Cuadrado verde
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.75f, -1.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));


        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshColorList[6]->RenderMeshColor();

        // 7: Cuadrado café
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.7f, -0.8f, -1.6f));
        model = glm::scale(model, glm::vec3(0.2f, 0.25f, 0.25f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshColorList[7]->RenderMeshColor();

        // 8: Cuadrado café
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.7f, -0.8f, -1.6f));
        model = glm::scale(model, glm::vec3(0.2f, 0.25f, 0.25f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshColorList[8]->RenderMeshColor();




		glUseProgram(0); 
		mainWindow.swapBuffers();

	}
	return 0;
}
