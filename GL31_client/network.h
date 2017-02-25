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
#include "player.h"

//=============================================================================
//	マクロ定義
//=============================================================================
const int PLAYER_NUM		= 4;
const int BULLET_NUM_MAX	= 1000;

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
	char*	pAddr;	// 通信先IPアドレス
} CONNECT_PROTOCOL;		// 通信情報

typedef struct {
	CBullet*	Instance;
	bool		IfUninit;
	bool		Use;
}BULLETDATA;

//=============================================================================
//	クラス定義
//=============================================================================
class CNetwork
{
public:
	static uint __stdcall ReceveThread(void *);

	static void	Init(void);
	static void	Clear(void);
	static void	Uninit(void);
	static void	Update(void);
	static void	Draw(void);

	static void SendData(char* format, ...);
	static void ReceiveData(void);

	static BULLETDATA m_BulletInstance[PLAYER_NUM][BULLET_NUM_MAX];
	static vector<int> m_Ranking;

private:
	static void RemoveDataTag(char* data);
	static void	ReadConnetProtocol(CONNECT_PROTOCOL *cp);
	static void	SetPlayerData(void);
	static void	CreateBullet(void);
	static void	DeleteBullet(void);
	static void	PlayerDamage(void);
	static void	GameEnd(void);
	static CONNECT_PROTOCOL	m_ConnectProtocol;	// 送信先情報

	static bool	m_ifInitialize;	// Init()が終了したかどうか
	static bool	m_ifMatched;		// マッチングが終了したかどうか

	static SOCKET		m_SockSend;				// UDPソケット
	static SOCKET		m_SockRecv;				// UDPソケット
	static sockaddr_in	m_AddrServer;			// サーバのアドレス
	static char			m_ReceiveData[65535];	// 受信データ
	static char			m_LastMessage[65535];	// 最後に送信されてきたデータ

	static uint			m_thID;	// スレッドID1
	static HANDLE		m_hTh;	// スレッドハンドル1
};

#endif