#include "In.h"
#include "Error.h"
#include <fstream>

namespace In {
    IN getin(char infile[]) {
        setlocale(LC_ALL, "Russian"); // ��������� ������� ������
        IN input;
        input.size = 0;
        input.lines = 0;
        input.ignor = 0;

        // ��������� ���� � ���������� ��� ������
        std::ifstream file(infile, std::ios::in);
        if (!file.is_open()) {
            throw ERROR_THROW(110);
        }

        // �������� ������ �����
        file.seekg(0, std::ios::end);
        int size = file.tellg();
        file.seekg(0, std::ios::beg);

        input.text = new char[size + 1]; // �������� ������ ��� �����

        // ������ ������ �� �����
        char ch;
        int lineNum = 0;
        while (file.get(reinterpret_cast<char&>(ch))) {
            if (ch == IN_CODE_ENDL) {
                lineNum++;
            }
            else if (ch == 'X') {
                // ������������� ������� '�'
                input.ignor++;
            }
            else if (ch == 'Y') {
                // �������� ������ 'Y' �� '!'
                input.text[input.size++] = '!';
            }
            else if (input.code[ch] == IN::F) {
                throw ERROR_THROW_IN(111, lineNum, 0);
            }
            else if (input.code[ch] != IN::I) {
                input.text[input.size++] = ch;
            }
        }

        file.close();

        input.text[input.size] = '\0'; // ��������� ����������� ������� ������

        input.lines = lineNum + 1;
        input.size = size; // ������������� ������ ������

        return input;
    }
}
