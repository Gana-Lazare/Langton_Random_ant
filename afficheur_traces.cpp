//	TP_Qt2 L3 EEA - 2019

#include "afficheur_traces.h"

AfficheurTraces:: AfficheurTraces(QImage * im, QGraphicsItem *parent )
    : QGraphicsPixmapItem(parent), _imageInd(im)
{
    setScale(10);  // échelle interne, ne pas modifier
}

QRectF AfficheurTraces::boundingRect()const
{
    if (_imageInd->isNull())
        return QRectF();
    return QRectF(offset(), _imageInd->size());
}



void AfficheurTraces::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    painter->setRenderHint(QPainter::SmoothPixmapTransform,transformationMode()== Qt::SmoothTransformation);
  //
    painter->drawImage(offset(),* _imageInd);
    QGraphicsPixmapItem::paint(painter, option, widget);
}
