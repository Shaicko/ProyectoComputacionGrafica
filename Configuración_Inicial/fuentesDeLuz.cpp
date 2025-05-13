/* PROYECTO DE COMPUTACI�N GR�FICA E INTERACCI�N HUMANO COMPUTADORA
* SEMESTRE 2025-2
* EQUIPO 9
* INTEGRANTES:
* Berdejo Guzm�n Leonardo Ariel
* Javier Antonio Rodriguez Garcia
* Santiago Adrián Cruz Hernández
*/
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


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
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void Animation(); //Funci�n para los frames 

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
glm::vec3 lightPos(0.0f, 0.0f, 5.0f);
int flag = 0;
bool hablar = false, musica1 = false, muica2 = false, musica3 = false, musicafinal = false, musicaCambio = false;
float tex1, tex2, tex3;
float tiempoTexto= 0.0f;
float contexto = 3.5f;
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


float vuelta1 = 0;
float vuelta2 = 0;

int pizzarron3 = 1;

int rackflag = 0;
int rack11 = 1;
float rackx=0.0f;
float rackz =0.0f;
float rackTam =1.0;
float radio = 0.0f;  // Radio del c�rculo
float angle = 0.0f;  // �ngulo inicial
bool moveRot = false;
float speed = 0.0001f;

float humoPosX = 0.0f, humoPosY = 10.0f, humoPosZ = 0.0f;
float rotatehumo = 0.0f;
float sizehumoxz = 0.0004, sizehumoy = 0.0012;
int part = 0;
float contadorhumo1 = 0.0;
float contadorhumo2 = 0.0;
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
float monitor1 = 1.0f;
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

// Variables para escala de teclados
float teclado1 = 1.0f;
float teclado2 = 1.0f;
float teclado3 = 1.0f;
float teclado4 = 1.0f;
float teclado5 = 1.0f;
float teclado6 = 1.0f;
float teclado7 = 1.0f;
float teclado8 = 1.0f;
float teclado9 = 1.0f;
float teclado10 = 1.0f;
float teclado11 = 1.0f;
float teclado12 = 1.0f;

float columna1 = -14.5f * 10;
float columna2 = -13.0f * 10;
float columna3 = 11.0f * 10;
float columna4 = 12.5f * 10;


float fila1 = 12.0f * 10;
float fila2 = -14.0f * 10;
float fila3 = -1.0f * 10;

float cpx1 = columna1;
float cpx2 = columna1;
float cpx3 = columna1;
float cpx4 = columna2;
float cpx5 = columna2;
float cpx6 = columna2;
float cpx7 = columna3;
float cpx8 = columna3;
float cpx9 = columna3;
float cpx10 = columna4;
float cpx11 = columna4;
float cpx12 = columna4;

float cpz1 = fila1;
float cpz2 = fila2;
float cpz3 = fila3;
float cpz4 = fila1;
float cpz5 = fila2;
float cpz6 = fila3;
float cpz7 = fila1;
float cpz8 = fila2;
float cpz9 = fila3;
float cpz10 = fila1;
float cpz11 = fila2;
float cpz12 = fila3;


float purtaRot = 0.0;

float tamppizpa = 1.0;

int pizzarronFlag = 0;
float tampiz = 1.0;
float brazorot = 0.0;



float pizzarron = 1.0;
//Modificar estos KeyFrames pues es para cada animaci�n

float poshumanox = 0.0f;
float poshumanoy = 122.055f;
float poshumanoz = 0.0f;
float RodillasI = 0.0f;
float RodillaD = 0.0f;
float HombroI = 0.0f;
float HombroD = 0.0f;
float PiernaI = 0.0f;
float PiernaD = 0.0f;
float RotHuman = 0.0f;

#define MAX_FRAMES 90
int i_max_steps = 90;
int i_curr_steps = 0;
float mx = 0, my = 0, mz = 0;
//-----------------------Definici�n de la estructura para los KeyFrames-----------------------
typedef struct _frame {

	float poshumanox = 0.0f;
	float poshumanoy = 0.0f;
	float poshumanoz = 0.0f;
	float RodillasI = 0.0f;
	float RodillaD = 0.0f;
	float HombroI = 0.0f;
	float HombroD = 0.0f;
	float PiernaI = 0.0f;
	float PiernaD = 0.0f;
	float RotHuman = 0.0f;
	
	float poshumanoxInc = 0.0f;
	float poshumanoyInc = 0.0f;
	float poshumanozInc = 0.0f;
	float RodillasIInc = 0.0f;
	float RodillaDInc = 0.0f;
	float HombroIInc = 0.0f;
	float HombroDInc = 0.0f;
	float PiernaIInc = 0.0f;
	float PiernaDInc = 0.0f;
	float RotHumanInc = 0.0f;



}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//En qu� lugar de la l�nea de tiempo me encuentro al guardar los datos
bool play = false;			//Si se est� reproduciendo la animaci�n
int playIndex = 0;			//En qu� lugar de la l�nea de tiempo me encuentro al estar reproduciendo la animaci�n
bool humoflag = true;
//flag1
struct Particle {
	glm::vec3 position;
	glm::vec3 size;
	float rotation;
};
Particle H[5];
void spawnParticle(int i, float x, float y, float z, float sizehumoxz, float sizehumoy, float rotation) {
	Particle p;
	p.position = glm::vec3(x, y, z); // Punto de origen
	p.size = glm::vec3(sizehumoxz, sizehumoy, sizehumoxz); // Punto de origen
	p.rotation = rotation;
	H[i] = p;
}

// Funci�n para guardar la animaci�n
void SaveAnimation(const char* filename = "Animacion.txt") {
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error al abrir el archivo para guardar." << std::endl;
		return;
	}

	for (int i = 0; i < FrameIndex; i++) {
		file << KeyFrame[i].poshumanox << " "
			<< KeyFrame[i].poshumanoy << " "
			<< KeyFrame[i].poshumanoz << " "
			<< KeyFrame[i].RodillasI << " "
			<< KeyFrame[i].RodillaD << " "
			<< KeyFrame[i].HombroI << " "
			<< KeyFrame[i].HombroD << " "
			<< KeyFrame[i].PiernaI << " "
			<< KeyFrame[i].PiernaD << " "
			<< KeyFrame[i].RotHuman << "\n";	
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
		file >> KeyFrame[FrameIndex].poshumanox
		>> KeyFrame[FrameIndex].poshumanoy
		>> KeyFrame[FrameIndex].poshumanoz
		>> KeyFrame[FrameIndex].RodillasI
		>> KeyFrame[FrameIndex].RodillaD
		>> KeyFrame[FrameIndex].HombroI
		>> KeyFrame[FrameIndex].HombroD
		>> KeyFrame[FrameIndex].PiernaI
		>> KeyFrame[FrameIndex].PiernaD
		>> KeyFrame[FrameIndex].RotHuman)
		 {
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

	KeyFrame[FrameIndex].poshumanox = poshumanox;
	KeyFrame[FrameIndex].poshumanoy = poshumanoy;
	KeyFrame[FrameIndex].poshumanoz = poshumanoz;

	KeyFrame[FrameIndex].RodillasI = RodillasI;
	KeyFrame[FrameIndex].RodillaD = RodillaD;
	KeyFrame[FrameIndex].HombroI = HombroI;
	KeyFrame[FrameIndex].HombroD = HombroD;
	KeyFrame[FrameIndex].PiernaI = PiernaI;
	KeyFrame[FrameIndex].PiernaD = PiernaD;

	KeyFrame[FrameIndex].RotHuman = RotHuman;


	FrameIndex++;
}

