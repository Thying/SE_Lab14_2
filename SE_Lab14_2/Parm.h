#pragma once

#define PARM_IN "-in:"          // ���� ��� ����� ��������� ���� 
#define PARM_OUT "-out:"        // ���� ��� ����� ���������� ���� 
#define PARM_LOG "-log:"        // ���� ��� ����� ������� 
#define PARM_MAX_SIZE 300        // ������������ ����� ������ ��������� 
#define PARM_OUT_DEFAULT_EXT ".out"  // ���������� ����� ���������� ���� �� ��������� 
#define PARM_LOG_DEFAULT_EXT ".log"  // ���������� ����� ��������� �� ���������


namespace Parm {
    // ��������� ������� ����������

    struct PARM {
        // ������� ���������
        char in[PARM_MAX_SIZE];    // -in: ��� ����� ��������� ����
        char out[PARM_MAX_SIZE];    // -out: ��� ����� ���������� ����
        char log[PARM_MAX_SIZE];    // -log: ��� ����� ���������
    };

    PARM getparm(int argc, char* argv[]);
    //int _tmain(int argc, _TCHAR* argv[])
    // ����������� struct PARM �� ������ ���������� ������� main
}