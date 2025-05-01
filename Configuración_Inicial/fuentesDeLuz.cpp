/* PROYECTO DE COMPUTACIÓN GRÁFICA E INTERACCIÓN HUMANO COMPUTADORA
* SEMESTRE 2025-2
* EQUIPO 9
* INTEGRANTES:
* Berdejo Guzmán Leonardo Ariel
* Javier Antonio Rodriguez Garcia
*/

#include <string>
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

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void MonitorAnimation();
void Animation(); //Función para los frames 

// Window dimensions
const GLuint WIDTH = 1500, HEIGHT = 650;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera camera(glm::vec3(0.0f, 0.5f, 0.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Light attributes
glm::vec3 lightPos(0.0f, 0.0f,5.0f);
bool active;
int flag = 0;
int luz1 = 0;
int luz2 = 0;
int luz3 = 0;
int luz4 = 0;
int cont = 0;

int nuevo = 0;
// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.43f,0.25f,1.6f),
	glm::vec3(1.1f,0.01f,0.86f),
	glm::vec3(0.84f,0.1f,-2.17f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};



glm::vec3 Light1 = glm::vec3(0);

// Variables para la animación de monitores
bool monitorAnimationActive = false;  // Indica si la animación está activa
int monitorAnimationState = 0;  // 0: monitores viejos, 1: transición, 2: monitores nuevos
float oldMonitorScale = 1.0f;  // Escala para monitores viejos
float newMonitorScale = 0.0f;  // Escala para monitores nuevos
int monitorAnimFrame = 0;  // Frame actual de la animación
const int MONITOR_ANIM_MAX_FRAMES = 60;  // Total de frames para cada transición
//////////////////////////////////// INICIO FRAMES ///////////////////////////////
//Anim
float rotBall = 0.0f;
float rotDog = 0.0f;
float rotDogX = 0; //Variable para rotación
int dogAnim = 0;
float FLegs = 0.0f;
float FLegsL = 0.0f;
float FLegsR = 0.0f;
float RLegs = 0.0f;
float head = 0.0f;
float tail = 0.0f;

float radio = 0.0f;  // Radio del círculo
float angle = 0.0f;  // Ángulo inicial
bool moveRot = false;
float speed = 0.0001f;


//Modificar estos KeyFrames pues es para cada animación
float dogPosX, dogPosY, dogPosZ;

#define MAX_FRAMES 50
int i_max_steps = 190;
int i_curr_steps = 0;

//-----------------------Definición de la estructura para los KeyFrames-----------------------
typedef struct _frame {

	float rotDog;
	float rotDogInc;
	float dogPosX;
	float dogPosY;
	float dogPosZ;
	float incX;
	float incY;
	float incZ;
	float head;
	float headInc;
	float tail;
	float tailInc;
	float FLegs;
	float FLegsInc;
	float FLegsL;
	float FLegsLInc;
	float FLegsR;
	float FLegsRInc;
	float RLegs;
	float RLegsInc;
	//Variables para la rotación
	float rotDogX;
	float rotDogXInc;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//En qué lugar de la línea de tiempo me encuentro al guardar los datos
bool play = false;			//Si se está reproduciendo la animación
int playIndex = 0;			//En qué lugar de la línea de tiempo me encuentro al estar reproduciendo la animación

// Función para guardar la animación
void SaveAnimation(const char* filename = "Animacion.txt") {
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error al abrir el archivo para guardar." << std::endl;
		return;
	}

	for (int i = 0; i < FrameIndex; i++) {
		file << KeyFrame[i].dogPosX << " "
			<< KeyFrame[i].dogPosY << " "
			<< KeyFrame[i].dogPosZ << " "
			<< KeyFrame[i].rotDog << " "
			<< KeyFrame[i].head << " "
			<< KeyFrame[i].tail << " "
			<< KeyFrame[i].FLegs << " "
			<< KeyFrame[i].FLegsL << " "
			<< KeyFrame[i].FLegsR << " "
			<< KeyFrame[i].RLegs << " "
			<< KeyFrame[i].rotDogX << "\n";
	}
	file.close();
	std::cout << "Animacion guardada correctamente." << std::endl;
}

// Función para cargar los KeyFrames
void LoadAnimation(const char* filename = "Animacion.txt") {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error al abrir el archivo para cargar." << std::endl;
		return;
	}

	FrameIndex = 0;
	while (FrameIndex < MAX_FRAMES &&
		file >> KeyFrame[FrameIndex].dogPosX
		>> KeyFrame[FrameIndex].dogPosY
		>> KeyFrame[FrameIndex].dogPosZ
		>> KeyFrame[FrameIndex].rotDog
		>> KeyFrame[FrameIndex].head
		>> KeyFrame[FrameIndex].tail
		>> KeyFrame[FrameIndex].FLegs
		>> KeyFrame[FrameIndex].FLegsL
		>> KeyFrame[FrameIndex].FLegsR
		>> KeyFrame[FrameIndex].RLegs
		>> KeyFrame[FrameIndex].rotDogX) {
		FrameIndex++;
	}
}

// Función para imprimir el contenido del archivo .txt en consola
void PrintAnimation(const char* filename = "Animacion.txt") {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error al abrir el archivo para imprimir." << std::endl;
		return;
	}

	std::string line;
	std::cout << "Contenido del archivo " << filename << ":\n";
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
	}
	file.close();
}

void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].dogPosX = dogPosX;
	KeyFrame[FrameIndex].dogPosY = dogPosY;
	KeyFrame[FrameIndex].dogPosZ = dogPosZ;

	KeyFrame[FrameIndex].rotDog = rotDog;
	KeyFrame[FrameIndex].rotDogX = rotDogX;

	KeyFrame[FrameIndex].head = head;
	KeyFrame[FrameIndex].tail = tail;
	KeyFrame[FrameIndex].FLegs = FLegs;
	KeyFrame[FrameIndex].FLegsL = FLegsL;
	KeyFrame[FrameIndex].FLegsR = FLegsR;
	KeyFrame[FrameIndex].RLegs = RLegs;

	FrameIndex++;
}

