#ifndef _VECTOR_H_
#define _VECTOR_H_
//=============================================================================
//
//	タイトル	ベクトル演算子
//	ファイル名	vector.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/05/26
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
	VECTOR2(const float *vec) { x = *vec; vec++; y = *vec; }	// initialize of array(配列(ポインタ)で初期化)
	VECTOR2(float nx, float ny) { x = nx; y = ny; }				// initialize of value(値で初期化)

	// casting(キャスト演算子(未実装))
	//operator float* ();
	//operator const float* () const;

	// assignment operators(代入演算子)
	VECTOR2& operator = (const VECTOR2& vec) { x = vec.x; y = vec.y;	return *this; }		// assign
	VECTOR2& operator += (const VECTOR2& vec) { x += vec.x; y += vec.y; return *this; }		// addition and assign
	VECTOR2& operator -= (const VECTOR2& vec) { x -= vec.x; y -= vec.y; return *this; }		// subtraction and assign
	VECTOR2& operator *= (float pow) { x *= pow; y *= pow; return *this; }					// multiplication and assign
	VECTOR2& operator /= (float pow) { if(pow != 0) { x /= pow; y /= pow; return *this; }
										else{ x = 0.0f; y = 0.0f; return *this; }}			// division and assign

	// unary operators(単項演算子)
	// VECTOR2 operator + () const;
	VECTOR2 operator - () const { return VECTOR2(-x, -y); }
	
	// binary operators(二項演算子)
	VECTOR2 operator + (const VECTOR2& vec) const { return VECTOR2((x + vec.x), (y + vec.y)); }	// addition
	VECTOR2 operator - (const VECTOR2& vec) const { return VECTOR2((x - vec.x), (y - vec.y)); }	// subtraction 
	VECTOR2 operator * (float pow) const { return VECTOR2((x * pow), (y * pow)); }				// multiplication
	VECTOR2 operator / (float pow) const { return (pow != 0) ? VECTOR2((x / pow), (y / pow)) : VECTOR2(0.0f, 0.0f); } // division

	friend VECTOR2 operator * (float pow, const struct VECTOR2& vec) { return VECTOR2((vec.x * pow), (vec.y * pow)); }
	
	// logical operators(論理演算子)
	bool operator == (const VECTOR2& vec) const{ return ((x == vec.x) && (y == vec.y)); }	// logical operation of equal
	bool operator != (const VECTOR2& vec) const{ return ((x != vec.x) || (y != vec.y)); }	// logical operation of not equal
	
	// vector magnitude(ベクトルの大きさ)
	float magnitude() const { return sqrt((x * x) + (y * y)); }

	// vector normalizing(ベクトルの正規化)
	VECTOR2& normalize() { float mag = magnitude(); if(mag > 0.0f) { x /= mag; y /= mag; } return *this; }

	// distance of 2 points(2つのベクトルの距離)
    static inline float distance(const VECTOR2 &a, const VECTOR2 &b) { return (a - b).magnitude(); }

	// distance of 2 points(点aから点bへの2Dベクトル)
	static inline VECTOR2 arrow(const VECTOR2 &a, const VECTOR2 &b) { return VECTOR2((b.x - a.x), (b.y - a.y)); }
	
	// dot product of 2D(2Dの内積)
	static inline float dot(const VECTOR2 &a, const VECTOR2 &b) { return ((a.x * b.x) + (a.y * b.y)); }

	// cross product of 2D(2Dの外積)
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
	
	// casting(キャスト演算子(未実装))
	//operator float* ();
	//operator const float* () const;

	// assignment operators(代入演算子)
	VECTOR3& operator = (const VECTOR3& vec) { x = vec.x; y = vec.y; z = vec.z;	return *this; }		// assign
	VECTOR3& operator += (const VECTOR3& vec) { x += vec.x; y += vec.y; z += vec.z; return *this; }	// addition and assign(加算代入)
	VECTOR3& operator -= (const VECTOR3& vec) { x -= vec.x; y -= vec.y; z -= vec.z; return *this; }	// subtraction and assign(減算代入)
	VECTOR3& operator *= (float pow) { x *= pow; y *= pow; z *= pow; return *this; }				// multiplication and assign(乗算代入)
	VECTOR3& operator /= (float pow) { if(pow != 0) { x /= pow; y /= pow; z /= pow; return *this; }
										else{ x = 0.0f; y = 0.0f; z = 0.0f; return *this; }}		// division and assign(除算代入)

	// unary operators(単項演算子)
	//VECTOR3 operator + () const;
	VECTOR3 operator - () const{ return VECTOR3(-x, -y, -z); }

	// binary operators(二項演算子)
	VECTOR3 operator + (const VECTOR3& vec) const { return VECTOR3((x + vec.x), (y + vec.y), (z + vec.z)); }	// addition(加算)
	VECTOR3 operator - (const VECTOR3& vec) const { return VECTOR3((x - vec.x), (y - vec.y), (z - vec.z)); }	// subtraction(減算)
	VECTOR3 operator * (float pow) const { return VECTOR3((x * pow), (y * pow), (z * pow)); }					// multiplication(乗算)
	VECTOR3 operator / (float pow) const { return (pow != 0) ? VECTOR3((x / pow), (y / pow), (z / pow)) : VECTOR3(0.0f, 0.0f, 0.0f); } // division(除算)

	friend VECTOR3 operator * (float pow, const struct VECTOR3& vec) { return VECTOR3((vec.x * pow), (vec.y * pow), (vec.z * pow)); }
	
	// logical operators(論理演算子)
	bool operator == (const VECTOR3& vec) const { return ((x == vec.x) && (y == vec.y) && (z == vec.z)); }	// logical operation of equal(一致)
	bool operator != (const VECTOR3& vec) const { return ((x != vec.x) || (y != vec.y) || (z != vec.z)); }	// logical operation of not equal(不一致)
	
	// vector magnitude(ベクトルの大きさ)
	float magnitude() const { return sqrt((x * x) + (y * y) + (z * z)); }

	// vector normalizing(ベクトルの正規化)
	VECTOR3& normalize() { float mag = magnitude(); if(mag > 0.0f) { x /= mag; y /= mag; z /= mag; } return *this; }

	// memory zero sets(メモリ初期化)
    inline void zeromem(void) { x = 0.0f; y = 0.0f; z = 0.0f; }

	// distance of 2 points(2つのベクトルの距離)
    static inline float distance(const VECTOR3 &a, const VECTOR3 &b) { return (a - b).magnitude(); }

	// distance of 2 points(点aから点bへの3Dベクトル)
	static inline VECTOR3 arrow(const VECTOR3 &a, const VECTOR3 &b) { return VECTOR3((b.x - a.x), (b.y - a.y), (b.z - a.z)); }

	// dot product of 3D(3Dの内積)
    static inline float dot(const VECTOR3 &a, const VECTOR3 &b) { return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z)); }

	// cross product of 3D(3Dの外積)
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

	// casting(キャスト演算子(未実装))
	//operator float* ();
	//operator const float* () const;

	// assignment operators(代入演算子)
	VECTOR4& operator = (const VECTOR4& vec) { x=vec.x; y=vec.y; z=vec.z; w=vec.w;	return *this; }		// assign
	VECTOR4& operator += (const VECTOR4& vec) { x+=vec.x; y+=vec.y; z+=vec.z; w+=vec.w; return *this; }	// addition and assign(加算代入)
	VECTOR4& operator -= (const VECTOR4& vec) { x-=vec.x; y-=vec.y; z-=vec.z; w-=vec.w; return *this; }	// subtraction and assign(減算代入)
	VECTOR4& operator *= (float pow) { x*=pow; y*=pow; z*=pow; w*=pow; return *this; }					// multiplication and assign(乗算代入)
	VECTOR4& operator /= (float pow) {
		if(pow != 0) { x /= pow; y /= pow; z /= pow; w /= pow; return *this; }
		else { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; return *this; }
	}		// division and assign(除算代入)

	// unary operators(単項演算子)
	//VECTOR4 operator + () const;
	VECTOR4 operator - () const { return VECTOR4(-x, -y, -z, -w); }

	// binary operators(二項演算子)
	VECTOR4 operator + (const VECTOR4& vec) const { return VECTOR4((x+vec.x), (y+vec.y), (z+vec.z), (w+vec.w)); }	// addition(加算)
	VECTOR4 operator - (const VECTOR4& vec) const { return VECTOR4((x-vec.x), (y-vec.y), (z-vec.z), (w-vec.w)); }	// subtraction(減算)
	VECTOR4 operator * (float pow) const { return VECTOR4((x * pow), (y * pow), (z * pow), (w * pow)); }			// multiplication(乗算)
	VECTOR4 operator / (float pow) const { return (pow!=0) ? VECTOR4((x/pow), (y/pow), (z/pow), (w/pow)) : VECTOR4(0.0f, 0.0f, 0.0f, 0.0f); } // division(除算)

	friend VECTOR4 operator * (float pow, const struct VECTOR4& vec) { return VECTOR4((vec.x*pow), (vec.y*pow), (vec.z*pow), (vec.w*pow)); }

	// logical operators(論理演算子)
	bool operator == (const VECTOR4& vec) const { return ((x==vec.x) && (y==vec.y) && (z==vec.z) && (w==vec.w)); }	// logical operation of equal(一致)
	bool operator != (const VECTOR4& vec) const { return ((x!=vec.x) || (y!=vec.y) || (z!=vec.z) || (z!=vec.z)); }	// logical operation of not equal(不一致)

	// vector magnitude(ベクトルの大きさ)
	float magnitude() const { return sqrt((x * x) + (y * y) + (z * z) + (w * w)); }

	// vector normalizing(ベクトルの正規化)
	VECTOR4& normalize() { float mag = magnitude(); if(mag > 0.0f) { x /= mag; y /= mag; z /= mag; w /= mag; } return *this; }

	// memory zero sets(メモリ初期化)
	inline void zeromem(void) { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; }
		
public:
#endif //__cplusplus
	float x, y, z, w;
} VECTOR4;

#define	VEC2_ZERO			(VECTOR2(0.0f, 0.0f))				// 2Dベクトルの0
#define	VEC3_ZERO			(VECTOR3(0.0f, 0.0f, 0.0f))			// 3Dベクトルの0
#define	VEC4_ZERO			(VECTOR4(0.0f, 0.0f, 0.0f, 0.0f))	// 4Dベクトルの0

#endif