#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"

namespace Log {

    // �������� ������������
    struct LOG {
        char logfile[PARM_MAX_SIZE]; // ��� ����� ���������
        std::ofstream* stream;          // �������� ����� ���������
    };

    // ������������� ��������� LOG
    static const LOG INITLOG = {"", nullptr };

    // ������������ ��������� LOG
    LOG getlog(const char* logfile);

    // ������� � �������� ������������ �����
    void WriteLine(LOG log, char* c, ...);

    // ������� � �������� ���������
    void WriteLog(LOG log);

    // ������� � �������� ���������� � ������� ����������
    void WriteParm(LOG log, Parm::PARM parm);

    // ������� � �������� ���������� � ������� ������
    void WriteIn(LOG& log, const In::IN& in);

    // ������� � �������� ���������� �� ������
    void WriteError(LOG log, Error::ERROR error);

    // ������� ����� ���������
    void Close(LOG log);

} // namespace Log