#ifndef APPLICATION_H
#define APPLICATION_H

#include <glad/glad.h>
#include <SDL2/SDL.h>

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
        virtual void OnInput();
        virtual void OnGUI();
        virtual void OnUpdate();

    private:
        SDL_Window* window_{};
        AppProperties app_setting_;
        SDL_GLContext gl_context_{};
        bool running_{};
        std::shared_ptr<Scene> active_scene_{};
    };

}  // namespace Rendervis

#endif