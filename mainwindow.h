//HAMRIOUI GANA LAZARE
//	TP_Qt2 L3 EEA - 2019


#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QtWidgets>
#include <QMainWindow>
#include "InterfaceAutomate.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QMenu * Option;
    QAction * run;
    QAction * stop;
    QAction * ralentir;
    QAction * reinitialiser;
    QAction * accelerer;
    QAction * sortir;
    QLabel * text;
    QLabel * label1;
    QLabel * label2;
    QWidget * x;
    QWidget * central_x;
    float vitesse =1;
    QTimer * chrono;
    int var_chrono=0;
    QLabel * affiche_chrono;
    QShortcut * raccourci;
    QStatusBar * barreEtat ;
    QAction * poluant;
    QAction * couleurfourmie;
    QAction * couleurtrace;
    QAction * couleurfond;

    // Bouton servant de "Start" "Stop"
       QPushButton* m_Bouton_StartStop;
       // Bouton "Reset"
       QPushButton* m_Bouton_Reset;
       // Afficheur de type LCD
       QLCDNumber* m_LCD;
       // Variable représentant le nombre de secondes écoulées depuis le lancement du timer
       int m_Timer_value;
       // Timer servant de base à notre chronomètre
       QTimer* m_timer;
       // Permet de savoir si l'utilisateur a cliqué sur "Start" ou "Stop"
       bool validStart;





    // les composants de la fenetre principale
    QWidget * centralWidget;        //Création d'un widget central
    InterfaceAutomate* vueAutomate; //CREATION FED LA VU DE TYPE interfaceautomate
    QTimer * timerFourmis;          //Création d'un timer

public:
    explicit MainWindow(QWidget *parent = 0);


protected:
    void resizeEvent(QResizeEvent *)
    {
        // événement redéfini pour ajuster l'affichage à la fenetre
        vueAutomate->ajusteEchelle();
    }
public slots:
    void accelereration();
    void ralentir_m();
    void arret_fourmis();
    void play();
    void chronometre();
    void aide_help();
    void sortir_quitter();
    void ajouter();
    void supprimer();
    void marquage_aleatoire();
    void click_StartStop(bool valid);
    void updatechrono();
    void couleur_foumie();
    void couleur_trace();

//    void couleur_fond();




};

#endif // MAINWINDOW_H
