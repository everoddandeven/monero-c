#include <inttypes.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <string_view>
#include <stdexcept>
#include <cctype>
#include <thread>
#include "monero_daemon_bridge.h"
#include "monero_utils_bridge.h"
#include "utils.hpp"

thread_local std::string last_error = "";

#define DEBUG_START()                                                             \
    try {

#define DEBUG_END()                                                               \
    } catch (const std::exception &e) {                                           \
        std::cerr << "Exception caught in function: " << __FUNCTION__             \
                  << " at " << __FILE__ << ":" << __LINE__ << std::endl           \
                  << "Message: " << e.what() << std::endl;                        \
        last_error = e.what();                                                                   \
    } catch (...) {                                                               \
        std::cerr << "Unknown exception caught in function: " << __FUNCTION__     \
                  << " at " << __FILE__ << ":" << __LINE__ << std::endl;          \
        std::abort();                                                                    \
    }

#ifdef __cplusplus
extern "C"
{
#endif

std::string to_hex(std::string_view bytes, std::string_view prefix = "0b") {
    static constexpr char hex[] = "0123456789abcdef";
    std::string out;
    out.reserve(prefix.size() + bytes.size() * 2);
    out.append(prefix);
    for (unsigned char b : bytes) {                 // cast importante!
        out.push_back(hex[b >> 4]);                 // nibble alto
        out.push_back(hex[b & 0x0F]);               // nibble basso
    }
    return out;
}

unsigned char from_hex_character(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    throw std::invalid_argument("Invalid hex character");
}

std::string from_hex(const std::string& hex, std::string_view prefix = "0b") {
    size_t start = 0;
    if (hex.rfind(prefix, 0) == 0) {
        start = prefix.size();
    }

    if (((hex.size() - start) % 2) != 0) {
        throw std::invalid_argument("Invalid hex string length");
    }

    std::string out;
    out.reserve((hex.size() - start) / 2);
    for (size_t i = start; i < hex.size(); i += 2) {
        unsigned char high = from_hex_character(hex[i]);
        unsigned char low  = from_hex_character(hex[i + 1]);
        out.push_back(static_cast<char>((high << 4) | low));
    }
    return out;
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
    if (standard_address == nullptr) {
        return nullptr;
    }

    monero_network_type net_type;

    if (!parse_network_type(network_type, net_type)) {
        return nullptr;
    }

    monero_integrated_address integrated_address = monero_utils::get_integrated_address(net_type, std::string(standard_address), payment_id != nullptr ? std::string(payment_id) : "");
    monero_integrated_address* ptr = new monero_integrated_address(integrated_address);
    return reinterpret_cast<void*>(ptr);
    DEBUG_END()
    return nullptr;
}

bool monero_utils_is_valid_address(const char* address, int network_type) {
    DEBUG_START()
    if (address == nullptr) {
        return false;
    }

    monero_network_type net_type;

    if (!parse_network_type(network_type, net_type)) {
        return false;
    }

    return monero_utils::is_valid_address(std::string(address), net_type);
    DEBUG_END()
    return false;
}

bool monero_utils_is_valid_private_view_key(const char* private_view_key) {
    DEBUG_START()
    if (private_view_key == nullptr) {
        return false;
    }

    return monero_utils::is_valid_private_view_key(std::string(private_view_key));
    DEBUG_END()
    return false;
}

bool monero_utils_is_valid_private_spend_key(const char* private_spend_key) {
    DEBUG_START()
    if (private_spend_key == nullptr) {
        return false;
    }

    return monero_utils::is_valid_private_spend_key(std::string(private_spend_key));
    DEBUG_END()
    return false;
}

bool monero_utils_is_valid_public_view_key(const char* public_view_key) {
    DEBUG_START()
    if (public_view_key == nullptr) {
        return false;
    }

    return monero_utils::is_valid_private_view_key(std::string(public_view_key));
    DEBUG_END()
    return false;
}

bool monero_utils_is_valid_public_spend_key(const char* public_spend_key) {
    DEBUG_START()
    if (public_spend_key == nullptr) {
        return false;
    }

    return monero_utils::is_valid_private_spend_key(std::string(public_spend_key));
    DEBUG_END()
    return false;
}

bool monero_utils_is_valid_language(const char* language) {
    DEBUG_START()
    if (language == nullptr) {
        return false;
    }

    return monero_utils::is_valid_language(std::string(language));
    DEBUG_END()
    return false;
}

const char* monero_utils_json_to_binary(const char* json) {
    DEBUG_START()
    if (json == nullptr) {
        return nullptr;
    }

    std::string bin;
    std::string json_str = std::string(json);
    monero_utils::json_to_binary(json_str, bin);
    bin = to_hex(bin);
    const std::string::size_type size = bin.length();
    char *buffer = new char[size];
    memcpy(buffer, bin.data(), size);
    return buffer;
    DEBUG_END()
    return nullptr;
}

const char* monero_utils_binary_to_json(const char* bin) {
    DEBUG_START()
    if (bin == nullptr) {
        return nullptr;
    }

    std::string json;
    std::string bin_str = from_hex(std::string(bin));
    monero_utils::binary_to_json(bin_str, json);
    const std::string::size_type size = json.size();
    char *buffer = new char[size + 1];
    memcpy(buffer, json.c_str(), size + 1);
    return buffer;
    DEBUG_END()
    return nullptr;
}

const char* monero_utils_binary_blocks_to_json(const char* bin) {
    DEBUG_START()
    if (bin == nullptr) {
        return nullptr;
    }

    std::string json;
    std::string bin_str = from_hex(std::string(bin));
    monero_utils::binary_blocks_to_json(bin_str, json);
    const std::string::size_type size = json.size();
    char *buffer = new char[size + 1];
    memcpy(buffer, json.c_str(), size + 1);
    return buffer;
    DEBUG_END()
    return nullptr;
}

const char* monero_utils_get_error() {
    if (last_error.empty()) {
        return "";
    }
    const std::string::size_type size = last_error.size();
    char *buffer = new char[size + 1];
    memcpy(buffer, last_error.c_str(), size + 1);
    last_error.clear();
    return buffer;
}

#ifdef __cplusplus
}
#endif