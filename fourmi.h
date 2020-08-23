//	TP_Qt2 L3 EEA - 2019

#ifndef FOURMI_H
#define FOURMI_H

#include <QGraphicsRectItem>
#include <QMargins>

class Fourmi : public QGraphicsRectItem
{
    int _identifiant;
    bool _bVivante;

public:
    Fourmi(int ind, QGraphicsItem *parent = Q_NULLPTR);

    void initPos(int x, int y, int dir);
    int indice()    { return _identifiant;}
    void avance();

    void kill()      { _bVivante = false; }
    bool isVivante() {return _bVivante;}

protected:
    virtual QRectF boundingRect()const override
    {
        // rajout de marge pour reaffichage propre des contours
        QRectF r = QGraphicsRectItem::boundingRect();
        return r.marginsAdded(QMarginsF(1.5,1.5,1.5,1.5));
    }
};

#endif // FOURMI_H
