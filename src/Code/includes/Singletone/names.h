#ifndef CODE_NAMES_H_
#define CODE_NAMES_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace sf;

//start

enum GameStatus
{
	introduction = 0,
	main_menu
};

class names
{
	public:

		static bool b_hitboxes_is_drawn;
		static bool b_shader_is_on;

		static Clock C_clock;

		static Event E_event;

		static float f_time;
		static float microsec;
		static float f_font_hitbox_scale;
		static float f_lifting_hitbox_text;

		static Color C_font_hitbox;

		static Font F_pixel;

		static unsigned u_factor_of_resolution;

		static GameStatus game_status;

		static string s_path;

		static void LoadFromMemory (Texture&, void const*, unsigned long, const string&, bool b = false);
		static void LoadFromMemory (Font&, void const*, unsigned long, const string&);
		static void LoadFromMemory (Image&, void const*, unsigned long, const string&);
		static void LoadFromMemory (SoundBuffer&, void const*, unsigned long, const string&);
		static void LoadFromMemory (Shader&, const string&, const string&);
		static void SetXCenterPosition (Text&, const float&);
		static void SetXCenterPosition (RectangleShape&, float);
		static void SetPath (char* argv);

		static string GetStringOfHyphenation (const string&, int);
		static wstring GetStringOfHyphenation (const wstring&, int);
};

#endif
