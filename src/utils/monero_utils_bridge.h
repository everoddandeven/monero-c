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

extern ADDAPI void monero_utils_set_log_level(int level);
extern ADDAPI void monero_utils_configure_logging(const char* path, bool console);
extern ADDAPI void* monero_utils_get_integrated_address(int network_type, const char* standard_address, const char* payment_id);
extern ADDAPI bool monero_utils_is_valid_address(const char* address, int network_type);
extern ADDAPI bool monero_utils_is_valid_private_view_key(const char* private_view_key);
extern ADDAPI bool monero_utils_is_valid_private_spend_key(const char* private_spend_key);
extern ADDAPI bool monero_utils_is_valid_language(const char* language);

extern ADDAPI const char* monero_utils_json_to_binary(const char* json);
extern ADDAPI const char* monero_utils_binary_to_json(const char* bin);
extern ADDAPI const char* monero_utils_binary_blocks_to_json(const char* bin);


#ifdef __cplusplus
}
#endif