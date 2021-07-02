// Public Resource ℗ 2021 Đ𝖺𝗌𝗁 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
// Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#ifndef BITCOIN_GOVERNANCE_GOVERNANCE_VALIDATORS_H
#define BITCOIN_GOVERNANCE_GOVERNANCE_VALIDATORS_H

#include <string>

#include <univalue.h>

class CProposalValidator
{
private:
    UniValue objJSON;
    bool fJSONValid;
    bool fAllowLegacyFormat;
    std::string strErrorMessages;

public:
    explicit CProposalValidator(const std::string& strDataHexIn = std::string(), bool fAllowLegacyFormat = true);

    bool Validate(bool fCheckExpiration = true);

    const std::string& GetErrorMessages()
    {
        return strErrorMessages;
    }

private:
    void ParseStrHexData(const std::string& strHexData);
    void ParseJSONData(const std::string& strJSONData);

    bool GetDataValue(const std::string& strKey, std::string& strValueRet);
    bool GetDataValue(const std::string& strKey, int64_t& nValueRet);
    bool GetDataValue(const std::string& strKey, double& dValueRet);

    bool ValidateType();
    bool ValidateName();
    bool ValidateStartEndEpoch(bool fCheckExpiration = true);
    bool ValidatePaymentAmount();
    bool ValidatePaymentAddress();
    bool ValidateURL();

    bool CheckURL(const std::string& strURLIn);
};

#endif // BITCOIN_GOVERNANCE_GOVERNANCE_VALIDATORS_H
