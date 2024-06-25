#include <iostream>
#include "Error.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");


    std::cout << "- - - тест Error::geterrorin" << std::endl << std::endl;

    try
    {
        throw ERROR_THROW_IN(111, 7, 7);
    }
    catch (Error::ERROR e)
    {
        std::cout << "Ошибка" << e.id << ": " << e.message
            << ", строка " << e.inext.line
            << ", позиция " << e.inext.col << std::endl << std::endl;
    }
}
