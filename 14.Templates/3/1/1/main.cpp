#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <stdexcept>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class ConsoleLogCommand : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << "[CONSOLE] " << message << std::endl;
    }
};

class FileLogCommand : public LogCommand {
private:
    std::string filePath;

public:
    explicit FileLogCommand(const std::string& path) : filePath(path) {}

    void print(const std::string& message) override {
        std::ofstream file(filePath, std::ios::app);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        file << "[FILE] " << message << std::endl;
    }

    const std::string& getFilePath() const {
        return filePath;
    }
};

void print(LogCommand& command, const std::string& message) {
    try {
        command.print(message);
    }
    catch (const std::exception& e) {
        std::cerr << "Command execution error: " << e.what() << std::endl;
    }
}

int main() {
    ConsoleLogCommand consoleCommand;
    FileLogCommand fileCommand("application.log");

    std::cout << "Logging to console:" << std::endl;
    print(consoleCommand, "First message");
    print(consoleCommand, "Second message");

    std::cout << "\nLogging to file:" << std::endl;
    print(fileCommand, "File message 1");
    print(fileCommand, "File message 2");

    std::cout << "\nUsing smart pointers:" << std::endl;
    std::unique_ptr<LogCommand> smartConsoleCommand = std::make_unique<ConsoleLogCommand>();
    std::unique_ptr<LogCommand> smartFileCommand = std::make_unique<FileLogCommand>("smart_log.log");

    print(*smartConsoleCommand, "Smart pointer console message");
    print(*smartFileCommand, "Smart pointer file message");

    return 0;
}