/**
 * Copyright (c) everoddandeven
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Parts of this file are originally copyright (c) woodser
 *
 * Parts of this file are originally copyright (c) 2014-2019, The Monero Project
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 * All rights reserved.
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Parts of this file are originally copyright (c) 2012-2013 The Cryptonote developers
 */
#pragma once

#ifndef monero_api_c_h
#define monero_api_c_h

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

/**
 * Public interface for libmonero-c API.
 */
#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __MINGW32__
    #define ADDAPI __declspec(dllexport)
#else
    #define ADDAPI __attribute__((__visibility__("default")))
#endif

// -------------------------------- MONERO NETWORK TYPE -----------------------------------

const int MONERO_NETWORK_MAINNET = 0;   // monero_network_type::MAINNET
const int MONERO_NETWORK_TESTNET = 1;   // monero_network_type::TESTNET
const int MONERO_NETWORK_STAGENET = 2;  // monero_network_type::STAGENET

// -------------------------------- MONERO MESSAGE SIGNATURE TYPE -----------------------------------

const int MONERO_MESSAGE_SIGN_WITH_SPEND_KEY = 0;  // monero_message_signature_type::SIGN_WITH_SPEND_KEY
const int MONERO_MESSAGE_SIGN_WITH_VIEW_KEY = 1;   // monero_message_signature_type::SIGN_WITH_VIEW_KEY

// -------------------------------- MONERO API ERROR -----------------------------------

/**
 * Get latest error message from monero API.
 *
 * @returns a pointer to a string containing the error message
 */
extern ADDAPI const char* monero_api_error();

// -------------------------------- MONERO UTILS -----------------------------------

/**
 * Set the library's log level with 0 being least verbose.
 *
 * @param level the library's log level
 */
extern ADDAPI void monero_utils_set_log_level(int level);

/**
 * Configure Monero logging.
 * 
 * @param path the path to write logs to
 * @param console specifies whether or not to write to the console
 */
extern ADDAPI void monero_utils_configure_logging(const char* path, bool console);

/**
 * Get an integrated address.
 * 
 * @param network_type is the network type of the integrated address
 * @param standard_address is the address to derive the integrated address from
 * @param payment_id optionally specifies the integrated address's payment id (defaults to random payment id)
 * @return the integrated address
 */
extern ADDAPI void* monero_utils_get_integrated_address(int network_type, const char* standard_address, const char* payment_id);

/**
 * Determine if the given address is valid.
 * 
 * @param address is the address to validate
 * @param network_type is the address's network type
 * @return true if the address is valid, false otherwise
 */
extern ADDAPI bool monero_utils_is_valid_address(const char* address, int network_type);

/**
 * Determine if the given private view key is valid.
 * 
 * @param private_view_key is the private view key to validate
 * @return true if the private view key is valid, false otherwise
 */
extern ADDAPI bool monero_utils_is_valid_private_view_key(const char* private_view_key);

/**
 * Determine if the given private spend key is valid.
 * 
 * @param private_spend_key is the private spend key to validate
 * @return true if the private spend key is valid, false otherwise
 */
extern ADDAPI bool monero_utils_is_valid_private_spend_key(const char* private_spend_key);

/**
 * Determine if the given public view key is valid.
 * 
 * @param public_view_key is the public view key to validate
 * @return true if the public view key is valid, false otherwise
 */
extern ADDAPI bool monero_utils_is_valid_public_view_key(const char* public_view_key);

/**
 * Determine if the given public spend key is valid.
 * 
 * @param public_spend_key is the public spend key to validate
 * @return true if the public spend key is valid, false otherwise
 */
extern ADDAPI bool monero_utils_is_valid_public_spend_key(const char* public_spend_key);

/**
 * Determine if the given language is valid.
 * 
 * @param language is the language to validate
 * @return true if the language is valid, false otherwise
 */
extern ADDAPI bool monero_utils_is_valid_language(const char* language);

// -------------------------------- MONERO WALLET -----------------------------------

/**
 * Indicates if the wallet is view-only, meaning it does have the private
 * spend key and can therefore only observe incoming outputs.
 *
 * @param wallet pointer to the wallet instance
 * @return true if the wallet is view-only, false otherwise
 */
extern ADDAPI bool monero_wallet_is_view_only(void* wallet);

/**
 * Set the wallet's daemon connection.
 *
 * @param wallet pointer to the wallet instance
 * @param uri is the daemon's URI
 * @param username is the username to authenticate with the daemon (optional)
 * @param password is the password to authenticate with the daemon (optional)
 * @param proxy_uri is the proxy to the daemon (e.g. over Tor)
 */
extern ADDAPI void monero_wallet_set_daemon_connection(void* wallet, const char* uri, const char* username, const char* password);

/**
 * Get the wallet's daemon connection.
 *
 * @param wallet pointer to the wallet instance
 * @return the wallet's daemon connection
 */
extern ADDAPI const char* monero_wallet_get_daemon_connection(void* wallet);

/**
 * Indicates if the wallet is connected a daemon.
 *
 * @param wallet pointer to the wallet instance
 * @return true if the wallet is connected to a daemon, false otherwise
 */
extern ADDAPI bool monero_wallet_is_connected_to_daemon(void* wallet);

