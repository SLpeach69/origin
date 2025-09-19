#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>

enum class Type {
    WARNING,
    ERROR,
    FATAL_ERROR,
    UNKNOWN
};

class LogMessage {
private:
    Type msgType;
    std::string msgContent;

public:
    LogMessage(Type type, const std::string& message)
        : msgType(type), msgContent(message) {}

    Type type() const {
        return msgType;
    }

    const std::string& message() const {
        return msgContent;
    }
};

class LogHandler {

public:
    std::unique_ptr<LogHandler> nextHandler;
    virtual ~LogHandler() = default;

    void setNext(std::unique_ptr<LogHandler> next) {
        nextHandler = std::move(next);
    }

    void handle(const LogMessage& message) {
        if (canHandle(message.type())) {
            processMessage(message);
        }
        else if (nextHandler) {
            nextHandler->handle(message);
        }
        else {
            throw std::runtime_error("Unhandled log message: " + message.message());
        }
    }

    virtual bool canHandle(Type type) const = 0;

protected:
    virtual void processMessage(const LogMessage& message) = 0;
};

class FatalErrorHandler : public LogHandler {
protected:
    void processMessage(const LogMessage& message) override {
        throw std::runtime_error("FATAL ERROR: " + message.message());
    }

public:
    bool canHandle(Type type) const override {
        return type == Type::FATAL_ERROR;
    }
};

class ErrorHandler : public LogHandler {
private:
    std::string filePath;

protected:
    void processMessage(const LogMessage& message) override {
        std::ofstream file(filePath, std::ios::app);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open error log file: " + filePath);
        }
        file << "[ERROR] " << message.message() << std::endl;
    }

public:
    explicit ErrorHandler(const std::string& path) : filePath(path) {}

    bool canHandle(Type type) const override {
        return type == Type::ERROR;
    }
};

class WarningHandler : public LogHandler {
protected:
    void processMessage(const LogMessage& message) override {
        std::cout << "[WARNING] " << message.message() << std::endl;
    }

public:
    bool canHandle(Type type) const override {
        return type == Type::WARNING;
    }
};

class UnknownMessageHandler : public LogHandler {
protected:
    void processMessage(const LogMessage& message) override {
        throw std::runtime_error("Unknown message type received: " + message.message());
    }

public:
    bool canHandle(Type type) const override {
        return type == Type::UNKNOWN;
    }
};

class LogChainBuilder {
public:
    static std::unique_ptr<LogHandler> createDefaultChain() {
        auto fatalHandler = std::make_unique<FatalErrorHandler>();
        auto errorHandler = std::make_unique<ErrorHandler>("errors.log");
        auto warningHandler = std::make_unique<WarningHandler>();
        auto unknownHandler = std::make_unique<UnknownMessageHandler>();

        fatalHandler->setNext(std::move(errorHandler));
        fatalHandler->nextHandler->setNext(std::move(warningHandler));
        fatalHandler->nextHandler->nextHandler->setNext(std::move(unknownHandler));

        return fatalHandler;
    }
};

class Logger {
private:
    std::unique_ptr<LogHandler> chain;

public:
    Logger(std::unique_ptr<LogHandler> handlerChain) : chain(std::move(handlerChain)) {}

    void log(const LogMessage& message) {
        try {
            chain->handle(message);
        }
        catch (const std::exception& e) {
            std::cerr << "Logging exception: " << e.what() << std::endl;
            if (message.type() == Type::FATAL_ERROR) {
                throw;
            }
        }
    }

    void log(Type type, const std::string& message) {
        log(LogMessage(type, message));
    }
};

int main() {
    std::cout << "=== Chain of Responsibility Pattern Demonstration ===" << std::endl;

    try {
        auto chain = LogChainBuilder::createDefaultChain();
        Logger logger(std::move(chain));

        std::cout << "\n1. Testing warning message:" << std::endl;
        logger.log(Type::WARNING, "Low disk space");

        std::cout << "\n2. Testing error message:" << std::endl;
        logger.log(Type::ERROR, "Database connection failed");

        std::cout << "\n3. Testing unknown message:" << std::endl;
        try {
            logger.log(Type::UNKNOWN, "Some message");
        }
        catch (const std::exception& e) {
            std::cout << "Caught expected exception: " << e.what() << std::endl;
        }

        std::cout << "\n4. Testing fatal error message:" << std::endl;
        try {
            logger.log(Type::FATAL_ERROR, "System crash imminent!");
        }
        catch (const std::exception& e) {
            std::cout << "Caught fatal error exception: " << e.what() << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}