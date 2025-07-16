#include "../../includes/Classes/button.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/pc_mouse.h"

Button::Button ()
    : m_C_outline (Color (0, 0, 0, 0.0))
{
}

Button::Button (const string& s)
    : m_C_outline (Color (0, 0, 0, 0.0))
{
	m_text.setString (s);
	m_text.setCharacterSize (names::f_font_hitbox_scale);
	m_text.setFont (names::font);
	m_text.setFillColor (names::C_font_hitbox);
	m_rectangle_shape.setOutlineColor (names::C_font_hitbox);
	m_rectangle_shape.setOutlineThickness (1);
}

void Button::setSize (const Vector2f& V2f)
{
	m_rectangle_shape.setSize (V2f);
}

void Button::setFillColor (const Color& C)
{
	m_rectangle_shape.setFillColor (C);
}

void Button::setScale (const float& f)
{
	m_rectangle_shape.setScale (f, f);
	if (names::b_hitboxes_is_drawn)
	{
		m_rectangle_shape.setOutlineThickness (1);
		m_rectangle_shape.setOutlineColor (names::C_font_hitbox);
		m_text.setCharacterSize (f * names::f_font_hitbox_scale);
	}
	else if (m_C_outline.a == 0.0)
	{
		m_rectangle_shape.setOutlineThickness (0.0);
		m_text.setCharacterSize (0);
	}
	else
	{
		m_rectangle_shape.setOutlineThickness (1);
		m_rectangle_shape.setOutlineColor (m_C_outline);
		m_text.setCharacterSize (0);
	}
}

void Button::setPosition (const float& fx, const float& fy)
{
	m_rectangle_shape.setPosition (fx, fy);
	m_text.setPosition (fx + m_rectangle_shape.getGlobalBounds ().width * 0.5 - m_text.getGlobalBounds ().width * 0.5,
	                      fy - m_text.getGlobalBounds ().height * names::f_lifting_hitbox_text);
}

void Button::setString (const string& s)
{
	m_text.setString (s);
	m_text.setCharacterSize (names::f_font_hitbox_scale);
	m_text.setFont (names::font);
	m_text.setFillColor (names::C_font_hitbox);
	m_rectangle_shape.setOutlineColor (names::C_font_hitbox);
	m_rectangle_shape.setOutlineThickness (1);
}

FloatRect Button::getGlobalBounds ()
{
	return m_rectangle_shape.getGlobalBounds ();
}

const RectangleShape& Button::getRectangleShape () const
{
	return m_rectangle_shape;
}

const Text& Button::getText () const
{
	return m_text;
}

bool Button::interect () const
{
	return PC_Mouse::getGlobalBounds ().intersects (m_rectangle_shape.getGlobalBounds ());
}

bool Button::pressed () const
{
	return (PC_Mouse::getGlobalBounds ().intersects (m_rectangle_shape.getGlobalBounds ()) and PC_Mouse::isLeftPressed ());
}

void Button::setOutline (const Color& C)
{
	m_C_outline = C;
}