/**
 * Indicates if the wallet's daemon is synced with the network.
 *
 * @param wallet pointer to the wallet instance
 * @return true if the daemon is synced with the network, false otherwise
*/
extern ADDAPI bool monero_wallet_is_daemon_synced(void* wallet);

/**
 * Indicates if the daemon is trusted or untrusted.
 *
 * @param wallet pointer to the wallet instance
 * @return true if the daemon is trusted, false otherwise
 */
extern ADDAPI bool monero_wallet_is_daemon_trusted(void* wallet);

/**
 * Indicates if the wallet is synced with the daemon.
 *
 * @param wallet pointer to the wallet instance
 * @return true if the wallet is synced with the daemon, false otherwise
 */
extern ADDAPI bool monero_wallet_is_synced(void* wallet);

/**
 * Get the wallet's version.
 *
 * @param wallet pointer to the wallet instance
 * @return the wallet's version
 */
extern ADDAPI const char* monero_wallet_get_version(void* wallet);

/**
 * Get the path of this wallet's file on disk.
 *
 * @param wallet pointer to the wallet instance
 * @return the path of this wallet's file on disk
 */
extern ADDAPI const char* monero_wallet_get_path(void* wallet);

/**
 * Get the wallet's network type (mainnet, testnet, or stagenet).
 *
 * @param wallet pointer to the wallet instance
 * @return the wallet's network type
 */
extern ADDAPI int monero_wallet_get_network_type(void* wallet);

/**
 * Get the wallet's mnemonic phrase or seed.
 *
 * @param wallet pointer to the wallet instance
 * @return the wallet's mnemonic phrase or seed
 */
extern ADDAPI const char* monero_wallet_get_seed(void* wallet);

/**
 * Get the language of the wallet's mnemonic phrase or seed.
 *
 * @param wallet pointer to the wallet instance
 * @return the language of the wallet's mnemonic phrase or seed
 */
extern ADDAPI const char* monero_wallet_get_seed_language(void* wallet);

/**
 * Get the wallet's public view key.
 *
 * @param wallet pointer to the wallet instance
 * @return the wallet's public view key
 */
extern ADDAPI const char* monero_wallet_get_public_view_key(void* wallet);

/**
 * Get the wallet's public spend key.
 *
 * @param wallet pointer to the wallet instance
 * @return the wallet's public spend key
 */
extern ADDAPI const char* monero_wallet_get_public_spend_key(void* wallet);

/**
 * Get the wallet's private view key.
 *
 * @param wallet pointer to the wallet instance
 * @return the wallet's private view key
 */
extern ADDAPI const char* monero_wallet_get_private_view_key(void* wallet);

/**
 * Get the wallet's private spend key.
 *
 * @param wallet pointer to the wallet instance
 * @return the wallet's private spend key
 */
extern ADDAPI const char* monero_wallet_get_private_spend_key(void* wallet);

/**
 * Get the wallet's primary address.
 *
 * @param wallet pointer to the wallet instance
 * @return the wallet's primary address
 */
extern ADDAPI const char* monero_wallet_get_primary_address(void* wallet);

/**
 * Get the address of a specific subaddress.
 *
 * @param wallet pointer to the wallet instance
 * @param account_idx specifies the account index of the address's subaddress
 * @param subaddress_idx specifies the subaddress index within the account
 * @return the receive address of the specified subaddress
 */
extern ADDAPI const char* monero_wallet_get_address(void* wallet, uint32_t account_idx, uint32_t subaddress_idx);

/**
 * Get the account and subaddress index of the given address.
 *
 * @param wallet pointer to the wallet instance
 * @param address is the address to get the account and subaddress index from
 * @return the account and subaddress indices
 */
extern ADDAPI const char* monero_wallet_get_address_index(void* wallet, const char* address);

/**
 * Get an integrated address from a standard address and a payment id.
 *
 * @param wallet pointer to the wallet instance
 * @param standard_address is the integrated addresse's standard address (defaults to wallet's primary address)
 * @param payment_id is the integrated addresse's payment id (defaults to randomly generating new payment id)
 * @return the integrated address
 */
extern ADDAPI const char* monero_wallet_get_integrated_address(void* wallet, const char* standard_address, const char* payment_id);

/**
 * Decode an integrated address to get its standard address and payment id.
 *
 * @param wallet pointer to the wallet instance
 * @param integrated_address is an integrated address to decode
 * @return the decoded integrated address including standard address and payment id
 */
extern ADDAPI const char* monero_wallet_decode_integrated_address(void* wallet, const char* integrated_address);

/**
 * Get the height of the last block processed by the wallet (its index + 1).
 *
 * @param wallet pointer to the wallet instance
 * @return the height of the last block processed by the wallet
 */
extern ADDAPI uint64_t monero_wallet_get_height(void* wallet);

/**
 * Get the height of the first block that the wallet scans.
 *
 * @param wallet pointer to the wallet instance
 * @return the height of the first block that the wallet scans
 */
extern ADDAPI uint64_t monero_wallet_get_restore_height(void* wallet);

/**
 * Set the height of the first block that the wallet scans.
 *
 * @param wallet pointer to the wallet instance
 * @param restore_height is the height of the first block that the wallet scans
 */
