//	TP_Qt2 L3 EEA - 2019

#ifndef AFFICHETRACE_H
#define AFFICHETRACE_H
#include <QtWidgets>


// spécialisation de la  classe GraphicsPixmap pour mise à jour dynamique de l'image associée
class AfficheurTraces : public QGraphicsPixmapItem
{
    QImage * _imageInd;

public:
    AfficheurTraces(QImage *,QGraphicsItem *parent = Q_NULLPTR );

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

};

#endif // AFFICHETRACE_H
