#ifndef _VECTOR_H_
#define _VECTOR_H_
//=============================================================================
//
//	�^�C�g��	�x�N�g�����Z�q
//	�t�@�C����	vector.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/05/26
//
//=============================================================================
#include <math.h>

//=============================================================================
//	class VECTOR
//=============================================================================
#ifndef VECTOR_DEFINED
typedef struct _VECTOR {
 float x;
 float y;
 float z;
} VECTOR;
#define VECTOR_DEFINED
#endif

//=============================================================================
//	class VECTOR2
//=============================================================================
typedef struct VECTOR2
{
#ifdef __cplusplus
public:
	VECTOR2() {};
	VECTOR2(const float *vec) { x = *vec; vec++; y = *vec; }	// initialize of array(�z��(�|�C���^)�ŏ�����)
	VECTOR2(float nx, float ny) { x = nx; y = ny; }				// initialize of value(�l�ŏ�����)

	// casting(�L���X�g���Z�q(������))
	//operator float* ();
	//operator const float* () const;

	// assignment operators(������Z�q)
	VECTOR2& operator = (const VECTOR2& vec) { x = vec.x; y = vec.y;	return *this; }		// assign
	VECTOR2& operator += (const VECTOR2& vec) { x += vec.x; y += vec.y; return *this; }		// addition and assign
	VECTOR2& operator -= (const VECTOR2& vec) { x -= vec.x; y -= vec.y; return *this; }		// subtraction and assign
	VECTOR2& operator *= (float pow) { x *= pow; y *= pow; return *this; }					// multiplication and assign
	VECTOR2& operator /= (float pow) { if(pow != 0) { x /= pow; y /= pow; return *this; }
										else{ x = 0.0f; y = 0.0f; return *this; }}			// division and assign

	// unary operators(�P�����Z�q)
	// VECTOR2 operator + () const;
	VECTOR2 operator - () const { return VECTOR2(-x, -y); }
	
	// binary operators(�񍀉��Z�q)
	VECTOR2 operator + (const VECTOR2& vec) const { return VECTOR2((x + vec.x), (y + vec.y)); }	// addition
	VECTOR2 operator - (const VECTOR2& vec) const { return VECTOR2((x - vec.x), (y - vec.y)); }	// subtraction 
	VECTOR2 operator * (float pow) const { return VECTOR2((x * pow), (y * pow)); }				// multiplication
	VECTOR2 operator / (float pow) const { return (pow != 0) ? VECTOR2((x / pow), (y / pow)) : VECTOR2(0.0f, 0.0f); } // division

	friend VECTOR2 operator * (float pow, const struct VECTOR2& vec) { return VECTOR2((vec.x * pow), (vec.y * pow)); }
	
	// logical operators(�_�����Z�q)
	bool operator == (const VECTOR2& vec) const{ return ((x == vec.x) && (y == vec.y)); }	// logical operation of equal
	bool operator != (const VECTOR2& vec) const{ return ((x != vec.x) || (y != vec.y)); }	// logical operation of not equal
	
	// vector magnitude(�x�N�g���̑傫��)
	float magnitude() const { return sqrt((x * x) + (y * y)); }

	// vector normalizing(�x�N�g���̐��K��)
	VECTOR2& normalize() { float mag = magnitude(); if(mag > 0.0f) { x /= mag; y /= mag; } return *this; }

	// distance of 2 points(2�̃x�N�g���̋���)
    static inline float distance(const VECTOR2 &a, const VECTOR2 &b) { return (a - b).magnitude(); }

	// distance of 2 points(�_a����_b�ւ�2D�x�N�g��)
	static inline VECTOR2 arrow(const VECTOR2 &a, const VECTOR2 &b) { return VECTOR2((b.x - a.x), (b.y - a.y)); }
	
	// dot product of 2D(2D�̓���)
	static inline float dot(const VECTOR2 &a, const VECTOR2 &b) { return ((a.x * b.x) + (a.y * b.y)); }

	// cross product of 2D(2D�̊O��)
    static inline float cross(const VECTOR2 &a, const VECTOR2 &b) { return (a.x * b.y - a.y * b.x); }

public:
#endif //__cplusplus
    float x, y;
} VECTOR2;

