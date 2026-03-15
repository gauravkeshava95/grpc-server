#pragma once
#include <grpcpp/grpcpp.h>
#include "greeter.grpc.pb.h"

class IGreeterService : public greeter::Greeter::Service {
public:
    virtual ~IGreeterService() = default;

    virtual grpc::Status SayHello(
        grpc::ServerContext* context,
        const greeter::HelloRequest* request,
        greeter::HelloReply* reply) = 0;

    virtual grpc::Status SayGoodbye(
        grpc::ServerContext* context,
        const greeter::GoodbyeRequest* request,
        greeter::GoodbyeReply* reply) = 0;
};