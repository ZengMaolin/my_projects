#include "ctp_beep.h"
#include <windows.h>
#include <thread>
#include <iostream>

#define qdo 262 
#define qre 294
#define qmi 330     //q前缀为低音，1后缀为高音，s前缀为半音阶 
#define qfa 349
#define qso 392
#define qla 440
#define qsi 494
#define do 523
#define re 578
#define mi 659
#define fa 698
#define so 784
#define la 880
#define si 988
#define do1 1046
#define re1 1175
#define mi1 1318
#define fa1 1480
#define so1 1568
#define la1 1760
#define si1 1976
#define sqdo 277
#define sqre 311
#define sqfa 370
#define sqso 415
#define sqla 466
#define sdo 554
#define sre 622
#define sfa 740
#define sso 831
#define sla 932
#define sdo1 1046
#define sre1 1245
#define sfa1 1480
#define sso1 1661
#define sla1 1865

std::thread* beep_process_thread = nullptr;
QList<int> beep_list;

void ctp_beep_init(void)
{
    beep_process_thread = new std::thread(&ctp_beep_run);
}

void ctp_beep_run(void)
{

    int pai = 400, ban = 200;
    int ting = 128;

    for (;;)
    {
        if (beep_list.size() > 0)
        {
            int type = beep_list.value(0);
            beep_list.removeAt(0);
            switch (type)
            {
            case 0: //登陆成功
                Beep(qfa, ban);
                Beep(fa, pai);
                break;
            case 1: //成功成交
                Beep(si, ban);
                Beep(so1, ban);
                break;
            case 2: //瘸腿
                Beep(si1, 100);
                Beep(si1, 100);
                Beep(si1, 100);
                break;
            case 3: //关闭tab音
                Beep(sso, 100);
                Beep(sla, 150);
                break;
            default:
                Beep(fa, 100);
                Beep(qfa, pai);
                break;
            }
        }
        Sleep(100);
    }
}

void ctp_beep_set(int type)
{
    beep_list.append(type);
}
