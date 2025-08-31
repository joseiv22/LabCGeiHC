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
const float toRadians = 3.14159265f / 180.0; //grados a radianes
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

static const char* vShaderAzul = "shaders/shaderazul.vert";
static const char* vShaderVerdeD = "shaders/shaderverdeD.vert";
static const char* vShaderVerdeF = "shaders/shaderverdeF.vert";
static const char* vShaderRojo = "shaders/shaderrojo.vert";
static const char* vShaderCafe = "shaders/shadercafe.vert";

float angulo = 0.0f;


void CreateShaders()
{
    // solo se ocupa 1 por que los colores se asignan en el VAO
    Shader* shader1 = new Shader(); 
    shader1->CreateFromFiles(vShaderColor, fShaderColor);
    shaderList.push_back(*shader1);
    // Para la casa
	// shader 3 es verde oscuro es el 1 en la lista
	// shader 4 es verde claro es el 2 en la lista
	// shader 5 es rojo es el 3 en la lista
	// shader 6 es café es el 4 en la lista
	// shader 7 es azul es el 5 en la lista
    Shader* shader3 = new Shader();
    shader3->CreateFromFiles(vShaderVerdeD, fShader);
    shaderList.push_back(*shader3);

    Shader* shader4 = new Shader();
    shader4->CreateFromFiles(vShaderVerdeF, fShader);
    shaderList.push_back(*shader4);

    Shader* shader5 = new Shader();
    shader5->CreateFromFiles(vShaderRojo, fShader);
    shaderList.push_back(*shader5);

    Shader* shader6 = new Shader();
    shader6->CreateFromFiles(vShaderCafe, fShader);
    shaderList.push_back(*shader6);

    Shader* shader7 = new Shader();
    shader7->CreateFromFiles(vShaderAzul, fShader);
    shaderList.push_back(*shader7);


}
// Notas prioriza el color de los shaders sobre el color del VAO
// Si quieres que se vea el color del VAO usa un shader que no tenga color fijo
//El mesh color list es para pintar figuras con color por vértice
// El mesh list es para pintar figuras con un color fijo desde el shader y usando índices
//Pirámide triangular regular
void CreaPiramide()
{
    unsigned int indices[] = {
        0,1,2,
        1,3,2,
        3,0,2,
        1,0,3

    };
    GLfloat vertices[] = {
        -0.5f, -0.5f,0.0f,	//0
        0.5f,-0.5f,0.0f,	//1
        0.0f,0.5f, -0.25f,	//2
        0.0f,-0.5f,-0.5f,	//3

    };
    Mesh* obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
    unsigned int cubo_indices[] = {
        // front
        0, 1, 2,
        2, 3, 0,
        // right
        1, 5, 6,
        6, 2, 1,
        // back
        7, 6, 5,
        5, 4, 7,
        // left
        4, 0, 3,
        3, 7, 4,
        // bottom
        4, 5, 1,
        1, 0, 4,
        // top
        3, 2, 6,
        6, 7, 3
    };

    GLfloat cubo_vertices[] = {
        // front
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        // back
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f
    };
    Mesh* cubo = new Mesh();
    cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
    meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
// ===== LETRA J (ROJO, z=0.5f) =====
    GLfloat vertices_letraJ[] = {
    -0.65f, 0.50f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.75f, 0.50f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.65f, 0.40f, 0.5f,  1.0f, 0.0f, 0.0f,

    -0.75f, 0.50f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.75f, 0.40f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.65f, 0.40f, 0.5f,  1.0f, 0.0f, 0.0f,

    -0.65f, 0.50f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.65f, 0.30f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.55f, 0.50f, 0.5f,  1.0f, 0.0f, 0.0f,

    -0.55f, 0.50f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.65f, 0.30f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.55f, 0.10f, 0.5f,  1.0f, 0.0f, 0.0f,

    -0.65f, 0.30f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.65f, 0.10f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.55f, 0.10f, 0.5f,  1.0f, 0.0f, 0.0f,

    -0.65f, 0.10f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.80f, 0.10f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.65f, 0.175f,0.5f,  1.0f, 0.0f, 0.0f,

    -0.80f, 0.10f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.80f, 0.175f,0.5f,  1.0f, 0.0f, 0.0f,
    -0.65f, 0.175f,0.5f,  1.0f, 0.0f, 0.0f,

    -0.45f, 0.50f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.55f, 0.50f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.55f, 0.40f, 0.5f,  1.0f, 0.0f, 0.0f,

    -0.45f, 0.50f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.55f, 0.40f, 0.5f,  1.0f, 0.0f, 0.0f,
    -0.45f, 0.40f, 0.5f,  1.0f, 0.0f, 0.0f,
    };
    MeshColor* letraJ = new MeshColor();
    letraJ->CreateMeshColor(vertices_letraJ, sizeof(vertices_letraJ) / sizeof(GLfloat));
    meshColorList.push_back(letraJ);

    GLfloat vertices_letraC[] = {
        -0.20f, 0.50f, 0.5f,  1.0f, 0.84f, 0.0f,
        -0.25f, 0.50f, 0.5f,  1.0f, 0.84f, 0.0f,
        -0.20f, 0.20f, 0.5f,  1.0f, 0.84f, 0.0f,

        -0.25f, 0.50f, 0.5f,  1.0f, 0.84f, 0.0f,
        -0.25f, 0.20f, 0.5f,  1.0f, 0.84f, 0.0f,
        -0.20f, 0.20f, 0.5f,  1.0f, 0.84f, 0.0f,

        -0.05f, 0.20f, 0.5f,  1.0f, 0.84f, 0.0f,
        -0.25f, 0.20f, 0.5f,  1.0f, 0.84f, 0.0f,
        -0.05f, 0.10f, 0.5f,  1.0f, 0.84f, 0.0f,

        -0.25f, 0.20f, 0.5f,  1.0f, 0.84f, 0.0f,
        -0.25f, 0.10f, 0.5f,  1.0f, 0.84f, 0.0f,
        -0.05f, 0.10f, 0.5f,  1.0f, 0.84f, 0.0f,

        -0.20f, 0.50f, 0.5f,  1.0f, 0.84f, 0.0f,
        -0.20f, 0.40f, 0.5f,  1.0f, 0.84f, 0.0f,
        -0.05f, 0.40f, 0.5f,  1.0f, 0.84f, 0.0f,

        -0.20f, 0.50f, 0.5f,  1.0f, 0.84f, 0.0f,
        -0.05f, 0.40f, 0.5f,  1.0f, 0.84f, 0.0f,
        -0.05f, 0.50f, 0.5f,  1.0f, 0.84f, 0.0f,
    };
    MeshColor* letraC = new MeshColor();
    letraC->CreateMeshColor(vertices_letraC, sizeof(vertices_letraC) / sizeof(GLfloat));
    meshColorList.push_back(letraC);

    GLfloat vertices_letraP[] = {

        0.20f, 0.50f, 0.5f,   1.0f, 0.7f, 0.8f,
        0.15f, 0.50f, 0.5f,   1.0f, 0.7f, 0.8f,
        0.20f, 0.10f, 0.5f,   1.0f, 0.7f, 0.8f,

        0.15f, 0.50f, 0.5f,   1.0f, 0.7f, 0.8f,
        0.15f, 0.10f, 0.5f,   1.0f, 0.7f, 0.8f,
        0.20f, 0.10f, 0.5f,   1.0f, 0.7f, 0.8f,


        0.20f, 0.50f, 0.5f,   1.0f, 0.7f, 0.8f,
        0.20f, 0.45f, 0.5f,   1.0f, 0.7f, 0.8f,
        0.275f,0.45f, 0.5f,   1.0f, 0.7f, 0.8f,

        0.20f, 0.50f, 0.5f,   1.0f, 0.7f, 0.8f,
        0.275f,0.45f, 0.5f,   1.0f, 0.7f, 0.8f,
        0.35f, 0.50f, 0.5f,   1.0f, 0.7f, 0.8f,

        0.35f, 0.50f, 0.5f,   1.0f, 0.7f, 0.8f,
        0.275f,0.45f, 0.5f,   1.0f, 0.7f, 0.8f,
        0.35f, 0.45f, 0.5f,   1.0f, 0.7f, 0.8f,


        0.35f, 0.45f, 0.5f,   1.0f, 0.7f, 0.8f,
        0.30f, 0.45f, 0.5f,   1.0f, 0.7f, 0.8f,
        0.35f, 0.30f, 0.5f,   1.0f, 0.7f, 0.8f,

        0.35f, 0.30f, 0.5f,   1.0f, 0.7f, 0.8f,
        0.30f, 0.30f, 0.5f,   1.0f, 0.7f, 0.8f,
        0.32f, 0.395f,0.5f,   1.0f, 0.7f, 0.8f,

        0.32f, 0.395f,0.5f,   1.0f, 0.7f, 0.8f,
        0.20f, 0.30f, 0.5f,   1.0f, 0.7f, 0.8f,
        0.30f, 0.30f, 0.5f,   1.0f, 0.7f, 0.8f,


        0.32f, 0.395f,0.5f,   1.0f, 0.7f, 0.8f,
        0.20f, 0.345f,0.5f,   1.0f, 0.7f, 0.8f,
        0.20f, 0.30f, 0.5f,   1.0f, 0.7f, 0.8f,
    };
    MeshColor* letraP = new MeshColor();
    letraP->CreateMeshColor(vertices_letraP, sizeof(vertices_letraP) / sizeof(GLfloat));
    meshColorList.push_back(letraP);

}


