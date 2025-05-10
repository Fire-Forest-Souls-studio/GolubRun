#include "button.h"

class ImageButton : public Button
{
		// TODO: рефакторинг переменный по шаблону <m_TyPe_my_name>
		// TODO: добавить названия аргументам функций по шаблону <my_name>

	private:
		Texture texture_obj;

	public:
		using Button::Button;

		void setTexture ();

		Texture& getTexture ();
};
