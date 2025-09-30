#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __MINGW32__
    #define ADDAPI __declspec(dllexport)
#else
    #define ADDAPI __attribute__((__visibility__("default")))
#endif

// monero_integrated_address

#ifdef __cplusplus
}
#endif