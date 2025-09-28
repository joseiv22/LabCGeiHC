#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	rotax = 0.0f;
	rotay = 0.0f;
	rotaz = 0.0f;
	articulacion1 = 0.0f;
	articulacion2 = 0.0f;
	articulacion3 = 0.0f;
	articulacion4 = 0.0f;
	articulacion5 = 0.0f;
	articulacion6 = 0.0f;
	articulacion7 = 0.0f;
	articulacion8 = 0.0f;
	aumentandoArticulacion1 = true;
	aumentandoArticulacion2 = true;
	aumentandoArticulacion3 = true;
	aumentandoArticulacion4 = true;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Practica XX: Nombre de la práctica", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	
	if (key == GLFW_KEY_E)
	{
		theWindow->rotax += 10.0;
	}
	if (key == GLFW_KEY_R)
	{
		theWindow->rotay += 10.0; 
	}
	if (key == GLFW_KEY_T)
	{
		theWindow->rotaz += 10.0;
	}
//Codigo modificado	----------------------
	if (key == GLFW_KEY_F )
	{
		if (theWindow->aumentandoArticulacion1) {
			theWindow->articulacion1 += 15.0f; // Cambiado a 15
			if (theWindow->articulacion1 >= 45.0f) {
				theWindow->aumentandoArticulacion1 = false;
			}
		}
		else {
			theWindow->articulacion1 -= 15.0f; // Cambiado a 15
			if (theWindow->articulacion1 <= -45.0f) {
				theWindow->aumentandoArticulacion1 = true;
			}
		}
	}

	if (key == GLFW_KEY_G )
	{
		if (theWindow->aumentandoArticulacion2) {
			theWindow->articulacion2 += 15.0f; // Cambiado a 15
			if (theWindow->articulacion2 >= 45.0f) {
				theWindow->aumentandoArticulacion2 = false;
			}
		}
		else {
			theWindow->articulacion2 -= 15.0f; // Cambiado a 15
			if (theWindow->articulacion2 <= -45.0f) {
				theWindow->aumentandoArticulacion2 = true;
			}
		}
	}

	if (key == GLFW_KEY_H )
	{
		if (theWindow->aumentandoArticulacion3) {
			theWindow->articulacion3 += 15.0f; // Cambiado a 15
			if (theWindow->articulacion3 >= 45.0f) {
				theWindow->aumentandoArticulacion3 = false;
			}
		}
		else {
			theWindow->articulacion3 -= 15.0f; // Cambiado a 15
			if (theWindow->articulacion3 <= -45.0f) {
				theWindow->aumentandoArticulacion3 = true;
			}
		}
	}

	if (key == GLFW_KEY_J )
	{
		if (theWindow->aumentandoArticulacion4) {
			theWindow->articulacion4 += 15.0f; // Cambiado a 15
			if (theWindow->articulacion4 >= 45.0f) {
				theWindow->aumentandoArticulacion4 = false;
			}
		}
		else {
			theWindow->articulacion4 -= 15.0f; // Cambiado a 15
			if (theWindow->articulacion4 <= -45.0f) {
				theWindow->aumentandoArticulacion4 = true;
			}
		}
	}

	// Codigo modificado	----------------------
	if (key == GLFW_KEY_U)
	{
		theWindow->articulacion5 += 10.0;
	}

	if (key == GLFW_KEY_I)
	{
		theWindow->articulacion6 += 10.0;
	}
	if (key == GLFW_KEY_O)
	{
		theWindow->articulacion7 += 10.0;
	}

	if (key == GLFW_KEY_P)
	{
		theWindow->articulacion8 += 10.0;
	}


	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		//printf("se presiono la tecla: %s\n",key_name);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
