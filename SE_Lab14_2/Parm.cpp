#define _CRT_SECURE_NO_WARNINGS
#include "Parm.h"
#include "Error.h"
#include <cstring>

namespace Parm {
    PARM getparm(int argc, char* argv[]) {
        PARM parm = {}; // ������������� ��������� PARM

        // ���������, ������ �� �������� -in:.
        bool inFound = false;
        for (int i = 1; i < argc; ++i) {
            if (std::strncmp(argv[i], PARM_IN, strlen(PARM_IN)) == 0) {
                inFound = true;
                // ��������� �������� ��������� -in:
                std::strncpy(parm.in, argv[i] + strlen(PARM_IN), PARM_MAX_SIZE);
                break; // ���������� ����� -in:
            }
        }

        if (!inFound) {
            // ��������� ������, ���� -in: �� ������.
            throw ERROR_THROW(100);
        }

        // ���������� �������� �� ��������� ��� -out: � -log:, ���� ��� �� �������.
        std::strcpy(parm.out, parm.in);
        std::strcat(parm.out, PARM_OUT_DEFAULT_EXT);
        std::strcpy(parm.log, parm.in);
        std::strcat(parm.log, PARM_LOG_DEFAULT_EXT);

        // ��������� ���������� ��������� (-out: � -log:)
        for (int i = 1; i < argc; ++i) {
            if (std::strncmp(argv[i], PARM_OUT, strlen(PARM_OUT)) == 0) {
                std::strncpy(parm.out, argv[i] + strlen(PARM_OUT), PARM_MAX_SIZE);
            }
            else if (std::strncmp(argv[i], PARM_LOG, strlen(PARM_LOG)) == 0) {
                std::strncpy(parm.log, argv[i] + strlen(PARM_LOG), PARM_MAX_SIZE);
            }
        }

        // ��������� ����� ������� �������� ���������
        if (std::strlen(parm.in) > PARM_MAX_SIZE ||
            std::strlen(parm.out) > PARM_MAX_SIZE ||
            std::strlen(parm.log) > PARM_MAX_SIZE) {
            throw ERROR_THROW(104);
        }

        return parm;
    }
}
