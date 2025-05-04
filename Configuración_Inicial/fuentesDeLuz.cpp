/* PROYECTO DE COMPUTACI�N GR�FICA E INTERACCI�N HUMANO COMPUTADORA
* SEMESTRE 2025-2
* EQUIPO 9
* INTEGRANTES:
* Berdejo Guzm�n Leonardo Ariel
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
void Animation();

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

int flagg = 1;
int luz1 = 0;
int luz2 = 0;
int luz3 = 0;
int luz4 = 0;
int cont = 0;

bool nuevo = 0;
// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(-0.060000f,0.790000f,-1.080001f),
	glm::vec3(-0.060000f,0.790000f,0.059998f),
	glm::vec3(-0.060000f,0.790000f,1.129997f),
	glm::vec3(-0.070000f,0.470000f,-1.020001f)
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

// Variables para la animaci�n de monitores
bool monitorAnimationActive = false;  // Indica si la animaci�n est� activa
int monitorAnimationState = 0;  // 0: monitores viejos, 1: transici�n, 2: monitores nuevos
float oldMonitorScale = 1.0f;  // Escala para monitores viejos
float newMonitorScale = 0.0f;  // Escala para monitores nuevos
int monitorAnimFrame = 0;  // Frame actual de la animaci�n
const int MONITOR_ANIM_MAX_FRAMES = 60;  // Total de frames para cada transici�n
//////////////////////////////////// INICIO FRAMES ///////////////////////////////
//Anim
float rotBall = 0.0f;
float rotDog = 0.0f;
float rotDogX = 0; //Variable para rotaci�n
int dogAnim = 0;
float FLegs = 0.0f;
float FLegsL = 0.0f;
float FLegsR = 0.0f;
float RLegs = 0.0f;
float head = 0.0f;
float tail = 0.0f;

float radio = 0.0f;  // Radio del c�rculo
float angle = 0.0f;  // �ngulo inicial
bool moveRot = false;
float speed = 0.0001f;

float humoPosX = 0.0f, humoPosY=10.0f, humoPosZ=0.0f;
float rotatehumo=0.0f;
float sizehumoxz =0.0004, sizehumoy= 0.0012;
int part=0;
float contadorhumo1=0.0;
float contadorhumo2=0.0;
float contadorhumo3 = 0.0;
float contadorhumo4 = 0.0;
float contadorhumo5 = 0.0;
float contadorhumo6 = 0.0;
float contadorhumo7 = 0.0;
float contadorhumo8 = 0.0;
float contadorhumo9 = 0.0;
float contadorhumo10 = 0.0;
float rhumo = 0.0f;

int monitores = 0;
float monitor1 =1.0f;
float monitor2 = 1.0f;
float monitor3 = 1.0f;
float monitor4 = 1.0f;
float monitor5 = 1.0f;
float monitor6 = 1.0f;
float monitor7 = 1.0f;
float monitor8 = 1.0f;
float monitor9 = 1.0f;
float monitor10 = 1.0f;
float monitor11 = 1.0f;
float monitor12 = 1.0f;

float silla1 = 1.0f;
float silla222 = 1.0f;
float silla3 = 1.0f;
float silla4 = 1.0f;
float silla5 = 1.0f;
float silla6 = 1.0f;
float silla7 = 1.0f;
float silla8 = 1.0f;
float silla9 = 1.0f;
float silla10 = 1.0f;
float silla11 = 1.0f;
float silla12 = 1.0f;
float silla13 = 1.0f;
float silla14 = 1.0f;
float silla15 = 1.0f;
float silla16 = 1.0f;
float silla17 = 1.0f;
float silla18 = 1.0f;
float silla19 = 1.0f;
float silla20 = 1.0f;
float silla21 = 1.0f;
float silla22 = 1.0f;
float silla23 = 1.0f;
float silla24 = 1.0f;


//Modificar estos KeyFrames pues es para cada animaci�n
float dogPosX, dogPosY, dogPosZ;

#define MAX_FRAMES 50
int i_max_steps = 190;
int i_curr_steps = 0;
float mx = 0, my = 0, mz = 0;
//-----------------------Definici�n de la estructura para los KeyFrames-----------------------
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
	//Variables para la rotaci�n
	float rotDogX;
	float rotDogXInc;

	
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//En qu� lugar de la l�nea de tiempo me encuentro al guardar los datos
bool play = false;			//Si se est� reproduciendo la animaci�n
int playIndex = 0;			//En qu� lugar de la l�nea de tiempo me encuentro al estar reproduciendo la animaci�n
bool humoflag = false;
//flag1
struct Particle {
	glm::vec3 position;
	glm::vec3 size;
	float rotation;
};
Particle H[5];
void spawnParticle(int i,float x,float y, float z, float sizehumoxz, float sizehumoy,float rotation) {
	Particle p;
	p.position = glm::vec3(x, y, z); // Punto de origen
	p.size = glm::vec3(sizehumoxz, sizehumoy, sizehumoxz); // Punto de origen
	p.rotation = rotation;
	H[i] = p;
}

//void updateParticles(float deltaTime) {
//	for (auto& p : particles) {
//		p.life -= deltaTime;
//		if (p.life > 0.0f) {
//			p.position += p.velocity * deltaTime;
//		}
//	}
//	// Eliminar part�culas muertas
//	particles.erase(std::remove_if(particles.begin(), particles.end(),
//		[](const Particle& p) { return p.life <= 0.0f; }), particles.end());
//}
void renderParticles(glm::mat4 hum) {
	
	

}

// Funci�n para guardar la animaci�n
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

// Funci�n para cargar los KeyFrames
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

// Funci�n para imprimir el contenido del archivo .txt en consola
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
	for (int i = 0; i <= 4; i++) {
		spawnParticle(i, humoPosX, humoPosY, humoPosZ, sizehumoy, sizehumoy, rotatehumo);
	}
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

	Model Salon((char*)"Models/Salon1/salon.obj");
	Model ventanas((char*)"Models/Salon1/VentanaSalon.obj");

	Model mesa((char*)"Models/mesa/mesa.obj");
	Model silla((char*)"Models/chair1/chair1.obj");
	Model monitor((char*)"Models/monitor/monitor.obj");
	Model teclado((char*)"Models/keyboard/keyboard.obj");
	Model mouse((char*)"Models/mouse/mouse.obj");
	Model cpu((char*)"Models/CPU/CPU.obj");
	Model pizarra((char*)"Models/pizarra/pizarra.obj");
	Model Puer((char*)"Models/puertaA/puertaAzul.obj");
	Model neon((char*)"Models/TirasAzules/TirasAzules.obj");

	Model humo((char*)"Models/humo/humo.obj");
	Model escritorio((char*)"Models/mesanueva/model.obj");
	Model tele((char*)"Models/Tele/Tele.obj");
	Model tecladoled((char*)"Models/Led_Teclado/Teclado.obj");
	Model silla2((char*)"Models/GamerChair/GamerChair.obj");
	Model moniGamer((char*)"Models/MonitorNew/model.obj");
	Model servidor((char*)"Models/Rack/rackOld.obj");
	Model servidor2((char*)"Models/Rack/rackNew.obj");
	Model lampara((char*)"Models/lamp/lamp.obj");

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
		Animation();

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





		// Point light 1
		glm::vec3 lightColor;
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);


		if (!nuevo) {
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.4f, 0.4f, 0.4f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.4f, 0.4f, 0.4);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.01f, 0.01f, 0.01f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);

		

			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.4f, 0.4f, 0.4f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.4f, 0.4f, 0.4f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.1f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.7f);

		

			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.4f, 0.4f, 0.4f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.4f, 0.4f, 0.4f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.045f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.075f);

			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.001f, 0.001f, 0.001f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.001f, 0.001f, 0.001f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.001f, 0.001f, 0.001f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.001f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.001f);
		}

		
		if (nuevo == 1) {
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.01f, 0.01f, 0.01f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);



			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.1f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.7f);



			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.045f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.075f);

			// Point light 4
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.1f, 0.1f, 0.25f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.4f, 0.4f, 0.4f);
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
		glm::mat4 modelVentana(1);
		glm::mat4 model1(1);
		glm::mat4 model2(1);
		glm::mat4 moni(1);

		//Carga de modelo 
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		modelVentana = glm::mat4(1);
		model1 = glm::mat4(1);
		model2 = glm::mat4(1);
		moni = glm::mat4(1);

		glm::mat4 pivlamp = glm::mat4(1);
		glm::mat4 lamp = glm::mat4(1);
		glm::mat4 tecla = glm::mat4(1);
		glm::mat4 CU = glm::mat4(1);
		glm::mat4 pizarron = glm::mat4(1);
		glm::mat4 puerta = glm::mat4(1);
		glm::mat4 rack = glm::mat4(1.0f);
		glm::mat4 rack2 = glm::mat4(1.0f);
		glm::mat4 hum = glm::mat4(1);

		glm::mat4 neon1 = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Salon.Draw(lightingShader);

		puerta = model;
		puerta = glm::translate(puerta, glm::vec3(0.001f, 0.001f, 0.0f));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(puerta));
		Puer.Draw(lightingShader);
		//frente
	
	if(!nuevo){
		humoPosX = 0;
		humoPosY = 1.0 * 10 * 0.0012;
		humoPosZ = 0;

		pivlamp = model;
		pivlamp = glm::translate(pivlamp, glm::vec3(0.0f, 0.035f, 0.0f));
		lamp = glm::translate(pivlamp, glm::vec3(0.0f, 0.0f, -0.14f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(lamp));
		lampara.Draw(lightingShader);

		lamp = glm::translate(pivlamp, glm::vec3(0.0f, 0.0f, 0.07f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(lamp));
		lampara.Draw(lightingShader);

		lamp = glm::translate(pivlamp, glm::vec3(0.0f, 0.0f, -0.04f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(lamp));
		lampara.Draw(lightingShader);

		pizarron = model;
		pizarron = glm::scale(pizarron, glm::vec3(0.007f, 0.007f, 0.007f));
		pizarron = glm::rotate(pizarron, glm::radians(180.0f), glm::vec3(.00f, -1.0f, 0.0f));
		pizarron = glm::translate(pizarron, glm::vec3(0.0f, 6.0f, 20.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pizarron));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pizarron));
		pizarra.Draw(lightingShader);

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
		model2 = glm::scale(model2, glm::vec3(silla1, silla1, silla1));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(-20.0f, 0.0f, 50.0f));
		model2 = glm::scale(model2, glm::vec3(silla222, silla222, silla222));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(-20.0f, 0.0f, 32.0f));
		model2 = glm::scale(model2, glm::vec3(silla3, silla3, silla3));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(-20.0f, 0.0f, 22.0f));
		model2 = glm::scale(model2, glm::vec3(silla4, silla4, silla4));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		//centro izq
		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, 60.0f));
		model2 = glm::scale(model2, glm::vec3(silla5, silla5, silla5));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, 50.0f));
		model2 = glm::scale(model2, glm::vec3(silla6, silla6, silla6));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, 32.0f));
		model2 = glm::scale(model2, glm::vec3(silla7, silla7, silla7));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, 22.0f));
		model2 = glm::scale(model2, glm::vec3(silla8, silla8, silla8));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);


		//atras izq
		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, 60.0f));
		model2 = glm::scale(model2, glm::vec3(silla9, silla9, silla9));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, 50.0f));
		model2 = glm::scale(model2, glm::vec3(silla10, silla10, silla10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, 32.0f));
		model2 = glm::scale(model2, glm::vec3(silla11, silla11, silla11));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, 22.0f));
		model2 = glm::scale(model2, glm::vec3(silla12, silla12, silla12));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla.Draw(lightingShader);



		//delante der

		
		// Delante der
		model2 = glm::translate(pivotesillas, glm::vec3(-20.0f, 0.0f, -50.0f));
		model2 = glm::scale(model2, glm::vec3(silla13, silla13, silla13));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(-20.0f, 0.0f, -40.0f));
		model2 = glm::scale(model2, glm::vec3(silla14, silla14, silla14));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(-20.0f, 0.0f, -25.0f));
		model2 = glm::scale(model2, glm::vec3(silla15, silla15, silla15));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(-20.0f, 0.0f, -15.0f));
		model2 = glm::scale(model2, glm::vec3(silla16, silla16, silla16));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla.Draw(lightingShader);

		// Centro der
		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, -50.0f));
		model2 = glm::scale(model2, glm::vec3(silla17, silla17, silla17));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, -40.0f));
		model2 = glm::scale(model2, glm::vec3(silla18, silla18, silla18));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, -25.0f));
		model2 = glm::scale(model2, glm::vec3(silla19, silla19, silla19));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(20.0f, 0.0f, -15.0f));
		model2 = glm::scale(model2, glm::vec3(silla20, silla20, silla20));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla.Draw(lightingShader);

		// Atrás der
		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, -50.0f));
		model2 = glm::scale(model2, glm::vec3(silla21, silla21, silla21));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, -40.0f));
		model2 = glm::scale(model2, glm::vec3(silla22, silla22, silla22));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, -25.0f));
		model2 = glm::scale(model2, glm::vec3(silla23, silla23, silla23));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(60.0f, 0.0f, -15.0f));
		model2 = glm::scale(model2, glm::vec3(silla24, silla24, silla24));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla.Draw(lightingShader);



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

		moni = glm::translate(pivotecompus, glm::vec3(-55/monitor1, 0.0f, filaa/monitor1));
		moni = glm::scale(moni, glm::vec3(monitor1, monitor1, monitor1));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-55, 0.0f, -50));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);

		///////////////
		moni = glm::translate(pivotecompus, glm::vec3(-55/monitor2, 0.0f, filab / monitor2));
		moni = glm::scale(moni, glm::vec3(monitor2, monitor2, monitor2));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-55, 0.0f, -10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);

		///////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(-55, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(monitor3, monitor3, monitor3));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-55, 0.0f, filac - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);

		///////////////////

		moni = glm::translate(pivotecompus, glm::vec3(-30, 0.0f, filaa));
		moni = glm::scale(moni, glm::vec3(monitor4, monitor4, monitor4));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-30, 0.0f, filaa - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);

		/////////////////
		moni = glm::translate(pivotecompus, glm::vec3(-30, 0.0f, filab));
		moni = glm::scale(moni, glm::vec3(monitor5, monitor5, monitor5));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-30, 0.0f, filab - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);

		///////////////
		moni = glm::translate(pivotecompus, glm::vec3(-30, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(monitor6, monitor6, monitor6));
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
		if (humoflag) {
			/*humoPosX= 10.0f*10 ;
			humoPosY=3*10 *0.0012;
			humoPosZ= -10.0f*10 * 0.0004;*/
			for (int i = 0; i <= 3; i++) {
				hum = CU;
				glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				hum = glm::scale(hum, H[i].size / 0.0009f);
				hum = glm::translate(hum, H[i].position);
				hum = glm::rotate(hum, glm::radians(rhumo), glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(hum));
				glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(hum));
				humo.Draw(lightingShader);
				glDisable(GL_BLEND);

			}
		}
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
		moni = glm::scale(moni, glm::vec3(monitor7,monitor7, monitor7));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(45, 0.0f, filaa - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);

		////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(45, 0.0f, filab));
		moni = glm::scale(moni, glm::vec3(monitor8, monitor8, monitor8));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(45, 0.0f, filab - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);

		///////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(45, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(monitor9, monitor9, monitor9));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(45, 0.0f, filac - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);

		////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(17, 0.0f, filaa));
		moni = glm::scale(moni, glm::vec3(monitor10, monitor10, monitor10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(17, 0.0f, filaa - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);

		////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(17, 0.0f, filab));
		moni = glm::scale(moni, glm::vec3(monitor11, monitor11, monitor11));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		monitor.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(17, 0.0f, filab - 10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		teclado.Draw(lightingShader);

		///////////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(17, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(monitor12, monitor12, monitor12));
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

		if (humoflag) {
			/*humoPosX= 10.0f*10 ;
			humoPosY=3*10 *0.0012;
			humoPosZ= -10.0f*10 * 0.0004;*/
			for (int i = 0; i <= 3; i++) {
				hum = CU;
				glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				hum = glm::scale(hum, H[i].size/0.0010f);
				hum = glm::translate(hum, H[i].position);
				hum = glm::rotate(hum, glm::radians(rhumo), glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(hum));
				glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(hum));
				humo.Draw(lightingShader);
				glDisable(GL_BLEND);

			}
		}

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

		rack = model;
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(rack));
		servidor.Draw(lightingShader);
		glBindVertexArray(0);
	}
	else {
		neon1 = model; 
		// -1.449999, 5.760037, -2.889998
		neon1 = glm::scale(neon1, glm::vec3(0.02f, 0.012f, 0.05f));
		neon1 = glm::translate(neon1, glm::vec3(-3.179997, 4.640011, -2.899998));
		neon1 = glm::rotate(neon1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		neon1 = glm::rotate(neon1, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(neon1));
		neon.Draw(lightingShader);

		neon1 = model;
		neon1 = glm::scale(neon1, glm::vec3(0.02f, 0.012f, 0.05f));
		neon1 = glm::translate(neon1, glm::vec3(3.549997, 4.670012, -2.849998));
		neon1 = glm::rotate(neon1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		neon1 = glm::rotate(neon1, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, -1.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(neon1));
		neon.Draw(lightingShader);

		pizarron = model;
		pizarron = glm::scale(pizarron, glm::vec3(0.012f, 0.012f, 0.012f));
		pizarron = glm::rotate(pizarron, glm::radians(0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		pizarron = glm::translate(pizarron, glm::vec3(6.5f, 1.0f, -12.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pizarron));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pizarron));
		tele.Draw(lightingShader);

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

// FILA IZQUIERDA

// Delante izq
		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, 6.0f));
		model2 = glm::scale(model2, glm::vec3(silla1, silla1, silla1));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, 5.0f));
		model2 = glm::scale(model2, glm::vec3(silla222, silla222, silla222));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, 3.2f));
		model2 = glm::scale(model2, glm::vec3(silla3, silla3, silla3));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, 2.2f));
		model2 = glm::scale(model2, glm::vec3(silla4, silla4, silla4));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		// Centro izq
		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, 6.0f));
		model2 = glm::scale(model2, glm::vec3(silla5, silla5, silla5));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, 5.0f));
		model2 = glm::scale(model2, glm::vec3(silla6, silla6, silla6));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, 3.2f));
		model2 = glm::scale(model2, glm::vec3(silla7, silla7, silla7));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, 2.2f));
		model2 = glm::scale(model2, glm::vec3(silla8, silla8, silla8));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		// Atrás izq
		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, 6.0f));
		model2 = glm::scale(model2, glm::vec3(silla9, silla9, silla9));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, 5.0f));
		model2 = glm::scale(model2, glm::vec3(silla10, silla10, silla10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, 3.2f));
		model2 = glm::scale(model2, glm::vec3(silla11, silla11, silla11));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, 2.2f));
		model2 = glm::scale(model2, glm::vec3(silla12, silla12, silla12));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		// FILA DERECHA

		// Delante der
		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, -5.0f));
		model2 = glm::scale(model2, glm::vec3(silla13, silla13, silla13));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, -4.0f));
		model2 = glm::scale(model2, glm::vec3(silla14, silla14, silla14));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, -2.0f));
		model2 = glm::scale(model2, glm::vec3(silla15, silla15, silla15));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, -1.5f));
		model2 = glm::scale(model2, glm::vec3(silla16, silla16, silla16));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		// Centro der
		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, -5.0f));
		model2 = glm::scale(model2, glm::vec3(silla17, silla17, silla17));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, -4.0f));
		model2 = glm::scale(model2, glm::vec3(silla18, silla18, silla18));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, -2.5f));
		model2 = glm::scale(model2, glm::vec3(silla19, silla19, silla19));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn2, 0.0f, -1.5f));
		model2 = glm::scale(model2, glm::vec3(silla20, silla20, silla20));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		// Atrás der
		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, -5.0f));
		model2 = glm::scale(model2, glm::vec3(silla21, silla21, silla21));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, -4.0f));
		model2 = glm::scale(model2, glm::vec3(silla22, silla22, silla22));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, -2.5f));
		model2 = glm::scale(model2, glm::vec3(silla23, silla23, silla23));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);

		model2 = glm::translate(pivotesillas, glm::vec3(fSn3, 0.0f, -1.5f));
		model2 = glm::scale(model2, glm::vec3(silla24, silla24, silla24));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		silla2.Draw(lightingShader);


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
		moni = glm::scale(moni, glm::vec3(monitor1, monitor1, monitor1));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-230.0f, 0.0f, -75));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);
		///////////////
		moni = glm::translate(pivotecompus, glm::vec3(colca, 0.0f, filab));
		moni = glm::scale(moni, glm::vec3(monitor2, monitor2, monitor2));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-230, 0.0f,80));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);

		///////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(colca, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(monitor3, monitor3, monitor3));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-230, 0.0f,240));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);
		///////////////////

		moni = glm::translate(pivotecompus, glm::vec3(colcb, 0.0f, filaa));
		moni = glm::scale(moni, glm::vec3(monitor4, monitor4, monitor4));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-115, 0.0f, -75));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);

		/////////////////
		moni = glm::translate(pivotecompus, glm::vec3(colcb, 0.0f, filab));
		moni = glm::scale(moni, glm::vec3(monitor5, monitor5, monitor5));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(-115, 0.0f, 80));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);
		///////////////
		moni = glm::translate(pivotecompus, glm::vec3(colcb, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(monitor6, monitor6, monitor6));
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
		moni = glm::scale(moni, glm::vec3(monitor7, monitor7, monitor7));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(200, 0.0f, -75));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);
		////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(colcd, 0.0f, filab));
		moni = glm::scale(moni, glm::vec3(monitor8, monitor8, monitor8));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(200, 0.0f, 80));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);
		///////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(colcd, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(monitor9, monitor9, monitor9));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(200, 0.0f, 240));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);
		////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(colcc, 0.0f, filaa));
		moni = glm::scale(moni, glm::vec3(monitor10, monitor10, monitor10));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(90, 0.0f, -75));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);

		////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(colcc, 0.0f, filab));
		moni = glm::scale(moni, glm::vec3(monitor11, monitor11, monitor11));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
		moniGamer.Draw(lightingShader);

		tecla = glm::translate(pTeclado, glm::vec3(90, 0.0f, 80));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
		tecladoled.Draw(lightingShader);

		///////////////////////////////
		moni = glm::translate(pivotecompus, glm::vec3(colcc, 0.0f, filac));
		moni = glm::scale(moni, glm::vec3(monitor12, monitor12, monitor12));
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

		rack2 = model;
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(rack2));
		servidor2.Draw(lightingShader);
		glBindVertexArray(0);

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
	
		glBindVertexArray(0);

		// Draw skybox as last
		glDepthFunc(GL_LEQUAL); //hace que no interfiera con otros objetos //Funci�n de profundidad
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

		// Ventana transparente
		lightingShader.Use();
		glEnable(GL_BLEND); // Activa la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Aplicar esta matriz específica al shader
		modelVentana = glm::translate(modelVentana, glm::vec3(0.0f, 0.0f, 0.0f));
		modelVentana = glm::scale(modelVentana, glm::vec3(10.0f, 9.604f, 10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelVentana));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		ventanas.Draw(lightingShader);

		// Restaura configuración normal
		glDisable(GL_BLEND);

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
		mx += 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		mx -= 0.01f;
	}

	if (keys[GLFW_KEY_Y])
	{
		my += 0.01f;
	}

	if (keys[GLFW_KEY_H])
	{
		my -= 0.01f;
	}
	if (keys[GLFW_KEY_U])
	{
		mz -= 0.01f;
	}
	if (keys[GLFW_KEY_J])
	{
		mz += 0.01f;
	}

	if (keys[GLFW_KEY_X])
	{
		monitores = 1;
		humoflag = 1;
	}
	if (keys[GLFW_KEY_Z])
	{
		nuevo =1;
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


	if (key == GLFW_KEY_K && GLFW_PRESS == action)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame(); //Almacena cada frame
		}

	}

	if (key == GLFW_KEY_Q && GLFW_PRESS == action) {
		SaveAnimation();  // Guarda la animaci�n en "Animacion.txt"
	}

	if (key == GLFW_KEY_R && GLFW_PRESS == action) {

		resetElements();  // Resetear los elementos a los primeros keyframes cargados
		LoadAnimation(); //Carga la animaci�n por medio del archivo previamente guardado
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

	if (!nuevo) {
		if (monitores) {

			if (monitor1 > 0) {
				monitor1 -= 0.01;
			}
			else if (monitor2 > 0) {

				monitor2 -= 0.01;

			}
			else if (monitor3 > 0) {

				monitor3 -= 0.01;

			}
			else if (monitor4 > 0) {

				monitor4 -= 0.01;

			}
			else if (monitor5 > 0) {

				monitor5 -= 0.01;

			}
			else if (monitor6 > 0) {

				monitor6 -= 0.01;

			}
			else if (monitor7 > 0) {

				monitor7 -= 0.01;
			}
			else if (monitor8 > 0) {

				monitor8 -= 0.01;

			}
			else if (monitor9 > 0) {


				monitor9 -= 0.01;
			}
			else if (monitor10 > 0) {

				monitor10 -= 0.01;

			}
			else if (monitor11 > 0) {

				monitor11 -= 0.01;

			}
			else if (monitor12 > 0) {


				monitor12 -= 0.01;
			}else if (silla1 > 0) {
				silla1 -= 0.01;
			}
			else if (silla222 > 0) {
				silla222 -= 0.01;
			}
			else if (silla3 > 0) {
				silla3 -= 0.01;
			}
			else if (silla4 > 0) {
				silla4 -= 0.01;
			}
			else if (silla5 > 0) {
				silla5 -= 0.01;
			}
			else if (silla6 > 0) {
				silla6 -= 0.01;
			}
			else if (silla7 > 0) {
				silla7 -= 0.01;
			}
			else if (silla8 > 0) {
				silla8 -= 0.01;
			}
			else if (silla9 > 0) {
				silla9 -= 0.01;
			}
			else if (silla10 > 0) {
				silla10 -= 0.01;
			}
			else if (silla11 > 0) {
				silla11 -= 0.01;
			}
			else if (silla12 > 0) {
				silla12 -= 0.01;
			}
			else if (silla13 > 0) {
				silla13 -= 0.01;
			}
			else if (silla14 > 0) {
				silla14 -= 0.01;
			}
			else if (silla15 > 0) {
				silla15 -= 0.01;
			}
			else if (silla16 > 0) {
				silla16 -= 0.01;
			}
			else if (silla17 > 0) {
				silla17 -= 0.01;
			}
			else if (silla18 > 0) {
				silla18 -= 0.01;
			}
			else if (silla19 > 0) {
				silla19 -= 0.01;
			}
			else if (silla20 > 0) {
				silla20 -= 0.01;
			}
			else if (silla21 > 0) {
				silla21 -= 0.01;
			}
			else if (silla22 > 0) {
				silla22 -= 0.01;
			}
			else if (silla23 > 0) {
				silla23 -= 0.01;
			}
			else if (silla24 > 0) {
				silla24 -= 0.01;
			}
			else {
				nuevo = 1;
			}

		}
	}
	else {
		if (monitor1 < 1) {
			monitor1 += 0.01;
		}
		else if (monitor2 < 1) {
			monitor2 += 0.01;
		}
		else if (monitor3 < 1) {
			monitor3 += 0.01;
		}
		else if (monitor4 < 1) {
			monitor4 += 0.01;
		}
		else if (monitor4 < 1) {
			monitor4 += 0.01;
		}
		else if (monitor5 < 1) {
			monitor5 += 0.01;
		}
		else if (monitor6 < 1) {
			monitor6 += 0.01;
		}
		else if (monitor7 < 1) {
			monitor7 += 0.01;
		}
		else if (monitor8 < 1) {
			monitor8 += 0.01;
		}
		else if (monitor9 < 1) {
			monitor9 += 0.01;
		}
		else if (monitor10 < 1) {
			monitor10 += 0.01;
		}
		else if (monitor11 < 1) {
			monitor11 += 0.01;
		}
		else if (monitor12 < 1) {
			monitor12 += 0.01;
		}else if (silla1 < 1) {
			silla1 += 0.01;
		}
		else if (silla222 < 1) {
			silla222 += 0.01;
		}
		else if (silla3 < 1) {
			silla3 += 0.01;
		}
		else if (silla4 < 1) {
			silla4 += 0.01;
		}
		else if (silla5 < 1) {
			silla5 += 0.01;
		}
		else if (silla6 < 1) {
			silla6 += 0.01;
		}
		else if (silla7 < 1) {
			silla7 += 0.01;
		}
		else if (silla8 < 1) {
			silla8 += 0.01;
		}
		else if (silla9 < 1) {
			silla9 += 0.01;
		}
		else if (silla10 < 1) {
			silla10 += 0.01;
		}
		else if (silla11 < 1) {
			silla11 += 0.01;
		}
		else if (silla12 < 1) {
			silla12 += 0.01;
		}
		else if (silla13 < 1) {
			silla13 += 0.01;
		}
		else if (silla14 < 1) {
			silla14 += 0.01;
		}
		else if (silla15 < 1) {
			silla15 += 0.01;
		}
		else if (silla16 < 1) {
			silla16 += 0.01;
		}
		else if (silla17 < 1) {
			silla17 += 0.01;
		}
		else if (silla18 < 1) {
			silla18 += 0.01;
		}
		else if (silla19 < 1) {
			silla19 += 0.01;
		}
		else if (silla20 < 1) {
			silla20 += 0.01;
		}
		else if (silla21 < 1) {
			silla21 += 0.01;
		}
		else if (silla22 < 1) {
			silla22 += 0.01;
		}
		else if (silla23 < 1) {
			silla23 += 0.01;
		}
		else if (silla24 < 1) {
			silla24 += 0.01;
		}
		else {
			monitores = 0;
			humoflag = 0;
			nuevo = 1;
		}
	}	

	if (humoflag) {
		
		float rango = 40.0;
		rhumo += 0.1;
		
			if (contadorhumo1 >= rango){
				contadorhumo2 = 0.000001f;
				contadorhumo1= 0;

				//printf("111111111111111111111111111111");
			}
			if (contadorhumo3 >= rango){
				contadorhumo4 = 0.000001f;
				contadorhumo3 = 0;

				//printf("2222222222222222222222222222");
			}
			if (contadorhumo5 >= rango){
				contadorhumo6 = 0.000001f;
				contadorhumo5 = 0;

				//printf("3333333333333333333333333333333");
			}
			if (contadorhumo7 >= rango) {
				contadorhumo8 = 0.000001f;
				contadorhumo7 = 0;

				//printf("444444444444444444444444444444444");
			}
			if (contadorhumo9>= rango) {
				contadorhumo10 = 0.000001f;
				contadorhumo9 = 0;
			}
			if (flagg) {
				if (contadorhumo1 == 0) {
					contadorhumo1 += 0.000001f;
					H[0].position = glm::vec3(humoPosX, humoPosY, humoPosZ);
					H[1].position = glm::vec3(humoPosX, humoPosY, humoPosZ);
					H[2].position = glm::vec3(humoPosX, humoPosY, humoPosZ);
					H[3].position = glm::vec3(humoPosX, humoPosY, humoPosZ);


					H[0].size = glm::vec3(0.000001f, 0.000001f, 0.000001f);
					H[1].size = glm::vec3(0.000001f, 0.000001f, 0.000001f);
					H[2].size = glm::vec3(0.000001f, 0.000001f, 0.000001f);
					H[3].size = glm::vec3(0.000001f, 0.000001f, 0.000001f);
				}
				if (contadorhumo1 >= 0 && contadorhumo1 < (rango / 4)) {
					contadorhumo2 += 0.000001f;
					contadorhumo1 += 0.05f;

					H[0].position = glm::vec3(humoPosX / contadorhumo2, contadorhumo1 + humoPosY / (contadorhumo2 * 2), humoPosZ / contadorhumo2);
					H[0].size = glm::vec3(contadorhumo2, contadorhumo2 * 2, contadorhumo2);
					

				}if (contadorhumo1 >= (rango / 4) && contadorhumo1 < (rango / 2)) {
					contadorhumo2 += 0.000001f;
					contadorhumo1 += 0.05f;
					contadorhumo4 += 0.000001f;
					contadorhumo3 += 0.05f;

					H[0].position = glm::vec3(humoPosX / contadorhumo2, contadorhumo1 + humoPosY / (contadorhumo2 * 2), humoPosZ / contadorhumo2);
					H[1].position = glm::vec3(humoPosX / contadorhumo4, contadorhumo3 + humoPosY / (contadorhumo4 * 2), humoPosZ / contadorhumo4);
					H[0].size = glm::vec3(contadorhumo2, contadorhumo2 * 2, contadorhumo2);
					H[1].size = glm::vec3(contadorhumo4, contadorhumo4 * 2, contadorhumo4);

				}
				if (contadorhumo1 >= (rango / 2) && contadorhumo1 < (rango * 3 / 4)) {
					contadorhumo2 += 0.000001f;
					contadorhumo1 += 0.05f;
					contadorhumo4 += 0.000001f;
					contadorhumo3 += 0.05f;
					contadorhumo6 += 0.000001f;
					contadorhumo5 += 0.05f;
					H[0].position = glm::vec3(humoPosX / contadorhumo2, contadorhumo1 + humoPosY / (contadorhumo2 * 2), humoPosZ / contadorhumo2);
					H[1].position = glm::vec3(humoPosX / contadorhumo4, contadorhumo3 + humoPosY / (contadorhumo4 * 2), humoPosZ / contadorhumo4);
					H[2].position = glm::vec3(humoPosX / contadorhumo6, contadorhumo5 + humoPosY / (contadorhumo6 * 2), humoPosZ / contadorhumo6);
					H[0].size = glm::vec3(contadorhumo2, contadorhumo2 * 2, contadorhumo2);
					H[1].size = glm::vec3(contadorhumo4, contadorhumo4 * 2, contadorhumo4);					
					H[2].size = glm::vec3(contadorhumo6, contadorhumo6 * 2, contadorhumo6);
					

				}
				if (contadorhumo1 >= (rango * 3 / 4) && contadorhumo1 < rango) {
					contadorhumo2 += 0.000001f;
					contadorhumo1 += 0.05f;
					contadorhumo4 += 0.000001f;
					contadorhumo3 += 0.05f;
					contadorhumo6 += 0.000001f;
					contadorhumo5 += 0.05f;
					contadorhumo8 += 0.000001f;
					contadorhumo7 += 0.05f;
					H[0].position = glm::vec3(humoPosX / contadorhumo2, contadorhumo1 + humoPosY / (contadorhumo2 * 2), humoPosZ / contadorhumo2);
					H[1].position = glm::vec3(humoPosX / contadorhumo4, contadorhumo3 + humoPosY / (contadorhumo4 * 2), humoPosZ / contadorhumo4);
					H[2].position = glm::vec3(humoPosX / contadorhumo6, contadorhumo5 + humoPosY / (contadorhumo6 * 2), humoPosZ / contadorhumo6);
					H[3].position = glm::vec3(humoPosX / contadorhumo8, contadorhumo7 + humoPosY / (contadorhumo8 * 2), humoPosZ / contadorhumo8);
					H[0].size = glm::vec3(contadorhumo2, contadorhumo2 * 2, contadorhumo2);
					H[1].size = glm::vec3(contadorhumo4, contadorhumo4 * 2, contadorhumo4);
					H[2].size = glm::vec3(contadorhumo6, contadorhumo6 * 2, contadorhumo6);
					H[3].size = glm::vec3(contadorhumo8, contadorhumo8 * 2, contadorhumo8);
					
					

				}

				if (contadorhumo1 >= rango) {
					flagg = 0;

					/*H[4].size = glm::vec3(contadorhumo2, contadorhumo2 * 2, contadorhumo2);
					H[4].position = glm::vec3(humoPosX, contadorhumo1 + humoPosY/contadorhumo2*2, humoPosZ);*/
				}
			}
			else {
				
					contadorhumo2 += 0.000001f;
					contadorhumo1 += 0.05f;
					contadorhumo4 += 0.000001f;
					contadorhumo3 += 0.05f;
					contadorhumo6 += 0.000001f;
					contadorhumo5 += 0.05f;
					contadorhumo8 += 0.000001f;
					contadorhumo7 += 0.05f;
					H[0].position = glm::vec3(humoPosX / contadorhumo2, contadorhumo1 + humoPosY/(contadorhumo2*2), humoPosZ / contadorhumo2);
					H[1].position = glm::vec3(humoPosX / contadorhumo4, contadorhumo3 + humoPosY / (contadorhumo4 * 2), humoPosZ  / contadorhumo4);
					H[2].position = glm::vec3(humoPosX / contadorhumo6, contadorhumo5 + humoPosY / (contadorhumo6 * 2), humoPosZ / contadorhumo6);
					H[3].position = glm::vec3(humoPosX / contadorhumo8, contadorhumo7 + humoPosY / (contadorhumo8 * 2), humoPosZ / contadorhumo8);
					H[0].size = glm::vec3(contadorhumo2, contadorhumo2 * 2, contadorhumo2);
					H[1].size = glm::vec3(contadorhumo4, contadorhumo4 * 2, contadorhumo4);
					H[2].size = glm::vec3(contadorhumo6, contadorhumo6 * 2, contadorhumo6);
					H[3].size = glm::vec3(contadorhumo8, contadorhumo8 * 2, contadorhumo8);
			}			
	}


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

//void MonitorAnimation() {
//	if (!monitorAnimationActive) return;
//
//	// Ya estamos en laboratorio nuevo pero seguimos mostrando la animaci�n de monitores
//	if (nuevo == 1) {
//		// Transici�n de monitores viejos a monitores nuevos (en lab nuevo)
//		if (monitorAnimationState == 1) {
//			// En el lab nuevo, empezamos con los monitores ocultos y los hacemos aparecer
//			newMonitorScale = (float)monitorAnimFrame / MONITOR_ANIM_MAX_FRAMES;
//
//			monitorAnimFrame++;
//			if (monitorAnimFrame >= MONITOR_ANIM_MAX_FRAMES) {
//				// La animaci�n ha terminado
//				monitorAnimationActive = false;
//				newMonitorScale = 1.0f;  // Monitores nuevos completamente visibles
//			}
//		}
//	}
//	else {
//		// Todav�a estamos en laboratorio viejo, hacemos la transici�n normal
//		if (monitorAnimationState == 0) {
//			// Desvaneciendo monitores viejos
//			
//
//			monitorAnimFrame++;
//			if (monitorAnimFrame >= MONITOR_ANIM_MAX_FRAMES * 3) {
//				monitorAnimFrame = 0;
//				monitorAnimationState = 1;
//
//				// Aqu� cambiamos al laboratorio nuevo justo despu�s de desvanecer los viejos
//				oldMonitorScale = 0.0f;
//				newMonitorScale = 0.0f;  // Empezamos con monitores nuevos ocultos
//				nuevo = 1;  // Cambiamos al laboratorio nuevo
//			}
//		}
//	}
//}

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