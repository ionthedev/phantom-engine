//
// Created by Brandon Friend on 8/8/24.
//


#include "Application.h"
#include "PhantomPch.h"
#include "Event_System/ApplicationEvent.h"
#include "Log.h"
#include "rlgl.h"
#include <iostream>

Phantom::Application::Application()
{
}

Phantom::Application::~Application()
{
}

void Phantom::Application::Run() // Literally just int maint()
{
    InitWindow(800, 450, "Phantom Works");


    //rlViewport(viewportPos.x, viewportPos.y, viewportSize.x, viewportSize.y);

    WindowResizeEvent e (1280, 720);
    PH_INFO(e);

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };

    Ray ray = { 0 };                    // Picking line ray
    RayCollision collision = { 0 };     // Ray collision hit info

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    rlImGuiSetup(true);

    //you can use whatever imgui theme you like!
    //ImGui::StyleColorsDark();
    //imguiThemes::yellow();
    //imguiThemes::gray();
    //imguiThemes::red();
    //imguiThemes::embraceTheDarkness();


    ImGuiIO &io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.FontGlobalScale = 2;

    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        //style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 0.5f;
        //style.Colors[ImGuiCol_DockingEmptyBg].w = 0.f;
    }

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {




        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();ClearBackground(RAYWHITE);


#pragma region imgui
        rlImGuiBegin();

        ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        ImGui::PopStyleColor(2);
#pragma endregion


        ImGui::Begin("Test");

        ImGui::Text("Hello");
        ImGui::Button("Button");
        ImGui::Button("Button2");

        ImGui::End();


        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);


#pragma region imgui
        rlImGuiEnd();

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
#pragma endregion


        EndDrawing();


        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

}

void Phantom::Application::MakeLayer(Layer *layer)
{
    m_LayerStack.MakeLayer(layer);
}

void Phantom::Application::MakeOverlay(Layer *layer)
{
    m_LayerStack.MakeOverlay(layer);
}
