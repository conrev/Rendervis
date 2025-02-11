
#include "core/Application.hpp"

#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <memory>

#include "core/Camera.hpp"
#include "core/Scene.hpp"
#include "renderer/Entity.hpp"
#include "renderer/Shader.hpp"

namespace Rendervis {

    std::shared_ptr<Scene> CreateExampleScene() {
        std::shared_ptr<Shader> object_shader =
            std::make_shared<Rendervis::Shader>("resources/shaders/phongVert.glsl", "resources/shaders/SolidColorPhong.glsl");
        std::shared_ptr<Shader> light_shader =
            std::make_shared<Rendervis::Shader>("resources/shaders/lightVert.glsl", "resources/shaders/lightFrag.glsl");

        // Vertices coordinates
        std::vector<GLfloat> plane_vertices{//     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
                                            -1.0f, 0.0f, 1.0f,  0.18f, 0.18f, 0.24f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                            -1.0f, 0.0f, -1.0f, 0.18f, 0.18f, 0.24f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                                            1.0f,  0.0f, -1.0f, 0.18f, 0.18f, 0.24f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                                            1.0f,  0.0f, 1.0f,  0.18f, 0.18f, 0.24f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f};

        // Indices for vertices order
        std::vector<GLint> plane_indices{0, 1, 2, 0, 2, 3};

        // Vertices coordinates
        std::vector<GLfloat> pyramid_vertices{
            //     COORDINATES     /        COLORS          /    TexCoord   / NORMALS //
            -0.5f, 0.0f, 0.5f,  0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.0f,  -1.0f, 0.0f,  // Bottom side
            -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 5.0f, 0.0f,  -1.0f, 0.0f,  // Bottom side
            0.5f,  0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 5.0f, 0.0f,  -1.0f, 0.0f,  // Bottom side
            0.5f,  0.0f, 0.5f,  0.83f, 0.70f, 0.44f, 5.0f, 0.0f, 0.0f,  -1.0f, 0.0f,  // Bottom side

            -0.5f, 0.0f, 0.5f,  0.83f, 0.70f, 0.44f, 0.0f, 0.0f, -0.8f, 0.5f,  0.0f,  // Left Side
            -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, -0.8f, 0.5f,  0.0f,  // Left Side
            0.0f,  0.8f, 0.0f,  0.92f, 0.86f, 0.76f, 2.5f, 5.0f, -0.8f, 0.5f,  0.0f,  // Left Side

            -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, 0.0f,  0.5f,  -0.8f,  // Non-facing side
            0.5f,  0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.0f,  0.5f,  -0.8f,  // Non-facing side
            0.0f,  0.8f, 0.0f,  0.92f, 0.86f, 0.76f, 2.5f, 5.0f, 0.0f,  0.5f,  -0.8f,  // Non-facing side

            0.5f,  0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.8f,  0.5f,  0.0f,  // Right side
            0.5f,  0.0f, 0.5f,  0.83f, 0.70f, 0.44f, 5.0f, 0.0f, 0.8f,  0.5f,  0.0f,  // Right side
            0.0f,  0.8f, 0.0f,  0.92f, 0.86f, 0.76f, 2.5f, 5.0f, 0.8f,  0.5f,  0.0f,  // Right side

            0.5f,  0.0f, 0.5f,  0.83f, 0.70f, 0.44f, 5.0f, 0.0f, 0.0f,  0.5f,  0.8f,  // Facing side
            -0.5f, 0.0f, 0.5f,  0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.0f,  0.5f,  0.8f,  // Facing side
            0.0f,  0.8f, 0.0f,  0.92f, 0.86f, 0.76f, 2.5f, 5.0f, 0.0f,  0.5f,  0.8f   // Facing side
        };

        // Indices for vertices order
        std::vector<GLint> pyramid_indices{
            0,  1,  2,   // Bottom side
            0,  2,  3,   // Bottom side
            4,  6,  5,   // Left side
            7,  9,  8,   // Non-facing side
            10, 12, 11,  // Right side
            13, 15, 14   // Facing side
        };

        std::shared_ptr<Entity> plane = std::make_shared<Rendervis::Entity>(plane_vertices, plane_indices);
        std::shared_ptr<Entity> light = std::make_shared<Rendervis::Entity>(pyramid_vertices, pyramid_indices);

        // fix the hardcoded aspect ratio
        std::shared_ptr<Rendervis::Camera> main_camera =
            std::make_shared<Rendervis::Camera>(glm::vec3(.0, 2.0, 5.0), (float)800 / 640, 0.1f, 100.0f, glm::radians(45.0f));

        std::shared_ptr<Rendervis::Scene> scene = std::make_shared<Rendervis::Scene>();
        scene->SetMainCamera(main_camera);

        scene->AddShader(object_shader, "object_shader");
        scene->AddShader(light_shader, "light_shader");

        scene->AddEntity(plane, "plane");
        scene->AddEntity(light, "light");

        return scene;
    }

