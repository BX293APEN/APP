#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>

// アクセス権の定数
#define OPEN_PROCESS_TOKEN      (TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY)

// プロセスハンドルから特権名を有効/無効
BOOL ProcessPrivilegeName( HANDLE hProcess, LPCTSTR lpPrivilegeName, BOOL bEnable ){
    BOOL          bSuccess = FALSE; // 戻り値(成功/失敗)
    HANDLE              hToken;     // アクセストークンのハンドル
    LUID                Luid;       // LUID(ローカル・ユニークID)
    DWORD               dwSize;     // 特権トークン容量(変更前の特権)
    TOKEN_PRIVILEGES    OldPriv;    // 特権トークン情報(変更前の特権)
    TOKEN_PRIVILEGES    NewPriv;    // 特権トークン情報(新しい特権)
    
    // アクセストークンのハンドルを取得
    if ( OpenProcessToken(hProcess,OPEN_PROCESS_TOKEN,&hToken) ){
        if ( LookupPrivilegeValue(NULL,lpPrivilegeName,&Luid) ){    // 特権名のLUIDを取得
            NewPriv.PrivilegeCount              = 1;                // 特権数
            NewPriv.Privileges[0].Luid          = Luid;             // 識別子
            NewPriv.Privileges[0].Attributes    = bEnable ? SE_PRIVILEGE_ENABLED : 0;
            
            // 特権トークン状態の有効/無効
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

    // ログオフ/シャットダウン/再起動を実行する
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
    printf("タイトルを入力\n");
    scanf("%s" , &tit);
    printf("テキストを入力\n");
    scanf("%s" , &tex);
    printf("ボタンの種類\n");
    printf("1.[OK]\n2.[OK][キャンセル]\n3.[はい][いいえ]\n4.[はい][いいえ][キャンセル]\n5.[中止][再試行][無視]\n6.[再試行][キャンセル]\n");
    scanf("%d" , &button);
    printf("アイコン\n");
    printf("1.なし\n2.注意\n3.情報\n4.質問\n5.警告\n");
    scanf("%d" , &icon);    
    printf("[ヘルプ]\n");
    printf("1.なし\n2.あり\n");
    scanf("%d" , &help);    
    ans = MsgBox(tit,tex,button,icon,help);
    return ans;
}