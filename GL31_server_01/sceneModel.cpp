//=============================================================================
//
//	�^�C�g��	�V�[���t�@�C��(3D)
//	�t�@�C����	scene3D.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/04/20
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include <stdio.h>
#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "sceneModel.h"
#include "cameraGL.h"
#include "network.h"
#include "bullet.h"
#include "game.h"
#include "debugProcGL.h"

//=============================================================================
//	�֐���	:CScene3D()
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CSceneModel::CSceneModel(int priority, OBJTYPE objType)
{

}

//=============================================================================
//	�֐���	:~CScene3D()
//	����	:����
//	�߂�l	:����
//	����	:�f�X�g���N�^�B
//=============================================================================
CSceneModel::~CSceneModel()
{

}

//=============================================================================
//	�֐���	:Init
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�������������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
void CSceneModel::Init(bool ifMinePlayer, VECTOR3 pos)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();
	
	// ���v���C���[���ǂ����Z�b�g
	m_ifMinePlayer = ifMinePlayer;

	// �e�평����
	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	m_nCntMove		= 0;
	m_Frame	= 0;
	m_ExecMotion	= -1;
	m_Move			= VECTOR3(0.0f, 0.0f, 0.0f);
	m_RotMove		= VECTOR3(0.0f, 0.0f, 0.0f);
	m_MoveDirection = VECTOR3(0.0f, 0.0f, 0.0f);
	m_bJump			= false;
	m_Scale			= VECTOR3(1.0f, 1.0f, 1.0f);
	m_Texture		= 0;
	
	
	m_Texture = renderer->CreateTextureTGA("./data/TEXTURE/"MODEL_TEXFILENAME000);
	LoadModel("./data/MODEL/"MODEL_FILENAME000);

	// ���[�V��������
	//m_Motion = new MOTION[MODEL_MOTION_NUM];
	//LoadMotion("data/MOTION/miku_01_01.anm", 0);
	//LoadMotion("data/MOTION/miku_01_02.anm", 0);

	m_Gauge = 100.0f;	//�Q�[�W�̏�����
	m_FlgLowSpeed = false;
	m_Radius = 30.0f;
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CSceneModel::Uninit(bool isLast)
{
	// �e�N�X�`���̍폜
	if(m_Texture != NULL)
	{
		if(isLast)
		glDeleteTextures(1, ((GLuint *)m_Texture));
	}

	/*
	// ���[�V��������
	if(m_Motion != NULL)
	{
		for(int nCntMotion = 0 ; nCntMotion < MODEL_MOTION_NUM ; nCntMotion++ )
		{
			if(m_Motion[nCntMotion].Pose != NULL)
			{
				if(m_Motion[nCntMotion].Pose != NULL)
				{
					for(int nCntParts = 0 ; nCntParts < m_nNumParts ; nCntParts++ )
					{
						delete[] m_Motion[nCntMotion].Pose[nCntParts];
					}
					delete[] m_Motion[nCntMotion].Pose;
				}
			}
		}
		delete[] m_Motion;
	}*/
}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CSceneModel::Update(void)
{
	CCameraGL	*camera = CManager::GetCamera();	// �J����

	if (CInput::GetKeyboardTrigger(DIK_SPACE)) m_FlgLowSpeed = true;
	else if (CInput::GetKeyboardRelease(DIK_SPACE)) m_FlgLowSpeed = false;

	// ���v���C���[�̏ꍇ�ɂ̂ݏ���
	if (m_ifMinePlayer)
	{
		if (CInput::GetKeyboardPress(DIK_W))				// �ړ������Ɉړ�
		{
			if (CInput::GetKeyboardPress(DIK_A))				// ������
			{
				//��]�ʂ̉��Z
				if (m_FlgLowSpeed == true) m_MoveDirection.y += LOWMOVE_ROT;
				else if (m_FlgLowSpeed == false) m_MoveDirection.y += MOVE_ROT;
			}
			if (CInput::GetKeyboardPress(DIK_D))				// �E���
			{
				//��]�ʂ̉��Z
				if (m_FlgLowSpeed == true) m_MoveDirection.y -= LOWMOVE_ROT;
				else if (m_FlgLowSpeed == false) m_MoveDirection.y -= MOVE_ROT;
			}

			// �ړ��ʂ�ݒ�
			if (m_FlgLowSpeed == true)
			{
				m_Move.x += sinf(m_Rot.y) * LOWFMOVE_SPEED;
				m_Move.z += cosf(m_Rot.y) * LOWFMOVE_SPEED;
			}
			if (m_FlgLowSpeed == false)
			{
				m_Move.x += sinf(m_Rot.y) * FMOVE_SPEED;
				m_Move.z += cosf(m_Rot.y) * FMOVE_SPEED;
			}
		}
		if (CInput::GetKeyboardPress(DIK_S))		// �ړ������Ɉړ��̔��΂Ɉړ�
		{
			if (CInput::GetKeyboardPress(DIK_A))				// ������
			{
				//��]�ʂ̉��Z
				if (m_FlgLowSpeed == true) m_MoveDirection.y -= LOWMOVE_ROT;
				else if (m_FlgLowSpeed == false) m_MoveDirection.y -= MOVE_ROT;
			}
			if (CInput::GetKeyboardPress(DIK_D))				// �E���
			{
				//��]�ʂ̉��Z
				if (m_FlgLowSpeed == true) m_MoveDirection.y += LOWMOVE_ROT;
				else if (m_FlgLowSpeed == false) m_MoveDirection.y += MOVE_ROT;
			}

			// �ړ��ʂ�ݒ�
			if (m_FlgLowSpeed == true)
			{
				m_Move.x += sinf(m_Rot.y + PI) * LOWBMOVE_SPEED;
				m_Move.z += cosf(m_Rot.y + PI) * LOWBMOVE_SPEED;
			}
			if (m_FlgLowSpeed == false)
			{
				m_Move.x += sinf(m_Rot.y + PI) * BMOVE_SPEED;
				m_Move.z += cosf(m_Rot.y + PI) * BMOVE_SPEED;
			}
		}
		if (m_bJump == true)
		{
			if (CInput::GetKeyboardPress(DIK_W))				// �ړ������Ɉړ�
			{
				if (CInput::GetKeyboardPress(DIK_A))				// ������
				{
					//��]�ʂ̉��Z
					if (m_FlgLowSpeed == true) m_MoveDirection.y += LOWMOVE_ROT;
					else if (m_FlgLowSpeed == false) m_MoveDirection.y += MOVE_ROT;
				}
				if (CInput::GetKeyboardPress(DIK_D))				// �E���
				{
					//��]�ʂ̉��Z
					if (m_FlgLowSpeed == true) m_MoveDirection.y -= LOWMOVE_ROT;
					else if (m_FlgLowSpeed == false) m_MoveDirection.y -= MOVE_ROT;
				}
			}
			else if (CInput::GetKeyboardPress(DIK_S))		// �ړ������Ɉړ��̔��΂Ɉړ�
			{
				if (CInput::GetKeyboardPress(DIK_A))				// ������
				{
					//��]�ʂ̉��Z
					if (m_FlgLowSpeed == true) m_MoveDirection.y -= LOWMOVE_ROT;
					else if (m_FlgLowSpeed == false) m_MoveDirection.y -= MOVE_ROT;
				}
				if (CInput::GetKeyboardPress(DIK_D))				// �E���
				{
					//��]�ʂ̉��Z
					if (m_FlgLowSpeed == true) m_MoveDirection.y += LOWMOVE_ROT;
					else if (m_FlgLowSpeed == false) m_MoveDirection.y += MOVE_ROT;
				}
			}
			else
			{
				if (CInput::GetKeyboardPress(DIK_A))				// ������
				{
					//��]�ʂ̉��Z
					if (m_FlgLowSpeed == true) m_MoveDirection.y += LOWMOVE_ROT;
					else if (m_FlgLowSpeed == false) m_MoveDirection.y += MOVE_ROT;
				}
				if (CInput::GetKeyboardPress(DIK_D))				// �E���
				{
					//��]�ʂ̉��Z
					if (m_FlgLowSpeed == true) m_MoveDirection.y -= LOWMOVE_ROT;
					else if (m_FlgLowSpeed == false) m_MoveDirection.y -= MOVE_ROT;
				}
			}
			
		}

		camera->m_CameraState.posV.x = m_Pos.x + sinf(camera->m_CameraState.Rot.y + m_Rot.y) *camera->m_CameraState.fDistance;
		camera->m_CameraState.posV.z = m_Pos.z + cosf(camera->m_CameraState.Rot.y + m_Rot.y) *camera->m_CameraState.fDistance;

		camera->m_CameraState.posR.x = m_Pos.x + sinf(m_Rot.y) * BMOVE_SPEED;
		camera->m_CameraState.posR.z = m_Pos.z + cosf(m_Rot.y) * BMOVE_SPEED;

		// �W�����v
		if (CInput::GetKeyboardTrigger(DIK_J) && !m_bJump)
		{
			m_Move.y += PLAYER_JUMP;

			m_bJump = true;
		}
		// �e����
		if (CInput::GetKeyboardTrigger(DIK_L))
		{
			CBullet::Create( m_Pos , m_Rot , 10.0f );
		}
	}

	// ��]�ʕ␳
	if (m_Rot.y - m_MoveDirection.y > PI)				// ��]�ʂ��v���X�����ɋt�����̏ꍇ
	{
		// ��]�ʂ��t������
		m_Rot.y -= (PI * 2.0f);
	}
	else if (m_Rot.y - m_MoveDirection.y < -PI)			// ��]�ʂ��}�C�i�X�����ɋt�����̏ꍇ
	{
		// ��]�ʂ��t������
		m_Rot.y += (PI * 2.0f);
	}

	// ��]�ʂ�ݒ�
	m_Rot.y += (m_MoveDirection.y - m_Rot.y) * 0.1f;

	// �ړ��ʔ��f
	m_Pos.x += m_Move.x;
	m_Pos.z += m_Move.z;

	//�ړ��ʂ̌���
	if (m_bJump == true)
	{
		m_Move.x += (-m_Move.x * MODEL_SPEED_DOWNJ);
		m_Move.z += (-m_Move.z * MODEL_SPEED_DOWNJ);
		m_Move.y += (-m_Move.y * MODEL_SPEED_DOWN);
	}
	else
	{
		m_Move += (-m_Move * MODEL_SPEED_DOWN);
	}

	// �W�����v�ʂ̔��f
	m_Pos.y += m_Move.y;

	if (m_ifMinePlayer)
	{
		CollisionDetection();
	}

	// �v���C���[�̍�����ݒ�
	if (m_Pos.y < 20.0f)
	{
		m_Pos.y = 20.0f;
		m_bJump = false;
	}
	else
	{
		// �W�����v�ʂ̌���
		m_Move.y -= PLAYER_GRAVITY;
	}

	// ���v���C���[�̏ꍇ�A�ʒu�𑗐M
	if (m_ifMinePlayer)
	{
		char str[1024] = { NULL };

		sprintf(str, "1, %f, %f, %f", m_Pos.x, m_Pos.y, m_Pos.z);

		CNetwork::SendData(str);
	}
}

