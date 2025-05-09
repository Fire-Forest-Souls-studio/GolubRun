#ifndef MOUSE_H_
#define MOUSE_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class PC_Mouse
{

	private:

		static PC_Mouse* class_obj;

		PC_Mouse ();

		RectangleShape rectangle_shape_obj;

		Vector2f V2f_mouse_size;

		unsigned u_outline_scale;

		string string_obj;

		Mouse mouse_obj;

		Color color_obj;
		Color color_null;

		float f_font_scale;
		float f_lifting_text;
		float f_time_since_clic;

		Text text_obj;

		bool b_double_pressed;
		bool b_pressed;

	public:

		static PC_Mouse* getClass ();

		static void main ();

		static FloatRect getGlobalBounds ();

		static Text getTextBox ();

		static RectangleShape getHitBox ();

		static bool isLeftPressed ();

};

#endif
