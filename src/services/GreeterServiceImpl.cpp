#include "GreeterServiceImpl.h"

GreeterServiceImpl::GreeterServiceImpl(std::shared_ptr<ILogger> logger)
    : logger_(std::move(logger)) {}

grpc::Status GreeterServiceImpl::SayHello(
    grpc::ServerContext* context,
    const greeter::HelloRequest* request,
    greeter::HelloReply* reply)
{
    const std::string name = request->name().empty() ? "stranger" : request->name();
    logger_->info("SayHello called for: " + name);

    reply->set_message("Hello, " + name + "! Welcome.");
    return grpc::Status::OK;
}

grpc::Status GreeterServiceImpl::SayGoodbye(
    grpc::ServerContext* context,
    const greeter::GoodbyeRequest* request,
    greeter::GoodbyeReply* reply)
{
    const std::string name = request->name().empty() ? "stranger" : request->name();
    logger_->info("SayGoodbye called for: " + name);

    reply->set_message("Goodbye, " + name + ". See you soon!");
    return grpc::Status::OK;
}