extern ADDAPI void monero_wallet_set_restore_height(void* wallet, uint64_t restore_height);

/**
 * Get the height that the wallet's daemon is synced to.
 *
 * @param wallet pointer to the wallet instance
 * @return the height that the wallet's daemon is synced to
 */
extern ADDAPI uint64_t monero_wallet_get_daemon_height(void* wallet);

/**
 * Get the maximum height of the peers the wallet's daemon is connected to.
 *
 * @param wallet pointer to the wallet instance
 * @return the maximum height of the peers the wallet's daemon is connected to
 */
extern ADDAPI uint64_t monero_wallet_get_daemon_max_peer_height(void* wallet);

/**
 * Get the blockchain's height by date as a conservative estimate for scanning.
 * 
 * @param wallet pointer to the wallet instance
 * @param year year of the height to get
 * @param month month of the height to get as a number between 1 and 12
 * @param day day of the height to get as a number between 1 and 31
 * @return the blockchain's approximate height at the given date
*/
extern ADDAPI uint64_t monero_wallet_get_height_by_date(void* wallet, uint16_t year, uint8_t month, uint8_t day);

/**
 * Register a listener receive wallet notifications.
 *
 * @param wallet pointer to the wallet instance
 * @param listener is the listener to receive wallet notifications
 */
extern ADDAPI void monero_wallet_add_listener(void* wallet, void* listener);

/**
 * Unregister a listener to receive wallet notifications.
 *
 * @param wallet pointer to the wallet instance
 * @param listener is the listener to unregister
 */
extern ADDAPI void monero_wallet_remove_listener(void* wallet, void* listener);

/**
 * Synchronize the wallet with the daemon as a one-time synchronous process.
 *
 * @param wallet pointer to the wallet instance
 * @param start_height is the start height to sync from (ignored if less than last processed block)
 * @param listener listener to receive notifications during synchronization
 * @return the sync result
 */
extern ADDAPI const char* monero_wallet_sync(void* wallet, uint64_t start_height, void* listener);

/**
 * Start background synchronizing with a maximum period between syncs.
 *
 * @param wallet pointer to the wallet instance
 * @param sync_period_in_ms maximum period between syncs in milliseconds
 */
extern ADDAPI void monero_wallet_start_syncing(void* wallet, uint64_t sync_period_in_ms);

/**
 * Stop the asynchronous thread to continuously synchronize the wallet with the daemon.
 * @param wallet pointer to the wallet instance
 */
extern ADDAPI void monero_wallet_stop_syncing(void* wallet);

/**
 * Scan transactions by their hash/id.
 *
 * @param wallet pointer to the wallet instance
 * @param tx_hashes tx hashes to scan
 */
extern ADDAPI void monero_wallet_scan_txs(void* wallet, const char* tx_hashes);

/**
 * Rescan the blockchain for spent outputs.
 *
 * Note: this can only be called with a trusted daemon.
 *
 * Example use case: peer multisig hex is import when connected to an untrusted daemon,
 * so the wallet will not rescan spent outputs.  Then the wallet connects to a trusted
 * daemon.  This method should be manually invoked to rescan outputs.
 *
 * @param wallet pointer to the wallet instance
 */
extern ADDAPI void monero_wallet_rescan_spent(void* wallet);

/**
 * Rescan the blockchain from scratch, losing any information which cannot be recovered from
 * the blockchain itself.
 *
 * WARNING: This method discards local wallet data like destination addresses, tx secret keys,
 * tx notes, etc.
 *
 * @param wallet pointer to the wallet instance
 */
extern ADDAPI void monero_wallet_rescan_blockchain(void* wallet);

/**
 * Get the wallet's balance.
 *
 * @param wallet pointer to the wallet instance
 * @return the wallet's balance
 */
extern ADDAPI uint64_t monero_wallet_get_balance(void* wallet);

/**
 * Get an account's balance.
 *
 * @param wallet pointer to the wallet instance
 * @param account_idx is the index of the account to get the balance of
 * @return the account's balance
 */
extern ADDAPI uint64_t monero_wallet_get_account_balance(void* wallet, uint32_t account_idx);

/**
 * Get a subaddress's balance.
 *
 * @param wallet pointer to the wallet instance
 * @param account_idx is the index of the subaddress's account to get the balance of
 * @param subaddress_idx is the index of the subaddress to get the balance of
 * @return the subaddress's balance
 */
extern ADDAPI uint64_t monero_wallet_get_subaddress_balance(void* wallet, uint32_t account_idx, uint32_t subaddress_idx);

/**
 * Get the wallet's unlocked balance.
 *
 * @param wallet pointer to the wallet instance
 * @return the wallet's unlocked balance
 */
extern ADDAPI uint64_t monero_wallet_get_unlocked_balance(void* wallet);

/**
 * Get an account's unlocked balance.
 *
 * @param wallet pointer to the wallet instance
 * @param account_idx is the index of the account to get the unlocked balance of
 * @return the account's unlocked balance
 */
extern ADDAPI uint64_t monero_wallet_get_account_unlocked_balance(void* wallet, uint32_t account_idx);

