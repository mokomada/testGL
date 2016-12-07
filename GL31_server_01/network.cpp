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
#include "debugProcGL.h"
#include "game.h"
#include "sceneModel.h"
#include <process.h>
#include <mbstring.h>

#pragma comment(lib, "ws2_32.lib")

//=============================================================================
//	静的メンバ変数
//=============================================================================
CONNECT_PROTOCOL CNetwork::m_ConnectProtocol = { "127.0.0.1", "239.0.0.1", 20000, 20000 };

int			CNetwork::m_PlayerNum = 0;
WSADATA		CNetwork::m_Wsadata;
int			CNetwork::m_Sts;
int			CNetwork::m_Errcode;
SOCKET		CNetwork::m_SockTCPRecv;
SOCKET		CNetwork::m_SockUDPSend;
SOCKET		CNetwork::m_SockUDPRecv;
sockaddr_in	CNetwork::m_AddrUDPSend;
sockaddr_in	CNetwork::m_AddrUDPRecv;
sockaddr_in	CNetwork::m_AddrClient[4];
char		CNetwork::m_LastMessage[1024] = "NO DATA";
uint		CNetwork::m_thID;
HANDLE		CNetwork::m_hTh;
bool		CNetwork::m_ifInitialize = false;
int			CNetwork::m_ifBindSuccess[2] = { -1, -1 };

//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化処理を行う。
//=============================================================================
void CNetwork::Init(void)
{
	// †スレッド起動†
	m_hTh = (HANDLE)_beginthreadex(NULL, 0, ReceveThread, NULL, 0, &m_thID);

	WSADATA		wsadata;	// winsockデータ
	int			sts;		// スタートアップ情報
	int			errcode;	// エラーコード
	sockaddr_in	addr;		// アドレス


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

	// 接続先情報読み込み
	ReadConnetProtocol(&m_ConnectProtocol);

	// ソケット生成
	m_SockTCPRecv = socket(AF_INET, SOCK_STREAM, 0);
	//m_SockUDPSend = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	m_SockUDPRecv = socket(AF_INET, SOCK_DGRAM, 0);

	// アドレスタイプ設定
	addr.sin_family				= AF_INET;
	//m_AddrUDPSend.sin_family	= AF_INET;
	m_AddrUDPRecv.sin_family	= AF_INET;

	// ポート番号設定
	addr.sin_port			= htons(m_ConnectProtocol.RecvPort);
	m_AddrUDPSend.sin_port	= htons(m_ConnectProtocol.SendPort);
	m_AddrUDPRecv.sin_port	= htons(m_ConnectProtocol.SendPort + 1);

	// IPアドレス設定
	addr.sin_addr.s_addr			= INADDR_ANY;
	m_AddrUDPSend.sin_addr.s_addr	= inet_addr(m_ConnectProtocol.MAddr);
	m_AddrUDPRecv.sin_addr.s_addr	= INADDR_ANY;
	
	// ブロードキャスト許可
	int valueTCP = 1;
	setsockopt(m_SockUDPSend, SOL_SOCKET, SO_BROADCAST, (char *)&valueTCP, sizeof(valueTCP));
	//int valueUDP = 1;
	//setsockopt(m_SockUDPRecv, SOL_SOCKET, SO_BROADCAST, (char *)&valueUDP, sizeof(valueUDP));

	// バインド
	m_ifBindSuccess[0] = bind(m_SockTCPRecv, (sockaddr*)&addr, sizeof(addr));
	m_ifBindSuccess[1] = bind(m_SockUDPRecv, (sockaddr*)&m_AddrUDPRecv, sizeof(m_AddrUDPRecv));

	// クライアントからの接続待ち
	listen(m_SockTCPRecv, 5);

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
	if(m_SockTCPRecv) closesocket(m_SockTCPRecv);
	if(m_SockUDPSend) closesocket(m_SockUDPSend);
	if(m_SockUDPRecv) closesocket(m_SockUDPRecv);

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
	
}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CNetwork::Draw(void)
{
	CDebugProcGL::DebugProc("PLAYER_NUM:%d\n", m_PlayerNum);
	CDebugProcGL::DebugProc("LASTDATA:%s\n", m_LastMessage);
	CDebugProcGL::DebugProc("BIND:%d, %d\n", m_ifBindSuccess[0], m_ifBindSuccess[1]);
	CDebugProcGL::DebugProc("UDP_PORT:SEND->%d, RECV->%d\n", ntohs(m_AddrUDPSend.sin_port), ntohs(m_AddrUDPRecv.sin_port));
}

uint __stdcall CNetwork::ReceveThread(void *p)
{
	// クライアントと接続
	SOCKET sock;
	sockaddr_in client;
	int len;

	//while(m_PlayerNum < 4)
	while(m_PlayerNum < 4)
	{
		if(m_ifInitialize)
		{
			len = sizeof(client);
			sock = accept(m_SockTCPRecv, (sockaddr*)&client, &len);

			// 同じ接続先の場合カウントしない
			int i;
			for(i = 0 ; i < 4 ; i++)
			{
				if(m_AddrClient[i].sin_addr.s_addr == client.sin_addr.s_addr)
				{
					break;
				}
			}

			
			char buff[1024] = { NULL };

			if(i < 4)
			{// 一度接続されたクライアントの場合、そのプレイヤー番号を返信する

				// 重複しているプレイヤー番号をセット
				sprintf(buff, "%d", i);

				// プレイヤー番号を送信
				send(sock, buff, strlen(buff), 0);
			}
			else
			{// そうでない場合、現在のプレイヤー番号を返信する

				// クライアント情報の登録
				m_AddrClient[m_PlayerNum] = client;

				// 現在のプレイヤー番号をセット
				sprintf(buff, "%d", m_PlayerNum);

				// プレイヤー番号を送信
				send(sock, buff, strlen(buff), 0);

				// プレイヤー数を増やす
				m_PlayerNum++;
			}

			// ソケット終了
			closesocket(sock);

			// データ受信
			ReceiveData();
		}
	}

	// 初期化が終了している場合のみ処理
	while(1)
	{
		if(m_ifInitialize)
		{
			// データ受信
			while(1)
			{
				ReceiveData();
			}
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
	sendto(m_SockUDPSend, str, strlen(str) + 1, 0, (SOCKADDR*)&m_AddrUDPSend, sizeof(m_AddrUDPSend));
}

//=============================================================================
//	関数名	:ReceiveData
//	引数	:char *str	->	送信データ
//	戻り値	:無し
//	説明	:データの送信を行う。
//=============================================================================
void CNetwork::ReceiveData(void)
{
	char data[1024] = { NULL };	// 受信データ

	// データ受信
	recv(m_SockUDPRecv, data, strlen(data), 0);

	// データが送信されてきた場合記録
	if(strcmp(data, ""))
	{
		strcpy(m_LastMessage, data);
	}
	
	DATA_TAG dataTag = DT_MAX;

	sscanf(data, "%d, ", &dataTag);
	RemoveDataTag(data);

	switch(dataTag)
	{
	case 0:	// システムメッセージ
		// ゲームエントリー確認
		if(!strcmp(data, "entry"))
		{
			char str[1024];

			sprintf(str, "%d %d", DT_PLAYER_NUM, m_PlayerNum);
			m_PlayerNum++;

			// データ送信
			//sendto(m_SockSend, str, strlen(str) + 1, 0, (SOCKADDR*)&m_AddrClient, sizeof(m_AddrClient));
		}
		break;

	case 1:
		SetPlayerData(data);
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