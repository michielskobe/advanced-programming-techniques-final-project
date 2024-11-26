#ifndef OVERLAYRENDER_H
#define OVERLAYRENDER_H
#include <QImage>
#include <QString>

class OverlayRender
{
public: // constructors/destructors
    OverlayRender();
    ~OverlayRender() = default;
    OverlayRender(QString fileName);

public: // attributes
    QImage image;

public: // methods

    QImage getImage() const;
    void setImage(const QImage &newImage);
    void setImage(const QString fileName);
};

#endif // OVERLAYRENDER_H
