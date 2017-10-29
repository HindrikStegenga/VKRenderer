#include "Application.h"

int main() {

    auto app = Application();

    auto t = thread([&app]{
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        app.stop();
    });

    app.run();
    t.join();

    return EXIT_SUCCESS;
}