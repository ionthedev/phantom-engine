//
// Created by Brandon Friend on 8/8/24.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include "Game/Scene.h"


int main(int argc, char** argv);

namespace Phantom
{

    class Application {

    public:
        Application();
        ~Application()
        {
        }



        virtual void Start() const;
        virtual void Update(double _deltaTime) const;
        virtual void FixedUpdate(double _deltaTime) const;
        virtual void Render() const;
        Scene* currentScene;
    private:


    };

    Application* CreateApplication();



}
#endif //APPLICATION_H