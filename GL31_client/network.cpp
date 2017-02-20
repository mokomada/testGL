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
#include "player.h"
#include <process.h>
#include <mbstring.h>

#pragma comment(lib, "ws2_32.lib")

//=============================================================================
//	静的メンバ変数
//============================================================================
//uint __stdcall CNetwork::ReceveThread(void *);
CONNECT_PROTOCOL	CNetwork::m_ConnectProtocol;

bool		CNetwork::m_ifInitialize	= false;
bool		CNetwork::m_ifMatched		= false;

SOCKET		CNetwork::m_SockSend;
SOCKET		CNetwork::m_SockRecv;
sockaddr_in	CNetwork::m_AddrServer;
char		CNetwork::m_ReceiveData[65535] = "NO DATA";
char		CNetwork::m_LastMessage[65535] = "NO DATA";
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
	sockaddr_in	addr;

	m_ifInitialize	= false;
	m_ifMatched		= false;

	// †スレッド起動†
	m_hTh = (HANDLE)_beginthreadex(NULL, 0, ReceveThread, NULL, 0, &m_thID);

	// ＷＩＮＳＯＣＫ初期処理
	sts = WSAStartup(MAKEWORD(2, 0), &wsadata);
	if(sts != 0)
	{
		errcode = WSAGetLastError();
		printf("WSAStartupエラーです %d \n", errcode);
		return;
	}

	// バージョンチェック
	if(LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 0)
	{
		printf("バージョンエラーです\n");
		WSACleanup();
		return;
	}

	// 送信先情報読み取り
	ReadConnetProtocol(&m_ConnectProtocol);
	
	// ソケット生成
	if(1)
	{
		m_SockSend = socket(AF_INET, SOCK_STREAM, 0);
		m_SockRecv = socket(AF_INET, SOCK_STREAM, 0);
	}
	else
	{
		m_SockSend = socket(AF_INET, SOCK_DGRAM, 0);
		m_SockRecv = socket(AF_INET, SOCK_DGRAM, 0);
	}
	

	// アドレスタイプ設定
	addr.sin_family = AF_INET;
	m_AddrServer.sin_family = AF_INET;

	// ポート番号設定
	addr.sin_port = htons(20010);
	m_AddrServer.sin_port = htons(20010);

	// IPアドレス設定
	addr.sin_addr.s_addr = INADDR_ANY;
	//m_AddrServer.sin_addr.s_addr = inet_addr("172.29.33.59");
	m_AddrServer.sin_addr.s_addr = inet_addr("172.29.33.52");

	// バインド
	bind(m_SockRecv, (sockaddr*)&addr, sizeof(addr));
	
	// マッチング登録
	connect(m_SockSend, (sockaddr*)&m_AddrServer, sizeof(m_AddrServer));
	//sendto(m_SockSend, "0, entry", strlen("0, entry") + 1, 0, (sockaddr*)&m_AddrServer, sizeof(m_AddrServer));
	
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
#ifdef _DEBUG
	CDebugProcGL::DebugProc("LASTDATA:%s\n", m_LastMessage);
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
	char str[65535];

	// フォーマット変換
	va_start(list, format);
	vsprintf_s(str, format, list);
	va_end(list);

	// データ送信
	m_AddrServer.sin_port = htons(20010);
	send(m_SockSend, str, strlen(str) + 1, 0);
	//sendto(m_SockSend, str, strlen(str) + 1, 0, (SOCKADDR*)&m_AddrServer, sizeof(m_AddrServer));
}

//=============================================================================
//	関数名	:ReceiveData
//	引数	:char *str	->	送信データ
//	戻り値	:無し
//	説明	:データの送信を行う。
//=============================================================================
void CNetwork::ReceiveData(void)
{
	// サーバアドレスのサイズセット
	int len = sizeof(m_AddrServer);

	// データ受信
	recv(m_SockSend, m_ReceiveData, sizeof(m_ReceiveData), 0);
	//recvfrom(m_SockRecv, m_ReceiveData, sizeof(m_ReceiveData), 0, (sockaddr*)&m_AddrServer, &len);
	
	// データが送信されてきた場合記録
	if(strcmp(m_ReceiveData, ""))
	{
		strcpy(m_LastMessage, m_ReceiveData);
	}
	
	DATA_TAG dataTag = DT_MAX;

	sscanf(m_ReceiveData, "%d, ", &dataTag);
	RemoveDataTag(m_ReceiveData);

	int whatPlayer = -1;

	switch(dataTag)
	{
	case 0:	// マッチング
		if(!m_ifMatched)
		{
			int whatplayer = -1;
			sscanf(m_ReceiveData, "%d", &whatplayer);
			if(whatplayer >= 0)
			{
				CManager::SetWhatPlayer(whatplayer);

				m_ifMatched = true;
			}
		}
		break;
	case 1:
		SetPlayerData();
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
void CNetwork::SetPlayerData(void)
{
	vector<CPlayer*>	player = CGame::GetPlayer();
	VECTOR3 pos[4] = { VEC3_ZERO };
	VECTOR3 rot[4] = { VEC3_ZERO };
	VECTOR3 vec[4] = { VEC3_ZERO };

	// ゲームモードの時のみ処理
	if(CManager::GetModeState() == MODE_GAME)
	{
		// 受信データからプレイヤー座標を取得
		sscanf(m_ReceiveData,
			"POS(%.1f,%.1f,%.1f), ROT(%.1f,%.1f,%.1f), VEC(%.1f,%.1f,%.1f), "
			"POS(%.1f,%.1f,%.1f), ROT(%.1f,%.1f,%.1f), VEC(%.1f,%.1f,%.1f), "
			"POS(%.1f,%.1f,%.1f), ROT(%.1f,%.1f,%.1f), VEC(%.1f,%.1f,%.1f), "
			"POS(%.1f,%.1f,%.1f), ROT(%.1f,%.1f,%.1f), VEC(%.1f,%.1f,%.1f)",
			&pos[0].x, &pos[0].y, &pos[0].z, &rot[0].x, &rot[0].y, &rot[0].z, &vec[0].x, &vec[0].y, &vec[0].z,
			&pos[1].x, &pos[1].y, &pos[1].z, &rot[1].x, &rot[1].y, &rot[1].z, &vec[1].x, &vec[1].y, &vec[1].z,
			&pos[2].x, &pos[2].y, &pos[2].z, &rot[2].x, &rot[2].y, &rot[2].z, &vec[2].x, &vec[2].y, &vec[2].z,
			&pos[3].x, &pos[3].y, &pos[3].z, &rot[3].x, &rot[3].y, &rot[3].z, &vec[3].x, &vec[3].y, &vec[3].z);

		// 取得した座標をセット
		for(int i = 0 ; i < (int)player.size() ; i++)
		{
			if(i != CManager::GetWhatPlayer())
			{
				player[i]->SetPos(pos[i]);
				player[i]->SetRot(rot[i]);
				//player[i]->SetVec(vec[i]);
			}
		}
	}
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
	fscanf(fp, "SEND_ADDRESS:%s", cp->Addr);
	cp->pAddr = cp->Addr;

	// ファイルクローズ
	fclose(fp);
}