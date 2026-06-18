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

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __MINGW32__
    #define ADDAPI __declspec(dllexport)
#else
    #define ADDAPI __attribute__((__visibility__("default")))
#endif

// monero_network_type

const int MONERO_NETWORK_MAINNET = 0;
const int MONERO_NETWORK_TESTNET = 1;
const int MONERO_NETWORK_STAGENET = 2;

// monero_message_signature_type

const int MONERO_MESSAGE_SIGN_WITH_SPEND_KEY = 0;
const int MONERO_MESSAGE_SIGN_WITH_VIEW_KEY = 1;

// api error

extern ADDAPI const char* monero_api_error();

// monero_utils

extern ADDAPI void monero_utils_set_log_level(int level);
extern ADDAPI void monero_utils_configure_logging(const char* path, bool console);
extern ADDAPI void* monero_utils_get_integrated_address(int network_type, const char* standard_address, const char* payment_id);
extern ADDAPI bool monero_utils_is_valid_address(const char* address, int network_type);
extern ADDAPI bool monero_utils_is_valid_private_view_key(const char* private_view_key);
extern ADDAPI bool monero_utils_is_valid_private_spend_key(const char* private_spend_key);
extern ADDAPI bool monero_utils_is_valid_public_view_key(const char* public_view_key);
extern ADDAPI bool monero_utils_is_valid_public_spend_key(const char* public_spend_key);
extern ADDAPI bool monero_utils_is_valid_language(const char* language);
extern ADDAPI const char* monero_utils_json_to_binary(const char* json);
extern ADDAPI const char* monero_utils_binary_to_json(const char* bin);
extern ADDAPI const char* monero_utils_binary_blocks_to_json(const char* bin);

// monero_wallet