void resetElements(void)
{
	
	poshumanox = KeyFrame[0].poshumanox;
	poshumanoy = KeyFrame[0].poshumanoy;
	poshumanoz = KeyFrame[0].poshumanoz;

	RodillasI = KeyFrame[0].RodillasI;
	RodillaD = KeyFrame[0].RodillaD;
	HombroI = KeyFrame[0].HombroI;
	HombroD = KeyFrame[0].HombroD;
	PiernaI = KeyFrame[0].PiernaI;
	PiernaD = KeyFrame[0].PiernaD;

	RotHuman = KeyFrame[0].RotHuman;


}
void interpolation(void)
{


	KeyFrame[playIndex].poshumanoxInc = (KeyFrame[playIndex + 1].poshumanox - KeyFrame[playIndex].poshumanox) / i_max_steps;
	KeyFrame[playIndex].poshumanoyInc = (KeyFrame[playIndex + 1].poshumanoy - KeyFrame[playIndex].poshumanoy) / i_max_steps;
	KeyFrame[playIndex].poshumanozInc = (KeyFrame[playIndex + 1].poshumanoz - KeyFrame[playIndex].poshumanoz) / i_max_steps;

	KeyFrame[playIndex].RodillasIInc = (KeyFrame[playIndex + 1].RodillasI - KeyFrame[playIndex].RodillasI) / i_max_steps;
	KeyFrame[playIndex].RodillaDInc = (KeyFrame[playIndex + 1].RodillaD - KeyFrame[playIndex].RodillaD) / i_max_steps;
	KeyFrame[playIndex].HombroIInc = (KeyFrame[playIndex + 1].HombroI - KeyFrame[playIndex].HombroI) / i_max_steps;
	KeyFrame[playIndex].HombroDInc = (KeyFrame[playIndex + 1].HombroD - KeyFrame[playIndex].HombroD) / i_max_steps;
	KeyFrame[playIndex].PiernaIInc = (KeyFrame[playIndex + 1].PiernaI - KeyFrame[playIndex].PiernaI) / i_max_steps;
	KeyFrame[playIndex].PiernaDInc = (KeyFrame[playIndex + 1].PiernaD - KeyFrame[playIndex].PiernaD) / i_max_steps;

	KeyFrame[playIndex].RotHumanInc = (KeyFrame[playIndex + 1].RotHuman - KeyFrame[playIndex].RotHuman) / i_max_steps;


	//printf("Interpolando cuadro %d a %d: IncX = %f\n", playIndex, playIndex + 1, KeyFrame[playIndex].incX);
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
	Model EscritorioP((char*)"Models/escritorioProf/escritorioProf.obj");

	Model EscritorioPnew((char*)"Models/escritorioProfNew/escritorioProfNew.obj");

	Model humo((char*)"Models/humo/humo.obj");
	Model escritorio((char*)"Models/mesanueva/model.obj");
	Model tele((char*)"Models/Tele/Tele.obj");
	Model tecladoled((char*)"Models/Led_Teclado/Teclado.obj");
	Model silla2((char*)"Models/GamerChair/GamerChair.obj");
	Model moniGamer((char*)"Models/MonitorNew/model.obj");
	Model servidor((char*)"Models/Rack/rackOld.obj");
	Model servidor2((char*)"Models/Rack/rackNew.obj");
	Model lampara((char*)"Models/lamp/lamp.obj");

	Model TorsoCabezaM((char*)"Models/Persona/Torso-Cabeza.obj");
	Model ManoIM((char*)"Models/Persona/Mano I.obj");
	Model ManoDM((char*)"Models/Persona/Mano D.obj");
	Model PiernaDM((char*)"Models/Persona/Pierna D.obj");
	Model PiernaIM((char*)"Models/Persona/Pierna I.obj");
	Model PieDM((char*)"Models/Persona/Pie D.obj");
	Model PieIM((char*)"Models/Persona/Pie I.obj");
	Model texto1((char*)"Models/texto1/model.obj");
	Model texto2((char*)"Models/texto2/model.obj");
	Model texto3((char*)"Models/texto3/model.obj");



	////////////////////////// KEYFRAMES //////////////////////////////////

   /*Iniciarlizar todos los frames en 0 */
   //KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{

		KeyFrame[i].poshumanox = 0;
		KeyFrame[i].poshumanoy = 122.055;
		KeyFrame[i].poshumanoz = 0;
		KeyFrame[i].poshumanoxInc = 0;
		KeyFrame[i].poshumanoyInc = 0;
		KeyFrame[i].poshumanozInc = 0;

		KeyFrame[i].RodillasI = 0;
		KeyFrame[i].RodillaD = 0;
		KeyFrame[i].HombroI = 0;
		KeyFrame[i].HombroD = 0;
		KeyFrame[i].PiernaI = 0;
		KeyFrame[i].PiernaD = 0;
		KeyFrame[i].RotHuman = 0;

		KeyFrame[i].RodillasIInc = 0;
		KeyFrame[i].RodillaDInc = 0;
		KeyFrame[i].HombroIInc = 0;
		KeyFrame[i].HombroDInc = 0;
		KeyFrame[i].PiernaIInc = 0;
		KeyFrame[i].PiernaDInc = 0;
		KeyFrame[i].RotHumanInc = 0;

	}

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
	LoadAnimation(); //Carga la animaci�n por medio del archivo previamente guardado
	PrintAnimation(); //Imprime en terminar los valores del archivo
	resetElements(); // Resetear los elementos a los primeros keyframes cargados
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
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.3f, 0.3f, 0.3f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.3f, 0.3f, 0.3);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.01f, 0.01f, 0.01f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);



			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.3f, 0.3f, 0.3f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.3f, 0.3f, 0.3f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.1f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.7f);



			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.3f, 0.3f, 0.3f);
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



			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.3f, 0.3f, 0.3f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.3f, 0.3f, 0.3);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.01f, 0.01f, 0.01f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.045f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.075f);




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
		glm::mat4 escritorioP = glm::mat4(1);
		glm::mat4 rack = glm::mat4(1.0f);
		glm::mat4 rack2 = glm::mat4(1.0f);
		glm::mat4 hum = glm::mat4(1);
		//aqui

		glm::mat4 humTorsoCabeza = glm::mat4(1.0f);
		glm::mat4 humManoI = glm::mat4(1.0f);
		glm::mat4 humManoD = glm::mat4(1.0f);
		glm::mat4 humPiernaD = glm::mat4(1.0f);
		glm::mat4 humPiernaI = glm::mat4(1.0f);
		glm::mat4 humPieD = glm::mat4(1.0f);
		glm::mat4 humPieI = glm::mat4(1.0f);
		glm::mat4 PivTosrso = glm::mat4(1.0f);
		glm::mat4 neon1 = glm::mat4(1);

		glm::mat4 t1 = glm::mat4(1.0f);
		glm::mat4 t2= glm::mat4(1.0f);
		glm::mat4 t3 = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Salon.Draw(lightingShader);
		/*prueba.Draw(lightingShader);*/
		
		puerta = model;
		puerta = glm::translate(puerta, glm::vec3(-0.115f, 0.034f, -0.148f));
		puerta = glm::rotate(puerta, glm::radians(purtaRot), glm::vec3(0, 1, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(puerta));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(puerta));
		Puer.Draw(lightingShader);

		// Activa la funcionalidad para trabajar con el canal alfa (transparencia)
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelVentana));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		modelVentana = glm::scale(modelVentana, glm::vec3(10.0f, 9.64f, 10.0f));
		modelVentana = glm::translate(modelVentana, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelVentana));
		ventanas.Draw(lightingShader);
		glDisable(GL_BLEND);
		glBindVertexArray(0);

		
		PivTosrso = model;

		PivTosrso = glm::scale(PivTosrso, glm::vec3(0.00032f, 0.000315f, 0.00032f));
		PivTosrso = glm::translate(PivTosrso, glm::vec3(-10.0f, 0.0f, -20.0f));

		
		// Torso + Cabeza
		humTorsoCabeza = glm::translate(PivTosrso, glm::vec3(poshumanox, poshumanoy, poshumanoz));
		humTorsoCabeza = glm::rotate(humTorsoCabeza, glm::radians(RotHuman), glm::vec3(0, 1, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(humTorsoCabeza));
		TorsoCabezaM.Draw(lightingShader);

		t1 = glm::translate(humTorsoCabeza, glm::vec3(63.665321f, 70.696693f, 0.0f));
		t1 = glm::scale(t1, glm::vec3(tex1,tex1, tex1));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(t1));
		texto1.Draw(lightingShader);

		t2 = glm::translate(humTorsoCabeza, glm::vec3(63.665321f, 70.696693f, 0.0f));
		t2 = glm::scale(t2, glm::vec3(tex2, tex2, tex2));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(t2));
		texto2.Draw(lightingShader);
		t3 = glm::translate(humTorsoCabeza, glm::vec3(63.665321f, 70.696693f, 0.0f));
		t3 = glm::scale(t3, glm::vec3(tex3, tex3, tex3));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(t3));
		texto3.Draw(lightingShader);

		// Mano Izquierda
		humManoI = glm::translate(humTorsoCabeza, glm::vec3(22.757f, 19.155f, 0.0f));
		humManoI = glm::rotate(humManoI, glm::radians(HombroI), glm::vec3(1, 0, -brazorot));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(humManoI));
		ManoIM.Draw(lightingShader);

		// Mano Derecha
		humManoD = glm::translate(humTorsoCabeza, glm::vec3(-22.757f, 19.155f, 0.0f));
		humManoD = glm::rotate(humManoD, glm::radians(HombroD), glm::vec3(1, 0, brazorot));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(humManoD));
		ManoDM.Draw(lightingShader);

		// Pierna Izquierda
		humPiernaI = glm::translate(humTorsoCabeza, glm::vec3(7.864f, -31.574f, 0.0f));
		humPiernaI = glm::rotate(humPiernaI, glm::radians(PiernaI), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(humPiernaI));
		PiernaIM.Draw(lightingShader);

		// Pierna Derecha
		humPiernaD = glm::translate(humTorsoCabeza, glm::vec3(-9.66f, -31.574f, 1.337f));
		humPiernaD = glm::rotate(humPiernaD, glm::radians(PiernaD), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(humPiernaD));
		PiernaDM.Draw(lightingShader);

		// Pie Izquierdo
		humPieI = glm::translate(humPiernaI, glm::vec3(4.715f, -40.511f, 0.0f));
		humPieI = glm::rotate(humPieI, glm::radians(RodillasI), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(humPieI));
		PieIM.Draw(lightingShader);

		// Pie Derecho
		humPieD = glm::translate(humPiernaD, glm::vec3(-2.712f, -40.511f, -1.934f));
		humPieD = glm::rotate(humPieD, glm::radians(RodillaD), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(humPieD));
		PieDM.Draw(lightingShader);

		
		if (!nuevo) {
			escritorioP = model;

			escritorioP = glm::scale(escritorioP, glm::vec3(0.08f, 0.08f * tamppizpa, 0.08f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(escritorioP));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(escritorioP));
			EscritorioP.Draw(lightingShader);
			

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

			

			modelTemp = model;
			modelTemp = glm::scale(modelTemp, glm::vec3(0.0015f, 0.0015f * tamppizpa, 0.0015f));
			modelTemp = glm::translate(modelTemp, glm::vec3(40.0f, 0.0f, -0.0f));

			// Mesas - mantener igual
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

			// SILLAS
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

			// MONITORES Y TECLADOS
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

			// Monitor y teclado 1
			moni = glm::translate(pivotecompus, glm::vec3((-55 / monitor1), 0.0f, (filaa / monitor1)));
			moni = glm::scale(moni, glm::vec3(monitor1, monitor1, monitor1));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			monitor.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(-55, 0.0f, -50));
			tecla = glm::scale(tecla, glm::vec3(teclado1, teclado1, teclado1));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			teclado.Draw(lightingShader);

			// Monitor y teclado 2
			moni = glm::translate(pivotecompus, glm::vec3((-55 / monitor2), 0.0f, (filab / monitor2)));
			moni = glm::scale(moni, glm::vec3(monitor2, monitor2, monitor2));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			monitor.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(-55, 0.0f, -10));
			tecla = glm::scale(tecla, glm::vec3(teclado2, teclado2, teclado2));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			teclado.Draw(lightingShader);

			// Monitor y teclado 3
			moni = glm::translate(pivotecompus, glm::vec3(-55, 0.0f, filac));
			moni = glm::scale(moni, glm::vec3(monitor3, monitor3, monitor3));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			monitor.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(-55, 0.0f, (filac - 10)));
			tecla = glm::scale(tecla, glm::vec3(teclado3, teclado3, teclado3));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			teclado.Draw(lightingShader);

			// Monitor y teclado 4
			moni = glm::translate(pivotecompus, glm::vec3(-30, 0.0f, filaa));
			moni = glm::scale(moni, glm::vec3(monitor4, monitor4, monitor4));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			monitor.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(-30, 0.0f, (filaa - 10)));
			tecla = glm::scale(tecla, glm::vec3(teclado4, teclado4, teclado4));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			teclado.Draw(lightingShader);

			// Monitor y teclado 5
			moni = glm::translate(pivotecompus, glm::vec3(-30, 0.0f, filab));
			moni = glm::scale(moni, glm::vec3(monitor5, monitor5, monitor5));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			monitor.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(-30, 0.0f, (filab - 10)));
			tecla = glm::scale(tecla, glm::vec3(teclado5, teclado5, teclado5));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			teclado.Draw(lightingShader);

			// Monitor y teclado 6
			moni = glm::translate(pivotecompus, glm::vec3(-30, 0.0f, filac));
			moni = glm::scale(moni, glm::vec3(monitor6, monitor6, monitor6));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			monitor.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(-30, 0.0f, (filac - 10)));
			tecla = glm::scale(tecla, glm::vec3(teclado6, teclado6, teclado6));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			teclado.Draw(lightingShader);

			// Monitor y teclado 7
			moni = glm::translate(pivotecompus, glm::vec3(45, 0.0f, filaa));
			moni = glm::scale(moni, glm::vec3(monitor7, monitor7, monitor7));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			monitor.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(45, 0.0f, (filaa - 10)));
			tecla = glm::scale(tecla, glm::vec3(teclado7, teclado7, teclado7));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			teclado.Draw(lightingShader);

			// Monitor y teclado 8
			moni = glm::translate(pivotecompus, glm::vec3(45, 0.0f, filab));
			moni = glm::scale(moni, glm::vec3(monitor8, monitor8, monitor8));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			monitor.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(45, 0.0f, (filab - 10)));
			tecla = glm::scale(tecla, glm::vec3(teclado8, teclado8, teclado8));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			teclado.Draw(lightingShader);

			// Monitor y teclado 9
			moni = glm::translate(pivotecompus, glm::vec3(45, 0.0f, filac));
			moni = glm::scale(moni, glm::vec3(monitor9, monitor9, monitor9));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			monitor.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(45, 0.0f, (filac - 10)));
			tecla = glm::scale(tecla, glm::vec3(teclado9, teclado9, teclado9));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			teclado.Draw(lightingShader);

			// Monitor y teclado 10
			moni = glm::translate(pivotecompus, glm::vec3(17, 0.0f, filaa));
			moni = glm::scale(moni, glm::vec3(monitor10, monitor10, monitor10));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			monitor.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(17, 0.0f, (filaa - 10)));
			tecla = glm::scale(tecla, glm::vec3(teclado10, teclado10, teclado10));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			teclado.Draw(lightingShader);

			// Monitor y teclado 11
			moni = glm::translate(pivotecompus, glm::vec3(17, 0.0f, filab));
			moni = glm::scale(moni, glm::vec3(monitor11, monitor11, monitor11));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			monitor.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(17, 0.0f, (filab - 10)));
			tecla = glm::scale(tecla, glm::vec3(teclado11, teclado11, teclado11));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			teclado.Draw(lightingShader);

			// Monitor y teclado 12
			moni = glm::translate(pivotecompus, glm::vec3(17, 0.0f, filac));
			moni = glm::scale(moni, glm::vec3(monitor12, monitor12, monitor12));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			monitor.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(17, 0.0f, (filac - 10)));
			tecla = glm::scale(tecla, glm::vec3(teclado12, teclado12, teclado12));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			teclado.Draw(lightingShader);

			// CPUs - mantener igual
			CU = glm::translate(CPUpiv, glm::vec3(cpx1, 0.0f,cpz1));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			cpu.Draw(lightingShader);

			CU = glm::translate(CPUpiv, glm::vec3(cpx2, 0.0f, cpz2));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			cpu.Draw(lightingShader);


			CU = glm::translate(CPUpiv, glm::vec3(cpx3, 0.0f, cpz3));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			cpu.Draw(lightingShader);

			CU = glm::translate(CPUpiv, glm::vec3(cpx4, 0.0f, cpz4));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			cpu.Draw(lightingShader);

			// Humo si está activado
			if (humoflag) {
				for (int i = 0; i <= 3; i++) {
					hum = CU;
					glEnable(GL_BLEND);//Activa la funcionalidad para trabajar el canal alfa
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

			// CPUs atras izq
			CU = glm::translate(CPUpiv, glm::vec3(cpx5, 0.0f, cpz5));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			cpu.Draw(lightingShader);

			CU = glm::translate(CPUpiv, glm::vec3(cpx6, 0.0f, cpz6));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			cpu.Draw(lightingShader);

			// CPUs de mesa de adelante (derecha)
			CU = glm::translate(CPUpiv, glm::vec3(cpx7, 0.0f, cpz7));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			cpu.Draw(lightingShader);

			CU = glm::translate(CPUpiv, glm::vec3(cpx8, 0.0f, cpz8));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			cpu.Draw(lightingShader);

			// Humo si está activado (segunda ubicación)
			if (humoflag) {
				for (int i = 0; i <= 3; i++) {
					hum = CU;
					glEnable(GL_BLEND);//Activa la funcionalidad para trabajar el canal alfa
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					hum = glm::scale(hum, H[i].size / 0.0010f);
					hum = glm::translate(hum, H[i].position);
					hum = glm::rotate(hum, glm::radians(rhumo), glm::vec3(0.0f, 1.0f, 0.0f));
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(hum));
					glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(hum));
					humo.Draw(lightingShader);
					glDisable(GL_BLEND);
				}
			}

			// CPUs MEDIO DER
			CU = glm::translate(CPUpiv, glm::vec3(cpx9, 0.0f, cpz9));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			cpu.Draw(lightingShader);

			CU = glm::translate(CPUpiv, glm::vec3(cpx10, 0.0f, cpz10));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			cpu.Draw(lightingShader);

			// CPUs atras der
			CU = glm::translate(CPUpiv, glm::vec3(cpx11, 0.0f, cpz11));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			cpu.Draw(lightingShader);

			CU = glm::translate(CPUpiv, glm::vec3(cpx12, 0.0f, cpz12));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CU));
			cpu.Draw(lightingShader);

		}
		else {
			escritorioP = model;
			escritorioP = glm::scale(escritorioP, glm::vec3(1.f, 1.0f * tamppizpa, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(escritorioP));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(escritorioP));
			EscritorioPnew.Draw(lightingShader);

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

			

			modelTemp = model;
			modelTemp = glm::scale(modelTemp, glm::vec3(0.08f, 0.08f * tamppizpa, 0.08f));
			modelTemp = glm::translate(modelTemp, glm::vec3(0.0f, 0.13f, 0.0f));
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

			model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, -2.5f));
			model2 = glm::scale(model2, glm::vec3(silla15, silla15, silla15));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			silla2.Draw(lightingShader);

			model2 = glm::translate(pivotesillas, glm::vec3(fSn1, 0.0f, -1.3f));
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

			// MONITORES Y TECLADOS
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

			// Monitor y teclado 1
			moni = glm::translate(pivotecompus, glm::vec3(colca, 0.0f, filaa));
			moni = glm::scale(moni, glm::vec3(monitor1, monitor1, monitor1));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			moniGamer.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(-230.0f, 0.0f, -75));
			tecla = glm::scale(tecla, glm::vec3(teclado1, teclado1, teclado1));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			tecladoled.Draw(lightingShader);

			// Monitor y teclado 2
			moni = glm::translate(pivotecompus, glm::vec3(colca, 0.0f, filab));
			moni = glm::scale(moni, glm::vec3(monitor2, monitor2, monitor2));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			moniGamer.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(-230, 0.0f, 80));
			tecla = glm::scale(tecla, glm::vec3(teclado2, teclado2, teclado2));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			tecladoled.Draw(lightingShader);

			// Monitor y teclado 3
			moni = glm::translate(pivotecompus, glm::vec3(colca, 0.0f, filac));
			moni = glm::scale(moni, glm::vec3(monitor3, monitor3, monitor3));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			moniGamer.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(-230, 0.0f, 240));
			tecla = glm::scale(tecla, glm::vec3(teclado3, teclado3, teclado3));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			tecladoled.Draw(lightingShader);

			// Monitor y teclado 4
			moni = glm::translate(pivotecompus, glm::vec3(colcb, 0.0f, filaa));
			moni = glm::scale(moni, glm::vec3(monitor4, monitor4, monitor4));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			moniGamer.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(-115, 0.0f, -75));
			tecla = glm::scale(tecla, glm::vec3(teclado4, teclado4, teclado4));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			tecladoled.Draw(lightingShader);

			// Monitor y teclado 5
			moni = glm::translate(pivotecompus, glm::vec3(colcb, 0.0f, filab));
			moni = glm::scale(moni, glm::vec3(monitor5, monitor5, monitor5));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			moniGamer.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(-115, 0.0f, 80));
			tecla = glm::scale(tecla, glm::vec3(teclado5, teclado5, teclado5));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			tecladoled.Draw(lightingShader);

			// Monitor y teclado 6
			moni = glm::translate(pivotecompus, glm::vec3(colcb, 0.0f, filac));
			moni = glm::scale(moni, glm::vec3(monitor6, monitor6, monitor6));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			moniGamer.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(-115, 0.0f, 240));
			tecla = glm::scale(tecla, glm::vec3(teclado6, teclado6, teclado6));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			tecladoled.Draw(lightingShader);

			// Monitor y teclado 7
			moni = glm::translate(pivotecompus, glm::vec3(colcd, 0.0f, filaa));
			moni = glm::scale(moni, glm::vec3(monitor7, monitor7, monitor7));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			moniGamer.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(200, 0.0f, -75));
			tecla = glm::scale(tecla, glm::vec3(teclado7, teclado7, teclado7));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			tecladoled.Draw(lightingShader);

			// Monitor y teclado 8
			moni = glm::translate(pivotecompus, glm::vec3(colcd, 0.0f, filab));
			moni = glm::scale(moni, glm::vec3(monitor8, monitor8, monitor8));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			moniGamer.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(200, 0.0f, 80));
			tecla = glm::scale(tecla, glm::vec3(teclado8, teclado8, teclado8));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			tecladoled.Draw(lightingShader);

			// Monitor y teclado 9
			moni = glm::translate(pivotecompus, glm::vec3(colcd, 0.0f, filac));
			moni = glm::scale(moni, glm::vec3(monitor9, monitor9, monitor9));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			moniGamer.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(200, 0.0f, 240));
			tecla = glm::scale(tecla, glm::vec3(teclado9, teclado9, teclado9));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			tecladoled.Draw(lightingShader);
			// Monitor y teclado 10
			moni = glm::translate(pivotecompus, glm::vec3(colcc, 0.0f, filaa));
			moni = glm::scale(moni, glm::vec3(monitor10, monitor10, monitor10));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			moniGamer.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(90, 0.0f, -75));
			tecla = glm::scale(tecla, glm::vec3(teclado10, teclado10, teclado10));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			tecladoled.Draw(lightingShader);

			// Monitor y teclado 11
			moni = glm::translate(pivotecompus, glm::vec3(colcc, 0.0f, filab));
			moni = glm::scale(moni, glm::vec3(monitor11, monitor11, monitor11));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			moniGamer.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(90, 0.0f, 80));
			tecla = glm::scale(tecla, glm::vec3(teclado11, teclado11, teclado11));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			tecladoled.Draw(lightingShader);

			// Monitor y teclado 12
			moni = glm::translate(pivotecompus, glm::vec3(colcc, 0.0f, filac));
			moni = glm::scale(moni, glm::vec3(monitor12, monitor12, monitor12));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(moni));
			moniGamer.Draw(lightingShader);

			tecla = glm::translate(pTeclado, glm::vec3(90, 0.0f, 240));
			tecla = glm::scale(tecla, glm::vec3(teclado12, teclado12, teclado12));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tecla));
			tecladoled.Draw(lightingShader);

			
		}

		if (pizzarron3) {

			pizarron = model;
			pizarron = glm::scale(pizarron, glm::vec3(0.007f, 0.007f , 0.007f) * tampiz);
			pizarron = glm::rotate(pizarron, glm::radians(180.0f), glm::vec3(.00f, -1.0f, 0.0f));
			pizarron = glm::translate(pizarron, glm::vec3(0.0f, 6.0f, 20.0f) / tampiz);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pizarron));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pizarron));
			pizarra.Draw(lightingShader);
		}
		else {
			pizarron = model;
			pizarron = glm::scale(pizarron, glm::vec3(0.012f, 0.012f, 0.012f) * tampiz);
			pizarron = glm::rotate(pizarron, glm::radians(0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
			pizarron = glm::translate(pizarron, glm::vec3(6.5f, 1.0f, -12.5f) / tampiz);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pizarron));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pizarron));
			tele.Draw(lightingShader);
		}

		if (rack11) {
			
			// Servidor
			rack = model;
			rack = glm::scale(rack, glm::vec3(1.0, 1.0f, 1.0f) * rackTam);
			rack = glm::translate(rack, glm::vec3(rackx, 0.0f,0.136 +rackz)/rackTam);
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(rack));
			servidor.Draw(lightingShader);

		}
		else {
			// El servidor y otros objetos que se mantienen igual
			rack2 = model;
			rack2 = glm::scale(rack2, glm::vec3(1.0, 1.0f, 1.0f)*rackTam);
			rack2 = glm::translate(rack2, glm::vec3(rackx, 0.0f, rackz)/rackTam);
				glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(rack2));
			servidor2.Draw(lightingShader);
			

		}

		glBindVertexArray(0);

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

	
	

	if (keys[GLFW_KEY_O])
	{
		printf("%f,%f,%f \n", mx,my, mz);
		
	}

	

}
void falsos() {
	hablar = false;
	musica1 = false;
	muica2 = false;
	musica3 = false;
	musicafinal = false;
	musicaCambio = false;
	monitores = false;
	nuevo = 0;
	tiempoTexto = 0;
	 cpx1 = columna1;
	 cpx2 = columna1;
	 cpx3 = columna1;
	 cpx4 = columna2;
	 cpx5 = columna2;
	 cpx6 = columna2;
	 cpx7 = columna3;
	 cpx8 = columna3;
	 cpx9 = columna3;
	 cpx10 = columna4;
	 cpx11 = columna4;
	 cpx12 = columna4;

	 cpz1 = fila1;
	 cpz2 = fila2;
	 cpz3 = fila3;
	 cpz4 = fila1;
	 cpz5 = fila2;
	cpz6 = fila3;
	 cpz7 = fila1;
	 cpz8 = fila2;
	 cpz9 = fila3;
	 cpz10 = fila1;
	 cpz11 = fila2;
	cpz12 = fila3;
	pizzarronFlag = 0.0f;
	purtaRot = 0.0;
	vuelta1 = 0;
	vuelta2 = 0;
	pizzarron3 = 1;
	rack11 = 1;
	rackflag = 0;
	rackx = 0;
	rackz = 0;

}
// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (keys[GLFW_KEY_L])
	{
		if (play == false && (FrameIndex > 1))
		{
			
			PlaySound(TEXT("sonidos/caminata.wav"), NULL, SND_FILENAME | SND_ASYNC);
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


	if (keys[GLFW_KEY_K])
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame(); //Almacena cada frame
		}

	}

	if (key == GLFW_KEY_Q && GLFW_PRESS == action) {
		SaveAnimation ();  // Guarda la animaci�n en "Animacion.txt"
	}

	if (key == GLFW_KEY_R && GLFW_PRESS == action) {
		PlaySound(NULL, NULL, 0);
		falsos();
		LoadAnimation(); //Carga la animaci�n por medio del archivo previamente guardado
		PrintAnimation(); //Imprime en terminar los valores del archivo
		resetElements(); // Resetear los elementos a los primeros keyframes cargados
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
void verdaderos() {
	hablar = true;
	musica1 = true;
	muica2 = true;
	musica3 = true;
	musicafinal = true;
	musicaCambio = true;
}

void Animation() {
	
	if (!nuevo) {
		if (monitores) {
			if (musicaCambio) {
				PlaySound(NULL, NULL, 0);
				PlaySound(TEXT("sonidos/transformar.wav"), NULL, SND_FILENAME | SND_ASYNC);
				musicaCambio = false;
			}

				if (monitor1 > 0  && teclado1 > 0) {
					monitor1 -= 0.02;
					teclado1 -= 0.02;
				}
				else if (monitor2 > 0 && teclado2 > 0) {

					monitor2 -= 0.02;
					teclado2 -= 0.02;

				}
				else if (monitor3 > 0 && teclado3 > 0) {

					monitor3 -= 0.02;
					teclado3 -= 0.02;

				}
				else if (monitor4 > 0 && teclado4 > 0) {

					monitor4 -= 0.02;
					teclado4 -= 0.02;

				}
				else if (monitor5 > 0 && teclado5 > 0) {

					monitor5 -= 0.02;
					teclado5 -= 0.02;

				}
				else if (monitor6 > 0 && teclado6 > 0) {

					monitor6 -= 0.02;
					teclado6 -= 0.02;

				}
				else if (monitor7 > 0 && teclado7 > 0) {

					monitor7 -= 0.02;
					teclado7 -= 0.02;
				}
				else if (monitor8 > 0 && teclado8 > 0) {

					monitor8 -= 0.02;
					teclado8 -= 0.02;

				}
				else if (monitor9 > 0 && teclado9 > 0) {
					monitor9 -= 0.02;
					teclado9 -= 0.02;
				}
				else if (monitor10 > 0 && teclado10 > 0) {
					monitor10 -= 0.02;
					teclado10 -= 0.02;
				}
				else if (monitor11 > 0 && teclado11 > 0) {
					monitor11 -= 0.02;
					teclado11 -= 0.02;
				}
				else if (monitor12 > 0 && teclado12 > 0) {
					monitor12 -= 0.02;
					teclado12 -= 0.02;
				}
				else if (silla1 > 0) {
					silla1 -= 0.02;
				}
				else if (silla222 > 0) {
					silla222 -= 0.02;
				}
				else if (silla3 > 0) {
					silla3 -= 0.02;
				}
				else if (silla4 > 0) {
					silla4 -= 0.02;
				}
				else if (silla5 > 0) {
					silla5 -= 0.02;
				}
				else if (silla6 > 0) {
					silla6 -= 0.02;
				}
				else if (silla7 > 0) {
					silla7 -= 0.02;
				}
				else if (silla8 > 0) {
					silla8 -= 0.02;
				}
				else if (silla9 > 0) {
					silla9 -= 0.02;
				}
				else if (silla10 > 0) {
					silla10 -= 0.02;
				}
				else if (silla11 > 0) {
					silla11 -= 0.02;
				}
				else if (silla12 > 0) {
					silla12 -= 0.02;
				}
				else if (silla13 > 0) {
					silla13 -= 0.02;
				}
				else if (silla14 > 0) {
					silla14 -= 0.02;
				}
				else if (silla15 > 0) {
					silla15 -= 0.02;
				}
				else if (silla16 > 0) {
					silla16 -= 0.02;
				}
				else if (silla17 > 0) {
					silla17 -= 0.02;
				}
				else if (silla18 > 0) {
					silla18 -= 0.02;
				}
				else if (silla19 > 0) {
					silla19 -= 0.02;
				}
				else if (silla20 > 0) {
					silla20 -= 0.02;
				}
				else if (silla21 > 0) {
					silla21 -= 0.02;
				}
				else if (silla22 > 0) {
					silla22 -= 0.02;
				}
				else if (silla23 > 0) {
					silla23 -= 0.02;
				}
				else if (silla24 > 0) {
					silla24 -= 0.02;
					}
				else if (purtaRot > -90) {
						purtaRot -=1;
				}
				else if (cpx1 > -200.0) {
					cpx1 -= 3;
					if (RotHuman > -45) {
						RotHuman -= 2;
						if (RodillaD < 45) {
							PiernaD -= 2;
							RodillaD += 2;
						}
					}
				}
				else if (cpz1 > -500.0) {
					if (cpz1 > -490) {
						cpz1 -= 5;
						if (RotHuman > -90) {
						RotHuman -= 2;
						if (RodillaD > 0) {
							PiernaD += 2;
							RodillaD -= 2;
						}
					}
					}
					else if (RotHuman < -45) {
						RotHuman += 2;
						if (RodillaD < 45) {
							PiernaD -= 2;
							RodillaD += 2;
						}
					}
					else if (RotHuman < 0) {
						RotHuman += 2;
						if (RodillaD > 0) {
							PiernaD += 2;
							RodillaD -= 2;
						}
					}
					else if (RodillaD > 0) {
						PiernaD += 2;
						RodillaD -= 2;
					}
					else {
						cpz1 -= 5;
					}
				}
				
				else if (cpx2 > -200.0) {
					cpx2 -= 3;
					if (RotHuman > -45) {
						RotHuman -= 2;
						if (RodillaD < 45) {
							PiernaD -= 2;
							RodillaD += 2;
						}
					}
				}
				else if (cpz2 > -500.0) {
					if (cpz2 > -490) {
						cpz2 -= 5;
						if (RotHuman > -90) {
							RotHuman -= 2;
							if (RodillaD > 0) {
								PiernaD += 2;
								RodillaD -= 2;
							}
						}
					}
					else if (RotHuman < -45) {
						RotHuman += 2;
						if (RodillaD < 45) {
							PiernaD -= 2;
							RodillaD += 2;
						}
					}
					else if (RotHuman < 0) {
						RotHuman += 2;
						if (RodillaD > 0) {
							PiernaD += 2;
							RodillaD -= 2;
						}
					}
					else if (RodillaD > 0) {
						PiernaD += 2;
						RodillaD -= 2;
					}
					else {
						cpz2 -= 5;
					}
				}
				else if (cpx3 > -200.0) {
					cpx3 -= 3;
					if (RotHuman > -45) {
						RotHuman -= 2;
						if (RodillaD < 45) {
							PiernaD -= 2;
							RodillaD += 2;
						}
					}
				}
				else if (cpz3 > -500.0) {
					if (cpz3 > -490) {
						cpz3 -= 5;
						if (RotHuman > -90) {
							RotHuman -= 2;
							if (RodillaD > 0) {
								PiernaD += 2;
								RodillaD -= 2;
							}
						}
					}
					else if (RotHuman < -45) {
						RotHuman += 2;
						if (RodillaD < 45) {
							PiernaD -= 2;
							RodillaD += 2;
						}
					}
					else if (RotHuman < 0) {
						RotHuman += 2;
						if (RodillaD > 0) {
							PiernaD += 2;
							RodillaD -= 2;
						}
					}
					else if (RodillaD > 0) {
						PiernaD += 2;
						RodillaD -= 2;
					}
					else {
						cpz3 -= 5;
					}
				}
				
				else if (cpx4 > -200.0) {
					cpx4 -= 3;
					if (RotHuman > -45) {
						RotHuman -= 2;
						if (RodillaD < 45) {
							PiernaD -= 2;
							RodillaD += 2;
						}
					}
				}
				else if (cpz4 > -500.0) {
					if (cpz4 > -490) {
						cpz4 -= 5;
						if (RotHuman > -90) {
							RotHuman -= 2;
							if (RodillaD > 0) {
								PiernaD += 2;
								RodillaD -= 2;
							}
						}
					}
					else if (RotHuman < -45) {
						RotHuman += 2;
						if (RodillaD < 45) {
							PiernaD -= 2;
							RodillaD += 2;
						}
					}
					else if (RotHuman < 0) {
						RotHuman += 2;
						if (RodillaD > 0) {
							PiernaD += 2;
							RodillaD -= 2;
						}
					}
					else if (RodillaD > 0) {
						PiernaD += 2;
						RodillaD -= 2;
					}
					else {
						cpz4 -= 5;
					}
				}
				
				else if (cpx5 > -200.0) {
					cpx5 -= 3;
					if (RotHuman > -45) {
						RotHuman -= 2;
						if (RodillaD < 45) {
							PiernaD -= 2;
							RodillaD += 2;
						}
					}
				}
				else if (cpz5 > -500.0) {
					if (cpz5 > -490) {
						cpz5 -= 5;
						if (RotHuman > -90) {
							RotHuman -= 2;
							if (RodillaD > 0) {
								PiernaD += 2;
								RodillaD -= 2;
							}
						}
					}
					else if (RotHuman < -45) {
						RotHuman += 2;
						if (RodillaD < 45) {
							PiernaD -= 2;
							RodillaD += 2;
						}
					}
					else if (RotHuman < 0) {
						RotHuman += 2;
						if (RodillaD > 0) {
							PiernaD += 2;
							RodillaD -= 2;
						}
					}
					else if (RodillaD > 0) {
						PiernaD += 2;
						RodillaD -= 2;
					}
					else {
						cpz5 -= 5;
					}
				}
				
				else if (cpx6 > -200.0) {
    cpx6 -= 3;
    if (RotHuman > -45) {
        RotHuman -= 2;
        if (RodillaD < 45) {
            PiernaD -= 2;
            RodillaD += 2;
        }
    }
} 
				else if (cpz6 > -500.0) {
					if (cpz6 > -490) {
						cpz6 -= 5;
						if (RotHuman > -90) {
							RotHuman -= 2;
							if (RodillaD > 0) {
								PiernaD += 2;
								RodillaD -= 2;
							}
						}
					}
					else if (RotHuman < -45) {
						RotHuman += 2;
						if (RodillaD < 45) {
							PiernaD -= 2;
							RodillaD += 2;
						}
					}
					else if (RotHuman < 0) {
						RotHuman += 2;
						if (RodillaD > 0) {
							PiernaD += 2;
							RodillaD -= 2;
						}
					}
					else if (RodillaD > 0) {
						PiernaD += 2;
						RodillaD -= 2;
					}
					else {
						cpz6 -= 5;
					}
}
else if (cpx7 > -200.0) {
    cpx7 -= 3;
    if (RotHuman > -45) {
        RotHuman -= 1;
        if (RodillaD < 45) {
            PiernaD -= 1;
            RodillaD += 1;
        }
    }
}
else if (cpz7 > -500.0) {
	if (cpz7 > -490) {
		cpz7 -= 5;
		if (RotHuman > -90) {
			RotHuman -= 2;
			if (RodillaD > 0) {
				PiernaD += 2;
				RodillaD -= 2;
			}
		}
	}
	else if (RotHuman < -45) {
		RotHuman += 2;
		if (RodillaD < 45) {
			PiernaD -= 2;
			RodillaD += 2;
		}
	}
	else if (RotHuman < 0) {
		RotHuman += 2;
		if (RodillaD > 0) {
			PiernaD += 2;
			RodillaD -= 2;
		}
	}
	else if (RodillaD > 0) {
		PiernaD += 2;
		RodillaD -= 2;
	}
	else {
		cpz7 -= 5;
	}
}

else if (cpx8 > -200.0) {
    cpx8 -= 3;
    if (RotHuman > -45) {
        RotHuman -= 1;
        if (RodillaD < 45) {
            PiernaD -= 1;
            RodillaD += 1;
        }
    }
} 
else if (cpz8 > -500.0) {
	if (cpz8 > -490) {
		cpz8 -= 5;
		if (RotHuman > -90) {
			RotHuman -= 2;
			if (RodillaD > 0) {
				PiernaD += 2;
				RodillaD -= 2;
			}
		}
	}
	else if (RotHuman < -45) {
		RotHuman += 2;
		if (RodillaD < 45) {
			PiernaD -= 2;
			RodillaD += 2;
		}
	}
	else if (RotHuman < 0) {
		RotHuman += 2;
		if (RodillaD > 0) {
			PiernaD += 2;
			RodillaD -= 2;
		}
	}
	else if (RodillaD > 0) {
		PiernaD += 2;
		RodillaD -= 2;
	}
	else {
		cpz8 -= 5;
	}
}


else if (cpx9 > -200.0) {
    cpx9 -= 3;
    if (RotHuman > -45) {
        RotHuman -= 1;
        if (RodillaD < 45) {
            PiernaD -= 1;
            RodillaD += 1;
        }
    }
}
else if (cpz9 > -500.0) {
	if (cpz9 > -490) {
		cpz9 -= 5;
		if (RotHuman > -90) {
			RotHuman -= 2;
			if (RodillaD > 0) {
				PiernaD += 2;
				RodillaD -= 2;
			}
		}
	}
	else if (RotHuman < -45) {
		RotHuman += 2;
		if (RodillaD < 45) {
			PiernaD -= 2;
			RodillaD += 2;
		}
	}
	else if (RotHuman < 0) {
		RotHuman += 2;
		if (RodillaD > 0) {
			PiernaD += 2;
			RodillaD -= 2;
		}
	}
	else if (RodillaD > 0) {
		PiernaD += 2;
		RodillaD -= 2;
	}
	else {
		cpz9 -= 5;
	}
}


else if (cpx10 > -200.0) {
    cpx10 -= 3;
    if (RotHuman > -45) {
        RotHuman -= 1;
        if (RodillaD < 45) {
            PiernaD -= 1;
            RodillaD += 1;
        }
    }
} 
else if (cpz10 > -500.0) {
	if (cpz10 > -490) {
		cpz10 -= 5;
		if (RotHuman > -90) {
			RotHuman -= 2;
			if (RodillaD > 0) {
				PiernaD += 2;
				RodillaD -= 2;
			}
		}
	}
	else if (RotHuman < -45) {
		RotHuman += 2;
		if (RodillaD < 45) {
			PiernaD -= 2;
			RodillaD += 2;
		}
	}
	else if (RotHuman < 0) {
		RotHuman += 2;
		if (RodillaD > 0) {
			PiernaD += 2;
			RodillaD -= 2;
		}
	}
	else if (RodillaD > 0) {
		PiernaD += 2;
		RodillaD -= 2;
	}
	else {
		cpz10 -= 5;
	}
}


else if (cpx11 > -200.0) {
    cpx11 -= 3;
    if (RotHuman > -45) {
        RotHuman -= 1;
        if (RodillaD < 45) {
            PiernaD -= 1;
            RodillaD += 1;
        }
    }
}
else if (cpz11 > -500.0) {
	if (cpz11 > -490) {
		cpz11 -= 5;
		if (RotHuman > -90) {
			RotHuman -= 2;
			if (RodillaD > 0) {
				PiernaD += 2;
				RodillaD -= 2;
			}
		}
	}
	else if (RotHuman < -45) {
		RotHuman += 2;
		if (RodillaD < 45) {
			PiernaD -= 2;
			RodillaD += 2;
		}
	}
	else if (RotHuman < 0) {
		RotHuman += 2;
		if (RodillaD > 0) {
			PiernaD += 2;
			RodillaD -= 2;
		}
	}
	else if (RodillaD > 0) {
		PiernaD += 2;
		RodillaD -= 2;
	}
	else {
		cpz11 -= 5;
	}
}


else if (cpx12 > -200.0) {
    cpx12 -= 3;
    if (RotHuman > -45) {
        RotHuman -= 1;
        if (RodillaD < 45) {
            PiernaD -= 1;
            RodillaD += 1;
        }
    }
} 
else if (cpz12 > -500.0) {
	if (cpz12 > -490) {
		cpz12 -= 5;
		if (RotHuman > -90) {
			RotHuman -= 2;
			if (RodillaD > 0) {
				PiernaD += 2;
				RodillaD -= 2;
			}
		}
	}
	else if (RotHuman < -45) {
		RotHuman += 2;
		if (RodillaD < 45) {
			PiernaD -= 2;
			RodillaD += 2;
		}
	}
	else if (RotHuman < 0) {
		RotHuman += 2;
		if (RodillaD > 0) {
			PiernaD += 2;
			RodillaD -= 2;
		}
	}
	else if (RodillaD > 0) {
		PiernaD += 2;
		RodillaD -= 2;
	}
	else {
		cpz12 -= 5;
	}
}


else if (tamppizpa >0) {
	tamppizpa -= 0.01;
				}


				else {
					nuevo = 1;
				}
		}

}
	else {
		if (tamppizpa < 1) {
			tamppizpa += 0.01;
				}
			else if (monitor1 < 1 && teclado1 < 1) {
				monitor1 += 0.02;
				teclado1 += 0.02;
			}
			else if (monitor2 < 1 && teclado2 < 1) {
				monitor2 += 0.02;
				teclado2 += 0.02;
			}
			else if (monitor3 < 1 && teclado3 < 1) {
				monitor3 += 0.02;
				teclado3 += 0.02;
			}
			else if (monitor4 < 1 && teclado4 < 1) {
				monitor4 += 0.02;
				teclado4 += 0.02;
			}
			else if (monitor5 < 1 && teclado5 < 1) {
				monitor5 += 0.02;
				teclado5 += 0.02;
			}
			else if (monitor6 < 1 && teclado6 < 1) {
				monitor6 += 0.02;
				teclado6 += 0.02;
			}
			else if (monitor7 < 1 && teclado7 < 1) {
				monitor7 += 0.02;
				teclado7 += 0.02;
			}
			else if (monitor8 < 1 && teclado8 < 1) {
				monitor8 += 0.02;
				teclado8 += 0.02;
			}
			else if (monitor9 < 1 && teclado9 < 1) {
				monitor9 += 0.02;
				teclado9 += 0.02;
			}
			else if (monitor10 < 1 && teclado10 < 1) {
				monitor10 += 0.02;
				teclado10 += 0.02;
			}
			else if (monitor11 < 1 && teclado11 < 1) {
				monitor11 += 0.02;
				teclado11 += 0.02;
			}
			else if (monitor12 < 1 && teclado12 < 1) {
				monitor12 += 0.02;
				teclado12 += 0.02;
			}
			else if (silla1 < 1) {
				silla1 += 0.02;
			}
			else if (silla222 < 1) {
				silla222 += 0.02;
			}
			else if (silla3 < 1) {
				silla3 += 0.02;
			}
			else if (silla4 < 1) {
				silla4 += 0.02;
			}
			else if (silla5 < 1) {
				silla5 += 0.02;
			}
			else if (silla6 < 1) {
				silla6 += 0.02;
			}
			else if (silla7 < 1) {
				silla7 += 0.02;
			}
			else if (silla8 < 1) {
				silla8 += 0.02;
			}
			else if (silla9 < 1) {
				silla9 += 0.02;
			}
			else if (silla10 < 1) {
				silla10 += 0.02;
			}
			else if (silla11 < 1) {
				silla11 += 0.02;
			}
			else if (silla12 < 1) {
				silla12 += 0.02;
			}
			else if (silla13 < 1) {
				silla13 += 0.02;
			}
			else if (silla14 < 1) {
				silla14 += 0.02;
			}
			else if (silla15 < 1) {
				silla15 += 0.02;
			}
			else if (silla16 < 1) {
				silla16 += 0.02;
			}
			else if (silla17 < 1) {
				silla17 += 0.02;
			}
			else if (silla18 < 1) {
				silla18 += 0.02;
			}
			else if (silla19 < 1) {
				silla19 += 0.02;
			}
			else if (silla20 < 1) {
				silla20 += 0.02;
			}
			else if (silla21 < 1) {
				silla21 += 0.02;
			}
			else if (silla22 < 1) {
				silla22 += 0.02;
			}
			else if (silla23 < 1) {
				silla23 += 0.02;
			}
			else if (silla24 < 1) {
				silla24 += 0.02;
				}
			else if (!rackflag) {
				rackflag = 1;
			}
			
		}
		if (rackflag) {
			if (rack11) {


				if (rackz > -0.232) {
					rackz -= 0.0005;
					if (RotHuman > -45) {
						RotHuman -= 0.15;
						if (RodillaD < 45) {
							PiernaD -= 0.4;
							RodillaD += 0.4;
						}
					}
					else if (RotHuman > -90) {
						RotHuman -= 0.15;
						if (RodillaD > 0) {
							PiernaD += 0.4;
							RodillaD -= 0.4;
						}

					}
				}
				else if (rackx > -0.090) {
					rackx -= 0.001;

				}
				else if (rackTam > 0.7) {
					rackTam -= 0.001;
				}
				else if (rackz > -0.320) {
					rackz -= 0.0003;
					if (RotHuman > -135) {
						RotHuman -= 0.1;
					}
				}
				else {
					rack11 = 0;
				}

			}
			else {

				if (rackz < -0.0700) {
					rackz += 0.0005;
					if(RotHuman < -90) {
						RotHuman += 0.05;

					}

				}
				else if (rackTam<1) {
					rackTam += 0.001;
					RotHuman = -90;
				}
				else if (purtaRot < 0) {
					purtaRot += 1;
				}
				else if (!pizzarronFlag) {
					pizzarronFlag = 1;
					vuelta1 = 1;
				}

			}
		
			

		
		}




		if (pizzarronFlag) {
			
			if (vuelta1) {

				if (RotHuman > -135) {
					RotHuman -= 1;
					if (RodillaD < 45) {
						PiernaD -= 1;
						RodillaD += 1;
					}
				}
				else if (RotHuman > -180) {
					RotHuman -= 1;
					if (RodillaD > 0) {
						PiernaD += 1;
						RodillaD -= 1;
					}

				}
				else {
					vuelta1 = 0;
					vuelta2 = 1;
				}
			}
			else {
				
				if (vuelta2) {
					if (tampiz > 0) {
						brazorot -= 0.0025;
						tampiz -= 0.005;
					}
					else {
						pizzarron3 = 0;
						vuelta2 = 0;
					}

				}
				else {
					if (tampiz < 1) {
						brazorot += 0.0025;
						tampiz += 0.005;
					}
					else if (RotHuman < -90) {
						RotHuman += 1;
						if (RodillaD < 45) {
							PiernaD -= 2;
							RodillaD += 2;
						}
					}
					else if (RotHuman < 0) {
						RotHuman += 1;
						if (RodillaD > 0) {
							PiernaD += 2;
							RodillaD -= 2;
						}
					}
					else if (RodillaD > 0) {
						PiernaD += 2;
						RodillaD -= 2;
					}else if (tiempoTexto < (contexto * 3)) {
						tiempoTexto += 0.01;
						tex3 = 1.0f;
						tex1 = 0.0f;
						tex2 = 0.0f;
						if (musica3) {
							PlaySound(NULL, NULL, 0);
							PlaySound(TEXT("sonidos/hablar.wav"), NULL, SND_FILENAME | SND_ASYNC);
							musica3 = false;
						}
					}
					else if (HombroD <= 0.0f) {
						HombroD += 0.3f;
						HombroI += 0.3f;
						tex3 = 0.0f;
						if (musicafinal) {
							PlaySound(NULL, NULL, 0);
							PlaySound(TEXT("sonidos/final.wav"), NULL, SND_FILENAME | SND_ASYNC);
							musicafinal = false;
						}

					}


				}



				
			}
		}
			



		if (hablar) {

			if (tiempoTexto < contexto) {
				tiempoTexto += 0.01;
				tex1 = 1.0f;
				tex2 = 0.0f;
				tex3 = 0.0f;
				printf("%f\n", tiempoTexto);
				if (musica1) {
					PlaySound(TEXT("sonidos/hablar.wav"), NULL, SND_FILENAME | SND_ASYNC);
					musica1 = false;
				}
			}
			else if (tiempoTexto < (contexto * 2)) {
				tiempoTexto += 0.01;
				tex1 = 0.0f;
				tex2 = 1.0f;
				tex3 = 0.0f;
				if (muica2) {
					PlaySound(NULL, NULL, 0);
					PlaySound(TEXT("sonidos/hablar.wav"), NULL, SND_FILENAME | SND_ASYNC);
					muica2 = false;
				}
			}
			else {
				if (HombroD > -90.0f) {
					HombroD -= 0.3f;
					HombroI -= 0.3f;

				}
				else {
					monitores = 1;
					hablar = 0;
				}
			}





		}


		if (humoflag) {

			float rango = 40.0;
			rhumo += 0.1;

			if (contadorhumo1 >= rango) {
				contadorhumo2 = 0.000001f;
				contadorhumo1 = 0;

				//printf("111111111111111111111111111111");
			}
			if (contadorhumo3 >= rango) {
				contadorhumo4 = 0.000001f;
				contadorhumo3 = 0;

				//printf("2222222222222222222222222222");
			}
			if (contadorhumo5 >= rango) {
				contadorhumo6 = 0.000001f;
				contadorhumo5 = 0;

				//printf("3333333333333333333333333333333");
			}
			if (contadorhumo7 >= rango) {
				contadorhumo8 = 0.000001f;
				contadorhumo7 = 0;

				//printf("444444444444444444444444444444444");
			}
			if (contadorhumo9 >= rango) {
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
				H[0].position = glm::vec3(humoPosX / contadorhumo2, contadorhumo1 + humoPosY / (contadorhumo2 * 2), humoPosZ / contadorhumo2);
				H[1].position = glm::vec3(humoPosX / contadorhumo4, contadorhumo3 + humoPosY / (contadorhumo4 * 2), humoPosZ / contadorhumo4);
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

					playIndex = 0;
					play = false;
					verdaderos();
					printf("termina anim\n");
					PlaySound(NULL, NULL, 0);

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
				poshumanox += KeyFrame[playIndex].poshumanoxInc;
				poshumanoy += KeyFrame[playIndex].poshumanoyInc;
				poshumanoz += KeyFrame[playIndex].poshumanozInc;

				RodillasI += KeyFrame[playIndex].RodillasIInc;
				RodillaD += KeyFrame[playIndex].RodillaDInc;
				HombroI += KeyFrame[playIndex].HombroIInc;
				HombroD += KeyFrame[playIndex].HombroDInc;
				PiernaI += KeyFrame[playIndex].PiernaIInc;
				PiernaD += KeyFrame[playIndex].PiernaDInc;

				RotHuman += KeyFrame[playIndex].RotHumanInc;


				i_curr_steps++;

			}

		}


	
}
void MouseCallback(GLFWwindow* window, double xPos, double yPos){
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