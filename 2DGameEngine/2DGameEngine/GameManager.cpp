#include "Game.h"

GameManager::GameManager(Game* game)
{
	this->focussedGame = game;

	setup();
	start();
}


GameManager::~GameManager()
{
	GameObjectManager::deletePool();
	delete this->gameRenderer;
}

#pragma region Game Loop
void GameManager::setup()
{
	initGLFW();
	initWindow();
	initGLEW();
	initOpenGLOptions();
	initShaders();
	initCamera();
	initRenderer();

	endNextFrame = false;
}

void GameManager::start()
{
	this->focussedGame->start();

	while (!this->endNextFrame)
	{
		update();

		draw();
	}
}

void GameManager::update()
{
	this->focussedGame->update();
}

void GameManager::draw()
{
	this->focussedGame->draw();
}

#pragma endregion

#pragma region Initializers

void GameManager::initGLFW()
{
	glfwSetErrorCallback(&GameManager::glfwErrorCallback);

	//Initialize GLFW
	if (glfwInit() == GL_FALSE)
	{
		std::cout << "Error, GLFW did not initialize" << "\n";
		glfwTerminate();
	}
}

void GameManager::initWindow()
{
	//Initialize the window
	this->gameWindow = new Window();
}

void GameManager::initGLEW()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		std::cout << "Error, Glew did not initialize. Did you create a window before GLEW initializes?" << "\n";
	}
}

void GameManager::initOpenGLOptions()
{
	//OpenGL Options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OpenGLErrorMessageCallBack, 0);

	//glEnable(GL_CULL_FACE);

	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GameManager::initShaders()
{
	this->gameObjectShader = new Shader(4, 4, "GameObjectVertexCore.glsl", "GameObjectFragmentCore.glsl");
}

void GameManager::initCamera()
{
	this->gameCamera = new Camera(new glm::vec3(400, 400, 0));
}

void GameManager::initRenderer()
{
	this->gameRenderer = new Renderer2D(this->mainShader, this->gameObjectShader, this->gameWindow, this->gameCamera);
	this->gameRenderer->setBackgroundColor(90.f / 255, 130.f / 255, 180.f / 255, 0.f);
}
#pragma endregion

#pragma region Callbacks

void GameManager::glfwErrorCallback(int id, const char* description)
{
	std::cout << description << "\n";
}

void APIENTRY GameManager::OpenGLErrorMessageCallBack(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

#pragma endregion