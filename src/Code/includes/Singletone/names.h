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

// start

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

		static Clock clock;

		static Event event;

		static float f_time;
		static float f_microsec;
		static float f_font_hitbox_scale;
		static float f_lifting_hitbox_text;

		static Color C_font_hitbox;

		static Font font;

		static unsigned m_u_factor_of_resolution;

		static GameStatus game_status;

		static string s_path;

		static void LoadFromMemory (Texture& texture, void const* data, unsigned long size, const string& resourcepack_path, bool two_tetures_for_shader = false);
		static void LoadFromMemory (Font& font, void const* data, unsigned long size, const string& resourcepack_path);
		static void LoadFromMemory (Image& image, void const* data, unsigned long size, const string& resourcepack_path);
		static void LoadFromMemory (SoundBuffer& sound_buffer, void const* data, unsigned long size, const string& resourcepack_path);
		static void LoadFromMemory (Shader& shader, const string& memory, const string& resourcepack_path);
		static void SetXCenterPosition (Text& text, const float& y);
		static void SetXCenterPosition (RectangleShape& rectangle, float y);
		static void SetPath (char* argv);

		static string GetStringOfHyphenation (const string& str, int symbols_in_line);
		static wstring GetStringOfHyphenation (const wstring& str, int symbols_in_line);
};

#endif
