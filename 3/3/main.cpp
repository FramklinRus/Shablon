

#include <iostream>
#include <fstream>  
#include <string>

using namespace std;

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class First : public LogCommand {
    
public:
  
    
   void print(const string& message) override {
       
       cout << message;

   }

};

class Second : public LogCommand {

public:


    void print(const string& message) override {

        std::ofstream file("output.txt"); // открыть файл для записи

        if (!file.is_open()) {
            std::cerr << "Не удалось открыть файл!" << std::endl;
          
        }
      file << message << std::endl; // запись строки в файл
              file.close();

    }

};

void print(LogCommand& l)
{
    l.print("Hello World!!");


}

int main_1()
{
    First im;
    Second j;

    print(im);
    print(j);
    return 0;

}

