#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>

SDL_Window *gWindow = NULL;
SDL_GLContext gGLContext = NULL;
bool gQuit = false;

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 640;
unsigned int VBO, VAO, EBO, shaderProgram;
float cycledColor[4]{1.0f, 0.0f, 0.0f, 1.0f};

GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f, // p0
    1.0f, 0.0f, 0.0f,   // c0
    0.5f, -0.5f, 0.0f,  // p1
    0.0f, 1.0f, 0.0f,   // c1
    -0.5f, 0.5f, 0.0f,  // p2
    0.0f, 0.0f, 1.0f,   // c2
    0.5f, 0.5f, 0.0f,   // p3
    0.0f, 0.0f, 1.0f    // c3

};

GLuint indices[] = {
    // note that we start from 0!
    0, 1, 2, // first triangle
    1, 3, 2  // second triangle
};

bool setupShader();
std::string loadShaderFromFile(const std::string &filename)
{
    std::string result = "";

    std::string line = "";
    std::ifstream file(filename.c_str());
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            result += line + '\n';
        }
        file.close();
    }

    return result;
}

bool init()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return false;
    }

    gWindow = SDL_CreateWindow("SDL2 Window",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT,
                               SDL_WINDOW_OPENGL);

    if (!gWindow)
    {
        std::cout << "Failed to create SDL Window";
        return false;
    }

    gGLContext = SDL_GL_CreateContext(gWindow);

    if (!gGLContext)
    {
        std::cout << "Failed to Create GL Context";
        return false;
    }

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    // initialize glViewport
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);

    // setupShader
    if (!setupShader())
    {
        std::cout << "Failed to setup Shader" << std::endl;
        return false;
    };

    return true;
}

void input()
{
    SDL_Event evt;

    while (SDL_PollEvent(&evt) != 0)
    {
        if (evt.type == SDL_QUIT)
        {
            gQuit = true;
        }
    }
}

bool setupShader()
{

    // shader debuggers
    int success;
    char infoLog[512];

    std::string vertexShaderSource = loadShaderFromFile("./shaders/vert.glsl");
    const char *vertexShaderSrc = vertexShaderSource.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        return success;
    }

    std::string fragmentShaderSource = loadShaderFromFile("./shaders/frag.glsl");
    const char *fragmentShaderSrc = fragmentShaderSource.c_str();

    unsigned int fragmentShader;

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        return success;
    }

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

void preDraw()
{
    // VAO stores pointers to VBO to potentially swap many different VBOs
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind the vertex array
    glBindVertexArray(VAO);
    // The array buffer is now bounded to our VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // the VBO now has data, our vertices array
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // bind array element buffer to our EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // put the data in
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    // tell opengl how to interpret our bounded array buffer, aka the VBO

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void draw()
{
    uint64_t time_elapsed = SDL_GetTicks64();
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    cycledColor[0] = (sin((float)time_elapsed / 100) / 2.0f) + 0.5;
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "cycledColor");
    glUseProgram(shaderProgram);
    glUniform4fv(vertexColorLocation, 1, cycledColor);
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void engineLoop()
{

    while (!gQuit)
    {
        input();

        preDraw();

        draw();
        // Swap front to back buffer
        SDL_GL_SwapWindow(gWindow);
    }
}

void cleanUp()
{

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDeleteProgram(shaderProgram);

    SDL_DestroyWindow(gWindow);

    SDL_Quit();
}

int main()
{
    int initState = init();

    if (!initState)
        return 1;

    engineLoop();
    cleanUp();

    return 0;
}