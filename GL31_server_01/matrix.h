#ifndef _MATRIX_H_
#define _MATRIX_H_
//=============================================================================
//
//	�^�C�g��	�}�g���N�X���Z�q
//	�t�@�C����	matrix.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/05/26
//
//=============================================================================
#include <math.h>
//=============================================================================
//	�}�N����`
//=============================================================================

//=============================================================================
//	�\����
//=============================================================================
#ifndef MMATRIX_DEFINED
typedef struct _MMATRIX {
    union {
        struct {
            float	_11, _12, _13, _14;
            float	_21, _22, _23, _24;
            float	_31, _32, _33, _34;
            float	_41, _42, _43, _44;

        };
        float m[4][4];
    };
} MMATRIX;
#define MMATRIX_DEFINED
#endif

typedef struct MATRIX : public MMATRIX
{
public:
	MATRIX() {};
	MATRIX(const float *);
	MATRIX(const MMATRIX& mtx){
		_11 = mtx._11; _12 = mtx._12; _13 = mtx._13; _14 = mtx._14; _21 = mtx._21; _22 = mtx._22; _23 = mtx._23; _24 = mtx._24;
		_31 = mtx._31; _32 = mtx._32; _33 = mtx._33; _34 = mtx._34; _41 = mtx._41; _42 = mtx._42; _43 = mtx._43; _44 = mtx._44;
	}	// initialize of array(�z��(�|�C���^)�ŏ�����)
	MATRIX(float m_11, float m_12, float m_13, float m_14, float m_21, float m_22, float m_23, float m_24,
			float m_31, float m_32, float m_33, float m_34, float m_41, float m_42, float m_43, float m_44){
		_11 = m_11; _12 = m_12; _13 = m_13; _14 = m_14; _21 = m_21; _22 = m_22; _23 = m_23; _24 = m_24;
		_31 = m_31; _32 = m_32; _33 = m_33; _34 = m_34; _41 = m_41; _42 = m_42; _43 = m_43; _44 = m_44;
	}	// initialize of value(�l�ŏ�����)
	
	
	// access grants(�A�N�Z�X����(������))
	//float& operator () (unsigned int Row, unsigned int Col);
	//float  operator () (unsigned int Row, unsigned int Col) const;
	
	// casting operators(�L���X�g���Z�q(������))
	//operator float* ();
	//operator const float* () const;
	
	// assignment operators(������Z�q)
	MATRIX& operator = (const MATRIX& mtx){
		_11 = mtx._11; _12 = mtx._12; _13 = mtx._13; _14 = mtx._14; _21 = mtx._21; _22 = mtx._22; _23 = mtx._23; _24 = mtx._24;
		_31 = mtx._31; _32 = mtx._32; _33 = mtx._33; _34 = mtx._34; _41 = mtx._41; _42 = mtx._42; _43 = mtx._43; _44 = mtx._44;
		return *this; }	// assign
	MATRIX& operator *= (const MATRIX& mtx){
		_11 = _11 * mtx._11 + _12 * mtx._21 + _13 * mtx._31 + _14 * mtx._41; _12 = _11 * mtx._12 + _12 * mtx._22 + _13 * mtx._32 + _14 * mtx._42;
		_13 = _11 * mtx._13 + _12 * mtx._23 + _13 * mtx._33 + _14 * mtx._43; _14 = _11 * mtx._14 + _12 * mtx._24 + _13 * mtx._34 + _14 * mtx._44;
		_21 = _21 * mtx._11 + _22 * mtx._21 + _23 * mtx._31 + _24 * mtx._41; _22 = _21 * mtx._12 + _22 * mtx._22 + _23 * mtx._32 + _24 * mtx._42;
		_23 = _21 * mtx._13 + _22 * mtx._23 + _23 * mtx._33 + _24 * mtx._43; _24 = _21 * mtx._14 + _22 * mtx._24 + _23 * mtx._34 + _24 * mtx._44;
		_31 = _31 * mtx._11 + _32 * mtx._21 + _33 * mtx._31 + _34 * mtx._41; _32 = _31 * mtx._12 + _32 * mtx._22 + _33 * mtx._32 + _34 * mtx._42;
		_33 = _31 * mtx._13 + _32 * mtx._23 + _33 * mtx._33 + _34 * mtx._43; _34 = _31 * mtx._14 + _32 * mtx._24 + _33 * mtx._34 + _34 * mtx._44;
		_41 = _41 * mtx._11 + _42 * mtx._21 + _43 * mtx._31 + _44 * mtx._41; _42 = _41 * mtx._12 + _42 * mtx._22 + _43 * mtx._32 + _44 * mtx._42;
		_43 = _41 * mtx._13 + _42 * mtx._23 + _43 * mtx._33 + _44 * mtx._43; _44 = _41 * mtx._14 + _42 * mtx._24 + _43 * mtx._34 + _44 * mtx._44;
		return *this;}						// multiplication of matrix and assign(�}�g���b�N�X�̏�Z���)
	MATRIX& operator += (const MATRIX&);	// addition and assign(���Z���)
	MATRIX& operator -= (const MATRIX&);	// subtraction and assign(���Z���)
	MATRIX& operator *= (float pow){
		_11 *= pow; _12 *= pow; _13 *= pow; _14 *= pow; _21 *= pow; _22 *= pow; _23 *= pow; _24 *= pow;
		_31 *= pow; _32 *= pow; _33 *= pow; _34 *= pow; _41 *= pow; _42 *= pow; _43 *= pow; _44 *= pow;
		return *this;}						// multiplication of value and assign(�l�̏�Z���)
	MATRIX& operator /= (float);
	
	// unary operators(�P�����Z�q)
	//MATRIX operator + () const;
	MATRIX operator - () const;
	
	// binary operators(�񍀉��Z�q)
	MATRIX operator * (const MATRIX& mtx) const{
		return MATRIX(
		(_11 * mtx._11 + _12 * mtx._21 + _13 * mtx._31 + _14 * mtx._41), (_11 * mtx._12 + _12 * mtx._22 + _13 * mtx._32 + _14 * mtx._42),
		(_11 * mtx._13 + _12 * mtx._23 + _13 * mtx._33 + _14 * mtx._43), (_11 * mtx._14 + _12 * mtx._24 + _13 * mtx._34 + _14 * mtx._44),
		(_21 * mtx._11 + _22 * mtx._21 + _23 * mtx._31 + _24 * mtx._41), (_21 * mtx._12 + _22 * mtx._22 + _23 * mtx._32 + _24 * mtx._42),
		(_21 * mtx._13 + _22 * mtx._23 + _23 * mtx._33 + _24 * mtx._43), (_21 * mtx._14 + _22 * mtx._24 + _23 * mtx._34 + _24 * mtx._44),
		(_31 * mtx._11 + _32 * mtx._21 + _33 * mtx._31 + _34 * mtx._41), (_31 * mtx._12 + _32 * mtx._22 + _33 * mtx._32 + _34 * mtx._42),
		(_31 * mtx._13 + _32 * mtx._23 + _33 * mtx._33 + _34 * mtx._43), (_31 * mtx._14 + _32 * mtx._24 + _33 * mtx._34 + _34 * mtx._44),
		(_41 * mtx._11 + _42 * mtx._21 + _43 * mtx._31 + _44 * mtx._41), (_41 * mtx._12 + _42 * mtx._22 + _43 * mtx._32 + _44 * mtx._42),
		(_41 * mtx._13 + _42 * mtx._23 + _43 * mtx._33 + _44 * mtx._43), (_41 * mtx._14 + _42 * mtx._24 + _43 * mtx._34 + _44 * mtx._44));
		}										// multiplication of matrix(�}�g���b�N�X�̏�Z)
	MATRIX operator + (const MATRIX&) const;	// addition(���Z)
	MATRIX operator - (const MATRIX&) const;	// subtraction(���Z)
	MATRIX operator * (float pow) const{
		return MATRIX(
		(_11 * pow), (_12 * pow), (_13 * pow), (_14 * pow), (_21 * pow), (_22 * pow), (_23 * pow), (_24 * pow),
		(_31 * pow), (_32 * pow), (_33 * pow), (_34 * pow), (_41 * pow), (_42 * pow), (_43 * pow), (_44 * pow));
		}										// multiplication of value(�l�̏�Z)
	MATRIX operator / (float) const;			// division(���Z)
	
	friend MATRIX operator * (float, const MATRIX&);
	
	// logical operators(�_�����Z�q)
	bool operator == (const MATRIX& mtx) const{
		return (
			(_11 == mtx._11) && (_12 == mtx._12) && (_13 == mtx._13) && (_14 == mtx._14)
		&&	(_21 == mtx._21) && (_22 == mtx._22) && (_23 == mtx._23) && (_24 == mtx._24)
		&&	(_31 == mtx._31) && (_32 == mtx._32) && (_33 == mtx._33) && (_34 == mtx._34)
		&&	(_41 == mtx._41) && (_42 == mtx._42) && (_43 == mtx._43) && (_44 == mtx._44)
		); }	// logical operation of equal(��v)
	bool operator != (const MATRIX& mtx) const{
		return (
			(_11 != mtx._11) || (_12 != mtx._12) || (_13 != mtx._13) || (_14 != mtx._14)
		||	(_21 != mtx._21) || (_22 != mtx._22) || (_23 != mtx._23) || (_24 != mtx._24)
		||	(_31 != mtx._31) || (_32 != mtx._32) || (_33 != mtx._33) || (_34 != mtx._34)
		||	(_41 != mtx._41) || (_42 != mtx._42) || (_43 != mtx._43) || (_44 != mtx._44)
		); }	// logical operation of not equal(�s��v)

} MATRIX;

#endif