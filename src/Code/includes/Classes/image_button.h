#include "button.h"

class ImageButton : public Button
{
	private:
		Texture texture_obj;

	public:
		using Button::Button;

		void setTexture ();

		Texture& getTexture ();
};
