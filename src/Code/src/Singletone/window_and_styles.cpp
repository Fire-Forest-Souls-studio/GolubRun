#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/pc_mouse.h"
#include "../../includes/Singletone/error_class.h"
#include "../../includes/Singletone/introduction.h"

#include "../../../GetPixels/GPI.h"

// private

WindowAndStyles* WindowAndStyles::m_class_obj = NULL;

WindowAndStyles::WindowAndStyles ()
    : f_size_pix (300.0, 150.0),

      rectangle_shape_obj (f_size_pix),

      now (Default),

      m_f_time_since_clicking (0),

      w_game_name (L"GolubRun 4"),

      C_defolt_window (25, 25, 25, 255),
      C_clear_color (0, 0, 0, 255)
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

	if (Keyboard::isKeyPressed (Keyboard::F11) and WAS_->m_f_time_since_clicking > 1.0 and WAS_->window_obj.hasFocus ())
	{
		if (WAS_->now == Default)
		{
			WAS_->videomode_obj = VideoMode::getFullscreenModes ()[0];
			WAS_->render_texture_obj.create (
			    WAS_->videomode_obj.width / names::u_factor_of_resolution,
			    WAS_->videomode_obj.height / names::u_factor_of_resolution);
			WAS_->window_obj.create (
			    VideoMode (WAS_->videomode_obj.width, WAS_->videomode_obj.height),
			    WAS_->w_game_name,
			    Style::Fullscreen);

			WAS_->camera.setCenter (Vector2f (
			    static_cast<float> (WAS_->videomode_obj.width) * 0.5,
			    static_cast<float> (WAS_->videomode_obj.height) * 0.5));
			WAS_->camera.setSize (Vector2f (
			    static_cast<float> (WAS_->videomode_obj.width),
			    static_cast<float> (WAS_->videomode_obj.height)));
			WAS_->render_texture_obj.setView (WAS_->camera);
			WAS_->window_obj.setView (WAS_->camera);

			main_destroy ();

			WAS_->now = Fullscreen;
			WAS_->m_f_time_since_clicking = 0.0;
		}
		else if (WAS_->now == Fullscreen)
		{
			WAS_->videomode_obj = VideoMode::getDesktopMode ();
			WAS_->window_obj.create (
			    VideoMode (WAS_->videomode_obj.width, WAS_->videomode_obj.height),
			    WAS_->w_game_name,
			    Style::Default);
			WAS_->render_texture_obj.create (
			    static_cast<float> (WAS_->window_obj.getSize ().x) / names::u_factor_of_resolution,
			    static_cast<float> (WAS_->window_obj.getSize ().y) / names::u_factor_of_resolution);

			WAS_->camera.setCenter (Vector2f (
			    static_cast<float> (WAS_->window_obj.getSize ().x) * 0.5,
			    static_cast<float> (WAS_->window_obj.getSize ().y) * 0.5));
			WAS_->camera.setSize (Vector2f (
			    static_cast<float> (WAS_->window_obj.getSize ().x),
			    static_cast<float> (WAS_->window_obj.getSize ().y)));
			WAS_->render_texture_obj.setView (WAS_->camera);
			WAS_->window_obj.setView (WAS_->camera);

			main_destroy ();

			WAS_->now = Default;
			WAS_->m_f_time_since_clicking = 0;
		}
	}
}
void WindowAndStyles::main_event ()
{
	WindowAndStyles* WAS_ = getClass ();

	while (WAS_->window_obj.pollEvent (names::E_event))
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
		WAS_->camera.setCenter (Vector2f (
		    static_cast<float> (names::E_event.size.width) * 0.5,
		    static_cast<float> (names::E_event.size.height) * 0.5));
		WAS_->camera.setSize (Vector2f (
		    static_cast<float> (names::E_event.size.width),
		    static_cast<float> (names::E_event.size.height)));
		WAS_->render_texture_obj.create (
		    WAS_->camera.getSize ().x / names::u_factor_of_resolution,
		    WAS_->camera.getSize ().y / names::u_factor_of_resolution);
		WAS_->render_texture_obj.setView (WAS_->camera);
		WAS_->window_obj.setView (WAS_->camera);

		main_destroy ();
	}
}
void WindowAndStyles::clear_clear ()
{
	WindowAndStyles* WAS_ = getClass ();
	if (WAS_->C_clear_color.a > 250)
	{
		WAS_->render_texture_obj.clear (WAS_->C_clear_color);
		WAS_->window_obj.clear (WAS_->C_clear_color);
	}
	else
	{
		WAS_->render_texture_obj.clear (WAS_->C_defolt_window);
		WAS_->window_obj.clear (WAS_->C_defolt_window);
	}
}
void WindowAndStyles::clear_rectangle ()
{
	WindowAndStyles* WAS_ = getClass ();
	WAS_->rectangle_shape_obj.setSize (Vector2f (WAS_->camera.getSize ()));
	WAS_->rectangle_shape_obj.setPosition (WAS_->camera.getCenter ().x - WAS_->camera.getSize ().x * 0.5,
	                                       WAS_->camera.getCenter ().y - WAS_->camera.getSize ().y * 0.5);
}
void WindowAndStyles::clear_draw ()
{
	WindowAndStyles* WAS_ = getClass ();
	vector<Text>& T_ = Error_class::getText ();

	// boxes

    if (names::game_status == GameStatus::introduction)
    {
        WAS_->render_texture_obj.draw(Introduction::getRender());
    }

	// hitboxes

	if (names::b_hitboxes_is_drawn)
	{
		if (PC_Mouse::getGlobalBounds ().intersects (WAS_->rectangle_shape_obj.getGlobalBounds ()))
		{
			WAS_->render_texture_obj.draw (PC_Mouse::getHitBox ());
			WAS_->render_texture_obj.draw (PC_Mouse::getTextBox ());
		}
	}

	// errors
	WAS_->render_texture_obj.draw (Error_class::getRectangleShape ());
	for (size_t st (0); st < T_.size (); st++)
	{
		WAS_->render_texture_obj.draw (T_[st]);
	}
}
void WindowAndStyles::clear_display ()
{
	WindowAndStyles* WAS_ = getClass ();

	WAS_->render_texture_obj.display ();
	Sprite S (WAS_->render_texture_obj.getTexture ());
	S.setScale (names::u_factor_of_resolution, names::u_factor_of_resolution);
	WAS_->window_obj.draw (S);
	WAS_->window_obj.display ();
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

	names::LoadFromMemory (WAS_->image_obj, icon_png, icon_png_size, "Images/icon.png");

	WAS_->videomode_obj = VideoMode::getDesktopMode ();

	WAS_->window_obj.create (
	    VideoMode (WAS_->videomode_obj.width, WAS_->videomode_obj.height),
	    WAS_->w_game_name);
	WAS_->render_texture_obj.create (
	    static_cast<float> (WAS_->window_obj.getSize ().x) / names::u_factor_of_resolution,
	    static_cast<float> (WAS_->window_obj.getSize ().y) / names::u_factor_of_resolution);
	WAS_->now = Default;
	WAS_->window_obj.setIcon (WAS_->image_obj.getSize ().x, WAS_->image_obj.getSize ().y, WAS_->image_obj.getPixelsPtr ());

	// camera
	WAS_->camera.setCenter (Vector2f (
	    static_cast<float> (WAS_->window_obj.getSize ().x) * 0.5,
	    static_cast<float> (WAS_->window_obj.getSize ().y) * 0.5));
	WAS_->camera.setSize (Vector2f (
	    static_cast<float> (WAS_->window_obj.getSize ().x),
	    static_cast<float> (WAS_->window_obj.getSize ().y)));
	WAS_->render_texture_obj.setView (WAS_->camera);
	WAS_->window_obj.setView (WAS_->camera);
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
	WAS_->C_clear_color = C;
}

