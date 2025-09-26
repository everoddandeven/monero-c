#include <inttypes.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include "debug.hpp"
#include "../../external/monero-cpp/src/utils/monero_utils.h"

#ifdef __cplusplus
extern "C"
{
#endif

bool parse_network_type(int network_type, monero_network_type& net_type) {
    if (network_type == 0)
    {
        net_type = monero_network_type::MAINNET;
    }
    else if (network_type == 1) {
        net_type = monero_network_type::TESTNET;
    }
    else if (network_type == 2) {
        net_type = monero_network_type::STAGENET;
    }
    else {
        return false;
    }

    return true;
}

void monero_utils_set_log_level(int level) {
    DEBUG_START()
    monero_utils::set_log_level(level);
    DEBUG_END()
}

void monero_utils_configure_logging(const char* path, bool console) {
    DEBUG_START()
    monero_utils::configure_logging(std::string(path), console);
    DEBUG_END()
}

void* monero_utils_get_integrated_address(int network_type, const char* standard_address, const char* payment_id) {
    DEBUG_START()
    monero_network_type net_type;

    if (!parse_network_type(network_type, net_type)) {
        return nullptr;
    }

    monero_utils::get_integrated_address(net_type, std::string(standard_address), payment_id != nullptr ? std::string(payment_id) : "");
    return nullptr;
    DEBUG_END()
}

bool monero_utils_is_valid_address(const char* address, int network_type) {
    DEBUG_START()
    monero_network_type net_type;

    if (!parse_network_type(network_type, net_type)) {
        return false;
    }

    return monero_utils::is_valid_address(std::string(address), net_type);
    DEBUG_END()
}

bool monero_utils_is_valid_private_view_key(const char* private_view_key) {
    DEBUG_START()
    return monero_utils::is_valid_private_view_key(std::string(private_view_key));
    DEBUG_END()
}

bool monero_utils_is_valid_private_spend_key(const char* private_spend_key) {
    DEBUG_START()
    return monero_utils::is_valid_private_spend_key(std::string(private_spend_key));
    DEBUG_END()
}

bool monero_utils_is_valid_language(const char* language) {
    DEBUG_START()
    if (language == nullptr) {
        return false;
    }

    return monero_utils::is_valid_language(std::string(language));
    DEBUG_END()
}

const char* monero_utils_json_to_binary(const char* json) {
    DEBUG_START()
    std::string bin;
    monero_utils::json_to_binary(std::string(json), bin);
    return bin.c_str();
    DEBUG_END()
}

const char* monero_utils_binary_to_json(const char* bin) {
    DEBUG_START()
    std::string json;
    monero_utils::binary_to_json(std::string(bin), json);
    return json.c_str();
    DEBUG_END()
}

const char* monero_utils_binary_blocks_to_json(const char* bin) {
        DEBUG_START()
    std::string json;
    monero_utils::binary_blocks_to_json(std::string(bin), json);
    return json.c_str();
    DEBUG_END()
}

#ifdef __cplusplus
}
#endif