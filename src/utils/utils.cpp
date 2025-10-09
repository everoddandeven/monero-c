#include "utils.hpp"

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

bool parse_message_signature_type(int signature_type, monero_message_signature_type& sig_type) {
    if (signature_type == MONERO_MESSAGE_SIGN_WITH_SPEND_KEY) {
        sig_type = monero_message_signature_type::SIGN_WITH_SPEND_KEY;
    }
    else if (signature_type == MONERO_MESSAGE_SIGN_WITH_VIEW_KEY) {
        sig_type = monero_message_signature_type::SIGN_WITH_VIEW_KEY;
    }
    else {
        return false;
    }

    return true;
}
