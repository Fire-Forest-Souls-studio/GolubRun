#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/pc_mouse.h"
#include "../../includes/Singletone/error_class.h"
#include "../../includes/Singletone/introduction.h"

#include "../../../GetPixels/GPI.h"

// private

WindowAndStyles* WindowAndStyles::m_class_obj = NULL;

WindowAndStyles::WindowAndStyles ()
    : m_V2f_size_pix (311.0, 175.0),

      m_rectangle_shape (m_V2f_size_pix),

      m_SW_now (Default),

      m_f_time_since_clicking (0),

      m_w_game_name (L"GolubRun 4"),

      m_C_defolt_window (25, 25, 25, 255),
      m_C_clear_color (0, 0, 0, 255)
{
}

// protected
// void
void WindowAndStyles::main_time_work ()
{
	names::f_time = names::C_clock.restart ().asMicroseconds ();
	if (WindowAndStyles::hasFocus ())
	{
		names::f_time = names::f_time * 0.001;
	}
	else
	{
		names::f_time = 0.0;
	}
}
void WindowAndStyles::main_F11 ()
{
	WindowAndStyles* WAS_ = getClass ();

	WAS_->m_f_time_since_clicking += names::f_microsec * names::f_time;

	if (Keyboard::isKeyPressed (Keyboard::F11) and WAS_->m_f_time_since_clicking > 1.0 and WAS_->m_window.hasFocus ())
	{
		if (WAS_->m_SW_now == Default)
		{
			WAS_->m_videomode = VideoMode::getFullscreenModes ()[0];
			WAS_->m_render_texture.create (
			    WAS_->m_videomode.width / names::u_factor_of_resolution,
			    WAS_->m_videomode.height / names::u_factor_of_resolution);
			WAS_->m_window.create (
			    VideoMode (WAS_->m_videomode.width, WAS_->m_videomode.height),
			    WAS_->m_w_game_name,
			    Style::Fullscreen);

			WAS_->m_V_camera.setCenter (Vector2f (
			    static_cast<float> (WAS_->m_videomode.width) * 0.5,
			    static_cast<float> (WAS_->m_videomode.height) * 0.5));
			WAS_->m_V_camera.setSize (Vector2f (
			    static_cast<float> (WAS_->m_videomode.width),
			    static_cast<float> (WAS_->m_videomode.height)));
			WAS_->m_render_texture.setView (WAS_->m_V_camera);
			WAS_->m_window.setView (WAS_->m_V_camera);

			main_destroy ();

			WAS_->m_SW_now = Fullscreen;
			WAS_->m_f_time_since_clicking = 0.0;
		}
		else if (WAS_->m_SW_now == Fullscreen)
		{
			WAS_->m_videomode = VideoMode::getDesktopMode ();
			WAS_->m_window.create (
			    VideoMode (WAS_->m_videomode.width, WAS_->m_videomode.height),
			    WAS_->m_w_game_name,
			    Style::Default);
			WAS_->m_render_texture.create (
			    static_cast<float> (WAS_->m_window.getSize ().x) / names::u_factor_of_resolution,
			    static_cast<float> (WAS_->m_window.getSize ().y) / names::u_factor_of_resolution);

			WAS_->m_V_camera.setCenter (Vector2f (
			    static_cast<float> (WAS_->m_window.getSize ().x) * 0.5,
			    static_cast<float> (WAS_->m_window.getSize ().y) * 0.5));
			WAS_->m_V_camera.setSize (Vector2f (
			    static_cast<float> (WAS_->m_window.getSize ().x),
			    static_cast<float> (WAS_->m_window.getSize ().y)));
			WAS_->m_render_texture.setView (WAS_->m_V_camera);
			WAS_->m_window.setView (WAS_->m_V_camera);

			main_destroy ();

			WAS_->m_SW_now = Default;
			WAS_->m_f_time_since_clicking = 0;
		}
	}
}
void WindowAndStyles::main_event ()
{
	WindowAndStyles* WAS_ = getClass ();

	while (WAS_->m_window.pollEvent (names::E_event))
	{
		if (names::E_event.type == Event::Closed or (WindowAndStyles::hasFocus () and Keyboard::isKeyPressed (Keyboard::Escape)))
		{
			close ();
		}
	}
	if (names::E_event.type == sf::Event::Resized)
	{
		WindowAndStyles* WAS_ = getClass ();

		// camera
		WAS_->m_V_camera.setCenter (Vector2f (
		    static_cast<float> (names::E_event.size.width) * 0.5,
		    static_cast<float> (names::E_event.size.height) * 0.5));
		WAS_->m_V_camera.setSize (Vector2f (
		    static_cast<float> (names::E_event.size.width),
		    static_cast<float> (names::E_event.size.height)));
		WAS_->m_render_texture.create (
		    WAS_->m_V_camera.getSize ().x / names::u_factor_of_resolution,
		    WAS_->m_V_camera.getSize ().y / names::u_factor_of_resolution);
		WAS_->m_render_texture.setView (WAS_->m_V_camera);
		WAS_->m_window.setView (WAS_->m_V_camera);

		main_destroy ();
	}
}
void WindowAndStyles::clear_clear ()
{
	WindowAndStyles* WAS_ = getClass ();
	if (WAS_->m_C_clear_color.a > 250)
	{
		WAS_->m_render_texture.clear (WAS_->m_C_clear_color);
		WAS_->m_window.clear (WAS_->m_C_clear_color);
	}
	else
	{
		WAS_->m_render_texture.clear (WAS_->m_C_defolt_window);
		WAS_->m_window.clear (WAS_->m_C_defolt_window);
	}
}
void WindowAndStyles::clear_rectangle ()
{
	WindowAndStyles* WAS_ = getClass ();
	WAS_->m_rectangle_shape.setSize (Vector2f (WAS_->m_V_camera.getSize ()));
	WAS_->m_rectangle_shape.setPosition (WAS_->m_V_camera.getCenter ().x - WAS_->m_V_camera.getSize ().x * 0.5,
	                                     WAS_->m_V_camera.getCenter ().y - WAS_->m_V_camera.getSize ().y * 0.5);
}
void WindowAndStyles::clear_draw ()
{
	WindowAndStyles* WAS_ = getClass ();
	vector<Text>& T_ = Error_class::getText ();

	// boxes

	if (names::game_status == GameStatus::introduction)
	{
		WAS_->m_render_texture.draw (Introduction::getRender ());
	}

	// hitboxes

	if (names::b_hitboxes_is_drawn)
	{
		if (PC_Mouse::getGlobalBounds ().intersects (WAS_->m_rectangle_shape.getGlobalBounds ()))
		{
			WAS_->m_render_texture.draw (PC_Mouse::getHitBox ());
			WAS_->m_render_texture.draw (PC_Mouse::getTextBox ());
		}
	}

	// errors
	WAS_->m_render_texture.draw (Error_class::getRectangleShape ());
	for (size_t st (0); st < T_.size (); st++)
	{
		WAS_->m_render_texture.draw (T_[st]);
	}
}
void WindowAndStyles::clear_display ()
{
	WindowAndStyles* WAS_ = getClass ();

	WAS_->m_render_texture.display ();
	Sprite S (WAS_->m_render_texture.getTexture ());
	S.setScale (names::u_factor_of_resolution, names::u_factor_of_resolution);

	WAS_->m_window.draw (S);
	WAS_->m_window.display ();
}