//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CSceneModel::Draw(void)
{
	glMatrixMode(GL_MODELVIEW);		// ���f���r���[�}�g���N�X�̐ݒ�
	glPushMatrix();					// �}�g���N�X�̑ޔ�

	// ���[���h�}�g���N�X�̐ݒ�
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef((GLfloat)(m_Rot.z * 180.0 / PI), 0.0f, 0.0f, 1.0f);	// ��]�}�g���b�N�X�̐ݒ�A�p�x�͓x���@��
	glRotatef((GLfloat)(m_Rot.y * 180.0 / PI), 0.0f, 1.0f, 0.0f);	// ��]�}�g���b�N�X�̐ݒ�A�p�x�͓x���@��
	glRotatef((GLfloat)(m_Rot.x * 180.0 / PI), 1.0f, 0.0f, 0.0f);	// ��]�}�g���b�N�X�̐ݒ�A�p�x�͓x���@��
	//glScalef(m_Scale.x, m_Scale.y, m_Scale.z);

	// �`�揈����������
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	// 2D�e�N�X�`���L����
	glEnable(GL_TEXTURE_2D);
	
	// �[�x�o�b�t�@�L����
	glEnable(GL_DEPTH_TEST);

	// �J�����O������
	glDisable(GL_CULL_FACE);
	
	// ���_�F�ݒ�
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);

	// ���f���`��
	DrawModel();
	
	// 2D�e�N�X�`��������
	glDisable(GL_TEXTURE_2D);
	
	// �[�x�o�b�t�@������
	glDisable(GL_DEPTH_TEST);

	// �J�����O�L����
	glEnable(GL_CULL_FACE);


	glMatrixMode(GL_MODELVIEW);		// ���f���r���[�}�g���b�N�X�̐ݒ�
	glPopMatrix();					// �ۑ��}�g���b�N�X�̎��o��

