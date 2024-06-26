#include <iostream>
#include "Error.h"
#include "Parm.h"
#include "In.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    std::cout << "- - - ���� In::getin" << std::endl << std::endl;

try
{
    char a[] = "C:/Games/in.txt";
    In::IN in = In::getin(a);
    std::cout << in.text << std::endl;
    std::cout << "����� ��������: " << in.size << std::endl;
    std::cout << "����� �����: " << in.lines << std::endl;
    std::cout << "���������: " << in.ignor << std::endl;
}
catch (Error::ERROR e)
{
    std::cout << "������" << e.id << ": " << e.message << std::endl << std::endl;
}
}
