#!/usr/bin/env python3
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
"""Verify that starting amerox with -h works as expected."""
import subprocess

from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import assert_equal

class HelpTest(BitcoinTestFramework):
    def set_test_params(self):
        self.setup_clean_chain = True
        self.num_nodes = 1

    def setup_network(self):
        self.add_nodes(self.num_nodes)
        # Don't start the node

    def run_test(self):
        self.log.info("Start amerox with -h for help text")
        self.nodes[0].start(extra_args=['-h'], stderr=subprocess.PIPE, stdout=subprocess.PIPE)
        # Node should exit immediately and output help to stdout.
        ret_code = self.nodes[0].process.wait(timeout=1)
        assert_equal(ret_code, 0)
        output = self.nodes[0].process.stdout.read()
        assert b'Options' in output
        self.log.info("Help text received: {} (...)".format(output[0:60]))
        self.nodes[0].running = False

        self.log.info("Start amerox with -version for version information")
        self.nodes[0].start(extra_args=['-version'], stderr=subprocess.PIPE, stdout=subprocess.PIPE)
        # Node should exit immediately and output version to stdout.
        ret_code = self.nodes[0].process.wait(timeout=1)
        assert_equal(ret_code, 0)
        output = self.nodes[0].process.stdout.read()
        assert b'version' in output
        self.log.info("Version text received: {} (...)".format(output[0:60]))
        # Clean up TestNode state
        self.nodes[0].running = False
        self.nodes[0].process = None
        self.nodes[0].rpc_connected = False
        self.nodes[0].rpc = None

if __name__ == '__main__':
    HelpTest().main()