#ifdef _DEBUG
	//CDebugProcGL::DebugProc("chara:(%.2f:%.2f:%.2f)\n", m_Pos.x, m_Pos.y, m_Pos.z);
#endif
}

//=============================================================================
//	�֐���	:Create
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�C���X�^���X�������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
CSceneModel *CSceneModel::Create(bool ifMinePlayer, VECTOR3 pos)
{
	CSceneModel *scene3D;

	scene3D = new CSceneModel;

	scene3D->Init(ifMinePlayer, pos);

	return scene3D;
}

//=============================================================================
//	�֐���	:LoadModel
//	����	:char* filename	->	�t�@�C����
//	�߂�l	:����
//	����	:�����Ŏw�肵���t�@�C�����̃��f������ǂݍ��ށB
//=============================================================================
void CSceneModel::LoadModel(char *fileName)
{
	FILE *fp		= NULL;	// �t�@�C���|�C���^
	FILE *fpBuff	= NULL;	// �t�@�C���|�C���^

	// �t�@�C���I�[�v��
	fp = fopen(fileName, "r");

	// �t�@�C���I���܂œǂݍ���
	while(!feof(fp))
	{
		char str[65535] = { NULL };
		memset(str, NULL, sizeof(str));

		// �P����擾
		fscanf(fp, "%s", str);

		if(strcmp(str, "g") == 0)
		{// �X�v���C������_��ǉ�

			m_Parts.resize((int)m_Parts.size() + 1);

			m_Parts[m_Parts.size() - 1].Parents = -1;
			m_Parts[m_Parts.size() - 1].Pos		= VEC3_ZERO;
			m_Parts[m_Parts.size() - 1].Rot		= VEC3_ZERO;
			m_Parts[m_Parts.size() - 1].Move	= VEC3_ZERO;
			m_Parts[m_Parts.size() - 1].RotMove	= VEC3_ZERO;
		}
		else if(strcmp(str, "v") == 0)
		{// ���_���W��ǉ�

			VECTOR3 pos = VEC3_ZERO;

			// �f�[�^�i�[
			fscanf_s(fp, " %f %f %f\n", &pos.x, &pos.y, &pos.z);
			pos *= MODEL_POWER;

			m_Parts[m_Parts.size() - 1].data.Vtx.push_back(pos);
		}
		else if(strcmp(str, "vt") == 0)
		{// �e�N�X�`�����W��ǉ�
			
			VECTOR2 tex = VEC2_ZERO;

			// �f�[�^�i�[
			fscanf_s(fp, " %f %f\n", &tex.x, &tex.y);

			m_Parts[m_Parts.size() - 1].data.Tex.push_back(tex);
		}
		else if(strcmp(str, "vn") == 0)
		{// �@���x�N�g����ǉ�

			VECTOR3 nrm = VEC3_ZERO;

			// �f�[�^�i�[
			fscanf_s(fp, " %f %f %f\n", &nrm.x, &nrm.y, &nrm.z);

			m_Parts[m_Parts.size() - 1].data.Nrm.push_back(nrm);
		}
		else if(strcmp(str, "f") == 0)
		{// �C���f�b�N�X��ǉ�

			// �C���f�b�N�X���z�񐶐�
			m_Parts[m_Parts.size() - 1].data.Idx.resize(m_Parts[m_Parts.size() - 1].data.Idx.size() + 1);
			
			// �f�[�^�i�[
			int idxArray = m_Parts[m_Parts.size() - 1].data.Idx.size() - 1;

			while(*fp->_ptr != '\n')
			{
				MODEL_INDEX idx = { 0 };

				// �C���f�b�N�X�̒l��ǂݍ���
				fscanf_s(fp, " %d/%d/%d", &idx.vtx, &idx.tex, &idx.nrm);
				// �C���f�b�N�X�̒l��␳
				idx.IdxRight();
				if((int)m_Parts.size() >= 2)
				{
					for(int j = 2 ; j <= (int)m_Parts.size() ; j++)
					{
						idx.vtx -= m_Parts[m_Parts.size() - j].data.Vtx.size();
						idx.tex -= m_Parts[m_Parts.size() - j].data.Tex.size();
						idx.nrm -= m_Parts[m_Parts.size() - j].data.Nrm.size();
					}
				}
				// �z�񐶐�
				m_Parts[m_Parts.size() - 1].data.Idx[idxArray].push_back(idx);
			}
		}
	}

	// �t�@�C���N���[�Y
	fclose(fp);
}

