//
// Created by Brandon Friend on 8/8/24.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include "PhantomPch.h"



int main(int argc, char** argv);

namespace Phantom
{

class Application {

    public:
    Application();
    virtual ~Application();

    void Run();

};

    Application* CreateApplication();

}
#endif //APPLICATION_H
