//	TP_Qt2 L3 EEA - 2019

#include "fourmi.h"
#include <stdlib.h>
#include <QPen>
#include <QtCore>

Fourmi::Fourmi(int ind, QGraphicsItem *parent)
    :QGraphicsRectItem(parent), _identifiant(ind)
{
    setScale(1/10);
    setRect(-5,-5,10,10);
    _bVivante=true;

    setTransformOriginPoint(.5,.5);
    setPen(Qt::NoPen);
}

void Fourmi::avance()
{
    if (!_bVivante)
        return;

    int x = 0,y=0;
    int dir=int(rotation()/90)%4;  // direction actuelle réduite aux 4 axes NSEO
    if (!(dir%2))
        x = (dir==0)?1:-1;
    else
        y = (dir==3)?1:-1;

    // gestion des bords du territoire :
    QPoint p=pos().toPoint();

    int nX = p.x() + x;
    int nY = p.y() + y;

    if (nX >= parentItem()->boundingRect().width())//  nLargeurTerritoire)
        nX = 0;
    if (nX < 0)
        nX = parentItem()->boundingRect().width()-1;
    if (nY >= parentItem()->boundingRect().height())
        nY = 0;
    if (nY < 0)
        nY = parentItem()->boundingRect().height()-1;

    setPos(nX,nY);  // nouvelle position de la fourmi
}

