#include <iostream>
#include "Error.h"
#include "Parm.h"
#include "In.h"
#include "Log.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");
    Log::LOG log = Log::INITLOG;
    try {
        Parm::PARM parm = Parm::getparm(argc, argv);
        log = Log::getlog(parm.log); // Предполагаем, что у parm есть поле log

        // Запись в лог
        Log::WriteLine(log, (char*)"Тест:", (char*)" без ошибок \n", "");
        Log::WriteLog(log);
        Log::WriteParm(log, parm);

        // Работа с вводом
        In::IN in = In::getin(parm.in); // Предполагаем, что у parm есть поле in
        Log::WriteIn(log, in);

        Log::Close(log);
    }
    catch (Error::ERROR e) {
        Log::WriteError(log, e);
    }

    return 0;
}
