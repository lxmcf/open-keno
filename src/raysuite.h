#ifndef RAYSUITE_H
#define RAYSUITE_H

// #define RAYSUITE_NO_MAIN     // Use if full raylib header is not needed
// #define RAYSUITE_NO_MATH     // Use if raymath header not needed

#ifndef RAYSUITE_NO_MAIN
    #include <raylib.h>
    #undef RAYSUITE_NO_MAIN
#endif

#ifndef RAYSUITE_NO_MATH
    #include <raymath.h>
    #undef RAYSUITE_NO_MATH
#endif

#endif // RAYSUITE_H
