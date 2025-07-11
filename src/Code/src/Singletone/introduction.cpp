#include "../../includes/Singletone/introduction.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"

#include "../../../GetPixels/GPI_Introduction.h"

Introduction* Introduction::m_class_obj = 0;
vector<Texture> Introduction::m_texture = vector<Texture> (3);
vector<unsigned> Introduction::m_u_frames = vector<unsigned> (3);
vector<unsigned> Introduction::m_u_frames_vertical = vector<unsigned> (3);
vector<float> Introduction::m_f_animation_speed = vector<float> (3);
RectangleShape Introduction::m_rectangle_shape = RectangleShape (Vector2f (300.0, 150.0));
float Introduction::m_f_frame = 0.0;

Introduction* Introduction::getClass ()
{
	if (m_class_obj != 0)
		return m_class_obj;

	m_class_obj = new Introduction ();
	return m_class_obj;
}

Introduction::Introduction ()
{
	m_u_frames[0] = 42;
	m_u_frames_vertical[0] = 8;
	m_f_animation_speed[0] = 15.0;
	m_u_frames[1] = 108;
	m_u_frames_vertical[1] = 14;
	m_f_animation_speed[1] = 7.5;
	m_u_frames[2] = 53;
	m_u_frames_vertical[2] = 9;
	m_f_animation_speed[2] = 7.5;
}

void Introduction::start ()
{
    getClass();
	names::LoadFromMemory (m_texture[0], introductiion0, introductiion0_size, "Images/Introduction/introduction0.png");
	names::LoadFromMemory (m_texture[1], introductiion1, introductiion1_size, "Images/Introduction/introduction1.png");
	names::LoadFromMemory (m_texture[2], introductiion2, introductiion2_size, "Images/Introduction/introduction2.png");
	m_rectangle_shape.setTexture (&m_texture[0]);
	m_rectangle_shape.setTextureRect (IntRect (0, 0, m_rectangle_shape.getSize ().x, m_rectangle_shape.getSize ().y));
}

void Introduction::main ()
{
	m_f_frame += m_f_animation_speed[0] * names::f_microsec * names::f_time;
	m_rectangle_shape.setScale (WindowAndStyles::getFactorY (), WindowAndStyles::getFactorY ());
    names::SetXCenterPosition(m_rectangle_shape, 0.0);
}

const RectangleShape& Introduction::getRender ()
{
	return m_rectangle_shape;
}
