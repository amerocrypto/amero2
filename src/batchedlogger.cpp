// Public Resource β 2021 ΔπΊππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#include <batchedlogger.h>
#include <util.h>

CBatchedLogger::CBatchedLogger(uint64_t _category, const std::string& _header) :
    accept(LogAcceptCategory(_category)), header(_header)
{
}

CBatchedLogger::~CBatchedLogger()
{
    Flush();
}

void CBatchedLogger::Flush()
{
    if (!accept || msg.empty()) {
        return;
    }
    LogPrintStr(strprintf("%s:\n%s", header, msg));
    msg.clear();
}
