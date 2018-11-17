#include "Application.h"
#include "Serializables/VulkanTypes.h"

int main() {


    VertexBufferFormatDescriptor vertexBufferFormatDescriptor;
    MeshDescriptor meshDescriptor;

    std::ifstream file("resources/descriptors/vertex buffer formats/PositionTexCoordsNormals.json");

    if(!file.is_open())
        Logger::failure("File could not be opened:");

    std::stringstream buffer;
    buffer << file.rdbuf();

    auto json_rep = json::parse(buffer.str());

    vertexBufferFormatDescriptor = json_rep.get<VertexBufferFormatDescriptor>();

    std::cout << vertexBufferFormatDescriptor.name << std::endl;

    for(auto& a : vertexBufferFormatDescriptor.formats) {
        std::cout << a.name << std::endl;
        std::cout << a.type << std::endl;
        std::cout << a.location << std::endl;
    }

    file.close();
    file = std::ifstream("resources/descriptors/meshes/cube.json");
    if(!file.is_open())
        Logger::failure("File could not be opened:");

    std::stringstream buffer2;
    buffer2 << file.rdbuf();

    auto json_rep2 = json::parse(buffer2.str());

    meshDescriptor = json_rep2.get<MeshDescriptor>();

    std::cout << meshDescriptor.name;

    for(auto& a : meshDescriptor.buffers) {
        std::cout << a.vertexBufferFileName << std::endl;
        std::cout << a.vertexFormat << std::endl;
        std::cout << a.indexBufferFileName << std::endl;
        std::cout << a.indexBufferTypeSize << std::endl;
    }
    file.close();

    Application app;
    app.run();

    return 0;
}