#include "core/Application.hpp"

#include <iostream>

namespace Rendervis {

    Application::~Application() {
        SDL_GL_DeleteContext(gl_context_);
        SDL_DestroyWindow(window_);
        SDL_Quit();
    }

    bool Application::Init() {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Failed to initialize the SDL2 library\n";
            return false;
        }

        window_ = SDL_CreateWindow(app_setting_.window_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   app_setting_.window_width, app_setting_.window_height, SDL_WINDOW_OPENGL);

        if (!window_) {
            std::cerr << "Failed to create SDL Window\n";
            return false;
        }

        SDL_GLContext gl_context = SDL_GL_CreateContext(window_);

        if (!gl_context) {
            std::cerr << "Failed to Create GL Context\n";
            return false;
        }

        if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
            std::cerr << "Failed to initialize GLAD\n";
            return false;
        }

        glViewport(0, 0, app_setting_.window_width, app_setting_.window_height);
        // glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);

        glEnable(GL_DEBUG_OUTPUT);
        // glDebugMessageCallback(glDebugOutput, 0);

        return true;
    }

    void Application::Run() {
        if (!Application::Init()) return;

        running_ = true;

        while (running_) {
            Application::OnInput();
            // Swap front to back buffer
            SDL_GL_SwapWindow(window_);
        }
    }

    void Application::OnGUI() {}

    void Application::OnInput() {
        SDL_Event evt;

        while (SDL_PollEvent(&evt) != 0) {
            if (evt.type == SDL_QUIT) {
                Application::Close();
            }
        }
    }

    void Application::OnUpdate() {}

    void Application::Close() {
        // For now just stop the engine loop, should be deallocate here?
        running_ = false;
    }

}  // namespace Rendervis