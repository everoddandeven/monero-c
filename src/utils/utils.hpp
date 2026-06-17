#include "utils/monero_utils.h"

// network type
const int MONERO_NETWORK_MAINNET = 0;
const int MONERO_NETWORK_TESTNET = 1;
const int MONERO_NETWORK_STAGENET = 2;

// message signature type
const int MONERO_MESSAGE_SIGN_WITH_SPEND_KEY = 0;
const int MONERO_MESSAGE_SIGN_WITH_VIEW_KEY = 1;

bool parse_network_type(int network_type, monero_network_type& net_type);
bool parse_message_signature_type(int signature_type, monero_message_signature_type& sig_type);
