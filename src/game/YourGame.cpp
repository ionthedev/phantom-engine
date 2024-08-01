//
// Created by Brandon Friend on 7/21/24.
//

#include "YourGame.h"
#include "rlgl.h"

#define GLSL_VERSION  330

YourGame::YourGame(bool _initialized)
{
    initialized = _initialized;
    //Initializes the engine and triggers the loop
    engine = PE_Core(true);

    engine.SetGame(this);
    engine.Loop();
}

YourGame::~YourGame() = default;



void YourGame::Start() const
{
    InitWindow(screenWidth, screenHeight, "Phantom Engine - Hello World!");
    SetTargetFPS(engine.targetFrameRate);

#pragma region imgui
    rlImGuiSetup(true);

    //you can use whatever imgui theme you like!
    //ImGui::StyleColorsDark();
    //imguiThemes::yellow();
    //imguiThemes::gray();
    imguiThemes::green();
    //imguiThemes::red();
    //imguiThemes::embraceTheDarkness();



    io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.FontGlobalScale = 2;

    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 8.0f;
        style.Colors[ImGuiCol_WindowBg].w = 0.5f;
        //style.Colors[ImGuiCol_DockingEmptyBg].w = 0.f;
    }

#pragma endregion
}

void YourGame::Update(double _deltaTime) const
{

}

void YourGame::FixedUpdate(double _deltaTime) const
{



}

void YourGame::Render() const
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
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

}

void YourGame::HandleInput() const
{
    Game::HandleInput();
}

