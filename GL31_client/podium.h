#ifndef _PODIUM_H_
#define _PODIUM_H_

class CPodium : public CSquare
{
	public:
		CPodium( bool ifListAdd = true, int priority = PRIORITY_WALL, OBJTYPE objType = OBJTYPE_NONE);
		~CPodium();

		void Init(VECTOR3 pos , VECTOR3 size, char* TexName, VECTOR4 color);

		static CPodium *Create(VECTOR3 pos , VECTOR3 size, char* TexName = "", VECTOR4 color = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	private:
		VECTOR3 m_Pos;


};


#endif