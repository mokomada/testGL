//=============================================================================
//
//	タイトル	シーンファイル(2DGL)
//	ファイル名	network.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/11/14
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "network.h"
#include "main.h"
#include "game.h"
#include "sceneModel.h"
#include <process.h>
#include <mbstring.h>

#pragma comment(lib, "ws2_32.lib")
unsigned int __stdcall thread1(void *);

//=============================================================================
//	静的メンバ変数
//=============================================================================
bool		CNetwork::m_ifInitialize = false;
CONNECT_PROTOCOL	CNetwork::m_ConnectProtocol = { "127.0.0.1", "239.0.0.1", 20000, 20000 };

SOCKET		CNetwork::m_SockSend;
SOCKET		CNetwork::m_SockRecv;
sockaddr_in	CNetwork::m_AddrServerTCP;
sockaddr_in	CNetwork::m_AddrServerUDP;
sockaddr_in	CNetwork::m_AddrRecv;
char		CNetwork::m_LastMessage[1024] = "NO DATA";
uint		CNetwork::m_thID;
HANDLE		CNetwork::m_hTh;

//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化処理を行う。
//=============================================================================
void CNetwork::Init(void)
{
	WSADATA		wsadata;
	int			sts;
	int			errcode;
	SOCKET		sock;		// ソケット

	// †スレッド起動†
	m_hTh = (HANDLE)_beginthreadex(NULL, 0, ReceveThread, NULL, 0, &m_thID);

	// ＷＩＮＳＯＣＫ初期処理
	sts = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if(sts != 0)
	{
		errcode = WSAGetLastError();
		printf("WSAStartupエラーです %d \n", errcode);
		//return -1;
	}

	// バージョンチェック
	if(LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 2)
	{
		printf("バージョンエラーです\n");
		WSACleanup();
		//return -1;
	}

	// 送信先情報読み取り
	ReadConnetProtocol(&m_ConnectProtocol);
	
	// ソケット生成
	sock = socket(AF_INET, SOCK_STREAM, 0);
	m_SockSend = socket(AF_INET, SOCK_DGRAM, 0);

	// アドレスタイプ設定
	m_AddrServerTCP.sin_family	= AF_INET;
	m_AddrServerUDP.sin_family = AF_INET;

	// ポート番号設定
	m_AddrServerTCP.sin_port	= htons(m_ConnectProtocol.SendPort);
	m_AddrServerUDP.sin_port	= htons(m_ConnectProtocol.SendPort + 1);

	// IPアドレス設定
	m_AddrServerTCP.sin_addr.s_addr	= inet_addr(m_ConnectProtocol.Addr);
	m_AddrServerUDP.sin_addr.s_addr = inet_addr(m_ConnectProtocol.Addr);
	//m_AddrServerTCP.sin_addr.s_addr	= inet_addr("127.0.0.1");
	//m_AddrServerUDP.sin_addr.s_addr	= inet_addr("127.0.0.1");

	// サーバに接続
	connect(sock, (sockaddr*)&m_AddrServerTCP, sizeof(m_AddrServerTCP));

	char data[1024];
	memset(data, 0, sizeof(data));

	// データ受信
	recv(sock, data, sizeof(data), 0);

	// プレイヤー番号セット
	if(strcmp(data, ""))
	{
		int whatplayer = -1;
		sscanf(data, "%d", &whatplayer);
		if(whatplayer >= 0)
		{
			CManager::SetWhatPlayer(whatplayer);
		}
	}

	// ソケット終了
	if(sock) closesocket(sock);

	// 初期化終了告知
	m_ifInitialize = true;
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CNetwork::Uninit(void)
{
	// ソケット終了
	if(m_SockSend)	closesocket(m_SockSend);
	if(m_SockRecv)	closesocket(m_SockRecv);

	// ＷＩＮＳＯＣＫ後処理
	WSACleanup();
}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CNetwork::Update(void)
{
	SendData("hoge");
}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CNetwork::Draw(void)
{
#ifdef _DEBUG
	CDebugProcGL::DebugProc("LASTDATA:%s\n", m_LastMessage);
	CDebugProcGL::DebugProc("TO_SERVER_PORT:TCP->%d, UDP->%d\n", ntohs(m_AddrServerTCP.sin_port), ntohs(m_AddrServerUDP.sin_port));
#endif
}

uint __stdcall CNetwork::ReceveThread(void *p)
{
	// データ受信
	while(1)
	{
		// 初期化が終了している場合のみ処理
		if(m_ifInitialize)
		{
			ReceiveData();
		}
	}

	return 0;
}

//=============================================================================
//	関数名	:SendData
//	引数	:char *format	->	送信データ
//	戻り値	:無し
//	説明	:データの送信を行う。
//=============================================================================
void CNetwork::SendData(char* format, ...)
{
	va_list list;
	char str[256];

	// フォーマット変換
	va_start(list, format);
	vsprintf_s(str, format, list);
	va_end(list);

	// データ送信
	sendto(m_SockSend, str, strlen(str) + 1, 0, (SOCKADDR*)&m_AddrServerUDP, sizeof(m_AddrServerUDP));
}

//=============================================================================
//	関数名	:ReceiveData
//	引数	:char *str	->	送信データ
//	戻り値	:無し
//	説明	:データの送信を行う。
//=============================================================================
void CNetwork::ReceiveData(void)
{
	char		data[1024] = { NULL };	// 受信データ

	
	// データ受信
	recv(m_SockRecv, data, strlen(data), 0);
	
	// データが送信されてきた場合記録
	if(strcmp(data, ""))
	{
		strcpy(m_LastMessage, data);
	}
	
	DATA_TAG dataTag = DT_MAX;

	sscanf(data, "%d, ", &dataTag);
	RemoveDataTag(data);

	int whatPlayer = -1;

	switch(dataTag)
	{
	case DT_PLAYER_NUM:
		break;

	default:
		break;
	}
}

//=============================================================================
//	関数名	:SetPlayerData
//	引数	:char *str	->	受信データ
//	戻り値	:無し
//	説明	:受信したプレイヤーのデータをセットする。
//=============================================================================
void CNetwork::SetPlayerData(char *str)
{/*
	CSceneModel	*player2 = CGame::GetPlayer2();
	VECTOR3		pos = VECTOR3::zero();

	// ゲームモードの時のみ処理
	if(CManager::GetModeState() == MODE_GAME)
	{
		// 受信データからプレイヤー座標を取得
		sscanf(str, "1, %f, %f, %f", &pos.x, &pos.y, &pos.z);

		// 取得した座標をセット
		player2->SetPos(pos);
	}*/
}

//=============================================================================
//	関数名	:RemoveDataTag
//	引数	:char *str	->	受信データ
//	戻り値	:無し
//	説明	:受信したプレイヤーのデータからタグを取り外す。
//=============================================================================
void CNetwork::RemoveDataTag(char *data)
{
	int offset = 0;

	for(; data[offset] != NULL ; offset++)
	{
		// 空白を見つけたら
		if(data[offset] == ' ')
		{
			// 文字列取り出し
			strcpy(data, &data[offset + 1]);

			// NULL追加
			data[strlen(data)] = NULL;

			break;
		}
	}
}

//=============================================================================
//	関数名	:ReadConnetProtocol
//	引数	:CONNECT_PROTOCOL *cp(コネクト情報のポインタ)
//	戻り値	:無し
//	説明	:IPv4通信に必要な情報をファイルから読み取る。
//=============================================================================
void CNetwork::ReadConnetProtocol(CONNECT_PROTOCOL *cp)
{
	FILE	*fp;	// ファイルポインタ


					// ファイルオープン
	if((fp = fopen("./data/connectprotocol.txt", "rb")) == NULL)
	{// ファイルのオープンに失敗した場合
		exit(EXIT_FAILURE);
	}

	// 情報読み取り
	fscanf(fp, "SEND_ADDRESS:%s\nMCAST_ADDRESS:%s\nSEND_PORT:%d\nRECV_PORT:%d\n", cp->Addr, cp->MAddr, &cp->SendPort, &cp->RecvPort);

	// ファイルクローズ
	fclose(fp);
}