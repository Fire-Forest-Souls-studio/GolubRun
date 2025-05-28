#include "../../includes/Classes/image_button.h"

void ImageButton::setTexture ()
{
	m_rectangle_shape.setTexture (&texture_obj);
}

Texture& ImageButton::getTexture ()
{
	return texture_obj;
}
