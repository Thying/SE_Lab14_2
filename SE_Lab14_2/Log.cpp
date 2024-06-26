#include "Error.h"   //обработка ошибок
#include "Parm.h"    //обработка параметров
#include "Log.h"   //работа с протоколом
#include "In.h"   // ввод исходного файла
#include <stdarg.h>
#include <fstream>
#include <iostream>
#include <cwchar>
#include <stdexcept>

namespace Log {

    // Функция для получения объекта LOG
    LOG getlog(wchar_t logfile[]) {
        LOG log = { { L'\0' }, nullptr };
        wcscpy_s(log.logfile, PARM_MAX_SIZE, logfile);

        // Попытка открыть файл для записи
        log.stream = new std::ofstream(log.logfile, std::ios::out | std::ios::binary);

        // Проверка успешного открытия файла
        if (!log.stream->is_open()) {
            // Генерирование исключения при ошибке открытия файла
            throw std::runtime_error("Ошибка открытия файла для записи лога.");
        }

        return log;
    }

    void WriteLine(LOG log, char* c, ...) {
        va_list args;
        va_start(args, c);

        std::string output = c;
        while (*c != '\0') {
            output += va_arg(args, char*);
            c++;
        }

        *log.stream << output << std::endl;

        va_end(args);
    }

    void WriteLine(LOG log, wchar_t* wc, ...) {
        va_list args;
        va_start(args, wc);

        std::wstring output = wc;
        while (*wc != L'\0') {
            output += va_arg(args, wchar_t*);
            wc++;
        }

        // Преобразование wstring в string
        std::string output_str;
        output_str.resize(output.size());
        std::copy(output.begin(), output.end(), output_str.begin());

        *log.stream << output_str << std::endl;

        va_end(args);
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
        *log.stream << "Размер:" << in.size << std::endl;
        *log.stream << "Тип данных:" << in.code << std::endl;
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