// bool

bool WindowAndStyles::isOpen ()
{
	return getClass ()->window_obj.isOpen ();
}
bool WindowAndStyles::hasFocus ()
{
	return getClass ()->window_obj.hasFocus ();
}

// float

float WindowAndStyles::getFactorX ()
{
	WindowAndStyles* WAS_ = getClass ();
	return WAS_->rectangle_shape_obj.getGlobalBounds ().width / WAS_->f_size_pix.x;
}
float WindowAndStyles::getFactorY ()
{
	WindowAndStyles* WAS_ = getClass ();
	return WAS_->rectangle_shape_obj.getGlobalBounds ().height / WAS_->f_size_pix.y;
}
float WindowAndStyles::getPixelsSizeX ()
{
	return getClass ()->f_size_pix.x;
}
float WindowAndStyles::getPixelsSizeY ()
{
	return getClass ()->f_size_pix.y;
}

// Window&

Window& WindowAndStyles::getWindow ()
{
	return getClass ()->window_obj;
}

// FloatRect

FloatRect WindowAndStyles::getGlobalBounds ()
{
	return getClass ()->rectangle_shape_obj.getGlobalBounds ();
}

// Color

Color WindowAndStyles::getDefoultColor ()
{
	return getClass ()->C_defolt_window;
}

void WindowAndStyles::main_destroy ()
{
}

void WindowAndStyles::draw (const Button& B)
{
	WindowAndStyles* WAS_ = getClass ();

	WAS_->render_texture_obj.draw (B.getRectangleShape ());
	if (names::b_hitboxes_is_drawn)
	{
		WAS_->render_texture_obj.draw (B.getText ());
	}
}

void WindowAndStyles::close ()
{
	getClass ()->window_obj.close ();
}
