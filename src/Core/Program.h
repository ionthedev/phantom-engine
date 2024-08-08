//
// Created by Brandon Friend on 8/7/24.
//

#ifndef PROGRAM_H
#define PROGRAM_H
#include "../PhantomEngine.h"

namespace Phantom {

    class Program {

    public:
        Program();
        virtual ~Program();

        static void Run();


    };

    static Program* CreateProgram()
    {
        return new Program();
    }

}



#endif //PROGRAM_H
