#ifndef _SQUARE_H_
#define _SQUARE_H_

typedef struct
{
		VECTOR3 pos;
		float rot;

}RANKING;

class CSquare : public CScene3DGL
{
	public:
		CSquare( bool ifListAdd = true, int priority = PRIORITY_WALL, OBJTYPE objType = OBJTYPE_NONE);
		~CSquare();

		void Init(VECTOR3 pos , VECTOR3 size, char* TexName, VECTOR4 color);
		void Draw(void);
		void Uninit(bool isLast = false);
		

		static CSquare *Create(VECTOR3 pos , VECTOR3 size, char* TexName = "", VECTOR4 color = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	private:
		//VECTOR3 m_pos;

		VECTOR4 m_Color;
		RANKING m_Ranking;
		//float	m_rot;

		int m_Texture;

		MATRIX	m_mtxWorld; // ワールドマトリックス


};


#endif