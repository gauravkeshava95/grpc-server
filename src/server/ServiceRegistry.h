#pragma once
#include <grpcpp/server_builder.h>
#include <vector>
#include <memory>

class ServiceRegistry {
public:
    void registerService(grpc::Service* service);
    void addServicesToBuilder(grpc::ServerBuilder& builder) const;

private:
    std::vector<grpc::Service*> services_;
};