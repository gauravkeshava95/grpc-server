## gRPC Server in C++

A gRPC server built in C++ with clean architecture. Built this to learn gRPC, protobuf, and how to structure C++ projects properly.

## What it does

Runs a server on port `50051` that handles two RPC calls:
- `SayHello` — takes a name, returns a greeting
- `SayGoodbye` — takes a name, returns a goodbye message

## Project structure
├── proto/greeter.proto         # defines the API
└── src/
    ├── interfaces/             # abstractions (ILogger, IGreeterService)
    ├── logger/                 # console logger
    ├── services/               # actual RPC logic
    ├── server/                 # server setup using builder pattern
    └── main.cpp                # wires everything together

## Setup (macOS)
```bash
brew install cmake grpc protobuf
```
```bash
git clone https://github.com/gauravkeshava95/grpc-server.git
cd grpc-server
mkdir build && cd build
cmake ..
make -j$(sysctl -n hw.logicalcpu)
``

## Run
```bash
./grpc_server
```

## Test
```bash
brew install grpcurl

grpcurl -plaintext \
  -import-path ./proto \
  -proto greeter.proto \
  -d '{"name": "Gaurav"}' \
  localhost:50051 greeter.Greeter/SayHello
```

## Things I applied

- SOLID principles
- Builder pattern for server construction
- Dependency injection for the logger
- Interfaces so implementations are swappable