void resetElements(void)
{
	dogPosX = KeyFrame[0].dogPosX;
	dogPosY = KeyFrame[0].dogPosY;
	dogPosZ = KeyFrame[0].dogPosZ;

	head = KeyFrame[0].head;
	tail = KeyFrame[0].tail;
	FLegs = KeyFrame[0].FLegs;
	FLegsL = KeyFrame[0].FLegsL;
	FLegsR = KeyFrame[0].FLegsR;
	RLegs = KeyFrame[0].RLegs;

	rotDog = KeyFrame[0].rotDog;
	rotDogX = KeyFrame[0].rotDogX;

}
void interpolation(void)
{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].dogPosX - KeyFrame[playIndex].dogPosX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].dogPosY - KeyFrame[playIndex].dogPosY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].dogPosZ - KeyFrame[playIndex].dogPosZ) / i_max_steps;

	KeyFrame[playIndex].headInc = (KeyFrame[playIndex + 1].head - KeyFrame[playIndex].head) / i_max_steps;
	KeyFrame[playIndex].tailInc = (KeyFrame[playIndex + 1].tail - KeyFrame[playIndex].tail) / i_max_steps;
	KeyFrame[playIndex].FLegsInc = (KeyFrame[playIndex + 1].FLegs - KeyFrame[playIndex].FLegs) / i_max_steps;
	KeyFrame[playIndex].FLegsLInc = (KeyFrame[playIndex + 1].FLegsL - KeyFrame[playIndex].FLegsL) / i_max_steps;
	KeyFrame[playIndex].FLegsRInc = (KeyFrame[playIndex + 1].FLegsR - KeyFrame[playIndex].FLegsR) / i_max_steps;
	KeyFrame[playIndex].RLegsInc = (KeyFrame[playIndex + 1].RLegs - KeyFrame[playIndex].RLegs) / i_max_steps;

	KeyFrame[playIndex].rotDogInc = (KeyFrame[playIndex + 1].rotDog - KeyFrame[playIndex].rotDog) / i_max_steps;
	KeyFrame[playIndex].rotDogXInc = (KeyFrame[playIndex + 1].rotDogX - KeyFrame[playIndex].rotDogX) / i_max_steps;

	printf("Interpolando cuadro %d a %d: IncX = %f\n", playIndex, playIndex + 1, KeyFrame[playIndex].incX);
}
//////////////////////////////////// FIN FRAMES ///////////////////////////////

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Grafica - Laboratorio de Redes y Seguridad", nullptr, nullptr);

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
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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



	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");
	Shader skyboxshader("Shader/SkyBox.vs", "Shader/SkyBox.frag");

	Model mesa((char*)"Models/mesa/mesa.obj");
	Model Moon((char*)"Models/Moon/moon.obj");
	//Model focos((char*)"Models/tele/pizarron.obj");
	Model Salon((char*)"Models/Salon1/model.obj");
	Model silla((char*)"Models/chair1/chair1.obj");
	Model monitor((char*)"Models/monitor/monitor.obj");
	Model teclado((char*)"Models/keyboard/keyboard.obj");
	Model mouse((char*)"Models/mouse/mouse.obj");
	Model cpu((char*)"Models/CPU/CPU.obj");
	Model pizarra((char*)"Models/pizarra/pizarra.obj");
	Model Puer((char*)"Models/puertaA/model.obj");


	Model escritorio((char*)"Models/mesanueva/model.obj");
	Model tele((char*)"Models/Tele/Tele.obj");
	Model tecladoled((char*)"Models/Led_Teclado/Teclado.obj");
	Model silla2((char*)"Models/GamerChair/GamerChair.obj");
	Model moniGamer((char*)"Models/MonitorNew/model.obj");
	Model servidor((char*)"Models/Rack/model.obj");
	
	Model prueba((char*)"Models/Pruebas/model.obj");

	////////////////////////// KEYFRAMES //////////////////////////////////

   /*Iniciarlizar todos los frames en 0 */
   //KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{

		KeyFrame[i].dogPosX = 0;
		KeyFrame[i].dogPosY = 0;
		KeyFrame[i].dogPosZ = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotDog = 0;
		KeyFrame[i].rotDogInc = 0;
		KeyFrame[i].tail = 0;
		KeyFrame[i].tailInc = 0;
		KeyFrame[i].FLegs = 0;
		KeyFrame[i].FLegsInc = 0;
		KeyFrame[i].FLegsL = 0;
		KeyFrame[i].FLegsLInc = 0;
		KeyFrame[i].FLegsR = 0;
		KeyFrame[i].FLegsRInc = 0;
		KeyFrame[i].RLegs = 0;
		KeyFrame[i].RLegsInc = 0;
		KeyFrame[i].rotDogX = 0;
		KeyFrame[i].rotDogXInc = 0;
		KeyFrame[i].head = 0;
		KeyFrame[i].headInc = 0;
	}

	//for (int i = 0; i < MAX_FRAMES_BOY; i++)
	//{
	//	//----------BOY------------

	//	KeyFrameBoy[i].boyPosX = 0;
	//	KeyFrameBoy[i].boyPosY = 0;
	//	KeyFrameBoy[i].boyPosZ = 0;

	//	KeyFrameBoy[i].sktPosX = 0;
	//	KeyFrameBoy[i].sktPosY = 0;
	//	KeyFrameBoy[i].sktPosZ = 0;

	//	KeyFrameBoy[i].rotBoy = 0;
	//	KeyFrameBoy[i].rotBoyInc = 0;
	//	KeyFrameBoy[i].rotBoyX = 0;
	//	KeyFrameBoy[i].rotBoyXInc = 0;

	//	KeyFrameBoy[i].cuerpoBoy = 0;
	//	KeyFrameBoy[i].cuerpoBoyInc = 0;
	//	KeyFrameBoy[i].bicepDer = 0;
	//	KeyFrameBoy[i].bicepDerInc = 0;
	//	KeyFrameBoy[i].bicepIzq = 0;
	//	KeyFrameBoy[i].bicepIzqInc = 0;
	//	KeyFrameBoy[i].brazoDer = 0;
	//	KeyFrameBoy[i].brazoDerInc = 0;
	//	KeyFrameBoy[i].brazoIzq = 0;
	//	KeyFrameBoy[i].brazoIzqInc = 0;
	//	KeyFrameBoy[i].piernaDer = 0;
	//	KeyFrameBoy[i].piernaDerInc = 0;
	//	KeyFrameBoy[i].piernaIzq = 0;
	//	KeyFrameBoy[i].piernaIzqInc = 0;
	//	KeyFrameBoy[i].pantDer = 0;
	//	KeyFrameBoy[i].pantDerInc = 0;
	//	KeyFrameBoy[i].pantIzq = 0;
	//	KeyFrameBoy[i].pantIzqInc = 0;

	//}

	//////////////////////////////////// FIN KEYFRAMES ///////////////////////////////
	GLfloat skyboxScale = 0.0000000001f;
	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f * skyboxScale,  1.0f * skyboxScale, -1.0f * skyboxScale,
		-1.0f * skyboxScale, -1.0f * skyboxScale, -1.0f * skyboxScale,
		1.0f * skyboxScale, -1.0f * skyboxScale, -1.0f * skyboxScale,
		1.0f * skyboxScale, -1.0f * skyboxScale, -1.0f * skyboxScale,
		1.0f * skyboxScale,  1.0f * skyboxScale, -1.0f * skyboxScale,
		-1.0f * skyboxScale,  1.0f * skyboxScale, -1.0f * skyboxScale,

		-1.0f * skyboxScale, -1.0f * skyboxScale,  1.0f * skyboxScale,
		-1.0f * skyboxScale, -1.0f * skyboxScale, -1.0f * skyboxScale,
		-1.0f * skyboxScale,  1.0f * skyboxScale, -1.0f * skyboxScale,
		-1.0f * skyboxScale,  1.0f * skyboxScale, -1.0f * skyboxScale,
		-1.0f * skyboxScale,  1.0f * skyboxScale,  1.0f * skyboxScale,
		-1.0f * skyboxScale, -1.0f * skyboxScale,  1.0f * skyboxScale,

		1.0f * skyboxScale, -1.0f * skyboxScale, -1.0f * skyboxScale,
		1.0f * skyboxScale, -1.0f * skyboxScale,  1.0f * skyboxScale,
		1.0f * skyboxScale,  1.0f * skyboxScale,  1.0f * skyboxScale,
		1.0f * skyboxScale,  1.0f * skyboxScale,  1.0f * skyboxScale,
		1.0f * skyboxScale,  1.0f * skyboxScale, -1.0f * skyboxScale,
		1.0f * skyboxScale, -1.0f * skyboxScale, -1.0f * skyboxScale,

		-1.0f * skyboxScale, -1.0f * skyboxScale,  1.0f * skyboxScale,
		-1.0f * skyboxScale,  1.0f * skyboxScale,  1.0f * skyboxScale,
		1.0f * skyboxScale,  1.0f * skyboxScale,  1.0f * skyboxScale,
		1.0f * skyboxScale,  1.0f * skyboxScale,  1.0f * skyboxScale,
		1.0f * skyboxScale, -1.0f * skyboxScale,  1.0f * skyboxScale,
		-1.0f * skyboxScale, -1.0f * skyboxScale,  1.0f * skyboxScale,

		-1.0f * skyboxScale,  1.0f * skyboxScale, -1.0f * skyboxScale,
		1.0f * skyboxScale,  1.0f * skyboxScale, -1.0f * skyboxScale,
		1.0f * skyboxScale,  1.0f * skyboxScale,  1.0f * skyboxScale,
		1.0f * skyboxScale,  1.0f * skyboxScale,  1.0f * skyboxScale,
		-1.0f * skyboxScale,  1.0f * skyboxScale,  1.0f * skyboxScale,
		-1.0f * skyboxScale,  1.0f * skyboxScale, -1.0f * skyboxScale,

		-1.0f * skyboxScale, -1.0f * skyboxScale, -1.0f * skyboxScale,
		-1.0f * skyboxScale, -1.0f * skyboxScale,  1.0f * skyboxScale,
		1.0f * skyboxScale, -1.0f * skyboxScale, -1.0f * skyboxScale,
		1.0f * skyboxScale, -1.0f * skyboxScale, -1.0f * skyboxScale,
		-1.0f * skyboxScale, -1.0f * skyboxScale,  1.0f * skyboxScale,
		1.0f * skyboxScale, -1.0f * skyboxScale,  1.0f * skyboxScale
	};


	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	///////////////////BUFFER SKYBOX//////////////////
	glGenBuffers(1, &EBO);
	/////////////////////////////////////////////////
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	///////////////////PIPELINE RENDERIZADO SKYBOX//////////////////
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	///////////////////////////////////////////////////////////////


	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

	///////////////////////////SKYBOX/////////////////////////
	GLuint skyBoxVBO, skyBoxVAO;
	glGenVertexArrays(1, &skyBoxVAO);
	glGenBuffers(1, &skyBoxVBO);
	glBindVertexArray(skyBoxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyBoxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	//Load textures
	vector < const GLchar*> faces;
	faces.push_back("SkyBox/right.jpg");
	faces.push_back("SkyBox/left.jpg");
	faces.push_back("SkyBox/top.jpg");
	faces.push_back("SkyBox/bottom.jpg");
	faces.push_back("SkyBox/back.jpg");
	faces.push_back("SkyBox/front.jpg");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);
	/////////////////////////////////////////////////////////

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);
	
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

		MonitorAnimation();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);



		//Load Model


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

		glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);
		GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "dirlight.position");
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		if (flag == 0) {
			// Directional light
			glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -lightPos.x, -lightPos.y, -lightPos.z);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.0f, 0.0f, 0.0f);

		}
		//dia
		if (flag == 1) {
			// Directional light
			glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -lightPos.x, -lightPos.y, -lightPos.z);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.8f, 0.8f, 0.8f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.1f, 0.1f, 0.1f);

		}



		// Point light 1
		glm::vec3 lightColor;
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);


		if (luz1 == 0) {
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.3f, 0.3f, 0.3f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);

		}
		if (luz1 == 1) {
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.000f, 0.000f, 0.000f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.000f, 0.000f, 0.000f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.001f, 0.001f, 0.001f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.001f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.001f);
		}

		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);

		if (luz2 == 0) {
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.3f, 0.3f, 0.3f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.7f, 0.7f, 0.7f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.1f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.7f);

		}
		if (luz2 == 1) {
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.001f, 0.001f, 0.001f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.001f, 0.001f, 0.001f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.001f, 0.001f, 0.001f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.001f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.001f);

		}


		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		if (luz3 == 0) {
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.3f, 0.3f, 0.3f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.55f, 0.55f, 0.55f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.045f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.075f);
		}

		if (luz3 == 1) {
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.0f);
		}

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);

		if (luz4 == 0) {
			// Point light 4
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.0f, 0.0f, 0.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.0f);

		}

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(1.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 pivotesillas = glm::mat4(1.0f); //Temp
		glm::mat4 pivotecompus = glm::mat4(1.0f); //Temp
		glm::mat4 pTeclado = glm::mat4(1.0f); //Temp
		glm::mat4 CPUpiv = glm::mat4(1.0f); //Temp
		glm::mat4 Rackpiv = glm::mat4(1.0f); //Temp

		glm::mat4 model(1);
		glm::mat4 model1(1);
		glm::mat4 model2(1);
		glm::mat4 moni(1);

		//Carga de modelo 
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model1 = glm::mat4(1);
		model2 = glm::mat4(1);
		moni = glm::mat4(1);

		glm::mat4 tecla = glm::mat4(1);
		glm::mat4 CU = glm::mat4(1);
		glm::mat4 pizarron = glm::mat4(1);
		glm::mat4 puerta = glm::mat4(1);
		glm::mat4 rack = glm::mat4(1.0f);
		glm::mat4 luna = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		//model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));

		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, -1.0f, 0.0f));
		//glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Salon.Draw(lightingShader);
		/*prueba.Draw(lightingShader);*/
	
	if(!nuevo){
		pizarron = model;
		pizarron = glm::scale(pizarron, glm::vec3(0.007f, 0.007f, 0.007f));
		pizarron = glm::rotate(pizarron, glm::radians(180.0f), glm::vec3(.00f, -1.0f, 0.0f));
		pizarron = glm::translate(pizarron, glm::vec3(0.0f, 6.0f, 20.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pizarron));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pizarron));
		pizarra.Draw(lightingShader);

		puerta = model;
		puerta = glm::scale(puerta, glm::vec3(0.1f, 0.1f, 0.1f));
		puerta = glm::translate(puerta, glm::vec3(-0.9f, 0.32f, -1.72f));
		puerta = glm::rotate(puerta, glm::radians(6.8f), glm::vec3(0.0f, 1.0f, 0.0f));
		puerta = glm::scale(puerta, glm::vec3(1.1f, 1.2f, 1.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(puerta));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(puerta));
		Puer.Draw(lightingShader);
		//frente

		modelTemp = model;
		modelTemp = glm::scale(modelTemp, glm::vec3(0.0015f, 0.0015f, 0.0015f));
		modelTemp = glm::translate(modelTemp, glm::vec3(40.0f, 0.0f, -0.0f));
		//modelTemp= glm::rotate(modelTemp, glm::radians(90.0f), glm::vec3(-1.0f, -1.0f, 0.0f));

		model1 = glm::translate(modelTemp, glm::vec3(-50.0f, 0.0f, -20.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		mesa.Draw(lightingShader);


		model1 = glm::translate(modelTemp, glm::vec3(-35.0f, 0.0f, -20.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		mesa.Draw(lightingShader);


		model1 = glm::translate(modelTemp, glm::vec3(23.0f, 0.0f, -20.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		mesa.Draw(lightingShader);

		model1 = glm::translate(modelTemp, glm::vec3(40.0f, 0.0f, -20.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		mesa.Draw(lightingShader);

		//medio
		model1 = glm::translate(modelTemp, glm::vec3(-50.0f, 0.0f, 20.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		mesa.Draw(lightingShader);


		model1 = glm::translate(modelTemp, glm::vec3(-35.0f, 0.0f, 20.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		mesa.Draw(lightingShader);


		model1 = glm::translate(modelTemp, glm::vec3(23.0f, 0.0f, 20.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		mesa.Draw(lightingShader);

		model1 = glm::translate(modelTemp, glm::vec3(40.0f, 0.0f, 20.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		mesa.Draw(lightingShader);

		//atras
		model1 = glm::translate(modelTemp, glm::vec3(-50.0f, 0.0f, 60.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model1));
		mesa.Draw(lightingShader);


		model1 = glm::translate(modelTemp, glm::vec3(-35.0f, 0.0f, 60.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model1));
		mesa.Draw(lightingShader);


		model1 = glm::translate(modelTemp, glm::vec3(23.0f, 0.0f, 60.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model1));
		mesa.Draw(lightingShader);

		model1 = glm::translate(modelTemp, glm::vec3(40.0f, 0.0f, 60.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model1));
		mesa.Draw(lightingShader);


		/*	pivotesillas = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			pivotesillas =glm::translate(model, glm::vec3(-70.0f, 0.0f, -33.0f));
			pivotesillas =glm::rotate(model, glm::radians(90.0f), glm::vec3(.00f, -1.0f, 0.0f));*/


		pivotesillas = model;
		pivotesillas = glm::scale(pivotesillas, glm::vec3(0.0015f, 0.0015f, 0.0015f));
		pivotesillas = glm::translate(pivotesillas, glm::vec3(12.0f, 0.0f, 28.0f));
		pivotesillas = glm::rotate(pivotesillas, glm::radians(90.0f), glm::vec3(.00f, -1.0f, 0.0f));
		//delante izq

		model2 = glm::translate(pivotesillas, glm::vec3(-20.0f, 0.0f, 60.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(-20.0f, 0.0f, 50.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(-20.0f, 0.0f, 32.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(-20.0f, 0.0f, 22.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		//centro izq
		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, 60.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, 50.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, 32.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, 22.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);


		//atras izq
		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, 60.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, 50.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, 32.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, 22.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);
		glBindVertexArray(0);


		//delante der

		model2 = glm::translate(pivotesillas, glm::vec3(-20.0f, 0.0f, -50.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(-20.0f, 0.0f, -40.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(-20.0f, 0.0f, -25.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(-20.0f, 0.0f, -15.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		//centro der
		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, -50.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, -40.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, -25.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, -15.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);


		//atras der
		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, -50.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, -40.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, -25.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, -15.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);
		glBindVertexArray(0);


		/*pivotesillas = model;
		pivotesillas = glm::scale(pivotesillas, glm::vec3(0.0015f, 0.0015f, 0.0015f));
		pivotesillas = glm::translate(pivotesillas, glm::vec3(12.0f, 0.0f, 28.0f));
		pivotesillas = glm::rotate(pivotesillas, glm::radians(90.0f), glm::vec3(.00f, -1.0f, 0.0f));*/

		pivotecompus = model;
		pivotecompus = glm::scale(pivotecompus, glm::vec3(0.0015f, 0.0015f, 0.0015f));
		pivotecompus = glm::translate(pivotecompus, glm::vec3(50.0f, 0.0f, 20.0f));

		float filaa = -40.0f;
		float filab = 0.0f;
		float filac = 40.0f;

		pTeclado = pivotecompus;
		pTeclado = glm::translate(pTeclado, glm::vec3(0.0f, -3.0f, 0.0f));

		CPUpiv = pivotecompus;
		CPUpiv = glm::translate(CPUpiv, glm::vec3(-50.0f, 17.0f, 0.0f));
		CPUpiv = glm::scale(CPUpiv, glm::vec3(0.3f, 0.3f, 0.3f));

		moni = glm::translate(pivotecompus, glm::vec3(-55, 0.0f, filaa));
		moni = glm::scale(moni, glm::vec3(oldMonitorScale, oldMonitorScale, oldMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-55, 0.0f, -50));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);
		///////////////
		moni = glm::translate(pivotecompus, glm::vec3(-55, 0.0f, filab));
		moni = glm::scale(moni, glm::vec3(oldMonitorScale, oldMonitorScale, oldMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-55, 0.0f, -10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);

		///////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(-55, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(oldMonitorScale, oldMonitorScale, oldMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-55, 0.0f, filac - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);
		///////////////////

		moni = glm::translate(pivotecompus, glm::vec3(-30, 0.0f, filaa));
		moni = glm::scale(moni, glm::vec3(oldMonitorScale, oldMonitorScale, oldMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-30, 0.0f, filaa - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);

		/////////////////
		moni = glm::translate(pivotecompus, glm::vec3(-30, 0.0f, filab));
		moni = glm::scale(moni, glm::vec3(oldMonitorScale, oldMonitorScale, oldMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-30, 0.0f, filab - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);
		///////////////
		moni = glm::translate(pivotecompus, glm::vec3(-30, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(oldMonitorScale, oldMonitorScale, oldMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-30, 0.0f, filac - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);

		////////cpus de mesa de adelante
		CU = glm::translate(CPUpiv, glm::vec3(-14.5f * 10, 0.0f, -14.0f * 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		cpu.Draw(lightingShader);
		CU = glm::translate(CPUpiv, glm::vec3(-13.0f * 10, 0.0f, -14.0f * 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		cpu.Draw(lightingShader);

		//////////////////////////CPUS MEDIO IZQ
		CU = glm::translate(CPUpiv, glm::vec3(-14.5f * 10, 0.0f, -1.0f * 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		cpu.Draw(lightingShader);
		CU = glm::translate(CPUpiv, glm::vec3(-13.0f * 10, 0.0f, -1.0f * 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		cpu.Draw(lightingShader);

		////////////////////CPUS atras izq

		CU = glm::translate(CPUpiv, glm::vec3(-14.5f * 10, 0.0f, 12.0f * 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		cpu.Draw(lightingShader);
		CU = glm::translate(CPUpiv, glm::vec3(-13.0f * 10, 0.0f, 12.0f * 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		cpu.Draw(lightingShader);

		//////////////
		moni = glm::translate(pivotecompus, glm::vec3(45, 0.0f, filaa));
		moni = glm::scale(moni, glm::vec3(oldMonitorScale, oldMonitorScale, oldMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(45, 0.0f, filaa - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);
		////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(45, 0.0f, filab));
		moni = glm::scale(moni, glm::vec3(oldMonitorScale, oldMonitorScale, oldMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(45, 0.0f, filab - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);
		///////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(45, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(oldMonitorScale, oldMonitorScale, oldMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(45, 0.0f, filac - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);
		////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(17, 0.0f, filaa));
		moni = glm::scale(moni, glm::vec3(oldMonitorScale, oldMonitorScale, oldMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(17, 0.0f, filaa - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);

		////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(17, 0.0f, filab));
		moni = glm::scale(moni, glm::vec3(oldMonitorScale, oldMonitorScale, oldMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(17, 0.0f, filab - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);

		///////////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(17, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(oldMonitorScale, oldMonitorScale, oldMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(17, 0.0f, filac - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);
		/////////////////////////

		////////cpus de mesa de adelante
		CU = glm::translate(CPUpiv, glm::vec3(11.0f * 10, 0.0f, -14.0f * 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		cpu.Draw(lightingShader);
		CU = glm::translate(CPUpiv, glm::vec3(9.5f * 10, 0.0f, -14.0f * 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		cpu.Draw(lightingShader);

		//////////////////////////CPUS MEDIO IZQ
		CU = glm::translate(CPUpiv, glm::vec3(11.0f * 10, 0.0f, -1.0f * 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		cpu.Draw(lightingShader);
		CU = glm::translate(CPUpiv, glm::vec3(9.5f * 10, 0.0f, -1.0f * 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		cpu.Draw(lightingShader);

		////////////////////CPUS atras izq

		CU = glm::translate(CPUpiv, glm::vec3(11.0f * 10, 0.0f, 12.0f * 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		cpu.Draw(lightingShader);
		CU = glm::translate(CPUpiv, glm::vec3(9.5f * 10, 0.0f, 12.0f * 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		cpu.Draw(lightingShader);



	}
	else {
		pizarron = model;
		pizarron = glm::scale(pizarron, glm::vec3(0.012f, 0.012f, 0.012f));
		pizarron = glm::rotate(pizarron, glm::radians(0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		pizarron = glm::translate(pizarron, glm::vec3(6.5f, 1.0f, -12.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pizarron));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pizarron));
		tele.Draw(lightingShader);

		puerta = model;
		puerta = glm::scale(puerta, glm::vec3(0.1f, 0.1f, 0.1f));
		puerta = glm::translate(puerta, glm::vec3(-0.9f, 0.32f, -1.72f));
		puerta = glm::rotate(puerta, glm::radians(6.8f), glm::vec3(0.0f, 1.0f, 0.0f));
		puerta = glm::scale(puerta, glm::vec3(1.1f, 1.2f, 1.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(puerta));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(puerta));
		Puer.Draw(lightingShader);
		//frente

		modelTemp = model;
		modelTemp = glm::scale(modelTemp, glm::vec3(0.08f, 0.08f, 0.08f));
		modelTemp = glm::translate(modelTemp, glm::vec3(0.0f,0.13f, 0.0f));
		//modelTemp= glm::rotate(modelTemp, glm::radians(90.0f), glm::vec3(-1.0f, -1.0f, 0.0f));

		model1 = glm::translate(modelTemp, glm::vec3(-1.02f, 0.0f, -0.65f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		escritorio.Draw(lightingShader);


		model1 = glm::translate(modelTemp, glm::vec3(-0.5f, 0.0f, -0.64f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		escritorio.Draw(lightingShader);


		model1 = glm::translate(modelTemp, glm::vec3(0.96f, 0.0f, -0.62f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		escritorio.Draw(lightingShader);

		model1 = glm::translate(modelTemp, glm::vec3(0.44f, 0.0f, -0.64f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		escritorio.Draw(lightingShader);

		//medio
		model1 = glm::translate(modelTemp, glm::vec3(-1.02f, 0.0f, 0.05f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		escritorio.Draw(lightingShader);


		model1 = glm::translate(modelTemp, glm::vec3(-0.5f, 0.0f, 0.06f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		escritorio.Draw(lightingShader);


		model1 = glm::translate(modelTemp, glm::vec3(0.96f, 0.0f, 0.07f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		escritorio.Draw(lightingShader);

		model1 = glm::translate(modelTemp, glm::vec3(0.44f, 0.0f, 0.06f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		escritorio.Draw(lightingShader);

		//atras
		model1 = glm::translate(modelTemp, glm::vec3(-1.02f, 0.0f, 0.8f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model1));
		escritorio.Draw(lightingShader);


		model1 = glm::translate(modelTemp, glm::vec3(-0.5f, 0.0f, 0.81f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model1));
		escritorio.Draw(lightingShader);


		model1 = glm::translate(modelTemp, glm::vec3(0.96f, 0.0f, 0.83f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model1));
		escritorio.Draw(lightingShader);

		model1 = glm::translate(modelTemp, glm::vec3(0.44f, 0.0f, 0.82f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model1));
		escritorio.Draw(lightingShader);


		float fSn1 = -1.0f;
		float fSn2 = 3.0f;
		float fSn3 = 7.0f;

		
		pivotesillas = model;
		pivotesillas = glm::scale(pivotesillas, glm::vec3(0.015f, 0.015f, 0.015f));
		pivotesillas = glm::translate(pivotesillas, glm::vec3(0.0f, 0.0f, 0.0f));
		pivotesillas = glm::rotate(pivotesillas, glm::radians(90.0f), glm::vec3(.00f, -1.0f, 0.0f));
		//delante izq

		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, 6.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, 5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, 3.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, 2.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		//centro izq
		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, 6.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, 5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);
		
		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, 3.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, 2.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);


		//atras izq
		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, 6.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, 5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, 3.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, 2.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);
		glBindVertexArray(0);


		//delante der

		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, -5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, -4.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, -2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		//centro der
		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, -5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, -4.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, -2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);


		//atras der
		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, -5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, -4.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, -2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla2.Draw(lightingShader);
		glBindVertexArray(0);


		/*pivotesillas = model;
		pivotesillas = glm::scale(pivotesillas, glm::vec3(0.0015f, 0.0015f, 0.0015f));
		pivotesillas = glm::translate(pivotesillas, glm::vec3(12.0f, 0.0f, 28.0f));
		pivotesillas = glm::rotate(pivotesillas, glm::radians(90.0f), glm::vec3(.00f, -1.0f, 0.0f));*/

		pivotecompus = model;
		pivotecompus = glm::scale(pivotecompus, glm::vec3(0.0010f, 0.0010f, 0.0010f));
		pivotecompus = glm::translate(pivotecompus, glm::vec3(0.0f, 21.0f, 0.0f));

		float filaa = -30.5f;
		float filab = 24.0f;
		float filac = 85.0f;

		float colca = -81.0f;
		float colcb = -40.0f;
		float colcc = 37.0f;
		float colcd = 76.0f;
		pTeclado = pivotecompus;
		pTeclado = glm::translate(pTeclado, glm::vec3(0.0f, 0.0f, 0.0f));
		pTeclado = glm::scale(pTeclado, glm::vec3(0.375f, 0.375f, 0.375f));

		/*CPUpiv = pivotecompus;
		CPUpiv = glm::translate(CPUpiv, glm::vec3(-50.0f, 17.0f, 0.0f));
		CPUpiv = glm::scale(CPUpiv, glm::vec3(0.1f, 0.1f, 0.1f));*/

		moni = glm::translate(pivotecompus, glm::vec3(colca, 0.0f, filaa));
		moni = glm::scale(moni, glm::vec3(newMonitorScale, newMonitorScale, newMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-230.0f, 0.0f, -75));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);
		///////////////
		moni = glm::translate(pivotecompus, glm::vec3(colca, 0.0f, filab));
		moni = glm::scale(moni, glm::vec3(newMonitorScale, newMonitorScale, newMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-230, 0.0f,80));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);

		///////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(colca, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(newMonitorScale, newMonitorScale, newMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-230, 0.0f,240));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);
		///////////////////

		moni = glm::translate(pivotecompus, glm::vec3(colcb, 0.0f, filaa));
		moni = glm::scale(moni, glm::vec3(newMonitorScale, newMonitorScale, newMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-115, 0.0f, -75));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);

		/////////////////
		moni = glm::translate(pivotecompus, glm::vec3(colcb, 0.0f, filab));
		moni = glm::scale(moni, glm::vec3(newMonitorScale, newMonitorScale, newMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-115, 0.0f, 80));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);
		///////////////
		moni = glm::translate(pivotecompus, glm::vec3(colcb, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(newMonitorScale, newMonitorScale, newMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-115, 0.0f, 240));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);

		////////cpus de mesa de adelante
		/*CU = glm::translate(CPUpiv, glm::vec3(-14.5f * 10, 0.0f, -14.0f * 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		cpu.Draw(lightingShader);
		CU = glm::translate(CPUpiv, glm::vec3(-13.0f * 10, 0.0f, -14.0f * 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		cpu.Draw(lightingShader);*/

		////////////////////////////CPUS MEDIO IZQ
		//CU = glm::translate(CPUpiv, glm::vec3(-14.5f * 10, 0.0f, -1.0f * 10));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//cpu.Draw(lightingShader);
		//CU = glm::translate(CPUpiv, glm::vec3(-13.0f * 10, 0.0f, -1.0f * 10));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//cpu.Draw(lightingShader);

		//////////////////////CPUS atras izq

		//CU = glm::translate(CPUpiv, glm::vec3(-14.5f * 10, 0.0f, 12.0f * 10));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//cpu.Draw(lightingShader);
		//CU = glm::translate(CPUpiv, glm::vec3(-13.0f * 10, 0.0f, 12.0f * 10));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//cpu.Draw(lightingShader);

		//////////////
		moni = glm::translate(pivotecompus, glm::vec3(colcd, 0.0f, filaa));
		moni = glm::scale(moni, glm::vec3(newMonitorScale, newMonitorScale, newMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(200, 0.0f, -75));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);
		////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(colcd, 0.0f, filab));
		moni = glm::scale(moni, glm::vec3(newMonitorScale, newMonitorScale, newMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(200, 0.0f, 80));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);
		///////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(colcd, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(newMonitorScale, newMonitorScale, newMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(200, 0.0f, 240));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);
		////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(colcc, 0.0f, filaa));
		moni = glm::scale(moni, glm::vec3(newMonitorScale, newMonitorScale, newMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(90, 0.0f, -75));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);

		////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(colcc, 0.0f, filab));
		moni = glm::scale(moni, glm::vec3(newMonitorScale, newMonitorScale, newMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(90, 0.0f, 80));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);

		///////////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(colcc, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(newMonitorScale, newMonitorScale, newMonitorScale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(90, 0.0f, 240));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);
		/////////////////////////
		//Rackpiv = model;
		//Rackpiv = glm::scale(Rackpiv, glm::vec3(0.0015f, 0.0015f, 0.0015f));
		rack = model;
		
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(rack));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		rack = glm::scale(rack, glm::vec3(0.05f, 0.05f, 0.05f));
		rack = glm::translate(rack, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(rack));
		servidor.Draw(lightingShader);
		glBindVertexArray(0);

		
		
	

		//////////cpus de mesa de adelante
		//CU = glm::translate(CPUpiv, glm::vec3(11.0f * 10, 0.0f, -14.0f * 10));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//cpu.Draw(lightingShader);
		//CU = glm::translate(CPUpiv, glm::vec3(9.5f * 10, 0.0f, -14.0f * 10));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//cpu.Draw(lightingShader);

		////////////////////////////CPUS MEDIO IZQ
		//CU = glm::translate(CPUpiv, glm::vec3(11.0f * 10, 0.0f, -1.0f * 10));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//cpu.Draw(lightingShader);
		//CU = glm::translate(CPUpiv, glm::vec3(9.5f * 10, 0.0f, -1.0f * 10));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//cpu.Draw(lightingShader);

		//////////////////////CPUS atras izq

		//CU = glm::translate(CPUpiv, glm::vec3(11.0f * 10, 0.0f, 12.0f * 10));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//cpu.Draw(lightingShader);
		//CU = glm::translate(CPUpiv, glm::vec3(9.5f * 10, 0.0f, 12.0f * 10));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
		//cpu.Draw(lightingShader);


	}
	
		/* Also draw the lamp object, again binding the appropriate shader*/
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(lightPos.x, lightPos.y, lightPos.z));
		model = glm::scale(model, glm::vec3(0.003f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Moon.Draw(lampShader);
		glBindVertexArray(VAO);
	
		glBindVertexArray(0);

		// Draw skybox as last
		glDepthFunc(GL_LEQUAL); //hace que no interfiera con otros objetos //Función de profundidad
		skyboxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(skyboxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(skyBoxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);


		// Swap the buffers
		glDeleteVertexArrays(1, &VAO);
		glfwSwapBuffers(window);

	}
	/////////////////Borramos buffers/////////////////
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &skyBoxVAO);
	glDeleteBuffers(1, &skyBoxVAO);


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

	if (keys[GLFW_KEY_T])
	{
		pointLightPositions[2].x += 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[2].x -= 0.01f;
	}

	if (keys[GLFW_KEY_Y])
	{
		pointLightPositions[2].y += 0.01f;
	}

	if (keys[GLFW_KEY_H])
	{
		pointLightPositions[2].y -= 0.01f;
	}
	if (keys[GLFW_KEY_U])
	{
		pointLightPositions[2].z -= 0.01f;
	}
	if (keys[GLFW_KEY_J])
	{
		pointLightPositions[2].z += 0.01f;
	}

	if (keys[GLFW_KEY_1]) {

		luz1 = 0;

		
	}
	if (keys[GLFW_KEY_2]) {

		luz1 = 1;


	}
	if (keys[GLFW_KEY_3]) {

		luz2 = 0;


	}
	if (keys[GLFW_KEY_4]) {

		luz2 = 1;


	}
	if (keys[GLFW_KEY_5]) {
		luz3 = 0;
	}
	if (keys[GLFW_KEY_6]) {
		luz3 = 1;
	}

	/*if (keys[GLFW_KEY_7]) {
		nuevo = 0;
	}
	if (keys[GLFW_KEY_8]) {
		nuevo = 1;
	}*/
	
	if (keys[GLFW_KEY_O])
	{

		if (lightPos.z == 5.0 && lightPos.y >=0) {
			if (flag == 0) {
				flag = 1;
			}
			else {
				flag = 0;
			}
			cont = 0;
		}
		if (lightPos.y >= 0) {
			if (lightPos.z >= 0.0) {
				lightPos.z -= 0.1;
				lightPos.y += 0.1;

			}
			if (lightPos.z < 0.0 ) {
				lightPos.z -= 0.1;
				lightPos.y -= 0.1;

			}
		}
		
		if (lightPos.y < 0) {

			if (lightPos.z < 0.0) {
				lightPos.z += 0.1;
				lightPos.y -= 0.1;
				
			}
			if (lightPos.z >= 0.0) {
				lightPos.z += 0.1;
				lightPos.y += 0.1;
				
			}
		}

		
	}

	if (keys[GLFW_KEY_X])
	{

		flag = 0;
	}
	if (keys[GLFW_KEY_Z])
	{

		flag =1;
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_L && GLFW_PRESS == action)
	{
		if (play == false && (FrameIndex > 1))
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}

	}

	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		// Tecla 'M' para iniciar/reiniciar la animación de monitores
		monitorAnimationActive = true;
		monitorAnimationState = 0;
		oldMonitorScale = 1.0f;
		newMonitorScale = 0.0f;
		monitorAnimFrame = 0;
		nuevo = 0; // Asegurar que empezamos mostrando el laboratorio viejo
	}

	if (key == GLFW_KEY_K && GLFW_PRESS == action)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame(); //Almacena cada frame
		}

	}

	if (key == GLFW_KEY_Q && GLFW_PRESS == action) {
		SaveAnimation();  // Guarda la animación en "Animacion.txt"
	}

	if (key == GLFW_KEY_R && GLFW_PRESS == action) {

		resetElements();  // Resetear los elementos a los primeros keyframes cargados
		LoadAnimation(); //Carga la animación por medio del archivo previamente guardado
		PrintAnimation(); //Imprime en terminar los valores del archivo
	}

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

void Animation() {

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			dogPosX += KeyFrame[playIndex].incX;
			dogPosY += KeyFrame[playIndex].incY;
			dogPosZ += KeyFrame[playIndex].incZ;
			head += KeyFrame[playIndex].headInc;
			tail += KeyFrame[playIndex].tailInc;
			FLegsL += KeyFrame[playIndex].FLegsLInc;
			FLegsR += KeyFrame[playIndex].FLegsRInc;
			RLegs += KeyFrame[playIndex].RLegsInc;
			FLegs += KeyFrame[playIndex].FLegsInc;
			rotDog += KeyFrame[playIndex].rotDogInc;
			rotDogX += KeyFrame[playIndex].rotDogXInc;

			i_curr_steps++;
		}

	}

}

void MonitorAnimation() {
	if (!monitorAnimationActive) return;

	// Ya estamos en laboratorio nuevo pero seguimos mostrando la animación de monitores
	if (nuevo == 1) {
		// Transición de monitores viejos a monitores nuevos (en lab nuevo)
		if (monitorAnimationState == 1) {
			// En el lab nuevo, empezamos con los monitores ocultos y los hacemos aparecer
			newMonitorScale = (float)monitorAnimFrame / MONITOR_ANIM_MAX_FRAMES;

			monitorAnimFrame++;
			if (monitorAnimFrame >= MONITOR_ANIM_MAX_FRAMES) {
				// La animación ha terminado
				monitorAnimationActive = false;
				newMonitorScale = 1.0f;  // Monitores nuevos completamente visibles
			}
		}
	}
	else {
		// Todavía estamos en laboratorio viejo, hacemos la transición normal
		if (monitorAnimationState == 0) {
			// Desvaneciendo monitores viejos
			oldMonitorScale = 1.0f - ((float)monitorAnimFrame / (MONITOR_ANIM_MAX_FRAMES * 3));

			monitorAnimFrame++;
			if (monitorAnimFrame >= MONITOR_ANIM_MAX_FRAMES * 3) {
				monitorAnimFrame = 0;
				monitorAnimationState = 1;

				// Aquí cambiamos al laboratorio nuevo justo después de desvanecer los viejos
				oldMonitorScale = 0.0f;
				newMonitorScale = 0.0f;  // Empezamos con monitores nuevos ocultos
				nuevo = 1;  // Cambiamos al laboratorio nuevo
			}
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