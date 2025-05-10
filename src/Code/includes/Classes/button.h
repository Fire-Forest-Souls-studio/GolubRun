#ifndef CODE_BUTTON_H_
#define CODE_BUTTON_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Button
{
		// TODO: рефакторинг переменный по шаблону <m_TyPe_my_name>
		// TODO: добавить названия аргументам функций по шаблону <my_name>

	protected:
		RectangleShape rectangle_shape_obj;

		Text text_obj;

		Color C_outline;

	public:
		Button ();
		Button (const string&);

		void setSize (const Vector2f&);
		void setFillColor (const Color&);
		void setScale (const float&);
		void setPosition (const float&, const float&);
		void setString (const string&);
		void setOutline (const Color&);

		FloatRect getGlobalBounds ();

		const RectangleShape& getRectangleShape () const;

		const Text& getText () const;

		bool interect () const;
		bool pressed () const;
};

#endif
