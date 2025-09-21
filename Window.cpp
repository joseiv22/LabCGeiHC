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
		theWindow->rotay += 10.0; //rotar sobre el eje y 10 grados
	}
	if (key == GLFW_KEY_T)
	{
		theWindow->rotaz += 10.0;
	}
	if (key == GLFW_KEY_F )
	{
		// Verificamos si la articulación está en modo 'subir'
		if (theWindow->aumentandoArticulacion1)
		{
			// Incrementamos el valor
			theWindow->articulacion1 += 10.0f;

			// Si llega o supera el nuevo límite superior (30), cambiamos de dirección
			if (theWindow->articulacion1 >= 30.0f)
			{
				theWindow->aumentandoArticulacion1 = false;
			}
		}
		else // Si no, está en modo 'bajar'
		{
			// Decrementamos el valor
			theWindow->articulacion1 -= 10.0f;

			// Si llega o supera el nuevo límite inferior (-60), cambiamos de dirección
			if (theWindow->articulacion1 <= -60.0f)
			{
				theWindow->aumentandoArticulacion1 = true;
			}
		}
	}
	if (key == GLFW_KEY_G )
	{
		// Verificamos si la articulación está en modo 'subir'
		if (theWindow->aumentandoArticulacion2)
		{
			// Incrementamos el valor
			theWindow->articulacion2 += 10.0f;

			// Si llega o supera el límite superior (60), cambiamos de dirección
			if (theWindow->articulacion2 >= 90.0f)
			{
				theWindow->aumentandoArticulacion2 = false;
			}
		}
		else // Si no, está en modo 'bajar'
		{
			// Decrementamos el valor
			theWindow->articulacion2 -= 10.0f;

			// Si llega o supera el límite inferior (-120), cambiamos de dirección
			if (theWindow->articulacion2 <= -90.0f)
			{
				theWindow->aumentandoArticulacion2 = true;
			}
		}
	}
	if (key == GLFW_KEY_H )
	{
		// Verificamos si la articulación está en modo 'subir'
		if (theWindow->aumentandoArticulacion3)
		{
			// Incrementamos el valor
			theWindow->articulacion3 += 10.0f;

			// Si llega o supera el límite superior (30), cambiamos de dirección
			if (theWindow->articulacion3 >= 30.0f)
			{
				theWindow->aumentandoArticulacion3 = false;
			}
		}
		else // Si no, está en modo 'bajar'
		{
			// Decrementamos el valor
			theWindow->articulacion3 -= 10.0f;

			// Si llega o supera el límite inferior (-30), cambiamos de dirección
			if (theWindow->articulacion3 <= -30.0f)
			{
				theWindow->aumentandoArticulacion3 = true;
			}
		}
	}
	if (key == GLFW_KEY_J )
	{
		// Verificamos si la articulación está en modo 'subir'
		if (theWindow->aumentandoArticulacion4)
		{
			// Incrementamos el valor
			theWindow->articulacion4 += 10.0f;

			// Si llega o supera el límite superior (20), cambiamos de dirección
			if (theWindow->articulacion4 >= 90.0f)
			{
				theWindow->aumentandoArticulacion4 = false;
			}
		}
		else // Si no, está en modo 'bajar'
		{
			// Decrementamos el valor
			theWindow->articulacion4 -= 10.0f;

			// Si llega o supera el límite inferior (-50), cambiamos de dirección
			if (theWindow->articulacion4 <= -20.0f)
			{
				theWindow->aumentandoArticulacion4 = true;
			}
		}
	}
	if (key == GLFW_KEY_K )
	{
		// Verificamos el estado: ¿estamos subiendo?
		if (theWindow->aumentandoArticulacion5)
		{
			// Sí, estamos subiendo. Aumentamos el valor.
			theWindow->articulacion5 += 10.0f;

			// ¿Llegamos o pasamos el límite superior (30)?
			if (theWindow->articulacion5 >= 30.0f)
			{
				// Sí, llegamos. Cambiamos el estado para empezar a bajar la próxima vez.
				theWindow->aumentandoArticulacion5 = false;
			}
		}
		else // Si no, significa que estamos bajando.
		{
			// Estamos bajando. Reducimos el valor.
			theWindow->articulacion5 -= 10.0f;

			// ¿Llegamos o pasamos el límite inferior (-60)?
			if (theWindow->articulacion5 <= -60.0f) // Asumo que querías decir -60
			{
				// Sí, llegamos. Cambiamos el estado para empezar a subir la próxima vez.
				theWindow->aumentandoArticulacion5 = true;
			}
		}
	}
	if (key == GLFW_KEY_L)
	{
		// Verificamos el estado: ¿estamos subiendo?
		if (theWindow->aumentandoArticulacion6)
		{
			// Sí, estamos subiendo.
			theWindow->articulacion6 += 10.0f;

			// ¿Llegamos o pasamos el límite superior (30)?
			if (theWindow->articulacion6 >= 30.0f)
			{
				// Sí, llegamos. Cambiamos el estado para empezar a bajar.
				theWindow->aumentandoArticulacion6 = false;
			}
		}
		else // Si no, significa que estamos bajando.
		{
			// Estamos bajando.
			theWindow->articulacion6 -= 10.0f;

			// ¿Llegamos o pasamos el límite inferior (-30)?
			if (theWindow->articulacion6 <= -30.0f)
			{
				// Sí, llegamos. Cambiamos el estado para empezar a subir.
				theWindow->aumentandoArticulacion6 = true;
			}
		}
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
