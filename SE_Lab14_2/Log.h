#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"

namespace Log {

    // Протокол логгирования
    struct LOG {
        char logfile[PARM_MAX_SIZE]; // Имя файла протокола
        std::ofstream* stream;          // Выходной поток протокола
    };

    // Инициализация структуры LOG
    static const LOG INITLOG = {"", nullptr };

    // Формирование структуры LOG
    LOG getlog(const char* logfile);

    // Вывести в протокол конкатенацию строк
    void WriteLine(LOG log, char* c, ...);

    // Вывести в протокол заголовок
    void WriteLog(LOG log);

    // Вывести в протокол информацию о входных параметрах
    void WriteParm(LOG log, Parm::PARM parm);

    // Вывести в протокол информацию о входном потоке
    void WriteIn(LOG& log, const In::IN& in);

    // Вывести в протокол информацию об ошибке
    void WriteError(LOG log, Error::ERROR error);

    // Закрыть поток протокола
    void Close(LOG log);

} // namespace Log