//=============================================================================
//	�֐���	:LoadMotion
//	����	:char*	filename	->	�t�@�C����
//			:int	nNumMotion	->	���[�V�����i���o�[
//	�߂�l	:����
//	����	:�����Ŏw�肵���t�@�C�����̃��[�V��������ǂݍ��ށB
//=============================================================================
void CSceneModel::LoadMotion(char *fileName, int nNumMotion)
{
	int		nCntData	= 0;	// �z�񐶐��p�J�E���^
	char	*str		= NULL;	// �t�@�C�����e�i�[������
	int		offset		= 0;	// �I�t�Z�b�g
	int		frame		= 0;
	

	// �o�C�i���t�@�C���ǂݍ���
	str = CReadFile::ReadBinaryFile(fileName);

	// �t���[�������J�E���g
	frame = CReadFile::SearchWordNumByString(str, 0, "fr ");

	// �t���[������ݒ�
	m_Motion[nNumMotion].Frame = frame;

	if((m_nNumParts > 0) && (m_Motion[nNumMotion].Frame > 0))
	{
		// �z�񐶐�
		m_Motion[nNumMotion].Pose = new POSE*[m_nNumParts];
		for(int nCntParts = 0 ; nCntParts < m_nNumParts ; nCntParts++)
		{
			m_Motion[nNumMotion].Pose[nCntParts] = new POSE[m_Motion[nNumMotion].Frame];
		}
	
		// �I�t�Z�b�g�̏�����
		offset = 0;

		// ���ǂݍ���
		for(int nCntFrame = 0 ; nCntFrame < m_Motion[nNumMotion].Frame ; nCntFrame++)
		{
			// �ǂݍ��݊J�n�ʒu���Z�b�g
			offset = CReadFile::SearchWordByString(str, offset, "fr ");

			// �p�[�c���Ƃɏ���ǂݍ���
			for(int nCntParts = 0 ; nCntParts < m_nNumParts ; nCntParts++)
			{
				float a;
				offset = CReadFile::SearchWordByString(str, offset + 1, "ky ");
				// �f�[�^�i�[
				sscanf_s(&str[offset], "ky %f %f %f %f %f %f",
					&m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosX,
					&m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosY,
					&m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosZ,
					&m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].RotX,
					&m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].RotY,
					&m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].RotZ);
				a = m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosX;
				a = 0;
			}
		}
	}

	FILE	*fp;

	fopen_s(&fp, "data/MOTION/test.txt", "w");

	// ��񏑂�����
	for(int nCntFrame = 0 ; nCntFrame < m_Motion[nNumMotion].Frame ; nCntFrame++)
	{
		fprintf_s(fp, "fr %d\n", nCntFrame);

		// �p�[�c���Ƃɏ�����������
		for(int nCntParts = 0 ; nCntParts < m_nNumParts ; nCntParts++)
		{
			// �f�[�^�i�[
			fprintf_s(fp, "ky %f %f %f %f %f %f\n",
				m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosX,
				m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosY,
				m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosZ,
				m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].RotX,
				m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].RotY,
				m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].RotZ);
			m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosX *= MODEL_POWER;
			m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosY *= MODEL_POWER;
			m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosZ *= MODEL_POWER;
		}

		fprintf_s(fp, "\n");
	}

	fclose(fp);
}

