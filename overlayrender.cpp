#include "overlayrender.h"

OverlayRender::OverlayRender() {}

QImage OverlayRender::getImage() const
{
    return image;
}

void OverlayRender::setImage(const QImage &newImage)
{
    image = newImage;
}

/*
 * Setter override for if only a file name can be given
 */
void OverlayRender::setImage(const QString fileName)
{
    image = QImage(fileName);
}
