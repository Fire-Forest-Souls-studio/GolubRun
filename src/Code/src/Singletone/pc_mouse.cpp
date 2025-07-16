#include "../../includes/Singletone/pc_mouse.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"

PC_Mouse* PC_Mouse::m_class_obj = 0;

PC_Mouse::PC_Mouse ()
    : m_V2f_mouse_size (1, 2),

      m_u_outline_scale (1),

      m_string ("PCM/hitbox/mouse"),

      m_color (names::C_font_hitbox),
      m_color_null (0, 0, 0, 0),

      m_f_font_scale (names::f_font_hitbox_scale),
      m_f_lifting_text (names::f_lifting_hitbox_text),
      m_f_time_since_clic (0.0),

      m_text (m_string, names::font, m_f_font_scale),

      m_b_double_pressed (false),
      m_b_pressed (false)

{
	m_rectangle_shape.setSize (m_V2f_mouse_size);
	m_rectangle_shape.setFillColor (m_color_null);
	m_rectangle_shape.setOutlineThickness (m_u_outline_scale);
	m_rectangle_shape.setOutlineColor (m_color);

	m_text.setFillColor (m_color);
}

PC_Mouse* PC_Mouse::getClass ()
{
	if (m_class_obj != 0)
		return m_class_obj;

	m_class_obj = new PC_Mouse ();
	return m_class_obj;
}

void PC_Mouse::main ()
{
	PC_Mouse* PCM_ = getClass ();
	Window& W_ = WindowAndStyles::getWindow ();
	float f = WindowAndStyles::getFactorY ();

	PCM_->m_rectangle_shape.setPosition (PCM_->m_mouse.getPosition (W_).x,
	                                       PCM_->m_mouse.getPosition (W_).y);
	PCM_->m_rectangle_shape.setScale (f, f);

	PCM_->m_text.setCharacterSize (PCM_->m_f_font_scale * f);
	PCM_->m_text.setPosition (PCM_->m_rectangle_shape.getPosition ().x + PCM_->m_rectangle_shape.getGlobalBounds ().width * 0.5 - PCM_->m_text.getGlobalBounds ().width * 0.5,
	                            PCM_->m_rectangle_shape.getPosition ().y - PCM_->m_text.getGlobalBounds ().height * PCM_->m_f_lifting_text);

	if (Mouse::isButtonPressed (Mouse::Left))
	{
		if (!PCM_->m_b_double_pressed)
		{
			PCM_->m_b_pressed = true;
			PCM_->m_b_double_pressed = true;
		}
		else
		{
			PCM_->m_b_pressed = false;
		}
	}
	else
	{
		PCM_->m_b_pressed = false;
		PCM_->m_b_double_pressed = false;
	}
	PCM_->m_f_time_since_clic += names::f_microsec * names::f_time;
}

FloatRect PC_Mouse::getGlobalBounds ()
{
	return getClass ()->m_rectangle_shape.getGlobalBounds ();
}

Text PC_Mouse::getTextBox ()
{
	return getClass ()->m_text;
}

RectangleShape PC_Mouse::getHitBox ()
{
	return getClass ()->m_rectangle_shape;
}

bool PC_Mouse::isLeftPressed ()
{
	PC_Mouse* PCM_ = getClass ();

	if (PCM_->m_b_pressed and PCM_->m_f_time_since_clic > 0.5)
	{
		PCM_->m_f_time_since_clic = 0.0;
		return true;
	}
	else
	{
		return false;
	}
}
