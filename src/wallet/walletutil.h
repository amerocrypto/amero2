// Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#ifndef BITCOIN_WALLET_WALLETUTIL_H
#define BITCOIN_WALLET_WALLETUTIL_H

#include <chainparamsbase.h>
#include <util.h>

//! Get the path of the wallet directory.
fs::path GetWalletDir();

//! The WalletLocation class provides wallet information.
class WalletLocation final
{
    std::string m_name;
    fs::path m_path;

public:
    explicit WalletLocation() {}
    explicit WalletLocation(const std::string& name);

    //! Get wallet name.
    const std::string& GetName() const { return m_name; }

    //! Get wallet absolute path.
    const fs::path& GetPath() const { return m_path; }

    //! Return whether the wallet exists.
    bool Exists() const;
};

#endif // BITCOIN_WALLET_WALLETUTIL_H