//=============================================================================
//	class VECTOR3
//=============================================================================
#ifdef __cplusplus
typedef struct VECTOR3 : public VECTOR
{
public:
	VECTOR3() {};
	VECTOR3(const float *vec) { x = *vec; vec++; y = *vec; vec++; z = *vec; }
	VECTOR3(const VECTOR3& vec) { x = vec.x; y = vec.y; z = vec.z;}		// copy constructor
	VECTOR3(float nx, float ny, float nz) { x = nx; y = ny; z = nz; }	// initialize on value
	
	// casting(�L���X�g���Z�q(������))
	//operator float* ();
	//operator const float* () const;

	// assignment operators(������Z�q)
	VECTOR3& operator = (const VECTOR3& vec) { x = vec.x; y = vec.y; z = vec.z;	return *this; }		// assign
	VECTOR3& operator += (const VECTOR3& vec) { x += vec.x; y += vec.y; z += vec.z; return *this; }	// addition and assign(���Z���)
	VECTOR3& operator -= (const VECTOR3& vec) { x -= vec.x; y -= vec.y; z -= vec.z; return *this; }	// subtraction and assign(���Z���)
	VECTOR3& operator *= (float pow) { x *= pow; y *= pow; z *= pow; return *this; }				// multiplication and assign(��Z���)
	VECTOR3& operator /= (float pow) { if(pow != 0) { x /= pow; y /= pow; z /= pow; return *this; }
										else{ x = 0.0f; y = 0.0f; z = 0.0f; return *this; }}		// division and assign(���Z���)

	// unary operators(�P�����Z�q)
	//VECTOR3 operator + () const;
	VECTOR3 operator - () const{ return VECTOR3(-x, -y, -z); }

	// binary operators(�񍀉��Z�q)
	VECTOR3 operator + (const VECTOR3& vec) const { return VECTOR3((x + vec.x), (y + vec.y), (z + vec.z)); }	// addition(���Z)
	VECTOR3 operator - (const VECTOR3& vec) const { return VECTOR3((x - vec.x), (y - vec.y), (z - vec.z)); }	// subtraction(���Z)
	VECTOR3 operator * (float pow) const { return VECTOR3((x * pow), (y * pow), (z * pow)); }					// multiplication(��Z)
	VECTOR3 operator / (float pow) const { return (pow != 0) ? VECTOR3((x / pow), (y / pow), (z / pow)) : VECTOR3(0.0f, 0.0f, 0.0f); } // division(���Z)

	friend VECTOR3 operator * (float pow, const struct VECTOR3& vec) { return VECTOR3((vec.x * pow), (vec.y * pow), (vec.z * pow)); }
	
	// logical operators(�_�����Z�q)
	bool operator == (const VECTOR3& vec) const { return ((x == vec.x) && (y == vec.y) && (z == vec.z)); }	// logical operation of equal(��v)
	bool operator != (const VECTOR3& vec) const { return ((x != vec.x) || (y != vec.y) || (z != vec.z)); }	// logical operation of not equal(�s��v)
	
	// vector magnitude(�x�N�g���̑傫��)
	float magnitude() const { return sqrt((x * x) + (y * y) + (z * z)); }

	// vector normalizing(�x�N�g���̐��K��)
	VECTOR3& normalize() { float mag = magnitude(); if(mag > 0.0f) { x /= mag; y /= mag; z /= mag; } return *this; }

	// memory zero sets(������������)
    inline void zeromem(void) { x = 0.0f; y = 0.0f; z = 0.0f; }

	// distance of 2 points(2�̃x�N�g���̋���)
    static inline float distance(const VECTOR3 &a, const VECTOR3 &b) { return (a - b).magnitude(); }

	// distance of 2 points(�_a����_b�ւ�3D�x�N�g��)
	static inline VECTOR3 arrow(const VECTOR3 &a, const VECTOR3 &b) { return VECTOR3((b.x - a.x), (b.y - a.y), (b.z - a.z)); }

	// dot product of 3D(3D�̓���)
    static inline float dot(const VECTOR3 &a, const VECTOR3 &b) { return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z)); }

	// cross product of 3D(3D�̊O��)
    static inline VECTOR3 cross(const VECTOR3 &a, const VECTOR3 &b) { return VECTOR3((a.y * b.z - a.z * b.y), (a.z * b.x - a.x * b.z), (a.x * b.y - a.y * b.x)); }

} VECTOR3;
#else //!__cplusplus
typedef struct _VECTOR VECTOR3;
#endif //!__cplusplus


