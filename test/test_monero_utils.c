#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "monero_daemon_bridge.h"
#include "monero_utils_bridge.h"

bool test_mainnet_address_validation() {
    // test mainnet primary address validation
    if (!monero_utils_is_valid_address("42U9v3qs5CjZEePHBZHwuSckQXebuZu299NSmVEmQ41YJZQhKcPyujyMSzpDH4VMMVSBo3U3b54JaNvQLwAjqDhKS3rvM3L", MONERO_NETWORK_MAINNET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("48ZxX3Y2y5s4nJ8fdz2w65TrTEp9PRsv5J8iHSShkHQcE2V31FhnWptioNst1K9oeDY4KpWZ7v8V2BZNVa4Wdky89iqmPz2", MONERO_NETWORK_MAINNET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("48W972Fx1SQMCHVKENnPpM7tRcL5oWMgpMCqQDbhH8UrjDFg2H9i5AQWXuU1qacJgUUCVLTsgDmZKXGz1vPLXY8QB5ypYqG", MONERO_NETWORK_MAINNET)) {
        return false;
    }

    // test mainnet integrated address validation
    if (!monero_utils_is_valid_address("4CApvrfMgUFZEePHBZHwuSckQXebuZu299NSmVEmQ41YJZQhKcPyujyMSzpDH4VMMVSBo3U3b54JaNvQLwAjqDhKeGLQ9vfRBRKFKnBtVH", MONERO_NETWORK_MAINNET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("4JGdXrMXaMP4nJ8fdz2w65TrTEp9PRsv5J8iHSShkHQcE2V31FhnWptioNst1K9oeDY4KpWZ7v8V2BZNVa4Wdky8DvDyXvDZXvE9jTQwom", MONERO_NETWORK_MAINNET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("4JCp7q5SchvMCHVKENnPpM7tRcL5oWMgpMCqQDbhH8UrjDFg2H9i5AQWXuU1qacJgUUCVLTsgDmZKXGz1vPLXY8QFySJXARQWju8AuRN2z", MONERO_NETWORK_MAINNET)) {
        return false;
    }

    // test mainnet subaddress validation
    if (!monero_utils_is_valid_address("891TQPrWshJVpnBR4ZMhHiHpLx1PUnMqa3ccV5TJFBbqcJa3DWhjBh2QByCv3Su7WDPTGMHmCKkiVFN2fyGJKwbM1t6G7Ea", MONERO_NETWORK_MAINNET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("88fyq3t8Gxn1QWMG189EufHtMHXZXkfJtJKFJXqeA4GpSiuyfjVwVyp47PeQJnD7Tc8iK8TDvvhcmEmfh8nx7Va2ToP8wAo", MONERO_NETWORK_MAINNET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("88hnoBiX3TPjbFaQE8RxgyBcf3DtMKZWWQMoArBjQfn37JJwtm568mPX6ipcCuGKDnLCzgjmpLSqce4aBDyapJJAFtNxUMb", MONERO_NETWORK_MAINNET)) {
        return false;
    }

    return true;
}

bool test_testnet_address_validation() {
    // test testnet primary address validation
    if (!monero_utils_is_valid_address("9tUBnNCkC3UKGygHCwYvAB1FscpjUuq5e9MYJd2rXuiiTjjfVeSVjnbSG5VTnJgBgy9Y7GTLfxpZNMUwNZjGfdFr1z79eV1", MONERO_NETWORK_TESTNET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("9xZmQa1kYakGoHcfXeBgcsLf622NCpChcACwXxfdgY9uAa9hXSPCV9cLvUsAShfDcFKDdPzCNJ1n5cFGKw5GVM722pjuGPd", MONERO_NETWORK_TESTNET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("A2TXS6QFQ4wEsp8U7C2Y4B7wBtiML8aDG7mdCbRvDQmRaRNj1YSSgJE46fSzUkwgpMUCXFqscvrQuN7oKpP6eDyQ7XuYsuf", MONERO_NETWORK_TESTNET)) {
        return false;
    }

    // test testnet integrated address validation
    if (!monero_utils_is_valid_address("A4AroB2EoJzKGygHCwYvAB1FscpjUuq5e9MYJd2rXuiiTjjfVeSVjnbSG5VTnJgBgy9Y7GTLfxpZNMUwNZjGfdFr2QY5Ba2aHhTEdQa2ra", MONERO_NETWORK_TESTNET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("A8GSRNqF9rGGoHcfXeBgcsLf622NCpChcACwXxfdgY9uAa9hXSPCV9cLvUsAShfDcFKDdPzCNJ1n5cFGKw5GVM723iPoCEF1Fs9BcPYxTW", MONERO_NETWORK_TESTNET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("ACACSuDk1LTEsp8U7C2Y4B7wBtiML8aDG7mdCbRvDQmRaRNj1YSSgJE46fSzUkwgpMUCXFqscvrQuN7oKpP6eDyQAdgDoT3UnMYKQz7SHC", MONERO_NETWORK_TESTNET)) {
        return false;
    }

    // test testnet subaddress validation
    if (!monero_utils_is_valid_address("BgnKzHPJQDcg7xiP7bMN9MfPv9Z8ciT71iEMYnCdgBRBFETWgu9nKTr8fnzyGfU9h9gyNA8SFzYYzHfTS9KhqytSU943Nu1", MONERO_NETWORK_TESTNET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("BZwiuKkoNP59zgPHTxpNw3PM4DW2xiAVQJWqfFRrGyeZ7afVdQqoiJg3E2dDL3Ja8BV4ov2LEoHx9UjzF3W4ihPBSZvWwTx", MONERO_NETWORK_TESTNET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("Bhf1DEYrentcehUvNreLK5gxosnC2VStMXNCCs163RTxQq4jxFYvpw7LrQFmrMwWW2KsXLhMRtyho6Lq11ci3Fb246bxYmi", MONERO_NETWORK_TESTNET)) {
        return false;
    }

    return true;
}

bool test_stagenet_address_validation() {
    // test stagenet primary address validation
    if (!monero_utils_is_valid_address("5B8s3obCY2ETeQB3GNAGPK2zRGen5UeW1WzegSizVsmf6z5NvM2GLoN6zzk1vHyzGAAfA8pGhuYAeCFZjHAp59jRVQkunGS", MONERO_NETWORK_STAGENET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("57VfotUbSZLG82UkKhWXDjS5ZEK9ZCDcmjdk4gpVq2fbKdEgwRCFrGTLZ2MMdSHphRWJDWVBi5qS8T7dz13JTCWtC228zyn", MONERO_NETWORK_STAGENET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("52FysgWJYmAG73QUQZRULJj2Dv2C2mceUMB5zHqNzMn8WBtfPWQrSUFSQUKTX9r7bUMmVSGbrau976xYLynR8jTWLdA7rfp", MONERO_NETWORK_STAGENET)) {
        return false;
    }

    // test stagenet integrated address validation
    if (!monero_utils_is_valid_address("5LqY4cQh9HkTeQB3GNAGPK2zRGen5UeW1WzegSizVsmf6z5NvM2GLoN6zzk1vHyzGAAfA8pGhuYAeCFZjHAp59jRj6LZRFrjuGK8Whthg2", MONERO_NETWORK_STAGENET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("5HCLphJ63prG82UkKhWXDjS5ZEK9ZCDcmjdk4gpVq2fbKdEgwRCFrGTLZ2MMdSHphRWJDWVBi5qS8T7dz13JTCWtHETX8zcUhDjVKcynf6", MONERO_NETWORK_STAGENET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("5BxetVKoA2gG73QUQZRULJj2Dv2C2mceUMB5zHqNzMn8WBtfPWQrSUFSQUKTX9r7bUMmVSGbrau976xYLynR8jTWVwQwpHNg5fCLgtA2Dv", MONERO_NETWORK_STAGENET)) {
        return false;
    }

    // test stagenet subaddress validation
    if (!monero_utils_is_valid_address("778B5D2JmMh5TJVWFbygJR15dvio5Z5B24hfSrWDzeroM8j8Lqc9sMoFE6324xg2ReaAZqHJkgfGFRugRmYHugHZ4f17Gxo", MONERO_NETWORK_STAGENET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("73U97wGEH9RCVUf6bopo45jSgoqjMzz4mTUsvWs5EusmYAmFcBYFm7wKMVmgtVKCBhMQqXrcMbHvwck2md63jMZSFJxUhQ2", MONERO_NETWORK_STAGENET)) {
        return false;
    }
    if (!monero_utils_is_valid_address("747wPpaPKrjDPZrF48jAfz9pRRUHLMCWfYu2UanP4ZfTG8NrmYrSEWNW8gYoadU8hTiwBjV14e6DLaC5xfhyEpX5154aMm6", MONERO_NETWORK_STAGENET)) {
        return false;
    }

    return true;
}

START_TEST(test_address_validation)
{
    bool result = test_mainnet_address_validation();
    ck_assert_msg(result, "Mainnet address validation test failed");
    result = test_testnet_address_validation();
    ck_assert_msg(result, "Testnet address validation test failed");
    result = test_stagenet_address_validation();
    ck_assert_msg(result, "Stagenet address validation test failed");
}
END_TEST

Suite *test_monero_utils_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("test_monero_utils");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_address_validation);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = test_monero_utils_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}