/**
 * Get a subaddress's unlocked balance.
 *
 * @param wallet pointer to the wallet instance
 * @param account_idx is the index of the subaddress's account to get the unlocked balance of
 * @param subaddress_idx is the index of the subaddress to get the unlocked balance of
 * @return the subaddress's unlocked balance
 */
extern ADDAPI uint64_t monero_wallet_get_subaddress_unlocked_balance(void* wallet, uint32_t account_idx, uint32_t subaddress_idx);

/**
 * Get all accounts.
 *
 * @param wallet pointer to the wallet instance
 * @param include_subaddresses specifies if subaddresses should be included
 * @return all accounts within the wallet
 */
extern ADDAPI const char* monero_wallet_get_accounts(void* wallet, bool include_subaddresses);

/**
 * Get accounts with a given tag.
 *
 * @param wallet pointer to the wallet instance
 * @param tag is the tag for filtering accounts, all accounts if null
 * @param include_subaddresses specifies if subaddresses should be included
 * @return List<monero_account> are all accounts for the wallet with the given tag
 */
extern ADDAPI const char* monero_wallet_get_accounts_by_tag(void* wallet, const char* tag, bool include_subaddresses);

/**
 * Get an account without subaddress information.
 *
 * @param wallet pointer to the wallet instance
 * @param account_idx specifies the account to get
 * @param include_subaddresses specifies if subaddresses should be included
 * @return the retrieved account
 */
extern ADDAPI const char* monero_wallet_get_account(void* wallet, uint32_t account_idx, bool include_subaddresses);

/**
 * Create a new account with a label for the first subaddress.
 *
 * @param wallet pointer to the wallet instance
 * @param label specifies the label for the account's first subaddress (optional)
 * @return the created account
 */
extern ADDAPI const char* monero_wallet_create_account(void* wallet, const char* label);

/**
 * Get subaddresses in an account.
 *
 * @param wallet pointer to the wallet instance
 * @param account_idx specifies the account to get subaddresses within
 * @param subaddress_indices are specific subaddresses to get (optional)
 * @return the retrieved subaddresses
 */
extern ADDAPI const char* monero_wallet_get_subaddresses(void* wallet, uint32_t account_idx, const char* subaddresses_indices);

/**
 * Get a subaddress.
 *
 * @param wallet pointer to the wallet instance
 * @param account_idx specifies the index of the subaddress's account
 * @param subaddress_idx specifies index of the subaddress within the account
 * @return the retrieved subaddress
 */
extern ADDAPI const char* monero_wallet_get_subaddress(void* wallet, uint32_t account_idx, uint32_t subaddress_idx);

/**
 * Create a subaddress within an account.
 *
 * @param wallet pointer to the wallet instance
 * @param account_idx specifies the index of the account to create the subaddress within
 * @param label specifies the the label for the subaddress (defaults to empty string)
 * @return the created subaddress
 */
extern ADDAPI const char* monero_wallet_create_subaddress(void* wallet, uint32_t account_idx, const char* label);

/**
 * Set a subaddress label.
 * 
 * @param wallet pointer to the wallet instance
 * @param account_idx index of the account to set the label for
 * @param subaddress_idx index of the subaddress to set the label for
 * @param label the label to set
 */
extern ADDAPI void monero_wallet_set_subaddress_label(void* wallet, uint32_t account_idx, uint32_t subaddress_idx, const char* label);

/**
 * Get wallet transactions.  Wallet transactions contain one or more
 * transfers that are either incoming or outgoing to the wallet.
 *
 * Query results can be filtered by passing in a transaction query.
 * Transactions must meet every criteria defined in the query in order to
 * be returned.  All filtering is optional and no filtering is applied when
 * not defined.
 *
 * @param wallet pointer to the wallet instance
 * @param query filters query results (optional)
 * @return wallet transactions per the query (free memory using monero_utils::free)
 */
extern ADDAPI const char* monero_wallet_get_txs(void* wallet, const char* query);

/**
 * Get incoming and outgoing transfers to and from this wallet.  An outgoing
 * transfer represents a total amount sent from one or more subaddresses
 * within an account to individual destination addresses, each with their
 * own amount.  An incoming transfer represents a total amount received into
 * a subaddress within an account.  Transfers belong to transactions which
 * are stored on the blockchain.
 *
 * Query results can be filtered by passing in a monero_transfer_query.
 * Transfers must meet every criteria defined in the query in order to be
 * returned.  All filtering is optional and no filtering is applied when not
 * defined.
 *
 * @param wallet pointer to the wallet instance
 * @param query filters query results (optional)
 * @return wallet transfers per the query (free memory using monero_utils::free)
 */
extern ADDAPI const char* monero_wallet_get_transfers(void* wallet, const char* query);

/**
 * Get outputs created from previous transactions that belong to the wallet
 * (i.e. that the wallet can spend one time).  Outputs are part of
 * transactions which are stored in blocks on the blockchain.
 *
 * Results can be configured by passing a monero_output_query.  Outputs must
 * meet every criteria defined in the query in order to be returned.  All
 * filtering is optional and no filtering is applied when not defined.
 *
 * @param wallet pointer to the wallet instance
 * @param query specifies query options (optional)
 * @return wallet outputs per the query (free memory using monero_utils::free)
 */
extern ADDAPI const char* monero_wallet_get_outputs(void* wallet, const char* outputs_query);

