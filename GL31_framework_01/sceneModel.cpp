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
#include "game.h"
#include "sceneModel.h"

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
void CSceneModel::Init(char* FileName)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();

	// �e�평����
	m_Frame	= 0;
	m_ExecMotion	= -1;
	m_Scale			= VECTOR3(1.0f, 1.0f, 1.0f);
	m_Texture		= 0;
	
	
	m_Texture = renderer->CreateTextureTGA("./data/TEXTURE/"MODEL_TEXFILENAME000);
	LoadModel(FileName);

	// ���[�V��������
	m_Motion = new MOTION[MODEL_MOTION_NUM];
	LoadMotion("data/MOTION/miku_01_01.anm", 0);
	//LoadMotion("data/MOTION/miku_01_02.anm", 0);
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

	// �z��̏���
	for(int nCntParts = 0 ; nCntParts < m_nNumParts ; nCntParts++ )
	{
		// ���W�z�����
		delete[] m_Parts[nCntParts].data.Pos;
		
		// �e�N�X�`�����W�z�����
		delete[] m_Parts[nCntParts].data.Tex;
		
		// �@���z�����
		delete[] m_Parts[nCntParts].data.Nrm;

		// �C���f�b�N�X�z�����
		for(int nCntIdx = 0 ; nCntIdx < m_Parts[nCntParts].dataNum.Idx ; nCntIdx++)
		{
			delete[] m_Parts[nCntParts].data.Idx[nCntIdx];
			m_Parts[nCntParts].data.Idx[nCntIdx] = NULL;
		}
		delete[] m_Parts[nCntParts].data.Idx;
		m_Parts[nCntParts].data.Idx = NULL;
	}

	// �p�[�c�z�����
	delete[] m_Parts;


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
	}
}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CSceneModel::Update(void)
{
	
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

	// �`�揈����������
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	// 2D�e�N�X�`���L����
	glEnable(GL_TEXTURE_2D);
	
	// �[�x�o�b�t�@�L����
	glEnable(GL_DEPTH_TEST);

	// �J�����O������
	glDisable(GL_CULL_FACE);
	
	// ���_�F�ݒ�
	switch(CManager::GetWhatPlayer())
	{
	case 0:	// 1P
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 1:	// 2P
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 2:	// 3P
		glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
		break;
	case 3:	// 4P
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	default:
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	}

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
}

//=============================================================================
//	�֐���	:Create
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�C���X�^���X�������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
CSceneModel *CSceneModel::Create(char* FileName)
{
	CSceneModel *model;

	model = new CSceneModel;

	model->Init(FileName);

	return model;
}

