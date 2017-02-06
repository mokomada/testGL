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
#include "player.h"
#include <process.h>
#include <mbstring.h>

#pragma comment(lib, "ws2_32.lib")

//=============================================================================
//	静的メンバ変数
//=============================================================================
CONNECT_PROTOCOL CNetwork::m_ConnectProtocol = { "127.0.0.1", "239.0.0.1", 20000, 20000 };

int			CNetwork::m_PlayerNum = 0;
SOCKET		CNetwork::m_SockSend;
SOCKET		CNetwork::m_SockRecv;
sockaddr_in	CNetwork::m_AddrClient[4];
sockaddr_in	CNetwork::m_RecvClient;
char		CNetwork::m_ReceiveData[1024] = "NO DATA";
char		CNetwork::m_LastMessage[1024] = "NO DATA";
uint		CNetwork::m_thID;
HANDLE		CNetwork::m_hTh;
bool		CNetwork::m_ifInitialize = false;
int			CNetwork::m_ifBindSuccess = -1;

list<CBullet*>	CNetwork::m_BulletInstance[PLAYER_NUM];

//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化処理を行う。
//=============================================================================
void CNetwork::Init(void)
{
	// †スレッド起動†
	m_hTh = (HANDLE)_beginthreadex(NULL, 0, ReceiveThread, NULL, 0, &m_thID);

	WSADATA		wsadata;	// winsockデータ
	int			sts;		// スタートアップ情報
	int			errcode;	// エラーコード
	sockaddr_in	addr;


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

	// 接続先情報読み込み
	ReadConnetProtocol(&m_ConnectProtocol);

	// ソケット生成
	m_SockSend = socket(AF_INET, SOCK_DGRAM, 0);
	m_SockRecv = socket(AF_INET, SOCK_DGRAM, 0);

	// アドレスタイプ設定
	addr.sin_family	= AF_INET;

	// ポート番号設定
	addr.sin_port = htons(20010);

	// IPアドレス設定
	addr.sin_addr.s_addr = INADDR_ANY;

	// バインド
	m_ifBindSuccess = bind(m_SockRecv, (sockaddr*)&addr, sizeof(addr));

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
	if(m_SockSend) closesocket(m_SockSend);
	if(m_SockSend) closesocket(m_SockSend);

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
	//CDebugProcGL::DebugProc("BIND:%d\n", m_ifBindSuccess);
}