/**
 * Export outputs in hex format.
 *
 * @param wallet pointer to the wallet instance
 * @param all export all outputs if true, else export outputs since the last export
 * @return outputs in hex format, empty std::string if no outputs
 */
extern ADDAPI const char* monero_wallet_export_outputs(void* wallet, bool all);

/**
 * Import outputs in hex format.
 *
 * @param wallet pointer to the wallet instance
 * @param outputs_hex are outputs in hex format
 * @return the number of outputs imported
 */
extern ADDAPI int monero_wallet_import_outputs(void* wallet, const char* outputs_hex);

/**
 * Export signed key images.
 *
 * @param wallet pointer to the wallet instance
 * @param all export all key images if true, else export key images since the last export
 * @return the wallet's signed key images
 */
extern ADDAPI const char* monero_wallet_export_key_images(void* wallet, bool all);

/**
 * Import signed key images and verify their spent status.
 *
 * @param wallet pointer to the wallet instance
 * @param key_images are key images to import and verify (requires hex and signature)
 * @return results of the import
 */
extern ADDAPI const char* monero_wallet_import_key_images(void* wallet, const char* key_images);

/**
 * Freeze an output.
 *
 * @param wallet pointer to the wallet instance
 * @param key_image key image of the output to freeze
 */
extern ADDAPI void monero_wallet_freeze_output(void* wallet, const char* key_image);

/**
 * Thaw a frozen output.
 *
 * @param wallet pointer to the wallet instance
 * @param key_image key image of the output to thaw
 */
extern ADDAPI void monero_wallet_thaw_output(void* wallet, const char* key_image);

/**
 * Check if an output is frozen.
 *
 * @param wallet pointer to the wallet instance
 * @param key_image key image of the output to check if frozen
 * @return true if the output is frozen, false otherwise
 */
extern ADDAPI bool monero_wallet_is_output_frozen(void* wallet, const char* key_image);

/**
 * Get the current default fee priority (unimportant, normal, elevated, etc).
 *
 * @param wallet pointer to the wallet instance
 * @return the current fee priority
 */
extern ADDAPI int monero_wallet_get_default_fee_priority(void* wallet);

/**
 * Create a transaction to transfer funds from this wallet.
 *
 * @param wallet pointer to the wallet instance
 * @param config configures the transaction to create
 * @return the created transaction (free memory using monero_utils::free)
 */
extern ADDAPI const char* monero_wallet_create_tx(void* wallet, const char* config);

/**
 * Create one or more transactions to transfer funds from this wallet.
 *
 * @param wallet pointer to the wallet instance
 * @param config configures the transactions to create
 * @return the created transactions (free memory using monero_utils::free)
 */
extern ADDAPI const char* monero_wallet_create_txs(void* wallet, const char* config);

/**
 * Sweep unlocked funds according to the given config.
 *
 * @param wallet pointer to the wallet instance
 * @param config is the sweep configuration
 * @return the created transactions (free memory using monero_utils::free)
 */
extern ADDAPI const char* monero_wallet_sweep_unlocked(void* wallet, const char* config);

/**
 * Sweep an output with a given key image.
 *
 * @param wallet pointer to the wallet instance
 * @param config configures the sweep transaction
 * @return the created transaction (free memory using monero_utils::free)
 */
extern ADDAPI const char* monero_wallet_sweep_output(void* wallet, const char* config);

/**
 * Sweep all unmixable dust outputs back to the wallet to make them easier to spend and mix.
 *
 * @param wallet pointer to the wallet instance
 * @param relay specifies if the resulting transaction should be relayed (default false)
 * @return the created transactions (free memory using monero_utils::free)
 */
extern ADDAPI const char* monero_wallet_sweep_dust(void* wallet, bool relay);

/**
 * Relay a transaction previously created without relaying.
 *
 * @param wallet pointer to the wallet instance
 * @param tx_metadata is transaction metadata previously created without relaying
 * @return std::string is the hash of the relayed tx
 */
extern ADDAPI const char* monero_wallet_relay_tx(void* wallet, const char* tx);

// TODO: extern ADDAPI const char* monero_wallet_relay_txs(void* wallet, const char* txs);

/**
 * Describes a tx set containing unsigned or multisig tx hex to a new tx set containing structured transactions.
 *
 * @param wallet pointer to the wallet instance
 * @param tx_set is a tx set containing unsigned or multisig tx hex
 * @return the tx set containing structured transactions
 */
extern ADDAPI const char* monero_wallet_describe_tx_set(void* wallet, const char* tx_set);

/**
 * Sign unsigned transactions from a view-only wallet.
 *
 * @param wallet pointer to the wallet instance
 * @param unsigned_tx_hex is unsigned transaction hex from when the transactions were created
 * @return the signed transaction set
 */
extern ADDAPI const char* monero_wallet_sign_txs(void* wallet, const char* unsigned_tx_hex);

/**
 * Submit signed transactions from a view-only wallet.
 *
 * @param wallet pointer to the wallet instance
 * @param signed_tx_hex is signed transaction hex from sign_txs()
 * @return the resulting transaction hashes
 */
extern ADDAPI const char* monero_wallet_submit_txs(void* wallet, const char* signed_tx_hex);

