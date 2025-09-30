#include "utils.hpp"
#include "daemon/monero_daemon_bridge.h"

bool parse_network_type(int network_type, monero_network_type& net_type) {
    if (network_type == MONERO_NETWORK_MAINNET)
    {
        net_type = monero_network_type::MAINNET;
    }
    else if (network_type == MONERO_NETWORK_TESTNET) {
        net_type = monero_network_type::TESTNET;
    }
    else if (network_type == MONERO_NETWORK_STAGENET) {
        net_type = monero_network_type::STAGENET;
    }
    else {
        return false;
    }

    return true;
}
