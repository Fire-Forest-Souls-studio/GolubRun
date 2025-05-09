#include "../../includes/Singletone/names.h"

#include <string>

#include "../../includes/Singletone/error_class.h"
#include "../../includes/Singletone/window_and_styles.h"

bool names::b_hitboxes_is_drawn (false);
bool names::b_shader_is_on (true);

Clock names::C_clock;

Event names::E_event;

float names::f_time (0);
float names::microsec (0.001);
float names::f_font_hitbox_scale (2.5);
float names::f_lifting_hitbox_text (2.5);

Color names::C_font_hitbox (100, 250, 0, 255);

Font names::F_pixel;

unsigned names::u_factor_of_resolution (1);

GameStatus names::game_status (GameStatus::introduction);

string names::s_path (" ");

void names::LoadFromMemory (Texture& T, void const* v, unsigned long ul, const string& s, bool b)
{
	if (!T.loadFromFile (s_path + "Resourcepack/" + s))
	{
		if (!T.loadFromMemory (v, ul))
		{
			Error_class::ec_error_LFM_Tvus (ul, s);
		}
		else if (b)
		{
			if (b_shader_is_on)
			{
				T.loadFromMemory (v, ul, IntRect (0, 0, T.getSize ().x * 0.5, T.getSize ().y));
			}
			else
			{
				T.loadFromMemory (v, ul, IntRect (T.getSize ().x * 0.5, 0, T.getSize ().x * 0.5, T.getSize ().y));
			}
		}
	}
	else if (b)
	{
		if (b_shader_is_on)
		{
			T.loadFromFile (s_path + "Resourcepack/" + s, IntRect (0, 0, T.getSize ().x * 0.5, T.getSize ().y));
		}
		else
		{
			T.loadFromFile (s_path + "Resourcepack/" + s, IntRect (T.getSize ().x * 0.5, 0, T.getSize ().x * 0.5, T.getSize ().y));
		}
	}
}
void names::LoadFromMemory (Font& F, void const* v, unsigned long ul, const string& s)
{
	if (!F.loadFromFile (s_path + "Resourcepack/" + s))
	{
		if (!F.loadFromMemory (v, ul))
		{
			Error_class::ec_error_LFM_Fvus (ul, s);
		}
	}
}
void names::LoadFromMemory (Image& I, void const* v, unsigned long ul, const string& s)
{
	if (!I.loadFromFile (s_path + "Resourcepack/" + s))
	{
		if (!I.loadFromMemory (v, ul))
		{
			Error_class::ec_error_LFM_Ivus (ul, s);
		}
	}
}
void names::LoadFromMemory (SoundBuffer& SB, void const* v, unsigned long ul, const string& s)
{
	if (!SB.loadFromFile (s_path + "Resourcepack/" + s))
	{
		if (!SB.loadFromMemory (v, ul))
		{
			Error_class::ec_error_LFM_Svus (ul, s);
		}
	}
}
void names::LoadFromMemory (Shader& S, const string& s0, const string& s1)
{
	if (!S.loadFromFile (s_path + "Shaderpack/" + s1, Shader::Fragment))
	{
		if (!S.loadFromMemory (s0, Shader::Fragment))
		{
			Error_class::ec_error_LFM_Sss (s0, s1);
		}
	}
}
void names::SetXCenterPosition (Text& T, const float& f)
{
	T.setPosition (WindowAndStyles::getGlobalBounds ().width * 0.5 - T.getGlobalBounds ().width * 0.5, f);
}
void names::SetXCenterPosition (RectangleShape& RS, float f)
{
	RS.setPosition (WindowAndStyles::getGlobalBounds ().left + WindowAndStyles::getGlobalBounds ().width * 0.5 - RS.getGlobalBounds ().width * 0.5, f);
}
void names::SetPath (char* argv)
{
	std::string argv_str (argv);
#ifdef SFML_SYSTEM_LINUX
	s_path = argv_str.substr (0, argv_str.find_last_of ("/"));
#else
	s_path = argv_str.substr (0, argv_str.find_last_of ("\\"));
#endif
	s_path += "/";
}

string names::GetStringOfHyphenation (const string& s, int i)
{
	string s0;
	for (size_t st (0); st < s.length (); st++)
	{
		s0 += s[st];
		if (st % i == 0 and st != 0)
		{
			s0 += "\n";
		}
	}
	return s0;
}

wstring names::GetStringOfHyphenation (const wstring& w, int i)
{
	wstring w0;
	int i_cout (0);

	for (size_t st (0); st < w.length (); st++)
	{
		if (w[st] == L'\n' or w[st] == L'\v')
		{
			i_cout = 0;
			w0 += w[st];
		}
		else if (w[st] == L'\t')
		{
			w0 += w[st];
			i_cout += 4;
		}
		else if (float (i_cout) / (float (i) - 1.0) > 1)
		{
			w0 += L"\n";
			i_cout = 0;
			st -= 1;
		}
		else if (not(i_cout == 0 and w[st] == L' '))
		{
			w0 += w[st];
			i_cout++;
		}
	}
	return w0;
}
