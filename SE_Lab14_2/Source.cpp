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
        log = Log::getlog(parm.log); // ������������, ��� � parm ���� ���� log

        // ������ � ���
        Log::WriteLine(log, (char*)"����:", (char*)" ��� ������ \n", "");
        Log::WriteLog(log);
        Log::WriteParm(log, parm);

        // ������ � ������
        In::IN in = In::getin(parm.in); // ������������, ��� � parm ���� ���� in
        Log::WriteIn(log, in);

        Log::Close(log);
    }
    catch (Error::ERROR e) {
        Log::WriteError(log, e);
    }

    return 0;
}
