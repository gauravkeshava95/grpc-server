#include "ServiceRegistry.h"

void ServiceRegistry::registerService(grpc::Service* service) {
    services_.push_back(service);
}

void ServiceRegistry::addServicesToBuilder(grpc::ServerBuilder& builder) const {
    for (auto* service : services_) {
        builder.RegisterService(service);
    }
}