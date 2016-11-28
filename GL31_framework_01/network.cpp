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

#pragma comment(lib, "ws2_32.lib")
unsigned int __stdcall thread1(void *);

//=============================================================================
//	静的メンバ変数
//=============================================================================
WSADATA		CNetwork::m_Wsadata;
int			CNetwork::m_Sts;
int			CNetwork::m_Errcode;
SOCKET		CNetwork::m_Sock;
sockaddr_in	CNetwork::m_Addr;
int			CNetwork::m_AddrLen;
sockaddr_in	CNetwork::m_AddrClient;
uint		CNetwork::thID1;
HANDLE		CNetwork::hTh1;
bool		CNetwork::m_IfInitialize = false;

//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化処理を行う。
//=============================================================================
void CNetwork::Init(void)
{
	// †スレッド起動†
	hTh1 = (HANDLE)_beginthreadex(NULL, 0, thread1, NULL, 0, &thID1);


	// ＷＩＮＳＯＣＫ初期処理
	m_Sts = WSAStartup(MAKEWORD(2, 2), &m_Wsadata);
	if(m_Sts != 0) {
		m_Errcode = WSAGetLastError();
		printf("WSAStartupエラーです %d \n", m_Errcode);
		//return -1;
	}

	// バージョンチェック
	if(LOBYTE(m_Wsadata.wVersion) != 2 ||
		HIBYTE(m_Wsadata.wVersion) != 2) {
		printf("バージョンエラーです\n");
		WSACleanup();
		//return -1;
	}

	// ソケット生成
	m_Sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// ポート番号設定
	m_Addr.sin_port = htons(20000);

	// アドレスタイプ設定
	m_Addr.sin_family = AF_INET;

	// IPアドレス設定
	m_Addr.sin_addr.s_addr = inet_addr("239.0.0.1");


	int value = 1;

	// ブロードキャスト許可
	setsockopt(m_Sock, SOL_SOCKET, SO_BROADCAST, (char *)&value, sizeof(value));

	// 初期化終了告知
	m_IfInitialize = true;
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
	closesocket(m_Sock);

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

}

unsigned int __stdcall thread1(void *p)
{
	// データ受信
	while(1)
	{
		// 初期化が終了している場合のみ処理
		if(CNetwork::m_IfInitialize)
		{
			CNetwork::ReceiveData();
		}
	}

	return 0;
}

//=============================================================================
//	関数名	:SendData
//	引数	:char *str	->	送信データ
//	戻り値	:無し
//	説明	:データの送信を行う。
//=============================================================================
void CNetwork::SendData(char *str)
{
	// データ送信
	sendto(m_Sock, str, strlen(str) + 1, 0, (SOCKADDR*)&m_Addr, sizeof(m_Addr));
}

//=============================================================================
//	関数名	:ReceiveData
//	引数	:char *str	->	送信データ
//	戻り値	:無し
//	説明	:データの送信を行う。
//=============================================================================
void CNetwork::ReceiveData(void)
{
	char		str[1024] = { NULL };	// 受信データ

	// バインド
	bind(m_Sock, (sockaddr*)&m_Addr, sizeof(m_Addr));

	// マルチキャストグループに参加
	ip_mreq mreq;

	memset(&mreq, 0, sizeof(mreq));
	mreq.imr_multiaddr.s_addr = inet_addr("239.0.0.1");
	mreq.imr_interface.s_addr = INADDR_ANY;
	setsockopt(m_Sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq));


	// データ受信待機
	m_AddrLen = sizeof(m_AddrClient);
	// データ受信
	recvfrom(m_Sock, str, strlen(str), 0, (sockaddr*)&m_AddrClient, &m_AddrLen);
	
	int dataPt = 0;

	sscanf(str, "%d, ", &dataPt);

	switch(dataPt)
	{
	case 1:
		SetPlayerData(str);
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
{
	CSceneModel	*player2 = CGame::GetPlayer2();
	VECTOR3		pos = VECTOR3::zero();

	// ゲームモードの時のみ処理
	if(CManager::GetModeState() == MODE_GAME)
	{
		// 受信データからプレイヤー座標を取得
		sscanf(str, "1, %f, %f, %f", &pos.x, &pos.y, &pos.z);

		// 取得した座標をセット
		player2->SetPos(pos);
	}
}