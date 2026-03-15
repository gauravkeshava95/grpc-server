#include "ServerBuilder.h"
#include <stdexcept>

GrpcServerBuilder& GrpcServerBuilder::withAddress(const std::string& address) {
    address_ = address;
    return *this;
}

GrpcServerBuilder& GrpcServerBuilder::withLogger(std::shared_ptr<ILogger> logger) {
    logger_ = std::move(logger);
    return *this;
}

GrpcServerBuilder& GrpcServerBuilder::withServiceRegistry(
    std::shared_ptr<ServiceRegistry> registry)
{
    registry_ = std::move(registry);
    return *this;
}

std::unique_ptr<grpc::Server> GrpcServerBuilder::build() {
    if (!logger_) throw std::runtime_error("Logger must be set before building server");
    if (!registry_) throw std::runtime_error("ServiceRegistry must be set before building server");

    grpc::ServerBuilder builder;
    builder.AddListeningPort(address_, grpc::InsecureServerCredentials());

    registry_->addServicesToBuilder(builder);

    logger_->info("Building gRPC server on " + address_);
    return builder.BuildAndStart();
}