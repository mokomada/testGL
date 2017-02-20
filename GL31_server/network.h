#ifndef _NETWORK_H_
#define _NETWORK_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(network.cpp)
//	ファイル名	network.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/11/14
//
//=============================================================================
#include "number.h"
#include "bullet.h"

//=============================================================================
//	マクロ定義
//=============================================================================
const int PLAYER_NUM		= 4;
const int BULLET_NUM_MAX	= 100;

//=============================================================================
//	構造体
//=============================================================================
typedef enum {
	DT_ENTRY = 0,
	DT_PLAYER_NUM,
	DT_PLAYER,
	DT_BULLET,
	DT_MAX
} DATA_TAG;

typedef struct {
	char	Addr[16];	// 通信先IPアドレス
	char	MAddr[16];	// マルチキャスト先IPアドレス
	int		SendPort;	// 送信ポート
	int		RecvPort;	// 受信ポート
} CONNECT_PROTOCOL;		// 通信情報

typedef struct {
	SOCKET		Sock;	// TCPソケット
	sockaddr_in	Addr;	// アドレス情報
} CLIENT;				// クライアント情報

//=============================================================================
//	クラス定義
//=============================================================================
class CNetwork
{
public:
	static uint __stdcall MatchThread(void*);
	static uint __stdcall ReceiveThread(void*);

	static void	Init(void);
	static void	Uninit(void);
	static void	Update(void);
	static void	Draw(void);

	static void SendData(char* format, ...);
	static void ReceiveData(void);

	static bool	m_ifInitialize;	// Init()が終了したかどうか

private:
	static void Matching(void);
	static void	SetPlayerData(void);
	static void	CreateBullet(void);
	static void	DeleteBullet(void);
	static void RemoveDataTag(char* data);
	static void	ReadConnetProtocol(CONNECT_PROTOCOL* cp);

	static int			m_PlayerNum;	// プレイヤー数
	static CONNECT_PROTOCOL	m_ConnectProtocol;	// 送信先情報

	static CLIENT		m_Client[PLAYER_NUM];		// クライアント情報
	static SOCKET		m_SockSend;					// UDPソケット
	static SOCKET		m_SockRecv;					// UDPソケット
	static sockaddr_in	m_AddrClient[PLAYER_NUM];	// 送信アドレス情報
	static sockaddr_in	m_RecvClient;				// 受信したデータの送信元情報
	static char			m_ReceiveData[65535];		// 受信データ
	static char			m_LastMessage[65535];		// 最後に送信されてきたデータ

	static uint			m_thIDMatch;	// スレッドID1
	static HANDLE		m_hThMatch;	// スレッドハンドル1
	static uint			m_thID;	// スレッドID1
	static HANDLE		m_hTh;	// スレッドハンドル1

	static int m_ifBindSuccess;

	static list<CBullet*> m_BulletInstance[PLAYER_NUM];
};

#endif