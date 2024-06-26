#include "In.h"
#include "Error.h"
#include <fstream>

namespace In {
    IN getin(char infile[]) {
        setlocale(LC_ALL, "Russian"); // Установка русской локали
        IN input;
        input.size = 0;
        input.lines = 0;
        input.ignor = 0;

        // Открываем файл и определяем его размер
        std::ifstream file(infile, std::ios::in);
        if (!file.is_open()) {
            throw ERROR_THROW(110);
        }

        // Получаем размер файла
        file.seekg(0, std::ios::end);
        int size = file.tellg();
        file.seekg(0, std::ios::beg);

        input.text = new char[size + 1]; // Выделяем память под текст

        // Чтение данных из файла
        char ch;
        int lineNum = 0;
        while (file.get(reinterpret_cast<char&>(ch))) {
            if (ch == IN_CODE_ENDL) {
                lineNum++;
            }
            else if (ch == 'X') {
                // Игнорирование символа 'Х'
                input.ignor++;
            }
            else if (ch == 'Y') {
                // Заменяет символ 'Y' на '!'
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

        input.text[input.size] = '\0'; // Добавляем завершающий нулевой символ

        input.lines = lineNum + 1;
        input.size = size; // Устанавливаем размер текста

        return input;
    }
}