/**
 * Sign a message.
 *
 * @param wallet pointer to the wallet instance
 * @param msg the message to sign
 * @param signature_type sign with spend key or spend key
 * @param account_idx the account index of the message signature (default 0)
 * @param subaddress_idx the subaddress index of the message signature (default 0)
 * @return the message signature
 */
extern ADDAPI const char* monero_wallet_sign_message(void* wallet, const char* msg, int signature_type, uint32_t account_idx, uint32_t subaddress_idx);

/**
 * Verify a message signature.
 *
 * @param wallet pointer to the wallet instance
 * @param msg the signed message
 * @param address signing address
 * @param signature signature
 * @return the message signature result
 */
extern ADDAPI const char* monero_wallet_verify_message(void* wallet, const char* msg, const char* address, const char* signature);

/**
 * Get a transaction's secret key from its hash.
 *
 * @param wallet pointer to the wallet instance
 * @param tx_hash is the transaction's hash
 * @return is the transaction's secret key
 */
extern ADDAPI const char* monero_wallet_get_tx_key(void* wallet, const char* tx_hash);

/**
 * Check a transaction in the blockchain with its secret key.
 *
 * @param wallet pointer to the wallet instance
 * @param tx_hash specifies the transaction to check
 * @param tx_key is the transaction's secret key
 * @param address is the destination public address of the transaction
 * @return the result of the check
 */
extern ADDAPI const char* monero_wallet_check_tx_key(void* wallet, const char* tx_hash, const char* tx_key, const char* address);

/**
 * Get a transaction signature to prove it.
 *
 * @param wallet pointer to the wallet instance
 * @param tx_hash specifies the transaction to prove
 * @param address is the destination public address of the transaction
 * @param message is a message to include with the signature to further authenticate the proof (optional)
 * @return the transaction signature
 */
extern ADDAPI const char* monero_wallet_get_tx_proof(void* wallet, const char* tx_hash, const char* address, const char* message);

/**
 * Prove a transaction by checking its signature.
 *
 * @param wallet pointer to the wallet instance
 * @param tx_hash specifies the transaction to prove
 * @param address is the destination public address of the transaction
 * @param message is a message included with the signature to further authenticate the proof (optional)
 * @param signature is the transaction signature to confirm
 * @return the result of the check
 */
extern ADDAPI const char* monero_wallet_check_tx_proof(void* wallet, const char* tx_hash, const char* address, const char* message, const char* signature);

/**
 * Generate a signature to prove a spend. Unlike proving a transaction, it does not require the destination public address.
 *
 * @param wallet pointer to the wallet instance
 * @param tx_hash specifies the transaction to prove
 * @param message is a message to include with the signature to further authenticate the proof (optional)
 * @return the transaction signature
 */
extern ADDAPI const char* monero_wallet_get_spend_proof(void* wallet, const char* tx_hash, const char* message);

/**
 * Prove a spend using a signature. Unlike proving a transaction, it does not require the destination public address.
 *
 * @param wallet pointer to the wallet instance
 * @param tx_hash specifies the transaction to prove
 * @param message is a message included with the signature to further authenticate the proof (optional)
 * @param signature is the transaction signature to confirm
 * @return true if the signature is good, false otherwise
 */
extern ADDAPI bool monero_wallet_check_spend_proof(void* wallet, const char* tx_hash, const char* message, const char* signature);

/**
 * Generate a signature to prove the entire balance of the wallet.
 *
 * @param wallet pointer to the wallet instance
 * @param message is a message included with the signature to further authenticate the proof (optional)
 * @return the reserve proof signature
 */
extern ADDAPI const char* monero_wallet_get_reserve_proof_wallet(void* wallet, const char* message);

/**
 * Generate a signature to prove an available amount in an account.
 *
 * @param wallet pointer to the wallet instance
 * @param account_idx specifies the account to prove ownership of the amount
 * @param amount is the minimum amount to prove as available in the account
 * @param message is a message to include with the signature to further authenticate the proof (optional)
 * @return the reserve proof signature
 */
extern ADDAPI const char* monero_wallet_get_reserve_proof_account(void* wallet, uint32_t account_idx, uint64_t amount, const char* message);

/**
 * Proves a wallet has a disposable reserve using a signature.
 *
 * @param wallet pointer to the wallet instance
 * @param address is the public wallet address
 * @param message is a message included with the signature to further authenticate the proof (optional)
 * @param signature is the reserve proof signature to check
 * @return the result of checking the signature proof
 */
extern ADDAPI const char* monero_wallet_check_reserve_proof(void* wallet, const char* address, const char* message, const char* signature);

/**
 * Get a transaction note.
 *
 * @param wallet pointer to the wallet instance
 * @param tx_hash specifies the transaction to get the note of
 * @return the tx note
 */
extern ADDAPI const char* monero_wallet_get_tx_note(void* wallet, const char* tx_hash);

/**
 * Get notes for multiple transactions.
 *
 * @param wallet pointer to the wallet instance
 * @param tx_hashes identify the transactions to get notes for
 * @returns notes for the transactions
 */
extern ADDAPI const char* monero_wallet_get_tx_notes(void* wallet, const char* tx_hashes);

