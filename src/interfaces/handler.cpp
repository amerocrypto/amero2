// Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#include <interfaces/handler.h>

#include <util.h>

#include <boost/signals2/connection.hpp>
#include <memory>
#include <utility>

namespace interfaces {
namespace {

class HandlerImpl : public Handler
{
public:
    HandlerImpl(boost::signals2::connection connection) : m_connection(std::move(connection)) {}

    void disconnect() override { m_connection.disconnect(); }

    boost::signals2::scoped_connection m_connection;
};

} // namespace

std::unique_ptr<Handler> MakeHandler(boost::signals2::connection connection)
{
    return MakeUnique<HandlerImpl>(std::move(connection));
}

} // namespace interfaces
