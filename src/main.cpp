#include "raylib.h"
#include <iostream>

#pragma region imgui
#include "imgui.h"
#include "rlImGui.h"
#include "imguiThemes.h"
#pragma endregion

#include "Core/Engine.h"
#include "Core/EntryPoint.h"
#include "FearTheCrow/PrototypeScene.h"


class FearTheCrow : public Phantom::Application
{
public:
	FearTheCrow()
	{

		PH_INFO("Initialized");
		//Initializes the engine and triggers the loop

		Phantom::Engine* engine = Phantom::Engine::GetSingleton(true);

		m_Scene = new FTC::PrototypeScene();
		engine->SetApp(this);
		engine->Loop();
	}

	~FearTheCrow()
	{
		Phantom::Engine* engine = Phantom::Engine::GetSingleton(true);
		engine->Shutdown();
	}

	void Start() const override;
	void Update(double _deltaTime) const override;
	void FixedUpdate(double _deltaTime) const override;
	void Render() const override;



};

void FearTheCrow::Start() const
{

	InitWindow(800, 500, "Fear The Crow");
	Application::Start();
	m_Scene->Start();
	SetTargetFPS(60);



}

void FearTheCrow::Update(double _deltaTime) const
{
	if(!WindowShouldClose())
	{
		m_Scene->Update();
	}
}

void FearTheCrow::FixedUpdate(double _deltaTime) const
{
	Application::FixedUpdate(_deltaTime);
	m_Scene->FixedUpdate();
}

void FearTheCrow::Render() const
{
	m_Scene->Render();
}

Phantom::Application* Phantom::CreateApplication()
{
	return new FearTheCrow();
}
