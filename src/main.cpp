#include "Application.h"
#include "Serializables/VulkanTypes.h"

int main() {


    VertexLayout layout;

    std::ifstream file("config/vertex_layouts/PositionTexCoordNormals.json");

    if(!file.is_open())
        Logger::failure("File could not be opened:");

    std::stringstream buffer;
    buffer << file.rdbuf();

    auto json_rep = json::parse(buffer.str());

    layout = json_rep.get<VertexLayout>();

    std::cout << layout.name << std::endl;
    for(const auto& c : layout.bindings) {
        std::cout << c.binding << std::endl;
        std::cout << c.inputRate << std::endl;

        for(const auto& a : c.attributes) {
            std::cout << a.name << std::endl;
            std::cout << a.location << std::endl;
            std::cout << a.type << std::endl;
        }
    }


    Application app;
    app.run();

    return 0;
}