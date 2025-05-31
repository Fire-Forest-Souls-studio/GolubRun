#include "../../includes/Classes/image_button.h"

void ImageButton::setTexture ()
{
	m_rectangle_shape.setTexture (&m_texture);
}

Texture& ImageButton::getTexture ()
{
	return m_texture;
}
