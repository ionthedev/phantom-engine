#include "Engine.h"

namespace Phantom {

    // Static instance pointer initialized to nullptr
    Engine* Engine::s_Instance = nullptr;

    Engine::Engine(bool _initialized)
    {

        PH_CORE_INFO("Engine Initialized");
        initialized = _initialized;

        Init();
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
    }

    void Engine::SetApp(Application *_application)
    {
        PH_CORE_TRACE("Applicaiton Set");
        m_Application = _application;
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

            tAccumulator += deltaTime;
            while (tAccumulator >= GetFixedDeltaTime())
            {
                m_Application->FixedUpdate(GetFixedDeltaTime());
                tAccumulator -= GetFixedDeltaTime();
            }
        }

        // De-Initialization and Kill Process
        //--------------------------------------------------------------------------------------
        CloseWindow(); // Close window and OpenGL context
        //--------------------------------------------------------------------------------------
    }

    void Engine::Shutdown()
    {
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
