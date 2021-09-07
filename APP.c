#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "winfunc.h"


MSG msg;
WNDCLASS winc;
HINSTANCE hInstance;
LPARAM lp;


HWND htmlwindow;   // ���O
HWND check;
HWND radio0;
HWND radio1;
HWND radio2;
HWND radio3;
HWND radio4;
HWND radio5;
HWND combo;
HWND text;
HWND second;
HWND file;
HWND shutdownoption;
HWND textedit;
HWND cmd;
HWND cmdgroup;
HWND dialogGroup;
HWND dialogSettings;
HWND dialogIcon;
HWND msgtit;
HWND msgtex;



// �{�^��ID
#define ID_STORE 2001    
#define ID_SHUTOP 2002
#define ID_SANSHO 2003
#define ID_CMDEXE 2004
#define ID_CHECK 2005
#define ID_MSGCREATE 2006



int checkbox = 0;  // ��ԕۑ��ϐ�
int radioval[6] = {0,0,0,0,0,0};
int list = -1;
int iconList = 0;
int shutsec;
int msgval;

PSTR textval;
PSTR secondval;
PSTR ftextval;
PSTR textall;
PSTR fileval;
PSTR cmdval;
PSTR tex;
PSTR tit;

FILE *fp;



LRESULT CALLBACK WndProc(HWND window , UINT msg , WPARAM wp , LPARAM lp) {
    HDC hdc;
    PAINTSTRUCT ps;


    switch (msg) {
        case WM_CLOSE:
            msgval = MsgBox("�m�F","�I�����܂����H",3,4,1);
            switch (msgval){
                case IDYES:
                    DestroyWindow(htmlwindow) ;
                    PostQuitMessage(0);
                    return 0;
            }
		    return 0;    

        case WM_CTLCOLORSTATIC:
            SetBkMode((HDC)wp,TRANSPARENT); //�w�i�𓧖��ɂ����Y��ɂ���
            if(shutdownoption ==(HWND)lp){
                SetTextColor((HDC)wp,RGB(255,0,0));//�e�L�X�g
            }
            return (LRESULT)CreateSolidBrush( RGB( 234, 234, 234 ) ); //�w�i�F


        case WM_PAINT:
            hdc = BeginPaint(htmlwindow , &ps);

            /* �e�L�X�g���� */
            SetBkColor(hdc , RGB(234 , 234 , 234));
            SetTextColor(hdc , RGB(0 , 0 , 0));
            TextOut(hdc , 75 , 80 , TEXT("�b") , lstrlen(TEXT("�b")));

            SetBkColor(hdc , RGB(0 , 0 , 0));
            SetTextColor(hdc , RGB(0 , 255 , 0));
            
            TextOut(hdc , 280 , 45 , TEXT("User@windows>~$          ") ,lstrlen(TEXT("User@windows>~$          ")));
            //�e�L�X�g�ǉ�
            
            EndPaint(htmlwindow , &ps);
            /* �e�L�X�g�����I�� */
            break;

        case WM_COMMAND:{
            int wmId = LOWORD(wp);
            // �I�����ꂽ���𒲂ׂ�
            switch (wmId){
                case ID_SHUTOP:
                    list = SendMessage(combo, CB_GETCURSEL, 0, 0);
                    secondval = malloc(32768);
                    GetWindowText(second , secondval , 32768);
                    shutsec = atoi(secondval);
                    free(secondval);
                    switch(list){
                        case 0:
                            DestroyWindow(htmlwindow) ;
                            PostQuitMessage(0);
                            shutop("logoff",shutsec);
                            return 0;
                        case 1:
                            DestroyWindow(htmlwindow) ;
                            PostQuitMessage(0);
                            shutop("shutdown",shutsec);
                            return 0;
                        case 2:
                            DestroyWindow(htmlwindow) ;
                            PostQuitMessage(0);
                            shutop("reboot",shutsec);
                            return 0;
                    }
                    break;

                case ID_STORE:
                    msgval = MsgBox("�m�F","���e��ۑ����܂����H",3,4,1);
                    switch (msgval){
                        case IDYES:
                            /*�������m��*/
                            textval = malloc(32768);
                            fileval = malloc(32768);

                            GetWindowText(text , textval , 32768);
                            GetWindowText(file , fileval , 32768);
                            fp = fopen(fileval,"r");
                            
                            /*���݂���t�@�C�����m�F*/
                            if(fp != NULL){
                                fclose(fp);
                                fp = fopen(fileval,"w");
                                fprintf(fp, "%s", textval);
                                
                            }
                            else{
                                msgval = MsgBox("����","�t�@�C��������܂���\n\n�V�K�t�@�C�����쐬���ĕۑ����܂����H",3,2,1);
                                switch (msgval){
                                    case IDYES:
                                        fclose(fp);
                                        fp = fopen(fileval,"w");
                                        fprintf(fp, "%s", textval);
                                }
                            }

                            fclose(fp);

                            /*���������*/
                            free(textval);
                            free(fileval);
                    }
                    break;
                
                case ID_SANSHO:
                    /*�������m��*/
                    ftextval = malloc(32768);
                    textall = malloc(32768);
                    fileval = malloc(32768);

                    GetWindowText(file , fileval , 32768);

                    /*���݂���t�@�C�����m�F*/
                    fp = fopen(fileval,"r");
                    if(fp != NULL){

                        fgets(ftextval,256,fp);
                        strcpy(textall, ftextval);

                        while(fgets(ftextval , 256 , fp) != NULL ) {
                            sprintf(textall, "%s%s" ,textall,ftextval);
                        
                        }
                    
                        SetWindowText(text , textall);
                    }
                    else{
                        printf("\a");
                    }
                    
                    fclose(fp);

                    /*���������*/
                    free(textall);
                    free(ftextval);
                    free(fileval);

                    break;

                case ID_CMDEXE:
                    /*�������m��*/
                    cmdval = malloc(32768);
                    GetWindowText(cmd , cmdval , 32768);

                    /* ���s */
                    system(cmdval);

                    /*���������*/
                    free(cmdval);
                    break;

                case ID_MSGCREATE:

                    tex = malloc(32768);
                    tit = malloc(32768);

                    GetWindowText(msgtex , tex , 32768);
                    GetWindowText(msgtit , tit , 32768);

                    radioval[0] = SendMessage(radio0, BM_GETCHECK, 0, 0);
                    radioval[1] = SendMessage(radio1, BM_GETCHECK, 0, 0);
                    radioval[2] = SendMessage(radio2, BM_GETCHECK, 0, 0);
                    radioval[3] = SendMessage(radio3, BM_GETCHECK, 0, 0);
                    radioval[4] = SendMessage(radio4, BM_GETCHECK, 0, 0);
                    radioval[5] = SendMessage(radio5, BM_GETCHECK, 0, 0);

                    checkbox = SendMessage(check, BM_GETCHECK, 0, 0);
                    iconList = SendMessage(dialogIcon, CB_GETCURSEL, 0, 0);


                    int val1 , val2 ,val3;
                    if(radioval[0] == 1){
                        val1 = MB_OK;
                    }
                    if(radioval[1] == 1){
                        val1 = MB_OKCANCEL;
                    }
                    else if(radioval[2] == 1){
                        val1 = MB_YESNO;
                    }
                    else if(radioval[3] == 1){
                        val1 = MB_YESNOCANCEL;
                    }
                    else if(radioval[4] == 1){
                        val1 = MB_ABORTRETRYIGNORE;
                    }
                    else if(radioval[5] == 1){
                        val1 = MB_RETRYCANCEL;
                    }

                    switch(iconList){
                        case 1:
                            val2 = MB_ICONWARNING;
                            break;
                        case 2:
                            val2 = MB_ICONINFORMATION;
                            break;
                        case 3:
                            val2 = MB_ICONQUESTION;
                            break;
                        case 4:
                            val2 = MB_ICONERROR;
                            break;
                        default:
                            val2 = 0;
                            break;

                    }

                    switch(checkbox){
                        case 1:
                            val3 = MB_HELP;
                            break;
                        default:
                            val3 = 0;
                            break;
                    }

                    int forms = val1 | val2 | val3;
                    MessageBox(NULL , tex , tit , forms ); 
                    break;
            }
        }
    }
    return DefWindowProc(window , msg , wp , lp);
}



