#include "../../includes/Singletone/error_class.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"

// private

Error_class* Error_class::class_obj = 0;

Error_class::Error_class ()
    : rectangle_shape_obj (Vector2f (1, 1)),

      text_obj (e_error_text::error),

      wstring_obj (e_error_text::error),

      b_error (false),

      C_rectangle_shape_color (250, 125, 125, 0),
      C_outline_color (250, 0, 0, 0),
      C_text_color (250, 250, 250, 0),

      u_font_scale (4),

      f_frame (0),
      f_animation_speed (255 / 2),
      f_time_to_destroy (4)
{
	for (size_t st (0); st < e_error_text::error; st++)
	{
		text_obj[st].setFont (names::F_pixel);
		text_obj[st].setFillColor (C_text_color);
	}
	rectangle_shape_obj.setFillColor (C_rectangle_shape_color);
	rectangle_shape_obj.setOutlineThickness (1);
	rectangle_shape_obj.setOutlineColor (C_outline_color);
}

// public:
// Erroe_class*

Error_class* Error_class::getClass ()
{
	if (class_obj != 0)
		return class_obj;

	class_obj = new Error_class ();
	return class_obj;
}

// void

void Error_class::main_transition ()
{
	Error_class* Ec_ = getClass ();

	if (Ec_->b_error)
	{
		if (Ec_->f_frame == 0.0)
		{
			for (size_t st (0); st < e_error_text::error; st++)
			{
				Ec_->text_obj[st].setString (Ec_->wstring_obj[st]);
			}
		}
		Ec_->f_frame += Ec_->f_animation_speed * names::microsec * names::f_time;
		if (Ec_->f_frame <= 255)
		{
			Ec_->C_text_color = Color (Ec_->C_text_color.r, Ec_->C_text_color.g, Ec_->C_text_color.b, Ec_->f_frame);
			Ec_->C_rectangle_shape_color = Color (Ec_->C_rectangle_shape_color.r, Ec_->C_rectangle_shape_color.g, Ec_->C_rectangle_shape_color.b, Ec_->f_frame);
			Ec_->C_outline_color = Color (Ec_->C_outline_color.r, Ec_->C_outline_color.g, Ec_->C_outline_color.b, Ec_->f_frame);
		}
		else if (Ec_->f_frame < 255 + Ec_->f_time_to_destroy * 0.5 * Ec_->f_animation_speed)
		{
			Ec_->C_text_color = Color (Ec_->C_text_color.r, Ec_->C_text_color.g, Ec_->C_text_color.b, 255);
			Ec_->C_rectangle_shape_color = Color (Ec_->C_rectangle_shape_color.r, Ec_->C_rectangle_shape_color.g, Ec_->C_rectangle_shape_color.b, 255);
			Ec_->C_outline_color = Color (Ec_->C_outline_color.r, Ec_->C_outline_color.g, Ec_->C_outline_color.b, 255);
		}
		else
		{
			Ec_->b_error = false;
		}
	}
	else
	{
		if (Ec_->f_frame > 0)
		{
			Ec_->f_frame -= Ec_->f_animation_speed * names::microsec * names::f_time;
			if (Ec_->f_frame > 255)
			{
				Ec_->C_text_color = Color (Ec_->C_text_color.r, Ec_->C_text_color.g, Ec_->C_text_color.b, 255);
				Ec_->C_rectangle_shape_color = Color (Ec_->C_rectangle_shape_color.r, Ec_->C_rectangle_shape_color.g, Ec_->C_rectangle_shape_color.b, 255);
				Ec_->C_outline_color = Color (Ec_->C_outline_color.r, Ec_->C_outline_color.g, Ec_->C_outline_color.b, 255);
			}
			else
			{
				Ec_->C_text_color = Color (Ec_->C_text_color.r, Ec_->C_text_color.g, Ec_->C_text_color.b, Ec_->f_frame);
				Ec_->C_rectangle_shape_color = Color (Ec_->C_rectangle_shape_color.r, Ec_->C_rectangle_shape_color.g, Ec_->C_rectangle_shape_color.b, Ec_->f_frame);
				Ec_->C_outline_color = Color (Ec_->C_outline_color.r, Ec_->C_outline_color.g, Ec_->C_outline_color.b, Ec_->f_frame);
			}
		}
		else
		{
			Ec_->f_frame = 0;
			Ec_->C_text_color = Color (Ec_->C_text_color.r, Ec_->C_text_color.g, Ec_->C_text_color.b, 0);
			Ec_->C_rectangle_shape_color = Color (Ec_->C_rectangle_shape_color.r, Ec_->C_rectangle_shape_color.g, Ec_->C_rectangle_shape_color.b, 0);
			Ec_->C_outline_color = Color (Ec_->C_outline_color.r, Ec_->C_outline_color.g, Ec_->C_outline_color.b, 0);
			for (size_t st (0); st < e_error_text::error; st++)
			{
				Ec_->wstring_obj[st].clear ();
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
		Ec_->text_obj[st].setCharacterSize (Ec_->u_font_scale * f);
		if (st != 0)
		{
			names::SetXCenterPosition (Ec_->text_obj[st],
			                           Ec_->text_obj[st - 1].getGlobalBounds ().top + Ec_->text_obj[st - 1].getGlobalBounds ().height);
		}
		else
		{
			names::SetXCenterPosition (Ec_->text_obj[st], 2 * f);
		}
		Ec_->text_obj[st].setFillColor (Ec_->C_text_color);
	}
	Ec_->rectangle_shape_obj.setPosition (Ec_->text_obj[e_error_text::function].getPosition ().x,
	                                      Ec_->text_obj[0].getPosition ().y);
	Ec_->rectangle_shape_obj.setSize (Vector2f (
	    Ec_->text_obj[e_error_text::function].getGlobalBounds ().width,
	    Ec_->text_obj[e_error_text::error - 1].getPosition ().y + Ec_->text_obj[e_error_text::error - 1].getGlobalBounds ().height - Ec_->text_obj[0].getPosition ().y));
	Ec_->rectangle_shape_obj.setFillColor (Ec_->C_rectangle_shape_color);
	Ec_->rectangle_shape_obj.setOutlineThickness (f);
	Ec_->rectangle_shape_obj.setOutlineColor (Ec_->C_outline_color);
}

void Error_class::main ()
{
	main_transition ();

	main_transform ();
}
void Error_class::ec_error_LFM_Tvus (unsigned long ul, const string& s)
{
	Error_class* Ec_ = getClass ();

	Ec_->b_error = true;
	if (Ec_->f_frame > 255)
	{
		Ec_->f_frame = 255;
	}

	Ec_->wstring_obj[e_error_text::report] = L"==========> ERROR [00000] <==========";
	Ec_->wstring_obj[e_error_text::function] = L"FUNCTION: void names::LoadFromMemory (Texture& T, void const* v, unsigned long ul, const string& s)";
	Ec_->wstring_obj[e_error_text::main_obj] = L"Texture& T";
	Ec_->wstring_obj[e_error_text::argument0] = L"void const* v";
	Ec_->wstring_obj[e_error_text::argument1] = L"unsigned long ul [ " + to_string (ul) + " ] ";
	Ec_->wstring_obj[e_error_text::argument2] = L"const string& s  [ " + s + " ] ";

	wcerr << endl
	      << Ec_->wstring_obj[e_error_text::report] << endl
	      << endl
	      << Ec_->wstring_obj[e_error_text::function] << endl
	      << endl
	      << Ec_->wstring_obj[e_error_text::main_obj] << endl
	      << Ec_->wstring_obj[e_error_text::argument0] << endl
	      << Ec_->wstring_obj[e_error_text::argument1] << endl
	      << Ec_->wstring_obj[e_error_text::argument2] << endl
	      << endl;
}
void Error_class::ec_error_LFM_Fvus (unsigned long ul, const string& s)
{
	Error_class* Ec_ = getClass ();

	Ec_->b_error = true;
	if (Ec_->f_frame > 255)
	{
		Ec_->f_frame = 255;
	}

	Ec_->wstring_obj[e_error_text::report] = L"==========> ERROR [00100] <==========";
	Ec_->wstring_obj[e_error_text::function] = L"FUNCTION: void names::LoadFromMemory (Font& F, void const* v, unsigned long ul, const string& s)";
	Ec_->wstring_obj[e_error_text::main_obj] = L"Font& F";
	Ec_->wstring_obj[e_error_text::argument0] = L"void const* v";
	Ec_->wstring_obj[e_error_text::argument1] = L"unsigned long ul [ " + to_string (ul) + " ] ";
	Ec_->wstring_obj[e_error_text::argument2] = L"const string& s  [ " + s + " ] ";

	wcerr << endl
	      << Ec_->wstring_obj[e_error_text::report] << endl
	      << endl
	      << Ec_->wstring_obj[e_error_text::function] << endl
	      << endl
	      << Ec_->wstring_obj[e_error_text::main_obj] << endl
	      << Ec_->wstring_obj[e_error_text::argument0] << endl
	      << Ec_->wstring_obj[e_error_text::argument1] << endl
	      << Ec_->wstring_obj[e_error_text::argument2] << endl
	      << endl;
}
void Error_class::ec_error_LFM_Ivus (unsigned long ul, const string& s)
{
	Error_class* Ec_ = getClass ();

	Ec_->b_error = true;
	if (Ec_->f_frame > 255)
	{
		Ec_->f_frame = 255;
	}

	Ec_->wstring_obj[e_error_text::report] = L"==========> ERROR [00200] <==========";
	Ec_->wstring_obj[e_error_text::function] = L"FUNCTION: void names::LoadFromMemory (Image& T, void const* v, unsigned long ul, const string& s)";
	Ec_->wstring_obj[e_error_text::main_obj] = L"Image& I";
	Ec_->wstring_obj[e_error_text::argument1] = L"void const* v";
	Ec_->wstring_obj[e_error_text::argument1] = L"unsigned long ul [ " + to_string (ul) + " ] ";
	Ec_->wstring_obj[e_error_text::argument2] = L"const string& s  [ " + s + " ] ";

	wcerr << endl
	      << Ec_->wstring_obj[e_error_text::report] << endl
	      << endl
	      << Ec_->wstring_obj[e_error_text::function] << endl
	      << endl
	      << Ec_->wstring_obj[e_error_text::main_obj] << endl
	      << Ec_->wstring_obj[e_error_text::argument0] << endl
	      << Ec_->wstring_obj[e_error_text::argument1] << endl
	      << Ec_->wstring_obj[e_error_text::argument2] << endl
	      << endl;
}
void Error_class::ec_error_LFM_Svus (unsigned long ul, const string& s)
{
	Error_class* Ec_ = getClass ();

	Ec_->b_error = true;
	if (Ec_->f_frame > 255)
	{
		Ec_->f_frame = 255;
	}

	Ec_->wstring_obj[e_error_text::report] = L"==========> ERROR [00300] <==========";
	Ec_->wstring_obj[e_error_text::function] = L"FUNCTION: void names::LoadFromMemory (SoundBuffer& SB, void const* v, unsigned long ul, const string& s)";
	Ec_->wstring_obj[e_error_text::main_obj] = L"SoundBuffer& SB";
	Ec_->wstring_obj[e_error_text::argument0] = L"void const* v";
	Ec_->wstring_obj[e_error_text::argument1] = L"unsigned long ul [ " + to_string (ul) + " ] ";
	Ec_->wstring_obj[e_error_text::argument2] = L"const string& s  [ " + s + " ] ";

	wcerr << endl
	      << Ec_->wstring_obj[e_error_text::report] << endl
	      << endl
	      << Ec_->wstring_obj[e_error_text::function] << endl
	      << endl
	      << Ec_->wstring_obj[e_error_text::main_obj] << endl
	      << Ec_->wstring_obj[e_error_text::argument0] << endl
	      << Ec_->wstring_obj[e_error_text::argument1] << endl
	      << Ec_->wstring_obj[e_error_text::argument2] << endl
	      << endl;
}
void Error_class::ec_error_LFM_Sss (const string& s0, const string& s1)
{
	Error_class* Ec_ = getClass ();

	Ec_->b_error = true;
	if (Ec_->f_frame > 255)
	{
		Ec_->f_frame = 255;
	}

	Ec_->wstring_obj[e_error_text::report] = L"==========> ERROR [00311] <==========";
	Ec_->wstring_obj[e_error_text::function] = L"FUNCTION: void names::LoadFromMemory (Shader& S, const string& s0, const string& s1)";
	Ec_->wstring_obj[e_error_text::main_obj] = L"Shader& S";
	Ec_->wstring_obj[e_error_text::argument0] = L"const string& s0 [ " + s0 + " ] ";
	Ec_->wstring_obj[e_error_text::argument1] = L"const string& s1 [ " + s1 + " ] ";

	wcerr << endl
	      << Ec_->wstring_obj[e_error_text::report] << endl
	      << endl
	      << Ec_->wstring_obj[e_error_text::function] << endl
	      << endl
	      << Ec_->wstring_obj[e_error_text::main_obj] << endl
	      << Ec_->wstring_obj[e_error_text::argument0] << endl
	      << Ec_->wstring_obj[e_error_text::argument1] << endl
	      << Ec_->wstring_obj[e_error_text::argument2] << endl
	      << endl;
}

// vector <Text>&

vector<Text>& Error_class::getText ()
{
	return getClass ()->text_obj;
}

// RectangleShape&

RectangleShape& Error_class::getRectangleShape ()
{
	return getClass ()->rectangle_shape_obj;
}
