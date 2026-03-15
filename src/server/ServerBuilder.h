#pragma once
#include "ServiceRegistry.h"
#include "../interfaces/ILogger.h"
#include <grpcpp/grpcpp.h>
#include <memory>
#include <string>

class GrpcServerBuilder {
public:
    GrpcServerBuilder& withAddress(const std::string& address);
    GrpcServerBuilder& withLogger(std::shared_ptr<ILogger> logger);
    GrpcServerBuilder& withServiceRegistry(std::shared_ptr<ServiceRegistry> registry);

    std::unique_ptr<grpc::Server> build();

private:
    std::string address_ = "0.0.0.0:50051";
    std::shared_ptr<ILogger> logger_;
    std::shared_ptr<ServiceRegistry> registry_;
};