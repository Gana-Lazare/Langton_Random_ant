#ifndef INTERFACEAUTOMATE_H
#define INTERFACEAUTOMATE_H

#include <QtWidgets>
#include "fourmi.h"
#include "afficheur_traces.h"


// valeurs prédéfinies pour limiter la taille des tableaux internes
const int NB_MAX_FOURMIS = 20;			// nombre maximum de fourmis affichées
const int MAX_TAILLE = 800;             // taille maximale de l'univers (nombre de cases)

class InterfaceAutomate : public QGraphicsView
{
    Q_OBJECT

    QGraphicsScene * sceneAutomate;     // la scène graphique associée

    // objets graphique de la scène
    QImage * imageTerritoire;
    AfficheurTraces * afficheTraces;
    QGraphicsRectItem * rectContours;
    QVector <Fourmi*> lesFourmis;


    // paramètres du territoire
    int _nbreFourmisVivantes;				// nombre effectif de fourmis créées
    int _nLargeurTerritoire;                // largeur du territoire (nombre de cases)
    int _nHauteurTerritoire;                // hauteur du territoire (nombre de cases)
    double _echelleInterne;                 // gestion interne de l'échelle
    int   _marge;                           // marge d'affichage autour du territoire des fourmis

    // couleurs
    // la couleur des cases vide est (nécessairement) à l'indice 0 du vecteur des traces
    QVector <QRgb> vectCouleurTrace;    // (NB_MAX_FOURMIS);
    QVector <QRgb> vectCouleurFourmi;

    // variables de l'animation
    int _nbreIterations;

    // fonction  private (appel interne uniquement)
    void InitialiseScene(int nbFourmis );

public:
    InterfaceAutomate(int nbFourmis=2, int largeur=200, int hauteur=150, QWidget* parent=nullptr);
        // constructeur, avec paramètres et valeurs par défaut
        //   les dimensions correspondent au nombre de cases en largeur et hauteur

    void ajusteEchelle()
    {
        // utilisée pour ajustement lors du redimensionnement de la fenetre
         fitInView(sceneAutomate->sceneRect(),Qt::KeepAspectRatio);
    }

    void CreeAutomate(int nbFourmis=2, int largeur=200, int hauteur=150);
            // initialise un nouvel automate vierge et supprime la précédente
            // A utiliser également pour modifier les dimensions (nombre de cases)

    int AjouterFourmi(int xCase = -1, int yCase = -1, int dir = -1);
            // ajoute une nouvelle fourmi, paramètres = indice en x et y de la case
            //									dir = orientation valeur 0 à 3 (-1 pour sélection aléatoire)
            // sans paramètres : position et orientation par tirage aléatoire

    void SupprimerFourmi(int numero = -1, bool bHide=false, bool bSupprimeTrace=false);
            // supprime une fourmi, paramètre indique le numéro de la fourmi à supprimer,
            //	par défaut -1 --> sélection aléatoire de la fourmi supprimée

    void EffacerTrace(int numero);
            // efface les traces de la fourmi numéro (indice en paramètre obligatoire)

    void MarquageAleatoire(int densite=10, QColor c= Qt::black);
            // inverse aléatoirement une certain pourcentage de cellule
            // densite  de [1 à 99] fixe le nombre de cellules modifiées sur 100)


    // modification des couleurs pour l'affichage du territoire, des fourmis et des traces
    void SetCouleurFond(QColor c, bool flagRedraw=false);
            // change la couleur des cases vides de la scéne,
            // le flag force le réaffichage pour application immédiate à toutes les cases
    void SetCouleurFourmi(QColor c, int numero = -1);
            // le paramètre numéro indique la fourmi à modifier,
            //              -1 (par défaut) --> modification appliquée à toutes les fourmis

    void SetCouleurTrace(QColor c, int fourmi = -1, bool flagRedraw=false);
            // le paramètre numéro indique la fourmi à modifier,
            //              -1 (par défaut) --> modification appliquée à toutes les fourmis


    // pour obtenir les informations d'état
    int nbreIterations()        { return _nbreIterations; }

    int nbreFourmisVivantes()   { return _nbreFourmisVivantes; }

    QColor GetCouleurFond() {return QColor(vectCouleurTrace[0]);}
    QColor GetCouleurFourmi(int numero) ;
        // retourne la couleur de la fourmi, si numéro correspond à une fourmi vivante, sinon retourne couleur du fond
    QColor GetCouleurTrace(int numero) ;
        // retourne la couleur de la trace si numéro correspond à une fourmi vivante, sinon retourne couleur du fond

    int GetFourmiCase(QPointF pos);
        // retourne le numéro de la fourmi sur la case en pos (x,y) ;
        // retourne -1 s'il n'y a pas de fourmi

    int GetFourmiTraceCase(QPointF pos);
        // retourne le numéro de la fourmi qui a marquée la case en pos ;
        // retourne -1 s'il n'y a pas de trace

public slots:
    void NouvelEtat();
            // détermine l'évolution de l'univers de Automate pour un cycle (t --> t+1)

signals:
    void iterationIncremented(int);
            // une nouvelle itération a été faite


protected:
    // utilisation des événement - en commentaires démonstration de l'utilisation des coordonnées dans ce tp

    virtual void mousePressEvent(QMouseEvent *mouseEvent) override
    {
        QPoint  pos1= mouseEvent->pos();                    // coordonnées dans la vue
        QPointF pos2=mapToScene(pos1);                      // coordonnées dans la scène
        QPointF  pos3= afficheTraces->mapFromScene(pos2);   // coordonnées en cases du territoire
        Q_UNUSED(pos3);

        // utiliser pos3 pour tester GetFourmiCase(pos3) ou GetFourmiTraceCase(pos3);

    }

};

#endif // INTERFACEAUTOMATE_H
