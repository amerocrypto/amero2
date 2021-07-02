#!/usr/bin/env python3
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
"""Test Wallet encryption"""

import time

from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import (
    assert_equal,
    assert_raises_rpc_error,
    assert_greater_than,
    assert_greater_than_or_equal,
)

class WalletEncryptionTest(BitcoinTestFramework):
    def set_test_params(self):
        self.setup_clean_chain = True
        self.num_nodes = 1

    def run_test(self):
        passphrase = "WalletPassphrase"
        passphrase2 = "SecondWalletPassphrase"

        # Make sure the wallet isn't encrypted first
        address = self.nodes[0].getnewaddress()
        privkey = self.nodes[0].dumpprivkey(address)
        assert_equal(privkey[:1], "c")
        assert_equal(len(privkey), 52)

        # Encrypt the wallet
        self.nodes[0].encryptwallet(passphrase)

        # Test that the wallet is encrypted
        assert_raises_rpc_error(-13, "Please enter the wallet passphrase with walletpassphrase first", self.nodes[0].dumpprivkey, address)

        # Check that walletpassphrase works
        self.nodes[0].walletpassphrase(passphrase, 2)
        assert_equal(privkey, self.nodes[0].dumpprivkey(address))

        # Check that the timeout is right
        time.sleep(4)  # Wait a little bit longer to make sure wallet gets locked
        assert_raises_rpc_error(-13, "Please enter the wallet passphrase with walletpassphrase first", self.nodes[0].dumpprivkey, address)

        # Test wrong passphrase
        assert_raises_rpc_error(-14, "wallet passphrase entered was incorrect", self.nodes[0].walletpassphrase, passphrase + "wrong", 10)

        # Test walletlock
        self.nodes[0].walletpassphrase(passphrase, 84600)
        assert_equal(privkey, self.nodes[0].dumpprivkey(address))
        self.nodes[0].walletlock()
        assert_raises_rpc_error(-13, "Please enter the wallet passphrase with walletpassphrase first", self.nodes[0].dumpprivkey, address)

        # Test passphrase changes
        self.nodes[0].walletpassphrasechange(passphrase, passphrase2)
        assert_raises_rpc_error(-14, "wallet passphrase entered was incorrect", self.nodes[0].walletpassphrase, passphrase, 10)
        self.nodes[0].walletpassphrase(passphrase2, 10)
        assert_equal(privkey, self.nodes[0].dumpprivkey(address))
        self.nodes[0].walletlock()

        # Test timeout bounds
        assert_raises_rpc_error(-8, "Timeout cannot be negative.", self.nodes[0].walletpassphrase, passphrase2, -10)
        # Check the timeout
        # Check a time less than the limit
        MAX_VALUE = 100000000
        expected_time = self.mocktime + MAX_VALUE - 600
        self.nodes[0].walletpassphrase(passphrase2, MAX_VALUE - 600)
        actual_time = self.nodes[0].getwalletinfo()['unlocked_until']
        assert_greater_than_or_equal(actual_time, expected_time)
        assert_greater_than(expected_time + 5, actual_time) # 5 second buffer
        # Check a time greater than the limit
        expected_time = self.mocktime + MAX_VALUE - 1
        self.nodes[0].walletpassphrase(passphrase2, MAX_VALUE + 1000)
        actual_time = self.nodes[0].getwalletinfo()['unlocked_until']
        assert_greater_than_or_equal(actual_time, expected_time)
        assert_greater_than(expected_time + 5, actual_time) # 5 second buffer

if __name__ == '__main__':
    WalletEncryptionTest().main()
