//
// Created by Brandon Friend on 8/7/24.
//

#ifndef CORE_H
#define CORE_H

// Define export/import macros
#if defined(_WIN32) || defined(_WIN64)
    #ifdef PHANTOM_ENGINE_EXPORTS
        #define PHANTOM_API __declspec(dllexport)
    #else
        #define PHANTOM_API __declspec(dllimport)
    #endif
#else
    #define PHANTOM_API __attribute__((visibility("default")))
#endif

#endif //CORE_H
