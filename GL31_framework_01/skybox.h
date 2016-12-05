#ifndef _SKYBOX_H_
#define _SKYBOX_H_

class CSkybox : public CScene3DGL
{
	public:
		CSkybox(int priority = 1, OBJTYPE objType = OBJTYPE_NONE);
		~CSkybox();

		void Init(void);
		void Update(void);
		void Draw(void);
		void Uninit(bool isLast = false);

		static CSkybox *Create(void);

	private:

		VECTOR3 m_pos;
		float	m_rot;
		int m_Texture;

		MATRIX	m_mtxWorld; // ワールドマトリックス


};


#endif