#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/pc_mouse.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/error_class.h"

#include "../../../GetPixels/GPS.h"

int main (int argc, char* argv[0])
{
	// Under

	srand (time (NULL));
	names::LoadFromMemory (names::F_pixel, pixel_font_by_BLACKFIRE_otf, pixel_font_by_BLACKFIRE_otf_size, "Shrift/pixel_font_by_BLACKFIRE.otf");
	names::SetPath (argv[0]);

	////////////////////////

	WindowAndStyles::start ();

	while (WindowAndStyles::isOpen ())
	{
		WindowAndStyles::main ();
		if (names::f_time != 0.0)
		{
			PC_Mouse::main ();
		}
		if (names::f_time != 0.0)
		{
			Error_class::main ();
		}

		WindowAndStyles::clear ();
	}

	return 0;
}
