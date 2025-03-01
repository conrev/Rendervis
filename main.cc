#include "core/Application.hpp"

int main(int argc, char *argv[]) {
    Rendervis::AppProperties prop;
    prop.window_name = "Rendervis App";
    prop.window_width = 1920;
    prop.window_height = 1080;
    Rendervis::Application app{prop};
    app.Run();

    return 0;
}