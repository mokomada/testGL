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
#include "fade.h"
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
char		CNetwork::m_ReceiveData[65535] = "";
char		CNetwork::m_LastMessage[65535] = "";
uint		CNetwork::m_thID;
HANDLE		CNetwork::m_hTh;

BULLETDATA	CNetwork::m_BulletInstance[PLAYER_NUM][BULLET_NUM_MAX];
vector<int> CNetwork::m_Ranking;

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
	//m_AddrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
	m_AddrServer.sin_addr.s_addr = inet_addr("172.29.33.48");

	// バインド
	bind(m_SockRecv, (sockaddr*)&addr, sizeof(addr));

	Clear();

	// 初期化終了告知
	m_ifInitialize = true;
	
	// マッチング登録
	connect(m_SockSend, (sockaddr*)&m_AddrServer, sizeof(m_AddrServer));
	//send(m_SockSend, "0, entry", strlen("0, entry") + 1, 0);
}

//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化処理を行う。
//=============================================================================
void CNetwork::Clear(void)
{
	for(int i = 0 ; i < PLAYER_NUM ; i++)
	{
		for(int j = 0 ; j < BULLET_NUM_MAX ; j++)
		{
			m_BulletInstance[i][j].Instance	= NULL;
			m_BulletInstance[i][j].Use		= false;
			m_BulletInstance[i][j].IfUninit	= false;
		}
	}

	m_Ranking.clear();
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
	//CDebugProcGL::DebugProc("LASTDATA:%s\n", m_LastMessage);
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
	send(m_SockSend, str, strlen(str) + 1, 0);
	//sendto(m_SockSend, str, strlen(str) + 1, 0, (SOCKADDR*)&m_AddrServer, sizeof(m_AddrServer));

	memset(str, NULL, sizeof(str));
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

	sscanf(m_ReceiveData, "TAG:%d, ", &dataTag);
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
	case 2:
		CreateBullet();
		break;
	case 3:
		DeleteBullet();
		break;

	case 10:
		PlayerDamage();
		break;

	case 100:
		GameEnd();
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

	// 受信データからプレイヤー座標を取得
	sscanf(m_ReceiveData,
		"POS(%f,%f,%f), ROT(%f,%f,%f), VEC(%f,%f,%f), "
		"POS(%f,%f,%f), ROT(%f,%f,%f), VEC(%f,%f,%f), "
		"POS(%f,%f,%f), ROT(%f,%f,%f), VEC(%f,%f,%f), "
		"POS(%f,%f,%f), ROT(%f,%f,%f), VEC(%f,%f,%f)",
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
			//player[i]->SetRot(rot[i]);
			player[i]->SetRotMove(rot[i]);
			//player[i]->SetVec(vec[i]);
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
	VECTOR3				rot		= VEC3_ZERO;
	float				speed	= 0.0f;
	int playerNum = 0, bulletNum = 0;

	// 受信データからデータを取得
	sscanf(m_ReceiveData, "%d, %d, POS(%f, %f, %f), ROT(%f, %f, %f), %f",
		&playerNum, &bulletNum, &pos.x, &pos.y, &pos.z, &rot.x, &rot.y, &rot.z, &speed);

	if(playerNum != CManager::GetWhatPlayer())
	{
		// 取得したデータをセット
		m_BulletInstance[playerNum][bulletNum].Instance = CBullet::Create(playerNum, bulletNum, pos, rot, speed, playerNum);
		m_BulletInstance[playerNum][bulletNum].Use = true;
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
	int playerNum = 0, bulletNum = 0;

	// 受信データからデータを取得
	sscanf(m_ReceiveData, "%d, %d",	&playerNum, &bulletNum);

	if(m_BulletInstance[playerNum][bulletNum].Use)
	{
		m_BulletInstance[playerNum][bulletNum].Instance->SetLife(-100);
	}
}

//=============================================================================
//	関数名	:PlayerDamage
//	引数	:無し
//	戻り値	:無し
//	説明	:ゲームの終了メッセージと共にランキング情報をクライアントに一斉送信。
//=============================================================================
void CNetwork::PlayerDamage(void)
{
	int playerNum = -1;

	// 受信データからデータを取得
	sscanf(m_ReceiveData, "%d", &playerNum);

	if(playerNum >= 0)
	{
		CGame::GetPlayer()[playerNum]->HitBullet();
	}
}

//=============================================================================
//	関数名	:GameEnd
//	引数	:無し
//	戻り値	:無し
//	説明	:ゲームの終了メッセージと共にランキング情報をクライアントに一斉送信。
//=============================================================================
void CNetwork::GameEnd(void)
{
	int ranking[PLAYER_NUM];

	// 受信データからデータを取得
	sscanf(m_ReceiveData, "%d, %d, %d, %d", &ranking[0], &ranking[1], &ranking[2], &ranking[3]);

	m_Ranking.push_back(ranking[0]);
	m_Ranking.push_back(ranking[1]);
	m_Ranking.push_back(ranking[2]);
	m_Ranking.push_back(ranking[3]);

	// リザルトへ
	CFade::Start(new CResult, MODE_RESULT, FS_OUT);
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