extern ADDAPI bool monero_wallet_is_view_only(void* wallet);
extern ADDAPI void monero_wallet_set_daemon_connection(void* wallet, const char* uri, const char* username, const char* password);
extern ADDAPI const char* monero_wallet_get_daemon_connection(void* wallet);
extern ADDAPI bool monero_wallet_is_connected_to_daemon(void* wallet);
extern ADDAPI bool monero_wallet_is_daemon_synced(void* wallet);
extern ADDAPI bool monero_wallet_is_daemon_trusted(void* wallet);
extern ADDAPI bool monero_wallet_is_synced(void* wallet);
extern ADDAPI const char* monero_wallet_get_version(void* wallet);
extern ADDAPI const char* monero_wallet_get_path(void* wallet);
extern ADDAPI int monero_wallet_get_network_type(void* wallet);
extern ADDAPI const char* monero_wallet_get_seed(void* wallet);
extern ADDAPI const char* monero_wallet_get_seed_language(void* wallet);
extern ADDAPI const char* monero_wallet_get_public_view_key(void* wallet);
extern ADDAPI const char* monero_wallet_get_public_spend_key(void* wallet);
extern ADDAPI const char* monero_wallet_get_private_view_key(void* wallet);
extern ADDAPI const char* monero_wallet_get_private_spend_key(void* wallet);
extern ADDAPI const char* monero_wallet_get_primary_address(void* wallet);
extern ADDAPI const char* monero_wallet_get_address(void* wallet, uint32_t account_idx, uint32_t subaddress_idx);
extern ADDAPI const char* monero_wallet_get_address_index(void* wallet, const char* address);
extern ADDAPI const char* monero_wallet_get_integrated_address(void* wallet, const char* standard_address, const char* payment_id);
extern ADDAPI const char* monero_wallet_decode_integrated_address(void* wallet, const char* integrated_address);
extern ADDAPI uint64_t monero_wallet_get_height(void* wallet);
extern ADDAPI uint64_t monero_wallet_get_restore_height(void* wallet);
extern ADDAPI void monero_wallet_set_restore_height(void* wallet, uint64_t restore_height);
extern ADDAPI uint64_t monero_wallet_get_daemon_height(void* wallet);
extern ADDAPI uint64_t monero_wallet_get_daemon_max_peer_height(void* wallet);
extern ADDAPI uint64_t monero_wallet_get_height_by_date(void* wallet, uint16_t year, uint8_t month, uint8_t day);
extern ADDAPI void monero_wallet_add_listener(void* wallet, void* listener);
extern ADDAPI void monero_wallet_remove_listener(void* wallet, void* listener);
extern ADDAPI const char* monero_wallet_sync(void* wallet, uint64_t start_height, void* listener);
extern ADDAPI void monero_wallet_start_syncing(void* wallet, uint64_t sync_period_in_ms);
extern ADDAPI void monero_wallet_stop_syncing(void* wallet);
extern ADDAPI void monero_wallet_scan_txs(void* wallet, const char* tx_hashes);
extern ADDAPI void monero_wallet_rescan_spent(void* wallet);
extern ADDAPI void monero_wallet_rescan_blockchain(void* wallet);
extern ADDAPI uint64_t monero_wallet_get_balance(void* wallet);
extern ADDAPI uint64_t monero_wallet_get_account_balance(void* wallet, uint32_t account_idx);
extern ADDAPI uint64_t monero_wallet_get_subaddress_balance(void* wallet, uint32_t account_idx, uint32_t subaddress_idx);
extern ADDAPI uint64_t monero_wallet_get_unlocked_balance(void* wallet);
extern ADDAPI uint64_t monero_wallet_get_account_unlocked_balance(void* wallet, uint32_t account_idx);
extern ADDAPI uint64_t monero_wallet_get_subaddress_unlocked_balance(void* wallet, uint32_t account_idx, uint32_t subaddress_idx);
extern ADDAPI const char* monero_wallet_get_accounts(void* wallet, bool include_subaddresses);
extern ADDAPI const char* monero_wallet_get_accounts_by_tag(void* wallet, const char* tag, bool include_subaddresses);
extern ADDAPI const char* monero_wallet_get_account(void* wallet, uint32_t account_idx, bool include_subaddresses);
extern ADDAPI const char* monero_wallet_create_account(void* wallet, const char* label);
extern ADDAPI const char* monero_wallet_get_subaddresses(void* wallet, uint32_t account_idx, const char* subaddresses_indices);
extern ADDAPI const char* monero_wallet_get_subaddress(void* wallet, uint32_t account_idx, uint32_t subaddress_idx);
extern ADDAPI const char* monero_wallet_create_subaddress(void* wallet, uint32_t account_idx, const char* label);
extern ADDAPI void monero_wallet_set_subaddress_label(void* wallet, uint32_t account_idx, uint32_t subaddress_idx, const char* label);
extern ADDAPI const char* monero_wallet_get_txs(void* wallet, const char* tx_query);
extern ADDAPI const char* monero_wallet_get_transfers(void* wallet, const char* transfer_query);
extern ADDAPI const char* monero_wallet_get_outputs(void* wallet, const char* outputs_query);
extern ADDAPI const char* monero_wallet_export_outputs(void* wallet, bool all);
extern ADDAPI int monero_wallet_import_outputs(void* wallet, const char* outputs_hex);
extern ADDAPI const char* monero_wallet_export_key_images(void* wallet, bool all);
extern ADDAPI const char* monero_wallet_import_key_images(void* wallet, const char* key_images);
extern ADDAPI void monero_wallet_freeze_output(void* wallet, const char* key_image);
extern ADDAPI void monero_wallet_thaw_output(void* wallet, const char* key_image);
extern ADDAPI bool monero_wallet_is_output_frozen(void* wallet, const char* key_image);
extern ADDAPI int monero_wallet_get_default_fee_priority(void* wallet);
extern ADDAPI const char* monero_wallet_create_tx(void* wallet, const char* config);
extern ADDAPI const char* monero_wallet_create_txs(void* wallet, const char* config);
extern ADDAPI const char* monero_wallet_sweep_unlocked(void* wallet, const char* config);
extern ADDAPI const char* monero_wallet_sweep_output(void* wallet, const char* config);
extern ADDAPI const char* monero_wallet_sweep_dust(void* wallet, bool relay);
extern ADDAPI const char* monero_wallet_relay_tx(void* wallet, const char* tx);
//extern ADDAPI const char* monero_wallet_relay_txs(void* wallet, const char* txs);
extern ADDAPI const char* monero_wallet_describe_tx_set(void* wallet, const char* tx_set);
extern ADDAPI const char* monero_wallet_sign_txs(void* wallet, const char* unsigned_tx_hex);
extern ADDAPI const char* monero_wallet_submit_txs(void* wallet, const char* signed_tx_hex);
extern ADDAPI const char* monero_wallet_sign_message(void* wallet, const char* msg, int signature_type, uint32_t account_idx, uint32_t subaddress_idx);
extern ADDAPI const char* monero_wallet_verify_message(void* wallet, const char* msg, const char* address, const char* signature);
extern ADDAPI const char* monero_wallet_get_tx_key(void* wallet, const char* tx_hash);
extern ADDAPI const char* monero_wallet_check_tx_key(void* wallet, const char* tx_hash, const char* tx_key, const char* address);
extern ADDAPI const char* monero_wallet_get_tx_proof(void* wallet, const char* tx_hash, const char* address, const char* message);
extern ADDAPI const char* monero_wallet_check_tx_proof(void* wallet, const char* tx_hash, const char* address, const char* message, const char* signature);
extern ADDAPI const char* monero_wallet_get_spend_proof(void* wallet, const char* tx_hash, const char* message);
extern ADDAPI bool monero_wallet_check_spend_proof(void* wallet, const char* tx_hash, const char* message, const char* signature);
extern ADDAPI const char* monero_wallet_get_reserve_proof_wallet(void* wallet, const char* message);
extern ADDAPI const char* monero_wallet_get_reserve_proof_account(void* wallet, uint32_t account_idx, uint64_t amount, const char* message);
extern ADDAPI const char* monero_wallet_check_reserve_proof(void* wallet, const char* address, const char* message, const char* signature);
extern ADDAPI const char* monero_wallet_get_tx_note(void* wallet, const char* tx_hash);
extern ADDAPI void monero_wallet_set_tx_note(void* wallet, const char* tx_hash, const char* note);
extern ADDAPI const char* monero_wallet_get_tx_notes(void* wallet, const char* tx_hashes);
//extern ADDAPI void monero_wallet_set_tx_notes(void* wallet, const char* tx_hashes, const char* notes);
//extern ADDAPI const char* monero_wallet_get_address_book_entries(void* wallet, const char* indices);
extern ADDAPI uint64_t monero_wallet_add_address_book_entry(void* wallet, const char* address, const char* description);
extern ADDAPI void monero_wallet_edit_address_book_entry(void* wallet, uint64_t index, bool set_address, const char* address, bool set_description, const char* description);
extern ADDAPI void monero_wallet_delete_address_book_entry(void* wallet, uint64_t index);
extern ADDAPI const char* monero_wallet_get_payment_uri(void* wallet, const char* config);
extern ADDAPI const char* monero_wallet_parse_payment_uri(void* wallet, const char* uri);
extern ADDAPI const char* monero_wallet_get_attribute(void* wallet, const char* key);
extern ADDAPI void monero_wallet_set_attribute(void* wallet, const char* key, const char* value);
extern ADDAPI void monero_wallet_start_mining(void* wallet, uint32_t num_threads, bool background_mining, bool ignore_battery);
extern ADDAPI void monero_wallet_stop_mining(void* wallet);
extern ADDAPI void monero_wallet_wait_for_next_block(void* wallet);
extern ADDAPI bool monero_wallet_is_multisig_import_needed(void* wallet);
extern ADDAPI bool monero_wallet_is_multisig(void* wallet);
extern ADDAPI const char* monero_wallet_get_multisig_info(void* wallet);
extern ADDAPI const char* monero_wallet_prepare_multisig(void* wallet);
extern ADDAPI const char* monero_wallet_make_multisig(void* wallet, const char* multisig_hexes, int threshold, const char* password);
extern ADDAPI const char* monero_wallet_exchange_multisig_keys(void* wallet, const char* multisig_hexes, const char* password);
extern ADDAPI const char* monero_wallet_export_multisig_hex(void* wallet);
extern ADDAPI int monero_wallet_import_multisig_hex(void* wallet, const char* multisig_hexes);
extern ADDAPI const char* monero_wallet_sign_multisig_tx_hex(void* wallet, const char* multisig_tx_hex);
extern ADDAPI const char* monero_wallet_submit_multisig_tx_hex(void* wallet, const char* signed_multisig_tx_hex);
extern ADDAPI void monero_wallet_change_password(void* wallet, const char* old_password, const char* new_password);
extern ADDAPI void monero_wallet_move_to(void* wallet, const char* path, const char* password);
extern ADDAPI void monero_wallet_save(void* wallet);
extern ADDAPI void monero_wallet_close(void* wallet, bool save);

// monero_wallet_full

extern ADDAPI bool monero_wallet_full_wallet_exists(const char* path);
extern ADDAPI void* monero_wallet_full_open_wallet(const char* path, const char* password, int network_type);
extern ADDAPI void* monero_wallet_full_create_wallet(const char* config);
extern ADDAPI const char* monero_wallet_full_get_seed_languages();

// monero_wallet_keys

extern ADDAPI void* monero_wallet_keys_create_wallet_random(const char* config);
extern ADDAPI void* monero_wallet_keys_create_wallet_from_seed(const char* config);
extern ADDAPI void* monero_wallet_keys_create_wallet_from_keys(const char* config);
extern ADDAPI const char* monero_wallet_keys_get_seed_languages();

#ifdef __cplusplus
}
#endif

#endif // monero_api_c_h