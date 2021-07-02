#!/usr/bin/env python3
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

from argparse import ArgumentParser
from base64 import urlsafe_b64encode
from binascii import hexlify
from getpass import getpass
from os import urandom

import hmac

def generate_salt(size):
    """Create size byte hex salt"""
    return hexlify(urandom(size)).decode()

def generate_password():
    """Create 32 byte b64 password"""
    return urlsafe_b64encode(urandom(32)).decode('utf-8')

def password_to_hmac(salt, password):
    m = hmac.new(bytearray(salt, 'utf-8'), bytearray(password, 'utf-8'), 'SHA256')
    return m.hexdigest()

def main():
    parser = ArgumentParser(description='Create login credentials for a JSON-RPC user')
    parser.add_argument('username', help='the username for authentication')
    parser.add_argument('password', help='leave empty to generate a random password or specify "-" to prompt for password', nargs='?')
    args = parser.parse_args()

    if not args.password:
        args.password = generate_password()
    elif args.password == '-':
        args.password = getpass()

    # Create 16 byte hex salt
    salt = generate_salt(16)
    password_hmac = password_to_hmac(salt, args.password)

    print('String to be appended to amero.conf:')
    print('rpcauth={0}:{1}${2}'.format(args.username, salt, password_hmac))
    print('Your password:\n{0}'.format(args.password))

if __name__ == '__main__':
    main()
