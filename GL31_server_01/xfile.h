//#ifndef _XFILE_H_
//#define _XFILE_H_
///******************************************************************************
//�C���N���[�h�t�@�C��
//*******************************************************************************/
//#include "sceneGL.h"
//
///******************************************************************************
//�}�N����`
//******************************************************************************/
///******************************************************************************
//�\���̒�`
//******************************************************************************/
//struct UV
//{
//	float u;//u�l
//	float v;//v�l
//};
//struct INDEX
//{
//	//�ʒu�C���f�b�N�X
//	int indexPos;
//	//�e�N�X�`���C���f�b�N�X
//	int indexTex;
//	//�@���C���f�b�N�X
//	int indexNor;
//};
//
///******************************************************************************
//�N���X
//*******************************************************************************/
//class CXfile :public CSceneGL
//{
//	public://�N�ł��g����
//		CXfile(int priority = 1, OBJTYPE objType = OBJTYPE_NONE);
//		~CXfile( );
//		void Init(void);
//		void Uninit(void);
//		void Updete(void);
//		void Draw(void);
//		static CXfile *Create(const char *xFile, const char *tgaFile);
//		int Load(char *filename);
//	private://���������g���Ȃ�
//		//���_���W
//		VECTOR3 *m_VertexPos;
//		//UV���
//		UV *m_uv2d;
//		//�@�����
//		VECTOR3 *m_nor;
//		//�C���f�b�N�X
//		INDEX *m_Index;
//		//���_��
//		int m_VCnt;
//		//�@����
//		int m_NCnt;
//		//UV��
//		int m_UVCnt;
//		//���_�C���f�b�N�X��
//		int m_ICnt;
//	protected://�p����N���X�ł͎g����
//};
//#endif