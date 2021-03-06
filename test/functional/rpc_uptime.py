#!/usr/bin/env python3
# Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
# Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
"""Test the RPC call related to the uptime command.

Test corresponds to code in rpc/server.cpp.
"""

import time

from test_framework.test_framework import BitcoinTestFramework


class UptimeTest(BitcoinTestFramework):
    def set_test_params(self):
        self.num_nodes = 1
        self.setup_clean_chain = True

    def run_test(self):
        self._test_uptime()

    def _test_uptime(self):
        wait_time = 10
        self.nodes[0].setmocktime(int(time.time() + wait_time))
        assert(self.nodes[0].uptime() >= wait_time)


if __name__ == '__main__':
    UptimeTest().main()
