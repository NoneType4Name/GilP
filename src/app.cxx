#include <format>
#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

static void glfw_error_callback( int error, const char *description )
{
    std::cout << std::format( "GLFW Error {}: {}\n", error, description );
}

// Main code
int main()
{
    glfwSetErrorCallback( glfw_error_callback ); // Errors callback.
    if( !glfwInit() )
        return 1;
    const char *glsl_version = "#version 130";
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 ); // Set gl 3.0 version.
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );

    GLFWwindow *window = glfwCreateWindow(
        800, 600, "Dummy Window", nullptr, nullptr );
    if( window == nullptr )
        return 1;
    glfwMakeContextCurrent( window ); // Set window as current context.
    glfwSwapInterval( 1 );            // Enable vsync.

    // Main loop
    while( !glfwWindowShouldClose( window ) )
    {
        glfwPollEvents();

        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize( window, &display_w, &display_h );
        glViewport( 0, 0, display_w, display_h );
        glClearColor( .5f, .1f, .3f, 1.f );
        glClear( GL_COLOR_BUFFER_BIT );
        glfwSwapBuffers( window );
    }

    // Cleanup
    glfwDestroyWindow( window );
    glfwTerminate();

    return 0;
}
