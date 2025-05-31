#ifndef ERROR_CLASS_H_
#define ERROR_CLASS_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

enum e_error_text
{

	report = 0,
	function,
	main_obj,
	argument0,
	argument1,
	argument2,
	error

};

class Error_class
{
	private:
		static Error_class* m_class_obj;

		Error_class ();

	protected:
		RectangleShape m_rectangle_shape;

		vector<Text> m_text;

		vector<wstring> m_wstring;

		bool m_b_error;

		Color m_C_rectangle_shape_color;
		Color m_C_outline_color;
		Color m_C_text_color;

		unsigned m_u_font_scale;

		float m_f_frame;
		float m_f_animation_speed;
		float m_f_time_to_destroy;

		static void main_transition ();
		static void main_transform ();

	public:
		static Error_class* getClass ();

		static void main ();
		static void ec_error_LFM_Tvus (unsigned long ul, const string& s);
		static void ec_error_LFM_Fvus (unsigned long ul, const string& s);
		static void ec_error_LFM_Ivus (unsigned long ul, const string& s);
		static void ec_error_LFM_Svus (unsigned long ul, const string& s);
		static void ec_error_LFM_Sss (const string&, const string&);

		static vector<Text>& getText ();
		static RectangleShape& getRectangleShape ();
};

#endif
