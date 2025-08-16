#include <iostream>
#include <string>
#include <vector>
#include <fstream> 

class Observer {
public:
    virtual ~Observer() = default;

    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

class Subject : public Observer {
   std::vector<Observer*> observers;
public:

    void addObserver(Observer* obs) {
        if (obs && std::find(observers.begin(), observers.end(), obs) == observers.end()) {
            observers.push_back(obs);
        }
    }
    void removeObserver(Observer* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }
    void warning(const std::string& message)
    {
        for (auto i : observers)
        {
          if (i)  i->onWarning(message);

        }

    }
    void error(const std::string& message) const {
        for (auto obs : observers) {
            if (obs) obs->onError(message);
        }
    }
    void fatalError(const std::string& message) const {
        for (auto obs : observers) {
            if (obs) obs->onFatalError(message);
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
    std::string filePath;
public:
    explicit ErrorObserver(const std::string& path) : filePath(path) {}

    void onError(const std::string& message) override {
        std::ofstream out(filePath, std::ios::app);
        if (out) {
            out << "[ERROR] " << message << std::endl;
        }
    }
};
class FatalErrorObserver : public Observer {
    std::string filePath;
public:
    explicit FatalErrorObserver(const std::string& path) : filePath(path) {}

    void onFatalError(const std::string& message) override {
        std::cout << "[FATAL] " << message << std::endl;

        std::ofstream out(filePath, std::ios::app);
        if (out) {
            out << "[FATAL] " << message << std::endl;
        }
    }
};
int main2() {
    Subject logger;

    WarningObserver warnObs;
    ErrorObserver errObs("errors.log");
    FatalErrorObserver fatalObs("errors.log");

    logger.addObserver(&warnObs);
    logger.addObserver(&errObs);
    logger.addObserver(&fatalObs);

    logger.warning("Low memory usage.");
    logger.error("File not found.");
    logger.fatalError("Critical system failure!");

    logger.removeObserver(&errObs); // корректно удаляем наблюдателя

    logger.error("This error won't be logged in file (observer removed).");

    return 0;
}