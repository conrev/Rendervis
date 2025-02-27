#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>

#include <memory>
#include <string>

#include "core/Scene.hpp"

namespace Rendervis {

    struct AppProperties {
        std::string window_name;
        uint16_t window_height;
        uint16_t window_width;
    };

    class Application {
        // TODO : Make this properly RAII
    public:
        Application(AppProperties setting) : app_setting_(setting) {}
        ~Application();

        bool Init();
        void Run();
        void Close();
        float AspectRatio() const;

    public:
        virtual void OnInput(float dt);
        virtual void OnGUI(float dt);
        virtual void OnUpdate(float dt);

    private:
        SDL_Window* window_{};
        AppProperties app_setting_;
        SDL_GLContext gl_context_{};
        bool running_{};
        std::shared_ptr<Scene> active_scene_{};
    };

}  // namespace Rendervis

#endif