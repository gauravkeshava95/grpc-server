#pragma once
#include "../interfaces/ILogger.h"

class ConsoleLogger final : public ILogger {
public:
    void info(const std::string& message) override;
    void error(const std::string& message) override;
    void debug(const std::string& message) override;

private:
    std::string timestamp() const;
};