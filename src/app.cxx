#include <format>
#include <iostream>
#include <string>
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
    glfwWindowHint( GLFW_DECORATED, 0 );
    glfwWindowHint( GLFW_FLOATING, 1 );
    glfwWindowHint( GLFW_TRANSPARENT_FRAMEBUFFER, 1 );

    GLFWwindow *window = glfwCreateWindow(
        800, 600, "GilP", nullptr, nullptr );
    if( window == nullptr )
        return 1;
    glfwMakeContextCurrent( window ); // Set window as current context.
    glfwSwapInterval( 1 );            // Enable vsync.

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ( void )io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls.
    // io.ConfigFlags |=
    //     ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls.
    // Setup Dear ImGui style.
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL( window, true ); // Init ImGui for OpenGL.
    ImGui_ImplOpenGL3_Init( glsl_version );       // Init GL backend.

    ImVec4 CColor = ImVec4( 0.f, 0.f, 0.f, 0.f ); // Clear color.
    std::string foregroundWindow;
    foregroundWindow.resize( 17 );

    // Main loop
    while( !glfwWindowShouldClose( window ) )
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to
        // tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to
        // your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input
        // data to your main application, or clear/overwrite your copy of the
        // keyboard data. Generally you may always pass all inputs to dear imgui,
        // and hide them from your application based on those two flags.
        glfwPollEvents();
        // if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
        //   ImGui_ImplGlfw_Sleep(10);
        //   continue;
        // }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            static float f     = 0.0f;
            static int counter = 0;

            ImGui::Begin( "Hello, world!" );                                                                        // Create a window called "Hello, world!"
                                                                                                                    // and append into it.
            ImGui::Text( "%s, %s", ( foregroundWindow == "Genshin Impact" ? "1" : "0" ), foregroundWindow.data() ); // Display some text (you can
                                                                                                                    // use a format strings too)

            ImGui::SliderFloat( "float", &f, 0.0f,
                                1.0f ); // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit4(
                "clear color",
                ( float * )&CColor ); // Edit 3 floats representing a color

            if( ImGui::Button( "Button" ) ) // Buttons return true when clicked (most
                                            // widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text( "counter = %d", counter );

            ImGui::Text( "Application average %.3f ms/frame (%.1f FPS)",
                         1000.0f / io.Framerate, io.Framerate );
            int32_t windowW, windowH;
            glfwGetWindowSize( window, &windowW, &windowH );
            ImVec2 size{ ImGui::GetWindowSize() };
            if( size.x + 1 != windowW || size.y != windowH )
                glfwSetWindowSize( window, size.x, size.y );
            ImVec2 pos{ ImGui::GetWindowPos() };
            if( pos.x || pos.y )
                ImGui::SetWindowPos( { 0, 0 } );
            glfwGetWindowPos( window, &windowW, &windowH );
            glfwSetWindowPos( window, windowW + ( pos.x ), windowH + ( pos.y ) );
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize( window, &display_w, &display_h );
        glViewport( 0, 0, display_w, display_h );
        glClearColor( CColor.x, CColor.y, CColor.z, CColor.w );
        glClear( GL_COLOR_BUFFER_BIT );
        ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

        glfwSwapBuffers( window );
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow( window );
    glfwTerminate();

    return 0;
}
