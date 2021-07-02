#!/usr/bin/env python3
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
"""Test the -uacomment option."""

import re

from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import assert_equal


class UacommentTest(BitcoinTestFramework):
    def set_test_params(self):
        self.num_nodes = 1
        self.setup_clean_chain = True

    def run_test(self):
        self.log.info("test multiple -uacomment")
        test_uacomment = self.nodes[0].getnetworkinfo()["subversion"][-12:-1]
        assert_equal(test_uacomment, "(testnode0)")

        self.restart_node(0, ["-uacomment=foo"])
        foo_uacomment = self.nodes[0].getnetworkinfo()["subversion"][-17:-1]
        assert_equal(foo_uacomment, "(testnode0; foo)")

        self.log.info("test -uacomment max length")
        self.stop_node(0)
        expected = "Error: Total length of network version string \([0-9]+\) exceeds maximum length \(256\). Reduce the number or size of uacomments."
        self.nodes[0].assert_start_raises_init_error(["-uacomment=" + 'a' * 256], expected)

        self.log.info("test -uacomment unsafe characters")
        for unsafe_char in ['/', ':', '(', ')']:
            expected = "Error: User Agent comment \(" + re.escape(unsafe_char) + "\) contains unsafe characters."
            self.nodes[0].assert_start_raises_init_error(["-uacomment=" + unsafe_char], expected)


if __name__ == '__main__':
    UacommentTest().main()
