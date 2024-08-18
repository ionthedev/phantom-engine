//
// Created by Brandon Friend on 8/14/24.
//

#ifndef ENGINE_H
#define ENGINE_H
#include <chrono>

#include "Application.h"
#include "Physics/Physics.h"


namespace Phantom {

    class Engine {
    public:
        // Static method to access the singleton instance
        static Engine* GetSingleton(bool initialized = false);

        // Delete copy constructor and assignment operator to prevent copies
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        void Init();
        void SetApp(Application* _application);
        void Loop();
        void Shutdown();

        double GetDeltaTime() const;
        double GetFixedDeltaTime() const;

        double targetFrameRate = 60;

    protected:
        Engine(bool _initialized); // Protected constructor
        ~Engine(); // Protected destructor

        double deltaTime;
        double tAccumulator;
        Application* m_Application;

    private:
        bool initialized;
        mutable std::chrono::steady_clock::time_point currentDeltaFrameTime;
        mutable std::chrono::steady_clock::time_point currentFixedFrameTime;

        static Engine* s_Instance; // Static instance pointer
        Physics* PhysicsServer;
    };

} // namespace Phantom

#endif // ENGINE_H