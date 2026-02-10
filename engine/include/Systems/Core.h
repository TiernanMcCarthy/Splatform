//
// Created by Tiern on 9/02/2026.
//

#pragma once

#ifdef _WIN32
    #ifdef BUILD_SHARED_LIBS
        #define API __declspec(dllexport)
    #else
        #define API __declspec(dllimport)
    #endif
#else
    #define API
#endif
