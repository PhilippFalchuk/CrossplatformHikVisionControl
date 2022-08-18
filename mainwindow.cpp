#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    bool async = false;

    bool isok = NET_DVR_Init();
    if(isok)
    {
        qDebug () << "SDK initialization succsesful";
                 // Устанавливаем время подключения и время переподключения
        NET_DVR_SetConnectTime(2000, 1);
        NET_DVR_SetReconnect(10000, true);
        //NET_DVR_DEVICEINFO_V30 struDeviceInfo;
        //int lUserID = NET_DVR_Login_V30(const_cast<char*>("192.168.0.228"), 8000, const_cast<char*>("admin"), const_cast<char*>("indicom2017"), &struDeviceInfo);

        NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
        NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};

        if (async)
        {
            struLoginInfo.bUseAsynLogin = true;
            //struLoginInfo.cbLoginResult = LoginResultCallBack;
            struLoginInfo.pUser = &struDeviceInfoV40;
        }
        else
        {
            struLoginInfo.bUseAsynLogin = false;
        }
        memcpy(struLoginInfo.sDeviceAddress, const_cast<char*>("192.168.0.228"), NET_DVR_DEV_ADDRESS_MAX_LEN);
        memcpy(struLoginInfo.sUserName, const_cast<char*>("admin"), NAME_LEN);
        memcpy(struLoginInfo.sPassword, const_cast<char*>("indicom2017"), PASSWD_LEN);
        struLoginInfo.wPort = 8000;
        struLoginInfo.byProxyType = 0;


        /*
            10.7.35.88  hik12345 //http->httpsЦШ¶ЁПт (ISAPI ЧФККУ¦)
            10.66.109.3 hik12345 //
            10.7.35.14  hik12345
            10.7.34.163 hik12345

            */
        //struLoginInfo.byUseTransport = 1;
        //struLoginInfo.byRes3[119] = 2;
        struLoginInfo.byHttps = 0;    //0-http 1-https 2-ЧФККУ¦
        struLoginInfo.byLoginMode = 0;  //0-private 1-ISAPI 2-ЧФККУ¦
        struLoginInfo.byVerifyMode = 0;

        int lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);


        if (lUserID < 0)
        {
            qDebug () << "login error:" << NET_DVR_GetLastError ();
            NET_DVR_Cleanup (); // Освободить ресурсы SDK
            return;
        }else{
            qDebug () << "login succsess";
            HWND hWnd = (HWND) ui->graphicsView->winId (); // Получить дескриптор окна
            NET_DVR_PREVIEWINFO struPlayInfo;
                struPlayInfo.hPlayWnd = hWnd; // Дескриптор должен быть установлен на допустимое значение, когда SDK декодируется, и его можно установить в null, когда поток только извлекается, но не декодируется
                struPlayInfo.lChannel = 1; // Предварительный просмотр номера канала
                struPlayInfo.dwStreamType = 0; // 0-основной поток, 1-дополнительный поток, 2-поток 3, 3-поток 4 и т. д.
                struPlayInfo.dwLinkMode = 0; // 0- режим TCP, 1- режим UDP, 2- режим многоадресной рассылки, 3- режим RTP, 4-RTP / RTSP, 5-RSTP / HTTP
                struPlayInfo.bBlocked = 1; // 0- неблокирующий поток выборки, 1- блокирующий поток выборки
            int lRealPlayHandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo, nullptr, nullptr);

            if (lRealPlayHandle < 0)
            {
                qDebug () << "preview error:" << NET_DVR_GetLastError ();
                NET_DVR_Logout(lUserID);
                NET_DVR_Cleanup();
                return;
            }
        }
    }else{
        qDebug () << "Ошибка инициализации SDK:" << NET_DVR_GetLastError ();
    }
}

