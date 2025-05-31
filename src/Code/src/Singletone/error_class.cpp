#include "../../includes/Singletone/error_class.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"

// private

Error_class* Error_class::m_class_obj = 0;

Error_class::Error_class ()
    : m_rectangle_shape (Vector2f (1, 1)),

      m_text (e_error_text::error),

      m_wstring (e_error_text::error),

      m_b_error (false),

      m_C_rectangle_shape_color (250, 125, 125, 0),
      m_C_outline_color (250, 0, 0, 0),
      m_C_text_color (250, 250, 250, 0),

      m_u_font_scale (4),

      m_f_frame (0),
      m_f_animation_speed (255 / 2),
      m_f_time_to_destroy (4)
{
	for (size_t st (0); st < e_error_text::error; st++)
	{
		m_text[st].setFont (names::F_pixel);
		m_text[st].setFillColor (m_C_text_color);
	}
	m_rectangle_shape.setFillColor (m_C_rectangle_shape_color);
	m_rectangle_shape.setOutlineThickness (1);
	m_rectangle_shape.setOutlineColor (m_C_outline_color);
}

// public:
// Erroe_class*

Error_class* Error_class::getClass ()
{
	if (m_class_obj != 0)
		return m_class_obj;

	m_class_obj = new Error_class ();
	return m_class_obj;
}

// void

void Error_class::main_transition ()
{
	Error_class* Ec_ = getClass ();

	if (Ec_->m_b_error)
	{
		if (Ec_->m_f_frame == 0.0)
		{
			for (size_t st (0); st < e_error_text::error; st++)
			{
				Ec_->m_text[st].setString (Ec_->m_wstring[st]);
			}
		}
		Ec_->m_f_frame += Ec_->m_f_animation_speed * names::f_microsec * names::f_time;
		if (Ec_->m_f_frame <= 255)
		{
			Ec_->m_C_text_color = Color (Ec_->m_C_text_color.r, Ec_->m_C_text_color.g, Ec_->m_C_text_color.b, Ec_->m_f_frame);
			Ec_->m_C_rectangle_shape_color = Color (Ec_->m_C_rectangle_shape_color.r, Ec_->m_C_rectangle_shape_color.g, Ec_->m_C_rectangle_shape_color.b, Ec_->m_f_frame);
			Ec_->m_C_outline_color = Color (Ec_->m_C_outline_color.r, Ec_->m_C_outline_color.g, Ec_->m_C_outline_color.b, Ec_->m_f_frame);
		}
		else if (Ec_->m_f_frame < 255 + Ec_->m_f_time_to_destroy * 0.5 * Ec_->m_f_animation_speed)
		{
			Ec_->m_C_text_color = Color (Ec_->m_C_text_color.r, Ec_->m_C_text_color.g, Ec_->m_C_text_color.b, 255);
			Ec_->m_C_rectangle_shape_color = Color (Ec_->m_C_rectangle_shape_color.r, Ec_->m_C_rectangle_shape_color.g, Ec_->m_C_rectangle_shape_color.b, 255);
			Ec_->m_C_outline_color = Color (Ec_->m_C_outline_color.r, Ec_->m_C_outline_color.g, Ec_->m_C_outline_color.b, 255);
		}
		else
		{
			Ec_->m_b_error = false;
		}
	}
	else
	{
		if (Ec_->m_f_frame > 0)
		{
			Ec_->m_f_frame -= Ec_->m_f_animation_speed * names::f_microsec * names::f_time;
			if (Ec_->m_f_frame > 255)
			{
				Ec_->m_C_text_color = Color (Ec_->m_C_text_color.r, Ec_->m_C_text_color.g, Ec_->m_C_text_color.b, 255);
				Ec_->m_C_rectangle_shape_color = Color (Ec_->m_C_rectangle_shape_color.r, Ec_->m_C_rectangle_shape_color.g, Ec_->m_C_rectangle_shape_color.b, 255);
				Ec_->m_C_outline_color = Color (Ec_->m_C_outline_color.r, Ec_->m_C_outline_color.g, Ec_->m_C_outline_color.b, 255);
			}
			else
			{
				Ec_->m_C_text_color = Color (Ec_->m_C_text_color.r, Ec_->m_C_text_color.g, Ec_->m_C_text_color.b, Ec_->m_f_frame);
				Ec_->m_C_rectangle_shape_color = Color (Ec_->m_C_rectangle_shape_color.r, Ec_->m_C_rectangle_shape_color.g, Ec_->m_C_rectangle_shape_color.b, Ec_->m_f_frame);
				Ec_->m_C_outline_color = Color (Ec_->m_C_outline_color.r, Ec_->m_C_outline_color.g, Ec_->m_C_outline_color.b, Ec_->m_f_frame);
			}
		}
		else
		{
			Ec_->m_f_frame = 0;
			Ec_->m_C_text_color = Color (Ec_->m_C_text_color.r, Ec_->m_C_text_color.g, Ec_->m_C_text_color.b, 0);
			Ec_->m_C_rectangle_shape_color = Color (Ec_->m_C_rectangle_shape_color.r, Ec_->m_C_rectangle_shape_color.g, Ec_->m_C_rectangle_shape_color.b, 0);
			Ec_->m_C_outline_color = Color (Ec_->m_C_outline_color.r, Ec_->m_C_outline_color.g, Ec_->m_C_outline_color.b, 0);
			for (size_t st (0); st < e_error_text::error; st++)
			{
				Ec_->m_wstring[st].clear ();
			}
		}
	}
}

