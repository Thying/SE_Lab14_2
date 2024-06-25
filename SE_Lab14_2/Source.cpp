#include <iostream>
#include "Error.h"
#include "Parm.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    std::cout << "- - - тест Parm::getparm" << std::endl << std::endl;

    try
    {
        Parm::PARM parm = Parm::getparm(argc, argv);
        std::wcout << "-in:" << parm.in << ", -out:" << parm.out << ", -log:" << parm.log << std::endl << std::endl;
    }
    catch (Error::ERROR e)
    {
        std::cout << "Ошибка" << e.id << ": " << e.message << std::endl << std::endl;
    }
}
