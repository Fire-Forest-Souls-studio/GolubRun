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
		static WindowAndStyles* getClass ();

		WindowAndStyles ();

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
		Vector2f m_V2f_size_pix;
		RectangleShape m_rectangle_shape;
		RenderWindow m_window;
		RenderTexture m_render_texture;
		StyleWindow m_SW_now;
		VideoMode m_videomode;
		View m_V_camera;
		float m_f_time_since_clicking;
		wstring m_w_game_name;
		Color m_C_defolt_window;
		Color m_C_clear_color;
		Image m_image;
        Shader m_shader;

	public:
		static void start ();
		static void main ();
		static void clear ();
		static void setColor (Color color);
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