/**
 * Set a note for a specific transaction.
 *
 * @param wallet pointer to the wallet instance
 * @param tx_hash specifies the transaction
 * @param note specifies the note
 */
extern ADDAPI void monero_wallet_set_tx_note(void* wallet, const char* tx_hash, const char* note);

// TODO: extern ADDAPI void monero_wallet_set_tx_notes(void* wallet, const char* tx_hashes, const char* notes);

// TODO: extern ADDAPI const char* monero_wallet_get_address_book_entries(void* wallet, const char* indices);

/**
 * Add an address book entry.
 *
 * @param wallet pointer to the wallet instance
 * @param address is the entry address
 * @param description is the entry description (optional)
 * @return the index of the added entry
 */
extern ADDAPI uint64_t monero_wallet_add_address_book_entry(void* wallet, const char* address, const char* description);

/**
 * Edit an address book entry.
 *
 * @param wallet pointer to the wallet instance
 * @param index is the index of the address book entry to edit
 * @param set_address specifies if the address should be updated
 * @param address is the updated address
 * @param set_description specifies if the description should be updated
 * @param description is the updated description
 */
extern ADDAPI void monero_wallet_edit_address_book_entry(void* wallet, uint64_t index, bool set_address, const char* address, bool set_description, const char* description);

/**
 * Delete an address book entry.
 *
 * @param wallet pointer to the wallet instance
 * @param index is the index of the entry to delete
 */
extern ADDAPI void monero_wallet_delete_address_book_entry(void* wallet, uint64_t index);

/**
 * Creates a payment URI from a tx configuration.
 *
 * @param wallet pointer to the wallet instance
 * @param config specifies configuration for a potential tx
 * @return is the payment uri
 */
extern ADDAPI const char* monero_wallet_get_payment_uri(void* wallet, const char* config);

/**
 * Parses a payment URI to a tx configuration.
 *
 * @param wallet pointer to the wallet instance
 * @param uri is the payment uri to parse
 * @return the tx configuration parsed from the uri
 */
extern ADDAPI const char* monero_wallet_parse_payment_uri(void* wallet, const char* uri);

/**
 * Get an attribute.
 *
 * @param wallet pointer to the wallet instance
 * @param key is the attribute to get the value of
 * @return the key's value if set
 */
extern ADDAPI const char* monero_wallet_get_attribute(void* wallet, const char* key);

/**
 * Set an arbitrary attribute.
 *
 * @param wallet pointer to the wallet instance
 * @param key is the attribute key
 * @param val is the attribute value
 */
extern ADDAPI void monero_wallet_set_attribute(void* wallet, const char* key, const char* val);


/**
 * Start mining.
 *
 * @param wallet pointer to the wallet instance
 * @param num_threads is the number of threads created for mining (optional)
 * @param background_mining specifies if mining should occur in the background (optional)
 * @param ignore_battery specifies if the battery should be ignored for mining (optional)
 */
extern ADDAPI void monero_wallet_start_mining(void* wallet, uint32_t num_threads, bool background_mining, bool ignore_battery);


/**
 * Stop mining.
 *
 * @param wallet pointer to the wallet instance
 */
extern ADDAPI void monero_wallet_stop_mining(void* wallet);

/**
 * Wait for the next block to be added to the chain.
 *
 * @param wallet pointer to the wallet instance
 * @return the height of the next block when it is added to the chain
 */
extern ADDAPI uint64_t monero_wallet_wait_for_next_block(void* wallet);

/**
 * Indicates if importing multisig data is needed for returning a correct balance.
 *
 * @param wallet pointer to the wallet instance
 * @return true if importing multisig data is needed for returning a correct balance, false otherwise
 */
extern ADDAPI bool monero_wallet_is_multisig_import_needed(void* wallet);

/**
 * Indicates if this wallet is a multisig wallet.
 *
 * @param wallet pointer to the wallet instance
 * @return true if this is a multisig wallet, false otherwise
 */
extern ADDAPI bool monero_wallet_is_multisig(void* wallet);

/**
 * Get multisig info about this wallet.
 *
 * @param wallet pointer to the wallet instance
 * @return multisig info about this wallet
 */
extern ADDAPI const char* monero_wallet_get_multisig_info(void* wallet);

/**
 * Get multisig info as hex to share with participants to begin creating a
 * multisig wallet.
 *
 * @param wallet pointer to the wallet instance
 * @return this wallet's multisig hex to share with participants
 */
extern ADDAPI const char* monero_wallet_prepare_multisig(void* wallet);

/**
 * Make this wallet multisig by importing multisig hex from participants.
 *
 * @param wallet pointer to the wallet instance
 * @param multisig_hexes are multisig hex from each participant
 * @param threshold is the number of signatures needed to sign transfers
 * @param password is the wallet password
 * @return this wallet's multisig hex to share with participants
 */
extern ADDAPI const char* monero_wallet_make_multisig(void* wallet, const char* multisig_hexes, int threshold, const char* password);

/**
 * Exchange multisig hex with participants in a M/N multisig wallet.
 *
 * This process must be repeated with participants exactly N-M times.
 *
 * @param wallet pointer to the wallet instance
 * @param multisig_hexes are multisig hex from each participant
 * @param password is the wallet's password // TODO monero-project: redundant? wallet is created with password
 * @return the result which has the multisig's address xor this wallet's multisig hex to share with participants iff not done
 */
