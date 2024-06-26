#define _CRT_SECURE_NO_WARNINGS
#include "Error.h"   //��������� ������
#include "Parm.h"    //��������� ����������
#include "Log.h"   //������ � ����������
#include "In.h"   // ���� ��������� �����
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

    // ������� ��� ��������� ������� LOG
    LOG getlog(const char* logfile) {
        LOG log = { { '\0' }, nullptr };
        strcpy_s(log.logfile, PARM_MAX_SIZE, logfile);

        // ������� ������� ���� ��� ������
        log.stream = new std::ofstream(log.logfile, std::ios::out);

        // �������� ��������� �������� �����
        if (!log.stream->is_open()) {
            // ������������� ���������� ��� ������ �������� �����
            throw std::runtime_error("������ �������� �����");
        }

        return log;
    }

    // ������� � �������� ������������ �����
    void WriteLine(LOG log, char* c, ...) {
        va_list args;
        va_start(args, c);

        std::string result = c;
        const char* next;
        while ((next = va_arg(args, const char*)) != nullptr) {
            // �������� ���� ��������� (� ������ ������ ������ ���������, ��� ��� ������)
            if (next == nullptr || strlen(next) == 0) {
                break;  // ��������� ����, ���� �������� �� �������� �������
            }
            result += next;
        }
        va_end(args);

        *log.stream << result << std::endl;
    }

    void WriteLog(LOG log) {
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "��� ���������:" << std::endl;
        *log.stream << "-------------------------" << std::endl;
    }

    void WriteParm(LOG log, Parm::PARM parm) {
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "������� ���������:" << std::endl;
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "������� ����: " << parm.in << std::endl;
        *log.stream << "�������� ����: " << parm.out << std::endl;
        *log.stream << "���� �����: " << parm.log << std::endl;
        *log.stream << "-------------------------" << std::endl;
    }

    void WriteIn(LOG& log, const In::IN& in) {
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "������� �����:" << std::endl;
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "���������� �������:" << in.size << std::endl;
        *log.stream << "���������� �������:" << in.ignor << std::endl;
        *log.stream << "���������� �����  :" << in.lines << std::endl;
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "���������� �����:" << std::endl;
        *log.stream << in.text << std::endl;
        *log.stream << "-------------------------" << std::endl;
    }

    void WriteError(LOG log, Error::ERROR error) {
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "������:" << std::endl;
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "��� ������:" << error.id << std::endl;
        *log.stream << "���������:" << error.message << std::endl;
        if (error.inext.line != -1 && error.inext.col != -1) {
            *log.stream << "������: " << error.inext.line << ", �������: " << error.inext.col << std::endl;
        }
        *log.stream << "-------------------------" << std::endl;
    }

    void Close(LOG log) {
        if (log.stream != nullptr) {
            log.stream->close();
            // ������� ����� ������ ���� �� ��� ������ � ������� 'new'
            if (log.stream != &std::cout && log.stream != &std::cerr) {
                delete log.stream;
            }
        }
    }

} // namespace Log
