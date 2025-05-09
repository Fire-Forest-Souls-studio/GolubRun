#include "../../includes/Classes/button.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/pc_mouse.h"

Button::Button () :
		C_outline (Color (0, 0, 0, 0.0))
{
}

Button::Button (const string& s) :
		C_outline (Color (0, 0, 0, 0.0))
{
	text_obj.setString (s);
	text_obj.setCharacterSize (names::f_font_hitbox_scale);
	text_obj.setFont (names::F_pixel);
	text_obj.setFillColor (names::C_font_hitbox);
	rectangle_shape_obj.setOutlineColor (names::C_font_hitbox);
	rectangle_shape_obj.setOutlineThickness (1);
}

void Button::setSize (const Vector2f& V2f)
{
	rectangle_shape_obj.setSize (V2f);
}

void Button::setFillColor (const Color& C)
{
	rectangle_shape_obj.setFillColor (C);
}

void Button::setScale (const float& f)
{
	rectangle_shape_obj.setScale (f, f);
	if (names::b_hitboxes_is_drawn)
	{
		rectangle_shape_obj.setOutlineThickness (1);
		rectangle_shape_obj.setOutlineColor (names::C_font_hitbox);
		text_obj.setCharacterSize (f * names::f_font_hitbox_scale);
	}
	else if (C_outline.a == 0.0)
	{
		rectangle_shape_obj.setOutlineThickness (0.0);
		text_obj.setCharacterSize (0);
	}
	else
	{
		rectangle_shape_obj.setOutlineThickness (1);
		rectangle_shape_obj.setOutlineColor (C_outline);
		text_obj.setCharacterSize (0);
	}
}

void Button::setPosition (const float& fx, const float& fy)
{
	rectangle_shape_obj.setPosition (fx, fy);
	text_obj.setPosition (fx + rectangle_shape_obj.getGlobalBounds ().width * 0.5 - text_obj.getGlobalBounds ().width * 0.5,
			fy - text_obj.getGlobalBounds ().height * names::f_lifting_hitbox_text);
}

void Button::setString (const string& s)
{
	text_obj.setString (s);
	text_obj.setCharacterSize (names::f_font_hitbox_scale);
	text_obj.setFont (names::F_pixel);
	text_obj.setFillColor (names::C_font_hitbox);
	rectangle_shape_obj.setOutlineColor (names::C_font_hitbox);
	rectangle_shape_obj.setOutlineThickness (1);
}

FloatRect Button::getGlobalBounds ()
{
	return rectangle_shape_obj.getGlobalBounds ();
}

const RectangleShape& Button::getRectangleShape () const
{
	return rectangle_shape_obj;
}

const Text& Button::getText () const
{
	return text_obj;
}

bool Button::interect () const
{
	return PC_Mouse::getGlobalBounds ().intersects (rectangle_shape_obj.getGlobalBounds ());
}

bool Button::pressed () const
{
	return (PC_Mouse::getGlobalBounds ().intersects (rectangle_shape_obj.getGlobalBounds ())
			and PC_Mouse::isLeftPressed ());
}

void Button::setOutline (const Color& C)
{
	C_outline = C;
}