//=============================================================================
//	�֐���	:LoadModel
//	����	:char* filename	->	�t�@�C����
//	�߂�l	:����
//	����	:�����Ŏw�肵���t�@�C�����̃��f������ǂݍ��ށB
//=============================================================================
void CSceneModel::LoadModel(char *fileName)
{
	int		nCntData	= 0;	// �z�񐶐��p�J�E���^
	char	*str		= NULL;	// �t�@�C�����e�i�[������
	int		offset		= 0;	// �I�t�Z�b�g
	

	// �o�C�i���t�@�C���ǂݍ���
	str = CReadFile::ReadBinaryFile(fileName);

	// �p�[�c�����J�E���g
	m_nNumParts = CReadFile::SearchWordNumByString(str, 0, "\ng ");
	// �p�[�c��񐶐�
	m_Parts = new PARTS[m_nNumParts];

	// �p�[�c��񏉊���
	for(int i = 0 ; i < m_nNumParts ; i++)
	{
		m_Parts[i].Parents	= -1;
		m_Parts[i].Pos		= VECTOR3(0.0f, 0.0f, 0.0f);
		m_Parts[i].Rot		= VECTOR3(0.0f, 0.0f, 0.0f);
		m_Parts[i].Move		= VECTOR3(0.0f, 0.0f, 0.0f);
		m_Parts[i].RotMove	= VECTOR3(0.0f, 0.0f, 0.0f);
	}

	// �z�񐶐�
	for(int i = 0 ; i < m_nNumParts ; i++)
	{
		// �I�t�Z�b�g�̏�����
		offset = 0;

		// �����J�n�ʒu���Z�b�g
		for(int j = 0 ; j <= i ; j++)
		{
			offset = CReadFile::SearchWordByString(str, offset + 3, "\ng ");
		}

		// ���W�����J�E���g
		nCntData = CReadFile::SearchWordNumByString(str, offset + 3, "\nv ", "\ng ");
		// ���W�����L�^
		m_Parts[i].dataNum.Pos = nCntData;
		// ���W�z�񐶐�
		m_Parts[i].data.Pos = new VECTOR3[nCntData];

		// �e�N�X�`�����W�����J�E���g
		nCntData = CReadFile::SearchWordNumByString(str, offset + 3, "\nvt ", "\ng ");
		// �e�N�X�`�����W�����L�^
		m_Parts[i].dataNum.Tex = nCntData;
		// �e�N�X�`�����W�z�񐶐�
		m_Parts[i].data.Tex = new VECTOR2[nCntData];

		// �@�������J�E���g
		nCntData = CReadFile::SearchWordNumByString(str, offset + 3, "\nvn ", "\ng ");
		// �@�������L�^
		m_Parts[i].dataNum.Nrm = nCntData;
		// �@���z�񐶐�
		m_Parts[i].data.Nrm = new VECTOR3[nCntData];

		// �C���f�b�N�X�����J�E���g
		nCntData = CReadFile::SearchWordNumByString(str, offset + 3, "\nf ", "\ng ");
		// �C���f�b�N�X�����L�^
		m_Parts[i].dataNum.Idx = nCntData;
		// �C���f�b�N�X�z�񐶐�
		m_Parts[i].data.Idx = new MODEL_INDEX*[nCntData];
		for(int nCntIdx = 0 ; nCntIdx < nCntData ; nCntIdx++)
		{
			m_Parts[i].data.Idx[nCntIdx] = new MODEL_INDEX[3];
		}
	}

	// ���ǂݍ���
	for(int nCntParts = 0 ; nCntParts < m_nNumParts ; nCntParts++)
	{
		// �I�t�Z�b�g�̏�����
		offset = 0;

		// �����J�n�ʒu���Z�b�g
		for(int j = 0 ; j <= nCntParts ; j++)
		{
			offset = CReadFile::SearchWordByString(str, offset + 3, "\ng ");
		}

		// ���W���ǂݍ���
		offset = CReadFile::SearchWordByString(str, offset, "\nv ");
		offset += 1;
		for(int nCntPos = 0 ; nCntPos < m_Parts[nCntParts].dataNum.Pos ; nCntPos++)
		{
			// �f�[�^�i�[
			sscanf_s(&str[offset], "v %f %f %f\n",
				&m_Parts[nCntParts].data.Pos[nCntPos].x,
				&m_Parts[nCntParts].data.Pos[nCntPos].y,
				&m_Parts[nCntParts].data.Pos[nCntPos].z);

			// �X�P�[�����f
			m_Parts[nCntParts].data.Pos[nCntPos].x *= MODEL_POWER;
			m_Parts[nCntParts].data.Pos[nCntPos].y *= MODEL_POWER;
			m_Parts[nCntParts].data.Pos[nCntPos].z *= MODEL_POWER;

			// �I�t�Z�b�g�ړ�
			offset += 1;
			if(nCntPos != (m_Parts[nCntParts].dataNum.Pos - 1))
			{
				offset = CReadFile::SearchWordByString(str, offset, "\nv ");
				offset += 1;
			}
		}

		// �e�N�X�`�����W���ǂݍ���
		offset = CReadFile::SearchWordByString(str, offset, "\nvt ");
		offset += 1;
		for(int nCntTex = 0 ; nCntTex < m_Parts[nCntParts].dataNum.Tex ; nCntTex++)
		{
			// �f�[�^�i�[
			sscanf_s(&str[offset], "vt %f %f\n",
				&m_Parts[nCntParts].data.Tex[nCntTex].x,
				&m_Parts[nCntParts].data.Tex[nCntTex].y);

			// �I�t�Z�b�g�ړ�
			offset += 1;
			if(nCntTex != (m_Parts[nCntParts].dataNum.Tex - 1))
			{
				offset = CReadFile::SearchWordByString(str, offset, "\nvt ");
				offset += 1;
			}
		}

		// �@�����ǂݍ���
		offset = CReadFile::SearchWordByString(str, offset, "\nvn ");
		offset += 1;
		for(int nCntNrm = 0 ; nCntNrm < m_Parts[nCntParts].dataNum.Nrm ; nCntNrm++)
		{
			// �f�[�^�i�[
			sscanf_s(&str[offset], "vn %f %f %f\n",
				&m_Parts[nCntParts].data.Nrm[nCntNrm].x,
				&m_Parts[nCntParts].data.Nrm[nCntNrm].y,
				&m_Parts[nCntParts].data.Nrm[nCntNrm].z);
			
			// �I�t�Z�b�g�ړ�
			offset += 1;
			if(nCntNrm != (m_Parts[nCntParts].dataNum.Nrm - 1))
			{
				offset = CReadFile::SearchWordByString(str, offset, "\nvn ");
				offset += 1;
			}
		}

		// �}�e���A���ǂݍ���
		;

		// �C���f�b�N�X���ǂݍ���
		offset = CReadFile::SearchWordByString(str, offset, "\nf ");
		offset += 1;
		for(int nCntIdx = 0 ; nCntIdx < m_Parts[nCntParts].dataNum.Idx ; nCntIdx++)
		{
			// �f�[�^�i�[
			sscanf_s(&str[offset], "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
				&m_Parts[nCntParts].data.Idx[nCntIdx][0].vtx,
				&m_Parts[nCntParts].data.Idx[nCntIdx][0].tex,
				&m_Parts[nCntParts].data.Idx[nCntIdx][0].nrm,
				&m_Parts[nCntParts].data.Idx[nCntIdx][1].vtx,
				&m_Parts[nCntParts].data.Idx[nCntIdx][1].tex,
				&m_Parts[nCntParts].data.Idx[nCntIdx][1].nrm,
				&m_Parts[nCntParts].data.Idx[nCntIdx][2].vtx,
				&m_Parts[nCntParts].data.Idx[nCntIdx][2].tex,
				&m_Parts[nCntParts].data.Idx[nCntIdx][2].nrm);

			// �f�[�^�␳
			m_Parts[nCntParts].data.Idx[nCntIdx][0].vtx--;
			m_Parts[nCntParts].data.Idx[nCntIdx][0].tex--;
			m_Parts[nCntParts].data.Idx[nCntIdx][0].nrm--;
			m_Parts[nCntParts].data.Idx[nCntIdx][1].vtx--;
			m_Parts[nCntParts].data.Idx[nCntIdx][1].tex--;
			m_Parts[nCntParts].data.Idx[nCntIdx][1].nrm--;
			m_Parts[nCntParts].data.Idx[nCntIdx][2].vtx--;
			m_Parts[nCntParts].data.Idx[nCntIdx][2].tex--;
			m_Parts[nCntParts].data.Idx[nCntIdx][2].nrm--;
			for(int idx = 0 ; idx < nCntParts ; idx++)
			{
				m_Parts[nCntParts].data.Idx[nCntIdx][0].vtx -= m_Parts[idx].dataNum.Pos;
				m_Parts[nCntParts].data.Idx[nCntIdx][0].tex -= m_Parts[idx].dataNum.Tex;
				m_Parts[nCntParts].data.Idx[nCntIdx][0].nrm -= m_Parts[idx].dataNum.Nrm;
				m_Parts[nCntParts].data.Idx[nCntIdx][1].vtx -= m_Parts[idx].dataNum.Pos;
				m_Parts[nCntParts].data.Idx[nCntIdx][1].tex -= m_Parts[idx].dataNum.Tex;
				m_Parts[nCntParts].data.Idx[nCntIdx][1].nrm -= m_Parts[idx].dataNum.Nrm;
				m_Parts[nCntParts].data.Idx[nCntIdx][2].vtx -= m_Parts[idx].dataNum.Pos;
				m_Parts[nCntParts].data.Idx[nCntIdx][2].tex -= m_Parts[idx].dataNum.Tex;
				m_Parts[nCntParts].data.Idx[nCntIdx][2].nrm -= m_Parts[idx].dataNum.Nrm;
			}

			// �I�t�Z�b�g�ړ�
			offset += 1;
			if(nCntIdx != (m_Parts[nCntParts].dataNum.Idx - 1))
			{
				offset = CReadFile::SearchWordByString(str, offset, "\nf ");
				offset += 1;
			}
		}
	}
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
	for(int nCntParts = 0 ; nCntParts < m_nNumParts ; nCntParts++)
	{
		glPushMatrix();	// �}�g���N�X�̑ޔ�
		
		// ���[�V�������̐ݒ�
		if(m_ExecMotion > -1)
		{
			glTranslatef(m_Motion[m_ExecMotion].Pose[nCntParts][m_Frame].PosX,
						m_Motion[m_ExecMotion].Pose[nCntParts][m_Frame].PosY,
						m_Motion[m_ExecMotion].Pose[nCntParts][m_Frame].PosZ);
			glRotatef((GLfloat)m_Motion[m_ExecMotion].Pose[nCntParts][m_Frame].RotZ, 0.0f, 0.0f, 1.0f);
			glRotatef((GLfloat)m_Motion[m_ExecMotion].Pose[nCntParts][m_Frame].RotY, 0.0f, 1.0f, 0.0f);
			glRotatef((GLfloat)m_Motion[m_ExecMotion].Pose[nCntParts][m_Frame].RotX, 1.0f, 0.0f, 0.0f);
		}

		// �C���f�b�N�X�������ʂ�`��
		for(int nCntIdx = 0 ; nCntIdx < m_Parts[nCntParts].dataNum.Idx ; nCntIdx++)
		{
			glBegin(GL_TRIANGLES);

			for(int idx = 0 ; idx < 3 ; idx++)
			{
				// �@��
				glNormal3f(	m_Parts[nCntParts].data.Nrm[m_Parts[nCntParts].data.Idx[nCntIdx][idx].nrm].x,
							m_Parts[nCntParts].data.Nrm[m_Parts[nCntParts].data.Idx[nCntIdx][idx].nrm].y,
							m_Parts[nCntParts].data.Nrm[m_Parts[nCntParts].data.Idx[nCntIdx][idx].nrm].z);

				// �e�N�X�`�����W
				glTexCoord2d(	m_Parts[nCntParts].data.Tex[m_Parts[nCntParts].data.Idx[nCntIdx][idx].tex].x,
								m_Parts[nCntParts].data.Tex[m_Parts[nCntParts].data.Idx[nCntIdx][idx].tex].y);

				// ���W
				glVertex3f(	m_Parts[nCntParts].data.Pos[m_Parts[nCntParts].data.Idx[nCntIdx][idx].vtx].x,
							m_Parts[nCntParts].data.Pos[m_Parts[nCntParts].data.Idx[nCntIdx][idx].vtx].y,
							m_Parts[nCntParts].data.Pos[m_Parts[nCntParts].data.Idx[nCntIdx][idx].vtx].z);
			}

			glEnd();

		}
		
		glPopMatrix();		// �ۑ��}�g���b�N�X�̎��o��
	}
}