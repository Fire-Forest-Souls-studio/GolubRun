#include "../../includes/Singletone/pc_mouse.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"

PC_Mouse* PC_Mouse::class_obj = 0;

PC_Mouse::PC_Mouse () :
		V2f_mouse_size (1, 2),

		u_outline_scale (1),

		string_obj ("PCM/hitbox/mouse"),

		color_obj (names::C_font_hitbox),
				color_null (0, 0, 0, 0),

				f_font_scale (names::f_font_hitbox_scale),
				f_lifting_text (names::f_lifting_hitbox_text),
				f_time_since_clic (0.0),

				text_obj (string_obj, names::F_pixel, f_font_scale),

				b_double_pressed (false),
				b_pressed (false)

{
	rectangle_shape_obj.setSize (V2f_mouse_size);
	rectangle_shape_obj.setFillColor (color_null);
	rectangle_shape_obj.setOutlineThickness (u_outline_scale);
	rectangle_shape_obj.setOutlineColor (color_obj);

	text_obj.setFillColor (color_obj);

}

PC_Mouse* PC_Mouse::getClass ()
{
	if (class_obj != 0)
		return class_obj;

	class_obj = new PC_Mouse ();
	return class_obj;
}

void PC_Mouse::main ()
{
	PC_Mouse* PCM_ = getClass ();
	Window& W_ = WindowAndStyles::getWindow ();
	float f = WindowAndStyles::getFactorY ();

	PCM_->rectangle_shape_obj.setPosition (PCM_->mouse_obj.getPosition (W_).x,
			PCM_->mouse_obj.getPosition (W_).y);
	PCM_->rectangle_shape_obj.setScale (f, f);

	PCM_->text_obj.setCharacterSize (PCM_->f_font_scale * f);
	PCM_->text_obj.setPosition (PCM_->rectangle_shape_obj.getPosition ().x + PCM_->rectangle_shape_obj.getGlobalBounds ().width * 0.5 - PCM_->text_obj.getGlobalBounds ().width * 0.5,
			PCM_->rectangle_shape_obj.getPosition ().y - PCM_->text_obj.getGlobalBounds ().height * PCM_->f_lifting_text);

	if (Mouse::isButtonPressed (Mouse::Left))
	{
		if (!PCM_->b_double_pressed)
		{
			PCM_->b_pressed = true;
			PCM_->b_double_pressed = true;
		}
		else
		{
			PCM_->b_pressed = false;
		}
	}
	else
	{
		PCM_->b_pressed = false;
		PCM_->b_double_pressed = false;
	}
	PCM_->f_time_since_clic += names::microsec * names::f_time;
}

FloatRect PC_Mouse::getGlobalBounds ()
{
	return getClass ()->rectangle_shape_obj.getGlobalBounds ();
}

Text PC_Mouse::getTextBox ()
{
	return getClass ()->text_obj;
}

RectangleShape PC_Mouse::getHitBox ()
{
	return getClass ()->rectangle_shape_obj;
}

bool PC_Mouse::isLeftPressed ()
{
	PC_Mouse* PCM_ = getClass ();

	if (PCM_->b_pressed and PCM_->f_time_since_clic > 0.5)
	{
		PCM_->f_time_since_clic = 0.0;
		return true;
	}
	else
	{
		return false;
	}
}