//=============================================================================
//	�֐���	:DrawModel
//	����	:����
//	�߂�l	:����
//	����	:�|���S���̒��_�����Z�b�g����B
//=============================================================================
void CSceneModel::DrawModel(void)
{
	// �p�[�c���Ԃ�`��
	for(int i = 0 ; i < (int)m_Parts.size() ; i++)
	{
		glPushMatrix();	// �}�g���N�X�̑ޔ�

		// �C���f�b�N�X�������ʂ�`��
		for(int j = 0 ; j < (int)m_Parts[i].data.Idx.size() ; j++)
		{
			// �`��V�[�P���X�J�n
			glBegin(GL_TRIANGLES);

			// �ʂ̐����擾
			int size = (int)m_Parts[i].data.Idx[j].size();

			// �ʂ̐��������_�f�[�^���Z�b�g
			for(int idx = 0 ; idx < size ; idx++)
			{
				// �@��
				glNormal3f(	m_Parts[i].data.Nrm[m_Parts[i].data.Idx[j][idx].nrm].x,
							m_Parts[i].data.Nrm[m_Parts[i].data.Idx[j][idx].nrm].y,
							m_Parts[i].data.Nrm[m_Parts[i].data.Idx[j][idx].nrm].z);

				// �e�N�X�`�����W
				glTexCoord2d(	m_Parts[i].data.Tex[m_Parts[i].data.Idx[j][idx].tex].x,
								m_Parts[i].data.Tex[m_Parts[i].data.Idx[j][idx].tex].y);

				// ���W
				glVertex3f(	m_Parts[i].data.Vtx[m_Parts[i].data.Idx[j][idx].vtx].x,
							m_Parts[i].data.Vtx[m_Parts[i].data.Idx[j][idx].vtx].y,
							m_Parts[i].data.Vtx[m_Parts[i].data.Idx[j][idx].vtx].z);
			}

			// �`��V�[�P���X�I��
			glEnd();

		}
		
		glPopMatrix();		// �ۑ��}�g���b�N�X�̎��o��
	}
}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CSceneModel::CollisionDetection(void)
{
	CGame *game = (CGame*)CManager::GetMode();
	vector<CSceneModel*>::iterator sceneModel = game->GetPlayer();
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (sceneModel[nCnt] != NULL)
		{
			if (sceneModel[nCnt]->m_ifMinePlayer == false)
			{
				VECTOR3 sub = GetPos() - sceneModel[nCnt]->GetPos();
				float distance = VECTOR3::dot(sub, sub);
				float radius = m_Radius + sceneModel[nCnt]->m_Radius;

				if (distance <= radius * radius)
				{
					CDebugProcGL::DebugProc("Hit%d\n", nCnt);

					VECTOR3 Pos0 = GetPos(), Pos1 = sceneModel[nCnt]->GetPos();
					float Radius = m_Radius + sceneModel[nCnt]->m_Radius;
					float Lenght = (Pos1 - Pos0).magnitude();
					VECTOR3 Vec = Pos0 - Pos1;
					Vec.normalize();
					Radius -= Lenght;
					Pos0 += VECTOR3(Vec.x * Radius, Vec.y * Radius, Vec.z * Radius);
					SetPos(Pos0);
				}
			}
		}
	}
}