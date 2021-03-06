#!/usr/bin/env python3
# Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
# Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
"""Create a blockchain cache.

Creating a cache of the blockchain speeds up test execution when running
multiple functional tests. This helper script is executed by test_runner when multiple
tests are being run in parallel.
"""

from test_framework.test_framework import BitcoinTestFramework

class CreateCache(BitcoinTestFramework):
    # Test network and test nodes are not required:

    def set_test_params(self):
        self.num_nodes = 0
        self.supports_cli = True

    def setup_network(self):
        pass

    def run_test(self):
        pass

if __name__ == '__main__':
    CreateCache().main()