// public
// WindowAndStyles*

WindowAndStyles* WindowAndStyles::getClass ()
{
	if (m_class_obj)
		return m_class_obj;

	m_class_obj = new WindowAndStyles ();
	return m_class_obj;
}

// void

void WindowAndStyles::start ()
{
	WindowAndStyles* WAS_ = getClass ();

	names::LoadFromMemory (WAS_->m_image, icon_png, icon_png_size, "Images/icon.png");

	WAS_->m_videomode = VideoMode::getDesktopMode ();

	WAS_->m_window.create (
	    VideoMode (WAS_->m_videomode.width, WAS_->m_videomode.height),
	    WAS_->m_w_game_name);
	WAS_->m_render_texture.create (
	    static_cast<float> (WAS_->m_window.getSize ().x) / names::u_factor_of_resolution,
	    static_cast<float> (WAS_->m_window.getSize ().y) / names::u_factor_of_resolution);
	WAS_->m_SW_now = Default;
	WAS_->m_window.setIcon (WAS_->m_image.getSize ().x, WAS_->m_image.getSize ().y, WAS_->m_image.getPixelsPtr ());

	// camera
	WAS_->m_V_camera.setCenter (Vector2f (
	    static_cast<float> (WAS_->m_window.getSize ().x) * 0.5,
	    static_cast<float> (WAS_->m_window.getSize ().y) * 0.5));
	WAS_->m_V_camera.setSize (Vector2f (
	    static_cast<float> (WAS_->m_window.getSize ().x),
	    static_cast<float> (WAS_->m_window.getSize ().y)));
	WAS_->m_render_texture.setView (WAS_->m_V_camera);
	WAS_->m_window.setView (WAS_->m_V_camera);
}
void WindowAndStyles::main ()
{
	// time work
	main_time_work ();

	// F11
	main_F11 ();

	// close
	main_event ();
}
void WindowAndStyles::clear ()
{
	// clear
	clear_clear ();

	// rectangle
	clear_rectangle ();

	// draw
	clear_draw ();

	// display
	clear_display ();
}
void WindowAndStyles::setColor (Color C)
{
	WindowAndStyles* WAS_ = getClass ();
	WAS_->m_C_clear_color = C;
}

// bool

bool WindowAndStyles::isOpen ()
{
	return getClass ()->m_window.isOpen ();
}
bool WindowAndStyles::hasFocus ()
{
	return getClass ()->m_window.hasFocus ();
}

// float

float WindowAndStyles::getFactorX ()
{
	WindowAndStyles* WAS_ = getClass ();
	return WAS_->m_rectangle_shape.getGlobalBounds ().width / WAS_->m_V2f_size_pix.x;
}
float WindowAndStyles::getFactorY ()
{
	WindowAndStyles* WAS_ = getClass ();
	return WAS_->m_rectangle_shape.getGlobalBounds ().height / WAS_->m_V2f_size_pix.y;
}
float WindowAndStyles::getPixelsSizeX ()
{
	return getClass ()->m_V2f_size_pix.x;
}
float WindowAndStyles::getPixelsSizeY ()
{
	return getClass ()->m_V2f_size_pix.y;
}

// Window&

Window& WindowAndStyles::getWindow ()
{
	return getClass ()->m_window;
}

// FloatRect

FloatRect WindowAndStyles::getGlobalBounds ()
{
	return getClass ()->m_rectangle_shape.getGlobalBounds ();
}

// Color

Color WindowAndStyles::getDefoultColor ()
{
	return getClass ()->m_C_defolt_window;
}

void WindowAndStyles::main_destroy ()
{
}

void WindowAndStyles::draw (const Button& B)
{
	WindowAndStyles* WAS_ = getClass ();

	WAS_->m_render_texture.draw (B.getRectangleShape ());
	if (names::b_hitboxes_is_drawn)
	{
		WAS_->m_render_texture.draw (B.getText ());
	}
}

void WindowAndStyles::close ()
{
	getClass ()->m_window.close ();
}
