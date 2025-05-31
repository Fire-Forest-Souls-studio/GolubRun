#include "button.h"

class ImageButton : public Button
{
	private:
		Texture m_texture;

	public:
		using Button::Button;

		void setTexture ();

		Texture& getTexture ();
};