    void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message,
                                const void *userParam) {
        // ignore non-significant error/warning codes
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

        std::cerr << "---------------" << std::endl;
        std::cerr << "Debug message (" << id << "): " << message << std::endl;

        switch (source) {
            case GL_DEBUG_SOURCE_API:
                std::cerr << "Source: API";
                break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                std::cerr << "Source: Window System";
                break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                std::cerr << "Source: Shader Compiler";
                break;
            case GL_DEBUG_SOURCE_THIRD_PARTY:
                std::cerr << "Source: Third Party";
                break;
            case GL_DEBUG_SOURCE_APPLICATION:
                std::cerr << "Source: Application";
                break;
            case GL_DEBUG_SOURCE_OTHER:
                std::cerr << "Source: Other";
                break;
        }
        std::cerr << std::endl;

        switch (type) {
            case GL_DEBUG_TYPE_ERROR:
                std::cerr << "Type: Error";
                break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                std::cerr << "Type: Deprecated Behaviour";
                break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                std::cerr << "Type: Undefined Behaviour";
                break;
            case GL_DEBUG_TYPE_PORTABILITY:
                std::cerr << "Type: Portability";
                break;
            case GL_DEBUG_TYPE_PERFORMANCE:
                std::cerr << "Type: Performance";
                break;
            case GL_DEBUG_TYPE_MARKER:
                std::cerr << "Type: Marker";
                break;
            case GL_DEBUG_TYPE_PUSH_GROUP:
                std::cerr << "Type: Push Group";
                break;
            case GL_DEBUG_TYPE_POP_GROUP:
                std::cerr << "Type: Pop Group";
                break;
            case GL_DEBUG_TYPE_OTHER:
                std::cerr << "Type: Other";
                break;
        }
        std::cerr << std::endl;

        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:
                std::cerr << "Severity: high";
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                std::cerr << "Severity: medium";
                break;
            case GL_DEBUG_SEVERITY_LOW:
                std::cerr << "Severity: low";
                break;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                std::cerr << "Severity: notification";
                break;
        }
        std::cerr << std::endl;
        std::cerr << std::endl;
    }

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
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Failed to initialize the SDL2 library\n";
            return false;
        }

        window_ = SDL_CreateWindow(app_setting_.window_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   app_setting_.window_width, app_setting_.window_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

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
        glEnable(GL_MULTISAMPLE);
        glDebugMessageCallback(glDebugOutput, 0);

        active_scene_ = CreateExampleScene();

        return true;
    }

    void Application::Run() {
        if (!Application::Init()) return;
        uint64_t last_frame = 0;
        running_ = true;
        while (running_) {
            uint64_t current = SDL_GetPerformanceCounter();
            float dt = (double)((current - last_frame) / (double)SDL_GetPerformanceFrequency());
            last_frame = current;

            // std::cout << "Current DeltaTime: " << std::to_string(dt) << std::endl;
            // std::cout << "Current FPS: " << std::to_string(1.0f / dt) << std::endl;

            Application::OnInput(dt);
            Application::OnUpdate(dt);
            uint64_t end = SDL_GetPerformanceCounter();

            // Swap front to back buffer
            SDL_GL_SwapWindow(window_);
        }
    }

    void Application::OnGUI(float dt) {}

    void Application::OnInput(float dt) {
        SDL_Event evt;

        glm::vec2 camera_delta = glm::vec2(0.0f);
        static bool is_clicked;

        while (SDL_PollEvent(&evt) != 0) {
            if (evt.type == SDL_QUIT) {
                Application::Close();
            }

            if (evt.type == SDL_MOUSEBUTTONDOWN) {
                if (evt.button.button == SDL_BUTTON_RIGHT) {
                    is_clicked = true;
                    SDL_SetRelativeMouseMode(SDL_TRUE);
                }
            }
            if (evt.type == SDL_MOUSEBUTTONUP) {
                if (evt.button.button == SDL_BUTTON_RIGHT) {
                    is_clicked = false;
                    SDL_SetRelativeMouseMode(SDL_FALSE);
                }
            }
            if (evt.type == SDL_MOUSEMOTION) {
                if (!is_clicked) continue;

                active_scene_->MainCamera()->Rotate(glm::vec3(-evt.motion.xrel, -evt.motion.yrel, 0), dt, 5.0f);
            }
        }

        uint8_t const *keys = SDL_GetKeyboardState(nullptr);
        float xDelta = 0, yDelta = 0;
        if (keys[SDL_SCANCODE_W] == 1) camera_delta.x += 1.0f;
        if (keys[SDL_SCANCODE_S] == 1) camera_delta.x -= 1.0f;
        if (keys[SDL_SCANCODE_A] == 1) camera_delta.y -= 1.0f;
        if (keys[SDL_SCANCODE_D] == 1) camera_delta.y += 1.0f;

        if (glm::length(camera_delta) > 0.0f) active_scene_->MainCamera()->Move(camera_delta, dt, 10.0f);
    }

    void Application::OnUpdate(float dt) {
        glClearColor(0.843f, 0.87f, 0.98f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Transform plane_transform{glm::vec3(0.0, 0.0, 0.0), glm::identity<glm::quat>(), glm::vec3(50.0f)};
        std::shared_ptr<Rendervis::Camera> main_camera = active_scene_->MainCamera();
        glm::mat4 view = main_camera->GetViewMatrix();
        glm::mat4 projection = main_camera->GetProjectionMatrix();

        std::shared_ptr<Rendervis::Entity> plane_object = active_scene_->GetEntity("plane");
        std::shared_ptr<Rendervis::Shader> plane_shader = active_scene_->GetShader("object_shader");

        plane_shader->Bind();

        plane_shader->SetUniformMat4("viewMatrix", view);
        plane_shader->SetUniformMat4("projectionMatrix", projection);
        plane_shader->SetUniformVec3("lightColor", glm::vec3(1.0f));
        plane_shader->SetUniformVec3("lightPosition", glm::vec3(1.0f, 4.0f, -1.0f));
        plane_shader->SetUniformVec3("viewPosition", main_camera->Position());

        plane_object->Draw(plane_shader, plane_transform);

        Transform light_transform{glm::vec3(1.0f, 10.0f, -1.0f), glm::identity<glm::quat>(), glm::vec3(1.0f)};

        std::shared_ptr<Rendervis::Entity> light_object = active_scene_->GetEntity("light");
        std::shared_ptr<Rendervis::Shader> light_shader = active_scene_->GetShader("light_shader");

        light_shader->Bind();
        light_shader->SetUniformMat4("viewMatrix", view);
        light_shader->SetUniformMat4("projectionMatrix", projection);
        plane_shader->SetUniformVec3("lightColor", glm::vec3(1.0f));
        light_object->Draw(light_shader, light_transform);
    }

    void Application::Close() {
        // For now just stop the engine loop, should be deallocate here?
        running_ = false;
    }

    float Application::AspectRatio() const {
        return (float)app_setting_.window_width / app_setting_.window_height;
    }

}  // namespace Rendervis