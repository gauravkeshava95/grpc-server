#pragma once
#include "../interfaces/IGreeterService.h"
#include "../interfaces/ILogger.h"
#include <memory>

class GreeterServiceImpl final : public IGreeterService {
public:
    // Constructor injection (Dependency Inversion Principle)
    explicit GreeterServiceImpl(std::shared_ptr<ILogger> logger);

    grpc::Status SayHello(
        grpc::ServerContext* context,
        const greeter::HelloRequest* request,
        greeter::HelloReply* reply) override;

    grpc::Status SayGoodbye(
        grpc::ServerContext* context,
        const greeter::GoodbyeRequest* request,
        greeter::GoodbyeReply* reply) override;

private:
    std::shared_ptr<ILogger> logger_;
};