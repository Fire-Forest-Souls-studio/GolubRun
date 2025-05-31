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
		static PC_Mouse* m_class_obj;

		PC_Mouse ();

		RectangleShape m_rectangle_shape;

		Vector2f m_V2f_mouse_size;

		unsigned m_u_outline_scale;

		string m_string;

		Mouse m_mouse;

		Color m_color;
		Color m_color_null;

		float m_f_font_scale;
		float m_f_lifting_text;
		float m_f_time_since_clic;

		Text m_text;

		bool m_b_double_pressed;
		bool m_b_pressed;

	public:
		static PC_Mouse* getClass ();

		static void main ();

		static FloatRect getGlobalBounds ();

		static Text getTextBox ();

		static RectangleShape getHitBox ();

		static bool isLeftPressed ();
};

#endif
