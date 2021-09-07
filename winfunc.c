#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>

// �A�N�Z�X���̒萔
#define OPEN_PROCESS_TOKEN      (TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY)

// �v���Z�X�n���h�������������L��/����
BOOL ProcessPrivilegeName( HANDLE hProcess, LPCTSTR lpPrivilegeName, BOOL bEnable ){
    BOOL          bSuccess = FALSE; // �߂�l(����/���s)
    HANDLE              hToken;     // �A�N�Z�X�g�[�N���̃n���h��
    LUID                Luid;       // LUID(���[�J���E���j�[�NID)
    DWORD               dwSize;     // �����g�[�N���e��(�ύX�O�̓���)
    TOKEN_PRIVILEGES    OldPriv;    // �����g�[�N�����(�ύX�O�̓���)
    TOKEN_PRIVILEGES    NewPriv;    // �����g�[�N�����(�V��������)
    
    // �A�N�Z�X�g�[�N���̃n���h�����擾
    if ( OpenProcessToken(hProcess,OPEN_PROCESS_TOKEN,&hToken) ){
        if ( LookupPrivilegeValue(NULL,lpPrivilegeName,&Luid) ){    // ��������LUID���擾
            NewPriv.PrivilegeCount              = 1;                // ������
            NewPriv.Privileges[0].Luid          = Luid;             // ���ʎq
            NewPriv.Privileges[0].Attributes    = bEnable ? SE_PRIVILEGE_ENABLED : 0;
            
            // �����g�[�N����Ԃ̗L��/����
            if ( AdjustTokenPrivileges(hToken,FALSE,&NewPriv,sizeof(TOKEN_PRIVILEGES),&OldPriv,&dwSize) ){
                if ( GetLastError() == ERROR_SUCCESS ){
                    bSuccess = TRUE;
                }
            }
        }
        CloseHandle( hToken );
    }
    return bSuccess;
}

int shutop(char op[256],int second){
    int uFlag;
    if (strcmp(op,"logoff")==0){
        uFlag = EWX_LOGOFF;
    }
    else if(strcmp(op,"shutdown")==0){
        uFlag = EWX_SHUTDOWN;
    }
    else if(strcmp(op,"reboot")==0){
        uFlag = EWX_REBOOT;
    }
    sleep(second);

    // ���O�I�t/�V���b�g�_�E��/�ċN�������s����
    ProcessPrivilegeName( GetCurrentProcess(), SE_SHUTDOWN_NAME, TRUE );
    ExitWindowsEx( uFlag, 0 );
    return 0;
}

int MsgBox(char tit[256],char tex[256],int button ,int icon,int help){
    int ans;
    int val1 , val2 ,val3;

    switch(button){
        case 2:
            val1 = MB_OKCANCEL;
            break;
        case 3:
            val1 = MB_YESNO;        
            break;
        case 4:
            val1 = MB_YESNOCANCEL;
            break;
        case 5:
            val1 = MB_ABORTRETRYIGNORE;
            break;
        case 6:
            val1 = MB_RETRYCANCEL;
            break;
        default:
            val1 = MB_OK;
            break;

    }
    switch(icon){
        case 2:
            val2 = MB_ICONWARNING;
            break;
        case 3:
            val2 = MB_ICONINFORMATION;
            break;
        case 4:
            val2 = MB_ICONQUESTION;
            break;
        case 5:
            val2 = MB_ICONERROR;
            break;
        default:
            break;

    }
    switch(help){
        case 2:
            val3 = MB_HELP;
            break;
        default:
            break;

    }
    int forms = val1 | val2 | val3;
    ans = MessageBox(NULL , tex , tit , forms ); 
    return ans;
}

int easyMsgBox(){
    int ans;
    char tit[256] ,tex[256];
    int button , icon, help, defo;
    printf("�^�C�g�������\n");
    scanf("%s" , &tit);
    printf("�e�L�X�g�����\n");
    scanf("%s" , &tex);
    printf("�{�^���̎��\n");
    printf("1.[OK]\n2.[OK][�L�����Z��]\n3.[�͂�][������]\n4.[�͂�][������][�L�����Z��]\n5.[���~][�Ď��s][����]\n6.[�Ď��s][�L�����Z��]\n");
    scanf("%d" , &button);
    printf("�A�C�R��\n");
    printf("1.�Ȃ�\n2.����\n3.���\n4.����\n5.�x��\n");
    scanf("%d" , &icon);    
    printf("[�w���v]\n");
    printf("1.�Ȃ�\n2.����\n");
    scanf("%d" , &help);    
    ans = MsgBox(tit,tex,button,icon,help);
    return ans;
}