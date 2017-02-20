//=============================================================================
//
//	�^�C�g��	�V�[���t�@�C��(3D)
//	�t�@�C����	meshfield.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/11/14
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "meshfield.h"

//=============================================================================
//	�֐���	:CMeshfield()
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CMeshfield::CMeshfield() : CScene3DGL(true, PRIORITY_FIELD, OBJTYPE_NONE)
{
	glMatrixIdentity(&m_mtxWorld);
}

//=============================================================================
//	�֐���	:~CMeshfield()
//	����	:����
//	�߂�l	:����
//	����	:�f�X�g���N�^�B
//=============================================================================
CMeshfield::~CMeshfield()
{

}

//=============================================================================
//	�֐���	:Init
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�������������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
void CMeshfield::Init(VECTOR3 pos, VECTOR2 size, char *texName)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();


	// �e�평����
	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Size = size;
	
	// �e�N�X�`���Ǎ�
	m_Texture = renderer->CreateTextureTGA(texName);

	// ���b�V���̃Z�b�e�B���O
	SetMeshData();
	SetMeshIndex(m_Index, MESHFIELD_HORIZONTAL, MESHFIELD_VERTICAL);
}

//=============================================================================
//	�֐���	:SetMeshData
//	����	:����
//	�߂�l	:����
//	����	:�|���S���̒��_�����Z�b�g����B
//=============================================================================
void CMeshfield::SetMeshData(void)
{
	// ���W�ݒ�
	for(int y = 0 ; y <= MESHFIELD_VERTICAL ; y++)
	{
		for(int x = 0 ; x <= MESHFIELD_HORIZONTAL ; x++)
		{
			m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos.x
				= (-(MESHFIELD_WIDTH * 0.5f * MESHFIELD_HORIZONTAL)) + (MESHFIELD_WIDTH * x);

			m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos.y = 0.0f;

			m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos.z
				= -((MESHFIELD_HEIGHT * 0.5f * MESHFIELD_VERTICAL) - (MESHFIELD_HEIGHT * y));
		}
	}

	// �@���ݒ�
	for(int y = 0 ; y <= MESHFIELD_VERTICAL ; y++)
	{
		for(int x = 0 ; x <= MESHFIELD_HORIZONTAL ; x++)
		{
			if((y != 0) && (y != (MESHFIELD_VERTICAL))
				&& (x != 0) && (x != (MESHFIELD_HORIZONTAL)))
			{
				// �@���ݒ�
				VECTOR3 nor, n1, n2, n3, n4, n5, n6, v01, v02, v03, v04, v05, v06;
				v01 = m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + (x - 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
				v02 = m_Mesh[((y - 1) * (MESHFIELD_HORIZONTAL + 1) + (x - 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
				v03 = m_Mesh[((y - 1) * (MESHFIELD_HORIZONTAL + 1) + x)].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
				v04 = m_Mesh[((y) * (MESHFIELD_HORIZONTAL + 1) + (x + 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
				v05 = m_Mesh[((y + 1) * (MESHFIELD_HORIZONTAL + 1) + x)].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
				v06 = m_Mesh[((y + 1) * (MESHFIELD_HORIZONTAL + 1) + (x + 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
				n1 = VECTOR3::cross(v01, v02);
				n1.normalize();
				n2 = VECTOR3::cross(v02, v03);
				n2.normalize();
				n3 = VECTOR3::cross(v03, v04);
				n3.normalize();
				n4 = VECTOR3::cross(v04, v05);
				n4.normalize();
				n5 = VECTOR3::cross(v05, v06);
				n5.normalize();
				n6 = VECTOR3::cross(v06, v01);
				n6.normalize();
				nor = (n1 + n2 + n3 + n4 + n5 + n6) / 6.0f;
				nor.normalize();
				m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Nor = nor;
			}
			else
			{
				m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Nor = VECTOR3(0.0f, 1.0f, 0.0f);
			}
		}
	}

	// �e�N�X�`�����W�ݒ�
	for(int y = 0 ; y <= MESHFIELD_VERTICAL ; y++)
	{
		for(int x = 0 ; x <= MESHFIELD_HORIZONTAL ; x++)
		{
			m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Tex.x = (float)x * 10.0f;
			m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Tex.y = (float)y * 10.0f;
		}
	}
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CMeshfield::Uninit(void)
{
	if(m_Texture != NULL)
	{
		// �e�N�X�`���폜
		glDeleteTextures(1, ((GLuint *)m_Texture));
	}
}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CMeshfield::Update(void)
{
	if(0)
	{
		// �@���ݒ�
		for(int y = 0 ; y <= MESHFIELD_VERTICAL ; y++)
		{
			for(int x = 0 ; x <= MESHFIELD_HORIZONTAL ; x++)
			{
				if((y != 0) && (y != (MESHFIELD_VERTICAL))
					&& (x != 0) && (x != (MESHFIELD_HORIZONTAL)))
				{
					// �@���ݒ�
					VECTOR3 nor;
					VECTOR3 n1, n2, n3, n4, n5, n6, v01, v02, v03, v04, v05, v06;


					v01 = m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + (x - 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
					v02 = m_Mesh[((y - 1) * (MESHFIELD_HORIZONTAL + 1) + (x - 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
					v03 = m_Mesh[((y - 1) * (MESHFIELD_HORIZONTAL + 1) + x)].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
					v04 = m_Mesh[((y) * (MESHFIELD_HORIZONTAL + 1) + (x + 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
					v05 = m_Mesh[((y + 1) * (MESHFIELD_HORIZONTAL + 1) + x)].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
					v06 = m_Mesh[((y + 1) * (MESHFIELD_HORIZONTAL + 1) + (x + 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;

					n1 = VECTOR3::cross(v01, v02).normalize();
					n2 = VECTOR3::cross(v02, v03).normalize();
					n3 = VECTOR3::cross(v03, v04).normalize();
					n4 = VECTOR3::cross(v04, v05).normalize();
					n5 = VECTOR3::cross(v05, v06).normalize();
					n6 = VECTOR3::cross(v06, v01).normalize();

					nor = ((n1 + n2 + n3 + n4 + n5 + n6) / 6.0f).normalize();
					m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Nor = nor;
				}
				else
				{
					m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Nor = VECTOR3(0.0f, 1.0f, 0.0f);
				}
			}
		}
	}
}

//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CMeshfield::Draw(void)
{
	// ���f���r���[�}�g���N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �}�g���N�X�̑ޔ�
	glPushMatrix();

	// ���[���h�}�g���N�X�̐ݒ�
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef((m_Rot.x * 180 / PI), 1.0f, 0.0f, 0.0f);
	glRotatef((m_Rot.y * 180 / PI), 0.0f, 1.0f, 0.0f);
	glRotatef((m_Rot.z * 180 / PI), 0.0f, 0.0f, 1.0f);
	glScalef(1.0f, 1.0f, 1.0f);

	// �`�揈����������
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glEnable(GL_TEXTURE_2D);
	
	// �[�x�o�b�t�@�ݒ�
	glEnable(GL_DEPTH_TEST);

	// ���C�e�B���O�I�t
	//glDisable(GL_LIGHTING);

	glBegin(GL_TRIANGLE_STRIP);
	{
		// ���_�F�ݒ�
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		// �|���S���`��
		for(int i = 0 ; i < MESHFIELD_INDEX_NUM ; i++)
		{
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2d(m_Mesh[m_Index[i]].Tex.x, m_Mesh[m_Index[i]].Tex.y);
			glVertex3f(m_Mesh[m_Index[i]].Pos.x, m_Mesh[m_Index[i]].Pos.y, m_Mesh[m_Index[i]].Pos.z);
		}
	}
	glEnd();

	// �e��ݒ�����߂�
	//glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	// ���f���r���[�}�g���b�N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �ۑ��}�g���b�N�X�̎��o��
	glPopMatrix();
}

//=============================================================================
//	�֐���	:Create
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�C���X�^���X�������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
CMeshfield *CMeshfield::Create(VECTOR3 pos, VECTOR2 size, char *texName)
{
	CMeshfield *meshfield;

	meshfield = new CMeshfield;

	meshfield->Init(pos, size, texName);

	return meshfield;
}

//=============================================================================
//	�֐���	:SetMeshIndex
//	����	:uint *idx	->	�C���f�b�N�X
//			:int x		->	���b�V���̉��u���b�N��
//			:int y		->	���b�V���̏c�u���b�N��
//	�߂�l	:����
//	����	:���b�V���̃C���f�b�N�X���Z�b�g����B
//=============================================================================
void CMeshfield::SetMeshIndex(uint *idxBuff, const int horizontal, const int vertical)
{
	int	idxNum = ((horizontal + 1) * 2) * vertical + ((vertical - 1) * 2);
	int	idxStd = ((horizontal + 1) * 2 + 2);
	int	idxVtxNum = (horizontal + 1) * (vertical + 1);


	int buff = (idxVtxNum / (vertical + 1));

	for(int nCntVertical = 0 ; nCntVertical < vertical ; nCntVertical++)
	{
		for(int nCntIdx = 0 ; nCntIdx < idxStd ; nCntIdx++)
		{
			if((nCntVertical == (vertical - 1)) && (nCntIdx == (idxStd - 2)))
			{// �����ł��؂�
				break;
			}

			if(nCntIdx == (idxStd - 1))
			{
				buff += (horizontal + 2);
				idxBuff[nCntVertical * idxStd + nCntIdx] = buff;
			}
			else if(nCntIdx == (idxStd - 2))
			{
				idxBuff[nCntVertical * idxStd + nCntIdx] = buff;
			}
			else
			{
				idxBuff[nCntVertical * idxStd + nCntIdx] = buff;

				if(nCntIdx % 2 == 0)
				{
					buff -= (horizontal + 1);
				}
				else
				{
					if(nCntIdx != (idxStd - 3))
					{
						buff += (horizontal + 2);
					}
				}
			}
		}
	}
}