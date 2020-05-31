#pragma once

#if _cplusplus >= 2011LL
    #define CG_DEPRECATED [[deprecated]]
    //#define CG_DEPRECATED(x) [[deprecated(x)]]
#else
    #define CG_DEPRECATED __attribute((deprecated))
    //#define CG_DEPRECATED(x) __attribute(deprecated(x))
#endif
