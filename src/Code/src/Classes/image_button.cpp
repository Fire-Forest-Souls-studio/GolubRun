#include "../../includes/Classes/image_button.h"

void ImageButton::setTexture ()
{
	rectangle_shape_obj.setTexture (&texture_obj);
}

Texture& ImageButton::getTexture ()
{
	return texture_obj;
}