//=============================================================================
//	関数名	:ReceiveThread
//	引数	:void* p
//	戻り値	:無し
//	説明	:データ受信スレッド。
//=============================================================================
uint __stdcall CNetwork::ReceiveThread(void* p)
{
	while(1)
	{
		if(m_ifInitialize)
		{
			while(1)
			{
				// データ受信
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
	char str[1024];

	// フォーマット変換
	va_start(list, format);
	vsprintf_s(str, format, list);
	va_end(list);

	// データ送信
	for(int i = 0 ; i < 4 ; i++)
	{
		sendto(m_SockSend, str, strlen(str) + 1, 0, (SOCKADDR*)&m_AddrClient[i], sizeof(m_AddrClient[i]));
	}
}

//=============================================================================
//	関数名	:ReceiveData
//	引数	:char *str	->	送信データ
//	戻り値	:無し
//	説明	:データの送信を行う。
//=============================================================================
void CNetwork::ReceiveData(void)
{
	// クライアント情報
	int len = sizeof(m_RecvClient);

	// データ受信
	recvfrom(m_SockRecv, m_ReceiveData, sizeof(m_ReceiveData), 0, (sockaddr*)&m_RecvClient, &len);

	// データが送信されてきた場合記録
	if(strcmp(m_ReceiveData, ""))
	{
		strcpy(m_LastMessage, m_ReceiveData);
	}
	
	DATA_TAG dataTag = DT_MAX;

	sscanf(m_ReceiveData, "%d, ", &dataTag);
	RemoveDataTag(m_ReceiveData);

	switch(dataTag)
	{
	case 0:	// システムメッセージ
		// ゲームエントリー確認
		if(!strcmp(m_ReceiveData, "entry"))
		{
			if(m_PlayerNum < PLAYER_NUM)
			{
				Matching();
			}
		}
		break;

	case 1:	// プレイヤーデータ
		SetPlayerData();
		break;

	default:
		break;
	}
}

//=============================================================================
//	関数名	:Matching
//	引数	:無し
//	戻り値	:無し
//	説明	:マッチング処理を行う。
//=============================================================================
void CNetwork::Matching(void)
{
	// 同じ接続先の場合カウントしない
	int i = 0;
	for(i = 0 ; i < 4 ; i++)
	{
		if(m_AddrClient[i].sin_addr.s_addr == m_RecvClient.sin_addr.s_addr)
		{
			break;
		}
	}


	char buff[1024] ={ NULL };

	if(i <= 3)
	{// 一度接続されたクライアントの場合、そのプレイヤー番号を返信する

		// 重複しているプレイヤー番号をセット
		sprintf(buff, "matching %d", i);

		// プレイヤー番号を送信
		sendto(m_SockSend, buff, strlen(buff), 0, (sockaddr*)&m_AddrClient[i], sizeof(m_AddrClient));
	}
	else
	{// そうでない場合、現在のプレイヤー番号を返信する

		// クライアント情報の登録
		m_AddrClient[m_PlayerNum]			= m_RecvClient;
		m_AddrClient[m_PlayerNum].sin_port	= htons(20010);

		// 現在のプレイヤー番号をセット
		sprintf(buff, "%d", m_PlayerNum);

		// プレイヤー番号を送信
		sendto(m_SockSend, buff, strlen(buff), 0, (sockaddr*)&m_AddrClient[m_PlayerNum], sizeof(m_AddrClient));

		// プレイヤー数を増やす
		m_PlayerNum++;
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
	VECTOR3				pos = VEC3_ZERO;
	VECTOR3				rot = VEC3_ZERO;
	VECTOR3				vec = VEC3_ZERO;


	for(int i = 0 ; i < PLAYER_NUM ; i++)
	{
		if(m_AddrClient[i].sin_addr.s_addr == m_RecvClient.sin_addr.s_addr)
		{
			// 受信データからデータを取得
			sscanf(m_ReceiveData, "%f, %f, %f, %f, %f, %f, %f, %f, %f",
				&pos.x, &pos.y, &pos.z,	&rot.x, &rot.y, &rot.z,	&vec.x, &vec.y, &vec.z);

			// 取得したデータをセット
			player[i]->SetPos(pos);
			player[i]->SetRot(rot);
			player[i]->SetVec(vec);
		}
	}
}

//=============================================================================
//	関数名	:CreateBullet
//	引数	:無し
//	戻り値	:無し
//	説明	:弾のデータを生成、同期を開始する。
//=============================================================================
void CNetwork::CreateBullet(void)
{
	vector<CPlayer*>	player	= CGame::GetPlayer();
	VECTOR3				pos		= VEC3_ZERO;
	float				speed	= 0.0f;


	for(int i = 0 ; i < PLAYER_NUM ; i++)
	{
		if(m_AddrClient[i].sin_addr.s_addr == m_RecvClient.sin_addr.s_addr)
		{
			// 受信データからデータを取得
			sscanf(m_ReceiveData, "%f, %f, %f, %f, %f, %f, %f, %f, %f",
				&pos.x, &pos.y, &pos.z, &speed);

			// 取得したデータをセット
			m_BulletInstance[i].push_back(CBullet::Create(pos, VEC3_ZERO, speed));
		}
	}
}

//=============================================================================
//	関数名	:DeleteBullet
//	引数	:無し
//	戻り値	:無し
//	説明	:受信したプレイヤーのデータをセットする。
//=============================================================================
void CNetwork::DeleteBullet(void)
{
	for(int i = 0 ; i < PLAYER_NUM ; i++)
	{
		if(m_AddrClient[i].sin_addr.s_addr == m_RecvClient.sin_addr.s_addr)
		{
			if(m_BulletInstance[i].size()) m_BulletInstance[i].pop_front();
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
	fscanf(fp, "SEND_ADDRESS:%s\nMCAST_ADDRESS:%s\nSEND_PORT:%d\nRECV_PORT:%d\n", cp->Addr, cp->MAddr, &cp->SendPort, &cp->RecvPort);

	// ファイルクローズ
	fclose(fp);
}