int main()
{
    mainWindow = Window(800, 600);
    mainWindow.Initialise();
    //--Descomentar para las letras
    //CrearLetrasyFiguras();
    CreaPiramide(); //índice 0 en MeshList
    CrearCubo();//índice 1 en MeshList
    CreateShaders();
    GLuint uniformProjection = 0;
    GLuint uniformModel = 0;
    //Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
    glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

    glm::mat4 model(1.0);

    //Loop mientras no se cierra la ventana
    while (!mainWindow.getShouldClose())
    {
        //Recibir eventos del usuario
        glfwPollEvents();
        //Limpiar la ventana
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

        //Para las letras descomentar esto y comentar la casa --------------------------------------------------
        // solo ocupo 1 shader por que los colores se asignan en el VAO 
  //      shaderList[0].useShader();
  //      uniformModel = shaderList[0].getModelLocation();
  //      uniformProjection = shaderList[0].getProjectLocation();

        //// 0: letra J
  //      model = glm::mat4(1.0f);
  //      model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.1f));

  //      glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
  //      glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
  //      meshColorList[0]->RenderMeshColor();
        ////Letra C
  //      model = glm::mat4(1.0f);
  //      model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.1f));

  //      glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
  //      glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
  //      meshColorList[1]->RenderMeshColor();
  //      //Letra P
  //      model = glm::mat4(1.0f);
  //      model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.1f));

  //      glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
  //      glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
  //      meshColorList[2]->RenderMeshColor();

        // aqui empieza la casa --------------------------------------------------
		// mesh meshList[0]->RenderMesh(); es piramide
		// meshList[1]->RenderMesh(); es cubo
        
        // 1) Pirámide azul
        shaderList[5].useShader();
        uniformModel = shaderList[5].getModelLocation();
        uniformProjection = shaderList[5].getProjectLocation();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.7f, -2.0f));
		model = glm::scale(model, glm::vec3(1.1f, 0.60f, 0.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->RenderMesh();

        // 2) Pirámide verde oscuro
        shaderList[1].useShader();
        uniformModel = shaderList[1].getModelLocation();
        uniformProjection = shaderList[1].getProjectLocation();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.8f, -0.38f, -1.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.6f, 0.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->RenderMesh();

        // 3) Pirámide verde oscuro
        shaderList[1].useShader();
        uniformModel = shaderList[1].getModelLocation();
        uniformProjection = shaderList[1].getProjectLocation();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.8f, -0.38f, -1.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.6f, 0.5f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->RenderMesh();

        // 4) Cubo rojo
        shaderList[3].useShader();
        uniformModel = shaderList[3].getModelLocation();
        uniformProjection = shaderList[3].getProjectLocation();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.28f, -2.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.35f, 0.7f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        // 5) Cubo verde claro
        shaderList[2].useShader();
        uniformModel = shaderList[2].getModelLocation();
        uniformProjection = shaderList[2].getProjectLocation();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.2f, 0.1f, -1.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.40f, 0.4f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        // 6) Cubo verde claro
        shaderList[2].useShader();
        uniformModel = shaderList[2].getModelLocation();
        uniformProjection = shaderList[2].getProjectLocation();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.2f, 0.1f, -1.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.40f, 0.4f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        // 7) Puerta cubo verde claro
        shaderList[2].useShader();
        uniformModel = shaderList[2].getModelLocation();
        uniformProjection = shaderList[2].getProjectLocation();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.755f, -1.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.40f, 0.4f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        // 8) Cubo café
        shaderList[4].useShader();
        uniformModel = shaderList[4].getModelLocation();
        uniformProjection = shaderList[4].getProjectLocation();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.8f, -0.8f, -3.5f));
        model = glm::scale(model, glm::vec3(0.20f, 0.25f, 0.4f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        // 9) Otro cubo café
        shaderList[4].useShader();
        uniformModel = shaderList[4].getModelLocation();
        uniformProjection = shaderList[4].getProjectLocation();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.8f, -0.8f, -3.5f));
        model = glm::scale(model, glm::vec3(0.20f, 0.25f, 0.4f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();



        glUseProgram(0);
        mainWindow.swapBuffers();


    }

    return 0;
}