//=============================================================================
//	class VECTOR4
//=============================================================================
#ifdef __cplusplus
typedef struct VECTOR4
{
public:
	VECTOR4() {};
	VECTOR4(const float *vec) { x = *vec; vec++; y = *vec; vec++; z = *vec; vec++; w = *vec; }
	VECTOR4(const VECTOR4& vec) { x = vec.x; y = vec.y; z = vec.z; w = vec.w;}				// copy constructor
	VECTOR4(float nx, float ny, float nz, float nw) { x = nx; y = ny; z = nz; w = nw; }		// initialize on value

	// casting(�L���X�g���Z�q(������))
	//operator float* ();
	//operator const float* () const;

	// assignment operators(������Z�q)
	VECTOR4& operator = (const VECTOR4& vec) { x=vec.x; y=vec.y; z=vec.z; w=vec.w;	return *this; }		// assign
	VECTOR4& operator += (const VECTOR4& vec) { x+=vec.x; y+=vec.y; z+=vec.z; w+=vec.w; return *this; }	// addition and assign(���Z���)
	VECTOR4& operator -= (const VECTOR4& vec) { x-=vec.x; y-=vec.y; z-=vec.z; w-=vec.w; return *this; }	// subtraction and assign(���Z���)
	VECTOR4& operator *= (float pow) { x*=pow; y*=pow; z*=pow; w*=pow; return *this; }					// multiplication and assign(��Z���)
	VECTOR4& operator /= (float pow) {
		if(pow != 0) { x /= pow; y /= pow; z /= pow; w /= pow; return *this; }
		else { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; return *this; }
	}		// division and assign(���Z���)

	// unary operators(�P�����Z�q)
	//VECTOR4 operator + () const;
	VECTOR4 operator - () const { return VECTOR4(-x, -y, -z, -w); }

	// binary operators(�񍀉��Z�q)
	VECTOR4 operator + (const VECTOR4& vec) const { return VECTOR4((x+vec.x), (y+vec.y), (z+vec.z), (w+vec.w)); }	// addition(���Z)
	VECTOR4 operator - (const VECTOR4& vec) const { return VECTOR4((x-vec.x), (y-vec.y), (z-vec.z), (w-vec.w)); }	// subtraction(���Z)
	VECTOR4 operator * (float pow) const { return VECTOR4((x * pow), (y * pow), (z * pow), (w * pow)); }			// multiplication(��Z)
	VECTOR4 operator / (float pow) const { return (pow!=0) ? VECTOR4((x/pow), (y/pow), (z/pow), (w/pow)) : VECTOR4(0.0f, 0.0f, 0.0f, 0.0f); } // division(���Z)

	friend VECTOR4 operator * (float pow, const struct VECTOR4& vec) { return VECTOR4((vec.x*pow), (vec.y*pow), (vec.z*pow), (vec.w*pow)); }

	// logical operators(�_�����Z�q)
	bool operator == (const VECTOR4& vec) const { return ((x==vec.x) && (y==vec.y) && (z==vec.z) && (w==vec.w)); }	// logical operation of equal(��v)
	bool operator != (const VECTOR4& vec) const { return ((x!=vec.x) || (y!=vec.y) || (z!=vec.z) || (z!=vec.z)); }	// logical operation of not equal(�s��v)

	// vector magnitude(�x�N�g���̑傫��)
	float magnitude() const { return sqrt((x * x) + (y * y) + (z * z) + (w * w)); }

	// vector normalizing(�x�N�g���̐��K��)
	VECTOR4& normalize() { float mag = magnitude(); if(mag > 0.0f) { x /= mag; y /= mag; z /= mag; w /= mag; } return *this; }

	// memory zero sets(������������)
	inline void zeromem(void) { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; }
		
public:
#endif //__cplusplus
	float x, y, z, w;
} VECTOR4;

#define	VEC2_ZERO			(VECTOR2(0.0f, 0.0f))				// 2D�x�N�g����0
#define	VEC3_ZERO			(VECTOR3(0.0f, 0.0f, 0.0f))			// 3D�x�N�g����0
#define	VEC4_ZERO			(VECTOR4(0.0f, 0.0f, 0.0f, 0.0f))	// 4D�x�N�g����0

#endif