extern ADDAPI const char* monero_wallet_exchange_multisig_keys(void* wallet, const char* multisig_hexes, const char* password);

/**
 * Export this wallet's multisig info as hex for other participants.
 *
 * @param wallet pointer to the wallet instance
 * @return this wallet's multisig info as hex for other participants
 */
extern ADDAPI const char* monero_wallet_export_multisig_hex(void* wallet);

/**
 * Import multisig info as hex from other participants.
 *
 * Note: If the daemon is not trusted, this method will not automatically
 * update the spent status after importing peer multisig hex.
 *
 * @param wallet pointer to the wallet instance
 * @param multisig_hexes are multisig hex from each participant
 * @param refresh_after_import specifies if the wallet should be refreshed after importing (default true)
 * @return the number of outputs signed with the given multisig hex
 */
extern ADDAPI int monero_wallet_import_multisig_hex(void* wallet, const char* multisig_hexes);

/**
 * Sign previously created multisig transactions as represented by hex.
 *
 * @param wallet pointer to the wallet instance
 * @param multisig_tx_hex is the hex shared among the multisig transactions when they were created
 * @return the result of signing the multisig transactions
 */
extern ADDAPI const char* monero_wallet_sign_multisig_tx_hex(void* wallet, const char* multisig_tx_hex);

/**
 * Submit signed multisig transactions as represented by a hex std::string.
 *
 * @param wallet pointer to the wallet instance
 * @param signed_multisig_tx_hex is the signed multisig hex returned from signMultisigTxs()
 * @return the resulting transaction hashes
 */
extern ADDAPI const char* monero_wallet_submit_multisig_tx_hex(void* wallet, const char* signed_multisig_tx_hex);

/**
 * Change the wallet password.
 *
 * @param wallet pointer to the wallet instance
 * @param old_password is the wallet's old password
 * @param new_password is the wallet's new password
 */
extern ADDAPI void monero_wallet_change_password(void* wallet, const char* old_password, const char* new_password);

/**
 * Move the wallet from its current path to the given path.
 *
 * @param wallet pointer to the wallet instance
 * @param path is the new wallet's path
 * @param password is the new wallet's password
 */
extern ADDAPI void monero_wallet_move_to(void* wallet, const char* path, const char* password);

/**
 * Save the wallet at its current path.
 *
 * @param wallet pointer to the wallet instance
 */
extern ADDAPI void monero_wallet_save(void* wallet);

/**
 * Optionally save then close the wallet.
 *
 * @param wallet pointer to the wallet instance
 * @param save specifies if the wallet should be saved before being closed (default false)
 */
extern ADDAPI void monero_wallet_close(void* wallet, bool save);

/**
 * Check if the wallet is closed.
 *
 * @param wallet pointer to the wallet instance
 */
extern ADDAPI bool monero_wallet_is_closed(void* wallet);

// -------------------------------- MONERO WALLET FULL -----------------------------------

/**
 * Indicates if a wallet exists at the given path.
 *
 * @param path is the path to check for a wallet
 * @return true if a wallet exists at the given path, false otherwise
 */
extern ADDAPI bool monero_wallet_full_wallet_exists(const char* path);

/**
 * Open an existing wallet from disk.
 *
 * @param path is the path to the wallet file to open
 * @param password is the password of the wallet file to open
 * @param network_type is the wallet's network type
 * @param regtest enable regtest
 * @return a pointer to the wallet instance
 */
extern ADDAPI void* monero_wallet_full_open_wallet(const char* path, const char* password, int network_type);

/**
 * Create a new wallet with the given configuration.
 *
 * @param config is the wallet configuration
 * @return a pointer to the wallet instance
 */
extern ADDAPI void* monero_wallet_full_create_wallet(const char* config);

/**
 * Get a list of available languages for the wallet's seed.
 *
 * @return the available languages for the wallet's seed
 */
extern ADDAPI const char* monero_wallet_full_get_seed_languages();

// -------------------------------- MONERO WALLET KEYS -----------------------------------

/**
 * Create a new wallet with a randomly generated seed.
 *
 * @param config is the wallet configuration (network type and language)
 * @return a pointer to the wallet instance
 */
extern ADDAPI void* monero_wallet_keys_create_wallet_random(const char* config);

/**
 * Create a wallet from an existing mnemonic phrase or seed.
 *
 * @param config is the wallet configuration (network type, seed, seed offset, isMultisig)
 * @return a pointer to the wallet instance
 */
extern ADDAPI void* monero_wallet_keys_create_wallet_from_seed(const char* config);

/**
 * Create a wallet from an address, view key, and spend key.
 * 
 * @param config is the wallet configuration (network type, address, view key, spend key, language)
 * @return a pointer to the wallet instance
 */
extern ADDAPI void* monero_wallet_keys_create_wallet_from_keys(const char* config);

/**
 * Get a list of available languages for the wallet's seed.
 *
 * @return the available languages for the wallet's seed
 */
extern ADDAPI const char* monero_wallet_keys_get_seed_languages();

#ifdef __cplusplus
}
#endif

#endif // monero_api_c_h