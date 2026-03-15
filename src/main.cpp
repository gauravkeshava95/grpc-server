#include "logger/ConsoleLogger.h"
#include "services/GreeterServiceImpl.h"
#include "server/ServerBuilder.h"
#include "server/ServiceRegistry.h"
#include <memory>
#include <iostream>
#include <csignal>

static grpc::Server* g_server = nullptr;

void signalHandler(int signal) {
    if (g_server) {
        std::cout << "\nShutting down server...\n";
        g_server->Shutdown();
    }
}

int main() {
    // 1. Create logger 
    auto logger = std::make_shared<ConsoleLogger>();

    // 2. Create services 
    auto greeterService = std::make_shared<GreeterServiceImpl>(logger);

    // 3. Register services
    auto registry = std::make_shared<ServiceRegistry>();
    registry->registerService(greeterService.get());

    // 4. Build server using builder pattern
    auto server = GrpcServerBuilder()
        .withAddress("0.0.0.0:50051")
        .withLogger(logger)
        .withServiceRegistry(registry)
        .build();

    if (!server) {
        logger->error("Failed to start server");
        return 1;
    }

    g_server = server.get();
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    logger->info("Server running on port 50051. Press Ctrl+C to stop.");
    server->Wait();  

    logger->info("Server stopped cleanly.");
    return 0;
}