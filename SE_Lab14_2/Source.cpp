#include <iostream>
#include "Error.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");


    std::cout << "- - - ���� Error::geterrorin" << std::endl << std::endl;

    try
    {
        throw ERROR_THROW_IN(111, 7, 7);
    }
    catch (Error::ERROR e)
    {
        std::cout << "������" << e.id << ": " << e.message
            << ", ������ " << e.inext.line
            << ", ������� " << e.inext.col << std::endl << std::endl;
    }
}
