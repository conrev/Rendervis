#include <memory>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;
const float CAMERA_SPEED = 0.01f;

SDL_Window *gWindow = NULL;
SDL_GLContext gGLContext = NULL;
bool gQuit = false;

unsigned int VBO, VAO, EBO, shaderProgram, texture;

GLfloat vertices[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
        0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
        0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f};

// Indices for vertices order
GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4};

GLubyte *textureData;
int textureWidth, textureHeight;
glm::vec3 cameraPosition = glm::vec3(0.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraTarget));

bool isClicked = false;

bool setupShader();

void APIENTRY glDebugOutput(GLenum source,
                   GLenum type,
                   unsigned int id,
                   GLenum severity,
                   GLsizei length,
                   const char *message,
                   const void *userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        std::cout << "Source: API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        std::cout << "Source: Window System";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        std::cout << "Source: Shader Compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        std::cout << "Source: Third Party";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        std::cout << "Source: Application";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        std::cout << "Source: Other";
        break;
    }
    std::cout << std::endl;

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        std::cout << "Type: Error";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "Type: Deprecated Behaviour";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "Type: Undefined Behaviour";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "Type: Portability";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "Type: Performance";
        break;
    case GL_DEBUG_TYPE_MARKER:
        std::cout << "Type: Marker";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        std::cout << "Type: Push Group";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        std::cout << "Type: Pop Group";
        break;
    case GL_DEBUG_TYPE_OTHER:
        std::cout << "Type: Other";
        break;
    }
    std::cout << std::endl;

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "Severity: high";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "Severity: medium";
        break;
    case GL_DEBUG_SEVERITY_LOW:
        std::cout << "Severity: low";
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        std::cout << "Severity: notification";
        break;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

unsigned char *loadTextures(const std::string &filename, int &width, int &height)
{
    int _;
    unsigned char *data = stbi_load(filename.c_str(), &textureWidth, &textureHeight, &_, 0);

    return data;
}

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
    else
    {
        std::cout << "Failed to Open File" << errno << std::endl;
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
    // glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(glDebugOutput, 0);

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
        if (evt.type == SDL_KEYDOWN)
        {
            Uint8 const *keys = SDL_GetKeyboardState(nullptr);
            if (keys[SDL_SCANCODE_W] == 1)
                cameraPosition += cameraTarget * CAMERA_SPEED;
            if (keys[SDL_SCANCODE_S] == 1)
                cameraPosition -= cameraTarget * CAMERA_SPEED;
            if (keys[SDL_SCANCODE_A] == 1)
                cameraPosition -= cameraRight * CAMERA_SPEED;
            if (keys[SDL_SCANCODE_D] == 1)
                cameraPosition += cameraRight * CAMERA_SPEED;
        }
        if (evt.type == SDL_MOUSEBUTTONDOWN)
        {
            if (evt.button.button == SDL_BUTTON_RIGHT)
            {
                isClicked = true;
                // SDL_WarpMouseInWindow(gWindow, 0, 0);
                std::cout << "disable cursor : " << SDL_ShowCursor(SDL_FALSE) << std::endl;
                // SDL_SetRelativeMouseMode(SDL_TRUE);
            }
        }
        if (evt.type == SDL_MOUSEBUTTONUP)
        {
            if (evt.button.button == SDL_BUTTON_RIGHT)
            {
                isClicked = false;
                // SDL_WarpMouseInWindow(gWindow, 0, 0);
                std::cout << "Re enabled cursor : " << SDL_ShowCursor(SDL_ENABLE) << std::endl;
                // SDL_SetRelativeMouseMode(SDL_FALSE);
            }
        }
        if (evt.type == SDL_MOUSEMOTION)
        {
            if (!isClicked)
                return;

            // std::cout << evt.motion.xrel << " " << evt.motion.yrel << std::endl;
            cameraTarget = glm::normalize(glm::rotate(cameraTarget, glm::radians(evt.motion.yrel * -0.1f), glm::normalize(glm::cross(cameraTarget, cameraUp))));
            cameraTarget = glm::normalize(glm::rotate(cameraTarget, glm::radians(evt.motion.xrel * -0.1f), cameraUp));

            cameraRight = glm::normalize(glm::cross(cameraTarget, cameraUp));
        }
    }
}

bool setupShader()
{

    // shader debuggers
    int success;
    char infoLog[512];

    std::string vertexShaderSource = loadShaderFromFile("./resources/shaders/vert.glsl");
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

    std::string fragmentShaderSource = loadShaderFromFile("./resources/shaders/frag.glsl");
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

    textureData = loadTextures("./resources/textures/sample-texture.jpg", textureWidth, textureHeight);
    if (textureData == nullptr)
    {
        std::cout << "ERROR::TEXTURE::LOAD_FAILED\n";
        return false;
    }

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

    // tell opengl how to interpret our bounded array buffer, aka the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // VAO attribute for textures
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // setup textures object
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // unbind everything to ensure we dont accidentally run anything
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void draw()
{

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);

    glm::mat4 transform = glm::mat4(1.0f);
    // transform = glm::rotate(transform, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // transform = glm::rotate(transform, float(SDL_GetTicks64()) / 1000.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraTarget, cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transformMatrix");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}

void engineLoop()
{

    preDraw();

    while (!gQuit)
    {
        input();

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
    stbi_image_free(textureData);
    SDL_DestroyWindow(gWindow);

    SDL_Quit();
}

int main(int argv, char** args)
{
    int initState = init();

    if (!initState)
        return 1;

    engineLoop();
    cleanUp();

    return 0;
}