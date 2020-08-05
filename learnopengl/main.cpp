#include <string>
#include <iostream>
#include <math.h>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <SDL2/SDL.h>

SDL_Window* mainWindow;

SDL_GLContext mainContext;

std::string programName = "Learn OpenGL!";

std::string g_VertexBuffer;
std::string g_FragmentBuffer;

unsigned int shaderProgram;

bool g_loop = true;
float offSet = 0.3f;

bool Init();
bool SetOpenGLAttributes();
void SetVAO();
void SetShaders();
std::string ReadFile(const char* file);
void RunGame();
void Render();
void Update();
void Events();
void Cleanup();

int main(int argc, char* argv[])
{
  if(!Init()) return -1;

  RunGame();

  Cleanup();

  return 0;
}

bool Init()
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "Fail to init SDL\n";
    return false;
  }

  mainWindow = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	 512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

  if(!mainWindow)
  {
    std::cout << "Unable to create window\n" << "Error: " << SDL_GetError() << std::endl;
    return false;
  }

  mainContext = SDL_GL_CreateContext(mainWindow);

  if (glewInit() == GLEW_OK) std::cout << "Glew Init Ok!" << std::endl;

  SetOpenGLAttributes();

  SDL_GL_SetSwapInterval(1);

  SetShaders();
  SetVAO();

  return true;
}

bool SetOpenGLAttributes()
{
	// Set our OpenGL version.
	// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	// Turn on double buffering with a 24bit Z buffer.
	// You may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	return true;
}

void SetVAO()
{
  float vertices[] =
  {
     0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
  };

  unsigned int indices[] =
  {
      0, 1, 3,
      1, 2, 3,
  };

  unsigned int VBO, VAO;
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  unsigned int position = glGetAttribLocation(shaderProgram, "aPos");
  glEnableVertexAttribArray(position);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  position = glGetAttribLocation(shaderProgram, "aColor");
  glEnableVertexAttribArray(position);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(VAO);
/*
  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
*/
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void SetShaders()
{
  unsigned int vertexShader, fragmentShader;
  g_VertexBuffer = ReadFile("vertex.glsl");
  const char *vertexShaderSource = g_VertexBuffer.c_str();
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int  success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  g_FragmentBuffer = ReadFile("fragment.glsl");
  const char *fragmentShaderSource = g_FragmentBuffer.c_str();
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  glUseProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

std::string ReadFile(const char* file)
{
		// Open file
		std::ifstream t(file);

		// Read file into buffer
		std::stringstream buffer;
		buffer << t.rdbuf();

		// Make a std::string and fill it with the contents of buffer
		std::string fileContent = buffer.str();

		return fileContent;
	}

void RunGame()
{
	while (g_loop)
	{
    Events();
    Update();
    Render();
	}
}

void Events()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
      g_loop = false;

    if (event.type == SDL_KEYDOWN)
    {
      switch (event.key.keysym.sym)
      {
      case SDLK_ESCAPE: g_loop = false; break;

      case SDLK_RIGHT: offSet += 0.1f; break;
      case SDLK_LEFT: offSet -= 0.1f; break;
      }
    }
  }
}

void Update()
{
  float timeValue = SDL_GetTicks() / 1000;
  float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
  int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
  glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

  int vertexLocation = glGetUniformLocation(shaderProgram, "offSet");
  glUniform2f(vertexLocation, offSet, 0.0f);
}

void Render()
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawArrays(GL_TRIANGLES, 0, 3);
  // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  SDL_GL_SwapWindow(mainWindow);
}

void Cleanup()
{
  SDL_GL_DeleteContext(mainContext);
  SDL_DestroyWindow(mainWindow);
  SDL_Quit();
}