void Error_class::main_transform ()
{
	Error_class* Ec_ = getClass ();
	float f = WindowAndStyles::getFactorY ();

	for (size_t st (0); st < e_error_text::error; st++)
	{
		Ec_->m_text[st].setCharacterSize (Ec_->m_u_font_scale * f);
		if (st != 0)
		{
			names::SetXCenterPosition (Ec_->m_text[st],
			                           Ec_->m_text[st - 1].getGlobalBounds ().top + Ec_->m_text[st - 1].getGlobalBounds ().height);
		}
		else
		{
			names::SetXCenterPosition (Ec_->m_text[st], 2 * f);
		}
		Ec_->m_text[st].setFillColor (Ec_->m_C_text_color);
	}
	Ec_->m_rectangle_shape.setPosition (Ec_->m_text[e_error_text::function].getPosition ().x,
	                                      Ec_->m_text[0].getPosition ().y);
	Ec_->m_rectangle_shape.setSize (Vector2f (
	    Ec_->m_text[e_error_text::function].getGlobalBounds ().width,
	    Ec_->m_text[e_error_text::error - 1].getPosition ().y + Ec_->m_text[e_error_text::error - 1].getGlobalBounds ().height - Ec_->m_text[0].getPosition ().y));
	Ec_->m_rectangle_shape.setFillColor (Ec_->m_C_rectangle_shape_color);
	Ec_->m_rectangle_shape.setOutlineThickness (f);
	Ec_->m_rectangle_shape.setOutlineColor (Ec_->m_C_outline_color);
}

