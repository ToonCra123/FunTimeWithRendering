#include "src/App.h"

#if defined(_WIN32)
// Windows-specific code

// step 2: jiggle fisics
#include <windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    App app;
    app.Run();

    return 0;
}

#elif defined(__APPLE__) && defined(__MACH__)
int main() {
    App app;
    app.Run();

    return 0;
}
#endif