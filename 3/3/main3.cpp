#include <iostream>
#include <string>
#include <vector>
#include <fstream> 
#include <memory>
#include <stdexcept>
enum class Type {
    Warning,
    Error,
    FatalError,
    Unknown
};
class LogMessage {

    Type type_;
    std::string message_;
public:
    LogMessage(Type t, const std::string& msg)
        : type_(t), message_(msg) {}

    Type type() const { return type_; }
    const std::string& message() const { return message_; }


};

class Handler
{
protected:
    Handler* next = nullptr;
public:
    void setnext(Handler* handler) { next = handler; }
    
    virtual void handle(LogMessage& msg)
    {
        if (next)
        {
            next->handle(msg);
        }
        else {
            throw std::runtime_error("No handler found for message");
        }
    }
    virtual ~Handler() = default;

};


class HandlerA : public Handler
{
public:

    void handle(LogMessage& msg) override
    {
        if (msg.type()==Type::Warning)
        {
            std::cout << "Message: " << msg.message() << std::endl;

        }
        else {
        Handler::handle(msg);
        }

    }

};

class HandlerB : public Handler
{
public:

    void handle(LogMessage& msg) override
    {
        if (msg.type() == Type::Unknown)
        {
            throw std::runtime_error("Message: " + msg.message());

        }
        else {
        Handler::handle(msg);
        }
    }

};
class HandlerC : public Handler {
public:
    void handle(LogMessage& msg) override {
        if (msg.type() == Type::Error) {
            std::ofstream out("log.txt", std::ios::app);
            out << "Message: " << msg.message() << std::endl;
        }
        else {
            Handler::handle(msg); // передать дальше
        }
    }
};
class HandlerD : public Handler {
public:
    void handle( LogMessage& msg) override {
        if (msg.type() == Type::FatalError) {
            throw std::runtime_error("Message: " + msg.message());
        }
        else {
            Handler::handle(msg); // передать дальше
        }
    }
};
int main()
{
    LogMessage Log(Type::Warning, "Warning");
    LogMessage Log2(Type::Unknown, "Unknown");
    LogMessage Log3(Type::Error, "Error");
    LogMessage Log4(Type::FatalError, "FatalError");
    HandlerA A;
    HandlerB B;
    HandlerC C;
    HandlerD D;
    A.setnext(&B);
    B.setnext(&C);
    C.setnext(&D);

   A.handle(Log);
   A.handle(Log2);
   A.handle(Log3);
   A.handle(Log4);

}