void Error_class::main ()
{
	main_transition ();

	main_transform ();
}
void Error_class::ec_error_LFM_Tvus (unsigned long ul, const string& s)
{
	Error_class* Ec_ = getClass ();

	Ec_->m_b_error = true;
	if (Ec_->m_f_frame > 255)
	{
		Ec_->m_f_frame = 255;
	}

	Ec_->m_wstring[e_error_text::report] = L"==========> ERROR [00000] <==========";
	Ec_->m_wstring[e_error_text::function] = L"FUNCTION: void names::LoadFromMemory (Texture& T, void const* v, unsigned long ul, const string& s)";
	Ec_->m_wstring[e_error_text::main_obj] = L"Texture& T";
	Ec_->m_wstring[e_error_text::argument0] = L"void const* v";
	Ec_->m_wstring[e_error_text::argument1] = L"unsigned long ul [ " + to_string (ul) + " ] ";
	Ec_->m_wstring[e_error_text::argument2] = L"const string& s  [ " + s + " ] ";

	wcerr << endl
	      << Ec_->m_wstring[e_error_text::report] << endl
	      << endl
	      << Ec_->m_wstring[e_error_text::function] << endl
	      << endl
	      << Ec_->m_wstring[e_error_text::main_obj] << endl
	      << Ec_->m_wstring[e_error_text::argument0] << endl
	      << Ec_->m_wstring[e_error_text::argument1] << endl
	      << Ec_->m_wstring[e_error_text::argument2] << endl
	      << endl;
}
void Error_class::ec_error_LFM_Fvus (unsigned long ul, const string& s)
{
	Error_class* Ec_ = getClass ();

	Ec_->m_b_error = true;
	if (Ec_->m_f_frame > 255)
	{
		Ec_->m_f_frame = 255;
	}

	Ec_->m_wstring[e_error_text::report] = L"==========> ERROR [00100] <==========";
	Ec_->m_wstring[e_error_text::function] = L"FUNCTION: void names::LoadFromMemory (Font& F, void const* v, unsigned long ul, const string& s)";
	Ec_->m_wstring[e_error_text::main_obj] = L"Font& F";
	Ec_->m_wstring[e_error_text::argument0] = L"void const* v";
	Ec_->m_wstring[e_error_text::argument1] = L"unsigned long ul [ " + to_string (ul) + " ] ";
	Ec_->m_wstring[e_error_text::argument2] = L"const string& s  [ " + s + " ] ";

	wcerr << endl
	      << Ec_->m_wstring[e_error_text::report] << endl
	      << endl
	      << Ec_->m_wstring[e_error_text::function] << endl
	      << endl
	      << Ec_->m_wstring[e_error_text::main_obj] << endl
	      << Ec_->m_wstring[e_error_text::argument0] << endl
	      << Ec_->m_wstring[e_error_text::argument1] << endl
	      << Ec_->m_wstring[e_error_text::argument2] << endl
	      << endl;
}
void Error_class::ec_error_LFM_Ivus (unsigned long ul, const string& s)
{
	Error_class* Ec_ = getClass ();

	Ec_->m_b_error = true;
	if (Ec_->m_f_frame > 255)
	{
		Ec_->m_f_frame = 255;
	}

	Ec_->m_wstring[e_error_text::report] = L"==========> ERROR [00200] <==========";
	Ec_->m_wstring[e_error_text::function] = L"FUNCTION: void names::LoadFromMemory (Image& T, void const* v, unsigned long ul, const string& s)";
	Ec_->m_wstring[e_error_text::main_obj] = L"Image& I";
	Ec_->m_wstring[e_error_text::argument1] = L"void const* v";
	Ec_->m_wstring[e_error_text::argument1] = L"unsigned long ul [ " + to_string (ul) + " ] ";
	Ec_->m_wstring[e_error_text::argument2] = L"const string& s  [ " + s + " ] ";

	wcerr << endl
	      << Ec_->m_wstring[e_error_text::report] << endl
	      << endl
	      << Ec_->m_wstring[e_error_text::function] << endl
	      << endl
	      << Ec_->m_wstring[e_error_text::main_obj] << endl
	      << Ec_->m_wstring[e_error_text::argument0] << endl
	      << Ec_->m_wstring[e_error_text::argument1] << endl
	      << Ec_->m_wstring[e_error_text::argument2] << endl
	      << endl;
}
void Error_class::ec_error_LFM_Svus (unsigned long ul, const string& s)
{
	Error_class* Ec_ = getClass ();

	Ec_->m_b_error = true;
	if (Ec_->m_f_frame > 255)
	{
		Ec_->m_f_frame = 255;
	}

	Ec_->m_wstring[e_error_text::report] = L"==========> ERROR [00300] <==========";
	Ec_->m_wstring[e_error_text::function] = L"FUNCTION: void names::LoadFromMemory (SoundBuffer& SB, void const* v, unsigned long ul, const string& s)";
	Ec_->m_wstring[e_error_text::main_obj] = L"SoundBuffer& SB";
	Ec_->m_wstring[e_error_text::argument0] = L"void const* v";
	Ec_->m_wstring[e_error_text::argument1] = L"unsigned long ul [ " + to_string (ul) + " ] ";
	Ec_->m_wstring[e_error_text::argument2] = L"const string& s  [ " + s + " ] ";

	wcerr << endl
	      << Ec_->m_wstring[e_error_text::report] << endl
	      << endl
	      << Ec_->m_wstring[e_error_text::function] << endl
	      << endl
	      << Ec_->m_wstring[e_error_text::main_obj] << endl
	      << Ec_->m_wstring[e_error_text::argument0] << endl
	      << Ec_->m_wstring[e_error_text::argument1] << endl
	      << Ec_->m_wstring[e_error_text::argument2] << endl
	      << endl;
}
void Error_class::ec_error_LFM_Sss (const string& s0, const string& s1)
{
	Error_class* Ec_ = getClass ();

	Ec_->m_b_error = true;
	if (Ec_->m_f_frame > 255)
	{
		Ec_->m_f_frame = 255;
	}

	Ec_->m_wstring[e_error_text::report] = L"==========> ERROR [00311] <==========";
	Ec_->m_wstring[e_error_text::function] = L"FUNCTION: void names::LoadFromMemory (Shader& S, const string& s0, const string& s1)";
	Ec_->m_wstring[e_error_text::main_obj] = L"Shader& S";
	Ec_->m_wstring[e_error_text::argument0] = L"const string& s0 [ " + s0 + " ] ";
	Ec_->m_wstring[e_error_text::argument1] = L"const string& s1 [ " + s1 + " ] ";

	wcerr << endl
	      << Ec_->m_wstring[e_error_text::report] << endl
	      << endl
	      << Ec_->m_wstring[e_error_text::function] << endl
	      << endl
	      << Ec_->m_wstring[e_error_text::main_obj] << endl
	      << Ec_->m_wstring[e_error_text::argument0] << endl
	      << Ec_->m_wstring[e_error_text::argument1] << endl
	      << Ec_->m_wstring[e_error_text::argument2] << endl
	      << endl;
}

// vector <Text>&

vector<Text>& Error_class::getText ()
{
	return getClass ()->m_text;
}

// RectangleShape&

RectangleShape& Error_class::getRectangleShape ()
{
	return getClass ()->m_rectangle_shape;
}
