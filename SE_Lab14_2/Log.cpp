#define _CRT_SECURE_NO_WARNINGS
#include "Error.h"   //обработка ошибок
#include "Parm.h"    //обработка параметров
#include "Log.h"   //работа с протоколом
#include "In.h"   // ввод исходного файла
#include <stdarg.h>
#include <fstream>
#include <iostream>
#include <cwchar>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdarg.h>
#include <cwchar>
#include <codecvt>
#include <locale>

namespace Log {

    // Функция для получения объекта LOG
    LOG getlog(const char* logfile) {
        LOG log = { { '\0' }, nullptr };
        strcpy_s(log.logfile, PARM_MAX_SIZE, logfile);

        // Попытка открыть файл для записи
        log.stream = new std::ofstream(log.logfile, std::ios::out);

        // Проверка успешного открытия файла
        if (!log.stream->is_open()) {
            // Генерирование исключения при ошибке открытия файла
            throw std::runtime_error("Ошибка открытия файла");
        }

        return log;
    }

    // Вывести в протокол конкатенацию строк
    void WriteLine(LOG log, char* c, ...) {
        va_list args;
        va_start(args, c);

        std::string result = c;
        const char* next;
        while ((next = va_arg(args, const char*)) != nullptr) {
            // Проверка типа аргумента (в данном случае просто проверяем, что это строка)
            if (next == nullptr || strlen(next) == 0) {
                break;  // Прерываем цикл, если аргумент не является строкой
            }
            result += next;
        }
        va_end(args);

        *log.stream << result << std::endl;
    }

    void WriteLog(LOG log) {
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "Лог программы:" << std::endl;
        *log.stream << "-------------------------" << std::endl;
    }

    void WriteParm(LOG log, Parm::PARM parm) {
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "Входные параметры:" << std::endl;
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "Входной файл: " << parm.in << std::endl;
        *log.stream << "Выходной файл: " << parm.out << std::endl;
        *log.stream << "Файл логов: " << parm.log << std::endl;
        *log.stream << "-------------------------" << std::endl;
    }

    void WriteIn(LOG& log, const In::IN& in) {
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "Входной поток:" << std::endl;
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "Количество сиволов:" << in.size << std::endl;
        *log.stream << "Количество игнорав:" << in.ignor << std::endl;
        *log.stream << "Количество строк  :" << in.lines << std::endl;
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "Содержимое файла:" << std::endl;
        *log.stream << in.text << std::endl;
        *log.stream << "-------------------------" << std::endl;
    }

    void WriteError(LOG log, Error::ERROR error) {
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "Ошибка:" << std::endl;
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "Код ошибки:" << error.id << std::endl;
        *log.stream << "Сообщение:" << error.message << std::endl;
        if (error.inext.line != -1 && error.inext.col != -1) {
            *log.stream << "Строка: " << error.inext.line << ", Колонна: " << error.inext.col << std::endl;
        }
        *log.stream << "-------------------------" << std::endl;
    }

    void Close(LOG log) {
        if (log.stream != nullptr) {
            log.stream->close();
            // Удаляем поток только если он был создан с помощью 'new'
            if (log.stream != &std::cout && log.stream != &std::cerr) {
                delete log.stream;
            }
        }
    }

} // namespace Log
