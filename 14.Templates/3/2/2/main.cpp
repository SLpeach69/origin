#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

class Observable {
private:
    std::vector<Observer*> observers;

public:
    virtual ~Observable() = default;

    void addObserver(Observer* observer) {
        if (observer && std::find(observers.begin(), observers.end(), observer) == observers.end()) {
            observers.push_back(observer);
        }
    }

    void removeObserver(Observer* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void warning(const std::string& message) const {
        for (auto observer : observers) {
            observer->onWarning(message);
        }
    }

    void error(const std::string& message) const {
        for (auto observer : observers) {
            observer->onError(message);
        }
    }

    void fatalError(const std::string& message) const {
        for (auto observer : observers) {
            observer->onFatalError(message);
        }
    }
};

class WarningObserver : public Observer {
public:
    void onWarning(const std::string& message) override {
        std::cout << "[WARNING] " << message << std::endl;
    }
};

class ErrorObserver : public Observer {
private:
    std::string filePath;

public:
    explicit ErrorObserver(const std::string& path) : filePath(path) {}

    void onError(const std::string& message) override {
        std::ofstream file(filePath, std::ios::app);
        if (file.is_open()) {
            file << "[ERROR] " << message << std::endl;
        }
        else {
            std::cerr << "Failed to open error log file: " << filePath << std::endl;
        }
    }
};

class FatalErrorObserver : public Observer {
private:
    std::string filePath;

public:
    explicit FatalErrorObserver(const std::string& path) : filePath(path) {}

    void onFatalError(const std::string& message) override {
        std::cerr << "[FATAL ERROR] " << message << std::endl;

        std::ofstream file(filePath, std::ios::app);
        if (file.is_open()) {
            file << "[FATAL ERROR] " << message << std::endl;
        }
        else {
            std::cerr << "Failed to open fatal error log file: " << filePath << std::endl;
        }
    }
};

class SafeObservable : public Observable {
private:
    std::vector<std::weak_ptr<Observer>> weakObservers;

    void cleanupExpiredObservers() {
        weakObservers.erase(
            std::remove_if(weakObservers.begin(), weakObservers.end(),
                [](const std::weak_ptr<Observer>& wp) { return wp.expired(); }),
            weakObservers.end()
        );
    }

public:
    void addObserver(std::weak_ptr<Observer> observer) {
        cleanupExpiredObservers();
        weakObservers.push_back(observer);
    }

    void warning(const std::string& message) const {
        Observable::warning(message);
        auto self = const_cast<SafeObservable*>(this);
        self->cleanupExpiredObservers();

        for (auto& weakObserver : self->weakObservers) {
            if (auto observer = weakObserver.lock()) {
                observer->onWarning(message);
            }
        }
    }

    void error(const std::string& message) const {
        Observable::error(message);
        auto self = const_cast<SafeObservable*>(this);
        self->cleanupExpiredObservers();

        for (auto& weakObserver : self->weakObservers) {
            if (auto observer = weakObserver.lock()) {
                observer->onError(message);
            }
        }
    }

    void fatalError(const std::string& message) const {
        Observable::fatalError(message);
        auto self = const_cast<SafeObservable*>(this);
        self->cleanupExpiredObservers();

        for (auto& weakObserver : self->weakObservers) {
            if (auto observer = weakObserver.lock()) {
                observer->onFatalError(message);
            }
        }
    }
};

int main() {
    std::cout << "Observer Pattern Example" << std::endl;

    WarningObserver warningObs;
    ErrorObserver errorObs("errors.log");
    FatalErrorObserver fatalObs("fatal.log");

    Observable logger;

    logger.addObserver(&warningObs);
    logger.addObserver(&errorObs);
    logger.addObserver(&fatalObs);

    std::cout << "\n1. Testing warnings:" << std::endl;
    logger.warning("Low memory warning");
    logger.warning("Connection timeout warning");

    std::cout << "\n2. Testing errors:" << std::endl;
    logger.error("Database connection failed");
    logger.error("File not found");

    std::cout << "\n3. Testing fatal errors:" << std::endl;
    logger.fatalError("System crash detected");
    logger.fatalError("Critical security breach");

    std::cout << "\n4. Testing with safe observable:" << std::endl;
    SafeObservable safeLogger;

    auto smartWarning = std::make_shared<WarningObserver>();
    auto smartError = std::make_shared<ErrorObserver>("safe_errors.log");

    safeLogger.addObserver(std::weak_ptr<Observer>(smartWarning));
    safeLogger.addObserver(std::weak_ptr<Observer>(smartError));

    safeLogger.warning("Safe warning");
    safeLogger.error("Safe error");

    return 0;
}