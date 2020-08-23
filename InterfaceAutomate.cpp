#include "InterfaceAutomate.h"

InterfaceAutomate::InterfaceAutomate(int nbFourmis, int largeur, int hauteur, QWidget* parent)
 : QGraphicsView(parent)
{
    // paramètres de l'automate de la scène
    _nLargeurTerritoire = qMin(largeur, MAX_TAILLE);
    _nHauteurTerritoire = qMin(hauteur, MAX_TAILLE);
    _marge = 5;         // marge d'affichage autour du territoire des fourmis

    // couleurs de traces et fourmis - valeur par défaut
    vectCouleurTrace.insert(0,QColor("white").rgb());       // couleur des cases vides
    vectCouleurTrace.insert(1,NB_MAX_FOURMIS, QColor("green").rgb());
    vectCouleurFourmi.insert(0,NB_MAX_FOURMIS+1,QColor("red").rgba());
    _nbreIterations=0;
    _echelleInterne=10;
    _nbreFourmisVivantes=0;

    // association d'une la scene graphique
    sceneAutomate=new QGraphicsScene(parent);
    setScene(sceneAutomate);

    InitialiseScene(nbFourmis);
}


void InterfaceAutomate::CreeAutomate(int nbFourmis, int largeur, int hauteur )
{
    // taille de la scène
    _nLargeurTerritoire = qMin(largeur, MAX_TAILLE);
    _nHauteurTerritoire = qMin(hauteur, MAX_TAILLE);

    // suppression des items actuels et des fourmis
    sceneAutomate->removeItem(afficheTraces);
    delete afficheTraces;
    sceneAutomate->removeItem(rectContours);
    delete rectContours;
    lesFourmis.erase(lesFourmis.begin(), lesFourmis.end());
    _nbreFourmisVivantes=0;

    InitialiseScene(nbFourmis);

    // ajustement de la taille de la vue
    ajusteEchelle();
}


void InterfaceAutomate::InitialiseScene(int nbFourmis )
{

    // création de la nouvelle image des traces de passage
    imageTerritoire = new QImage(_nLargeurTerritoire, _nHauteurTerritoire ,QImage::Format_Indexed8);
    imageTerritoire->setColorTable(vectCouleurTrace);
    imageTerritoire->fill(0);       // initialement vierge

    // affichage et ajustement des tailles
    afficheTraces=new AfficheurTraces(imageTerritoire);
    sceneAutomate->addItem(afficheTraces);
    afficheTraces->setScale(_echelleInterne);
    QRectF r2 = afficheTraces->mapRectToScene(afficheTraces->boundingRect());
    rectContours=sceneAutomate->addRect(r2);
    setSceneRect(r2.marginsAdded(QMargins(_marge,_marge,_marge,_marge)));

    // création fourmis (position aléatoire)
    for (int i=0;i<nbFourmis;i++)
    {
        AjouterFourmi();
    }

}

int InterfaceAutomate::AjouterFourmi(int xCase, int yCase, int dir)
{
    // vérification du maximum
    if (lesFourmis.size() >= NB_MAX_FOURMIS)
        return -1;

    // ajouter une nouvelle fourmi à la liste des fourmis
    int indice = lesFourmis.size()+1;
    auto f  = new Fourmi(indice, afficheTraces);
    lesFourmis.append(f);
    _nbreFourmisVivantes++;

    // paramètre d'affichage
    f->setScale(1.0/_echelleInterne);
    f->setBrush(QBrush(vectCouleurFourmi[indice]));

    // vérif coordonnées : initialisation aléatoire si besoin
    if (xCase < 0 || xCase >= _nLargeurTerritoire)
        xCase= rand() % _nLargeurTerritoire ;
    if (yCase < 0 || yCase >= _nHauteurTerritoire)
        yCase = rand() % _nHauteurTerritoire ;
    f->setPos(xCase,yCase);

    // orientation de la fourmi
    if (dir < 0)
        dir = rand() % 4;
    f->setRotation(90*dir);
    return indice-1;
}


void InterfaceAutomate::NouvelEtat()		// détermine l'évolution de l'univers  à t+1
{
    for (int i=0;i<lesFourmis.size();i++)
    {
        Fourmi * fourmi=lesFourmis[i];
        if (!fourmi->isVivante())       // pas active, on ne fait rien
            continue;

        // coordonnées actuelles de la foumi et valeur du pixel (pixel contient indice de la trace)
        QPoint p = fourmi->pos().toPoint();
        uchar * pixel= nullptr;
        if (imageTerritoire->valid(p))
            pixel=imageTerritoire->scanLine(p.y())+p.x();

        if (*pixel >0)      // si case marquée
        {
            // on efface la trace
            *pixel=0;
            // rotation de la fourmi antihoraire
            fourmi->setRotation(fourmi->rotation()-90);
        }
        else                // case vide
        {
            // marque la case avec son indice
            *pixel=fourmi->indice();
            // rotation de la fourmi horaire
            fourmi->setRotation(fourmi->rotation()+90);
        }
        fourmi->avance();
    }

    _nbreIterations++;
    emit iterationIncremented(_nbreIterations);
}


