#include <iostream>
#include "Error.h"
#include "Parm.h"
#include "In.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    std::cout << "- - - тест In::getin" << std::endl << std::endl;

    try
    {
        Parm::PARM parm = Parm::getparm(argc, argv);
        In::IN in = In::getin(parm.in);
        std::cout << in.text << std::endl;
        std::cout << "Всего символов: " << in.size << std::endl;
        std::cout << "Всего строк: " << in.lines << std::endl;
        std::cout << "Пропущено: " << in.ignor << std::endl;
    }
    catch (Error::ERROR e)
    {
        std::cout << "Ошибка" << e.id << ": " << e.message << std::endl << std::endl;
    }
}