int main(){
    winc.style                = CS_HREDRAW | CS_VREDRAW;
    winc.lpfnWndProc          = WndProc;
    winc.cbClsExtra           = winc.cbWndExtra = 0;
    winc.hInstance            = hInstance;
    winc.hIcon                = LoadIcon(NULL , IDI_APPLICATION);
    winc.hCursor              = LoadCursor(NULL , IDC_ARROW);
    winc.hbrBackground        = (HBRUSH)CreateSolidBrush( RGB( 234, 234, 234 ) );
    winc.lpszMenuName         = NULL;
    winc.lpszClassName        = "WINDOW";


    if (!RegisterClass(&winc)){
        return -1;
    }

    /* Window���� */
    htmlwindow = CreateWindow(
                "WINDOW",
                TEXT("�A�v��") ,
                (WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX) | WS_VISIBLE ,
                100 , 10 ,970 , 590 ,
                NULL , NULL , hInstance , NULL
            );

    


    /* �O���[�v�{�b�N�X���� */
    shutdownoption = CreateWindow(
        "BUTTON" , "�d���I�v�V����" ,
        WS_CHILD | WS_VISIBLE | BS_GROUPBOX ,
        20 , 20 , 240 , 120 ,
        htmlwindow , NULL , hInstance , NULL
    );


    /* ���X�g�{�b�N�X */
    combo = CreateWindow(
                "COMBOBOX",
                NULL, 
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST , 
                40 , 45 , 200 , 200 , 
                htmlwindow , (HMENU)1 ,hInstance, NULL
            );
    // ���X�g�{�b�N�X�̑I����
    SendMessage(combo , CB_ADDSTRING , 0 , (LPARAM)TEXT("���O�I�t"));
    SendMessage(combo , CB_ADDSTRING , 0 , (LPARAM)TEXT("�V���b�g�_�E��"));
    SendMessage(combo , CB_ADDSTRING , 0 , (LPARAM)TEXT("�ċN��"));

    
    /* �e�L�X�g�G���A���� */
    second = CreateWindow(
            "EDIT",
            NULL,
            WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_RIGHT | ES_NUMBER,
            40,80,30,20,
            htmlwindow,(HMENU)1,hInstance,NULL
        );

    /* �e�L�X�g�G���A�ɕ����\�� */
    SetWindowText(second, TEXT("30"));


    /* �{�^������ */
    CreateWindow(
        "BUTTON",
        TEXT("����"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
        140 , 100 , 100 , 30 ,
        htmlwindow , (HMENU)ID_SHUTOP , hInstance , NULL
    );





    /* �O���[�v�{�b�N�X���� */
    textedit = CreateWindow(
        "BUTTON" , "�e�L�X�g�ҏW" ,
        WS_CHILD | WS_VISIBLE | BS_GROUPBOX ,
        20 , 160 , 500 , 380 ,
        htmlwindow , NULL , hInstance , NULL
    );


    /* �e�L�X�g�G���A���� */
    file = CreateWindow(
            "EDIT",
            NULL,
            WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_LEFT | ES_AUTOHSCROLL | WS_HSCROLL,
            40,185,460,40,
            htmlwindow,(HMENU)1,hInstance,NULL
        );

    /* �e�L�X�g�G���A�ɕ����\�� */
    SetWindowText(file, TEXT("D:/�t�@�C���̐�΃p�X�����"));


    /* �{�^������ */
    CreateWindow(
        "BUTTON",
        TEXT("�Q��"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
        370 , 230 , 100 , 30 ,
        htmlwindow , (HMENU)ID_SANSHO , hInstance , NULL
    );


    /* �e�L�X�g�G���A���� */
    text = CreateWindow(
            "EDIT",
            NULL,
            WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_LEFT | ES_AUTOVSCROLL | WS_VSCROLL,
            40,280,400,200,
            htmlwindow,(HMENU)1,hInstance,NULL
        );

    /* �e�L�X�g�G���A�ɕ����\�� */
    SetWindowText(text, TEXT("�e�L�X�g"));

    
    /* �{�^������ */
    CreateWindow(
        "BUTTON",
        TEXT("�ۑ�"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
        370 , 490 , 100 , 30 ,
        htmlwindow , (HMENU)ID_STORE , hInstance , NULL
    );






    /* �O���[�v�{�b�N�X���� */
    cmdgroup = CreateWindow(
        "BUTTON" , "�R�}���h�v�����v�g" ,
        WS_CHILD | WS_VISIBLE | BS_GROUPBOX ,
        270 , 20 , 670 , 120 ,
        htmlwindow , NULL , hInstance , NULL
    );

    /* �e�L�X�g�G���A���� */
    cmd = CreateWindow(
            "EDIT",
            NULL,
            WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_LEFT | ES_AUTOHSCROLL | WS_HSCROLL,
            410,45,500,40,
            htmlwindow,(HMENU)1,hInstance,NULL
        );

    /* �{�^������ */
    CreateWindow(
        "BUTTON",
        TEXT("���s"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
        720 , 95 , 100 , 30 ,
        htmlwindow , (HMENU)ID_CMDEXE , hInstance , NULL
    );






    /* �O���[�v�{�b�N�X���� */
    dialogGroup = CreateWindow(
        "BUTTON" , "���b�Z�[�W�{�b�N�X�쐬" ,
        WS_CHILD | WS_VISIBLE | BS_GROUPBOX ,
        535 , 160 , 405 , 380 ,
        htmlwindow , NULL , hInstance , NULL
    );


    /* �O���[�v�{�b�N�X���� */
    dialogSettings = CreateWindow(
        "BUTTON" , "�ݒ�" ,
        WS_CHILD | WS_VISIBLE | BS_GROUPBOX  ,
        545 , 183 , 390 , 145 ,
        htmlwindow , NULL , hInstance , NULL
    );

    /* ���X�g�{�b�N�X */
    dialogIcon = CreateWindow(
                "COMBOBOX",
                NULL, 
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST , 
                560 , 210 , 130 , 130 , 
                htmlwindow , (HMENU)1 ,hInstance, NULL
            );
    // ���X�g�{�b�N�X�̑I����
    SendMessage(dialogIcon , CB_ADDSTRING , 0 , (LPARAM)TEXT("�A�C�R���Ȃ�"));
    SendMessage(dialogIcon , CB_ADDSTRING , 0 , (LPARAM)TEXT("���ӃA�C�R��"));
    SendMessage(dialogIcon , CB_ADDSTRING , 0 , (LPARAM)TEXT("���A�C�R��"));
    SendMessage(dialogIcon , CB_ADDSTRING , 0 , (LPARAM)TEXT("����A�C�R��"));
    SendMessage(dialogIcon , CB_ADDSTRING , 0 , (LPARAM)TEXT("�x���A�C�R��"));


    /* ���W�I�{�^������ */
    radio0 = CreateWindow(
            "BUTTON",
            TEXT("[OK]") ,
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
            560 , 235 , 160 , 30 ,
            htmlwindow , NULL ,hInstance , NULL
        );

    /* ���W�I�{�^������ */
    radio1 = CreateWindow(
            "BUTTON",
            TEXT("[OK][�L�����Z��]") ,
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON ,
            560 , 265 , 160 , 30 ,
            htmlwindow , NULL ,hInstance , NULL
        );

    /* ���W�I�{�^������ */
    radio2 = CreateWindow(
            "BUTTON",
            TEXT("[�͂�][������]") ,
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON ,
            560 , 295 , 160 , 30 ,
            htmlwindow , NULL ,hInstance , NULL
        );


    /* ���W�I�{�^������ */
    radio3 = CreateWindow(
            "BUTTON",
            TEXT("[�͂�][������][�L�����Z��]") ,
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON ,
            720 , 205 , 210 , 30 ,
            htmlwindow , NULL ,hInstance , NULL
        );

    /* ���W�I�{�^������ */
    radio4 = CreateWindow(
            "BUTTON",
            TEXT("[���~][�Ď��s][����]") ,
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON ,
            720 , 235 , 200 , 30 ,
            htmlwindow , NULL ,hInstance , NULL
        );

    /* ���W�I�{�^������ */
    radio5 = CreateWindow(
            "BUTTON",
            TEXT("[�Ď��s][�L�����Z��]") ,
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON ,
            720 , 265 , 200 , 30 ,
            htmlwindow , NULL ,hInstance , NULL
        );

    /* �`�F�b�N�{�b�N�X���� */
    check = CreateWindow(
            "BUTTON" ,
            TEXT("[�w���v]") ,
            WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX ,
            720 , 295 , 200 , 30 ,
            htmlwindow , (HMENU)ID_CHECK , hInstance , NULL
        );





    /* �e�L�X�g�G���A���� */
    msgtit = CreateWindow(
            "EDIT",
            NULL,
            WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_LEFT | ES_AUTOHSCROLL | WS_HSCROLL,
            550,335,350,40,
            htmlwindow,(HMENU)1,hInstance,NULL
        );
    /* �e�L�X�g�G���A�ɕ����\�� */
    SetWindowText(msgtit, TEXT("�^�C�g������"));
        
    /* �e�L�X�g�G���A���� */
    msgtex = CreateWindow(
            "EDIT",
            NULL,
            WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_LEFT | ES_AUTOVSCROLL | WS_VSCROLL,
            550,385,270,140,
            htmlwindow,(HMENU)1,hInstance,NULL
        );
    /* �e�L�X�g�G���A�ɕ����\�� */
    SetWindowText(msgtex, TEXT("�e�L�X�g����"));

    /* �{�^������ */
    CreateWindow(
        "BUTTON",
        TEXT("�쐬"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
        830 , 495 , 100 , 30 ,
        htmlwindow , (HMENU)ID_MSGCREATE , hInstance , NULL
    );


    /*�R�}���h�v�����v�g�̏����ݒ�*/
    system("title �A�v��");
    system("color 0A");

    while(GetMessage(&msg , NULL , 0 , 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }


    // ������̏���
    system("cls");
    printf("�I�����Ă��܂�\n");
    free(tex);
    free(tit);
    sleep(1);

    UnregisterClass("WINDOW",hInstance);
    return msg.wParam;
}