void InterfaceAutomate::SupprimerFourmi(int numero, bool bHide, bool bSupprimeTrace)
{
    if (_nbreFourmisVivantes == 0)
        return;

    while (numero < 0)			// tirage aléatoire parmi les vivantes
    {
        int n= rand() % lesFourmis.size();
        if (lesFourmis[n]->isVivante())
            numero = n;
    }

    if (numero > lesFourmis.size())
        return;

    lesFourmis[numero]->kill();
    _nbreFourmisVivantes--;

    if (bHide)
        lesFourmis[numero]->hide();
    if (bSupprimeTrace)
        EffacerTrace(numero);
}

void InterfaceAutomate::EffacerTrace(int numero)
{
    if (numero++< 0)
        return;
    if (numero >lesFourmis.size())
        return;

    // recherche et suppression de tous les marquages correspondant à la fourmi
    // parcourt de tous les pixels
    for (int y=0;y<imageTerritoire->height();y++)
    {    uchar * l =imageTerritoire->scanLine(y);
        for (int x=0;x<imageTerritoire->width();x++)
        {
            uchar * p=l+x;
            if (*p==numero)  // si correspond
                *p=0;        // remis à zéro
        }
    }
    afficheTraces->update();
}

void InterfaceAutomate::SetCouleurFond(QColor c, bool flagRedraw)
{
    vectCouleurTrace.replace(0,c.rgb());    // couleur des cases vides
    imageTerritoire->setColorTable(vectCouleurTrace);

    // selon flag redessiner tout
    if (flagRedraw)
        afficheTraces->update();
}

void InterfaceAutomate::SetCouleurFourmi(QColor c, int numero )
{
    if (numero <0){
        for (int indF = 0; indF < NB_MAX_FOURMIS; indF++)
        {
            vectCouleurFourmi[indF] =c.rgb();

            if (indF < _nbreFourmisVivantes)
                lesFourmis[indF]->setBrush(QBrush(c.rgb()));
        }
    }
    else
    {
        if (numero < NB_MAX_FOURMIS)
            vectCouleurFourmi[numero]=c.rgb();

        if (numero < _nbreFourmisVivantes)
            lesFourmis[numero]->setBrush(QBrush(c.rgb()));
    }
    update();
    }

void InterfaceAutomate::SetCouleurTrace(QColor c, int fourmi , bool flagRedraw)
{
    if (fourmi < 0)  // valeur négative -> on applique aux traces toutes les fourmis
        for (int indF = 0; indF < NB_MAX_FOURMIS; indF++)
        {
            vectCouleurTrace[indF+1] =c.rgb();
        }
    else if (fourmi < NB_MAX_FOURMIS)
        vectCouleurTrace[fourmi+1]=c.rgb();

    imageTerritoire->setColorTable(vectCouleurTrace);

    // selon flag redessiner aussi les traces anciennes
    if (flagRedraw)
        afficheTraces->update();
}

QColor InterfaceAutomate::GetCouleurFourmi(int numero)
{
    if((numero <0) ||(numero >= lesFourmis.size()))
        return QColor(vectCouleurTrace[0]);
    if (!lesFourmis[numero]->isVivante())
         return QColor(vectCouleurTrace[0]);

    // si fourmi ok
    return QColor(vectCouleurFourmi[numero]);
}

QColor InterfaceAutomate::GetCouleurTrace(int numero)
{
    if((numero <0) ||(numero >= lesFourmis.size()))
        return QColor(vectCouleurTrace[0]);

    // si fourmi ok
    return QColor(vectCouleurTrace[numero+1]);
}

int InterfaceAutomate::GetFourmiCase(QPointF pos)
{
    for (int i=0; i< lesFourmis.size(); i++)
    {
        if (lesFourmis[i]->isVivante())
        {
            if (lesFourmis[i]->pos()==pos.toPoint())
                return i;
        }
    }
    return -1;
}

int InterfaceAutomate::GetFourmiTraceCase(QPointF pos)
{
    int xCase=pos.x();
    int yCase=pos.y();
    uchar *ptrPixel=imageTerritoire->scanLine(yCase)+xCase;
    return (*ptrPixel)-1;
}

void InterfaceAutomate::MarquageAleatoire(int densite, QColor c)
{
    // marquage de cellules choisies aléatoirement

    // insertion de la couleur dans la palette
    vectCouleurTrace.push_back(c.rgba());
	 imageTerritoire->setColorTable(vectCouleurTrace);
    int indexT=vectCouleurTrace.size()-1;

    // parcours du territoire, et décision (stochastique) de changement
    for (int x=0;x<_nLargeurTerritoire;x++)
        for (int y=0;y<_nHauteurTerritoire;y++)
        {
            if ((rand()%100) < densite)  // tirage aléatoire
            {
                // inversion de l'état du pixel
                uchar *pixel=imageTerritoire->scanLine(y)+x;
                if (*pixel)
                    *pixel=0;
                else
                    *pixel=indexT;
            }
        }
}

