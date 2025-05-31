#ifndef CODE_WINDOW_AND_STYLES_H_
#define CODE_WINDOW_AND_STYLES_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

#include "../../includes/Classes/button.h"

using namespace sf;
using namespace std;

// start

enum StyleWindow
{
	Default = 0, // 0
	Fullscreen   // 1
};

class WindowAndStyles
{
	private:
		static WindowAndStyles* m_class_obj;

		WindowAndStyles ();

		Vector2f f_size_pix;

		RectangleShape rectangle_shape_obj;

		RenderWindow window_obj;

		RenderTexture render_texture_obj;

		StyleWindow now;

		VideoMode videomode_obj;

		View camera;

		float m_f_time_since_clicking;

		wstring w_game_name;

		Color C_defolt_window;
		Color C_clear_color;

		Image image_obj;

		static void main_time_work ();
		static void main_F11 ();
		static void main_event ();
		static void clear_clear ();
		static void clear_rectangle ();
		static void clear_draw ();
		static void clear_display ();
		static void main_destroy ();
		static void draw (const Button&);

	protected:
		static WindowAndStyles* getClass ();

	public:
		static void start ();
		static void main ();
		static void clear ();
		static void setColor (Color);
		static void close ();

		static bool isOpen ();
		static bool hasFocus ();

		static float getFactorX ();
		static float getFactorY ();
		static float getPixelsSizeX ();
		static float getPixelsSizeY ();

		static Window& getWindow ();

		static FloatRect getGlobalBounds ();

		static Color getDefoultColor ();
};

#endif /* WINDOW_AND_STYLES_H_ */
