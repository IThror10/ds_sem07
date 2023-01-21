#ifndef __SUM_LIB_HPP__
#define __SUM_LIB_HPP__

    #ifdef IMPORT
        __declspec(dllimport) int __cdecl lib_sum(int a, int b);
    #else
        __declspec(dllexport) int __cdecl lib_sum(int a, int b);
    #endif
    
#endif //__SUM_LIB_HPP__