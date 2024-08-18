#include "Engine.h"
#include "raylib.h"
#include "Log.h"

namespace Phantom {

    // Static instance pointer initialized to nullptr
    Engine* Engine::s_Instance = nullptr;

    Engine::Engine(bool _initialized)
    {

        PH_CORE_INFO("Engine Initialized");
        initialized = _initialized;

        Init();
    }

    Engine::~Engine()
    {
        delete PhysicsServer;
    }

    // Public static method to access the singleton instance
    Engine* Engine::GetSingleton(bool initialized)
    {
        if (s_Instance == nullptr)
        {

            PH_CORE_ERROR("Engine not initialized. Creating Singleton");
            s_Instance = new Engine(initialized);
        }
        return s_Instance;
    }

    void Engine::Init()
    {
        // Initialization code
        PhysicsServer = new Physics();

    }

    void Engine::SetApp(Application *_application)
    {
        PH_CORE_TRACE("Applicaiton Set");
        m_Application = _application;
        PhysicsServer->application = m_Application;
    }

    void Engine::Loop()
    {
        if(m_Application == nullptr)
        {
            PH_CORE_ERROR("NO APPLICATION SET");
            return;
        }

        m_Application->Start();
        while (s_Instance != nullptr || !initialized)
        {
            double deltaTime = GetDeltaTime();

            // Fixed update loop to handle fixed time steps
            m_Application->Update(deltaTime);

            while (tAccumulator >= GetFixedDeltaTime())
            {
                PhysicsServer->PhysicsUpdate(deltaTime);
                tAccumulator -= GetFixedDeltaTime();
            }

            BeginDrawing();
            BeginMode3D(m_Application->currentScene->camera);
            m_Application->Render();
            EndMode3D();
            EndDrawing();
            tAccumulator += deltaTime;

        }

        // De-Initialization and Kill Process
        //--------------------------------------------------------------------------------------
        Shutdown();
        // Close window and OpenGL context
        //--------------------------------------------------------------------------------------
    }

    void Engine::Shutdown()
    {
        CloseWindow();
        initialized = false;
    }

    double Engine::GetDeltaTime() const
    {
        static auto tLastUpdate = std::chrono::steady_clock::now();;

        currentDeltaFrameTime = std::chrono::steady_clock::now();

        double delta = std::chrono::duration<double>(currentDeltaFrameTime - tLastUpdate).count();
        tLastUpdate = currentDeltaFrameTime;

        return delta;
    }

    double Engine::GetFixedDeltaTime() const
    {
        return 1 / targetFrameRate;
    }
} // Phantom