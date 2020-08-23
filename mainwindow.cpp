//HAMRIOUI GANA LAZARE
//	TP_Qt2 L3 EEA - 2019

#include "mainwindow.h"
#include "afficheur_traces.h"
#include "InterfaceAutomate.h"
#include <QtWidgets>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // widget central et layout
    centralWidget = new QWidget;
    setCentralWidget(centralWidget);    //*UN WIDGET CENTRAL

    QHBoxLayout *layout = new QHBoxLayout(centralWidget); // *LAYOUT DE TYPE QHBOXLAYOUT

    // *paramètres de la fenetre principale
    resize(1000,680);
    setWindowTitle("L3 TP2");

    //Création d'une icon pour l'application
    setWindowIcon(QIcon("icon.gif"));

    // Création du Menu
    Option = new QMenu(this);
    Option = menuBar()->addMenu("&Option");
    run = Option->addAction("&Marche");
    stop = Option->addAction("&Stop");
    ralentir= Option->addAction("&Ralentir");
    reinitialiser = Option->addAction("&Réinitialiser");
    accelerer = Option->addAction("&Accelerer");
    sortir = Option -> addAction("&quitter");
    poluant=Option->addAction("&poluant");
    couleurfourmie=Option->addAction("&couleur fourmie");
    couleurtrace=Option->addAction("&Couleur Trace");

    //Création de la Toolbar
    QToolBar * toolbar = addToolBar("file");
    QAction * newact1 = new QAction(QIcon("a.png"),"&Marche",this);
    QAction * newact2 = new QAction(QIcon("b.png"),"&Arret",this);
    QAction * newact3 = new QAction(QIcon("c.png"),"&Ralentir",this);
    QAction * newact4 = new QAction(QIcon("d.png"),"&Accelerer",this);
    QAction * newact5 = new QAction(QIcon("e.png"),"&Aide",this);
    QAction * newact6 = new QAction(QIcon("f.png"),"&Chronometre",this);
    QAction * newact7 = new QAction(QIcon("g.png"),"&Ajouter une fourmie",this);
    QAction * newact8 = new QAction(QIcon("i.PNG"),"Supprimer une fourmie",this);

    newact1->setToolTip("Marche");
    newact2->setToolTip("arret");
    newact3->setToolTip("Ralentir");
    newact4->setToolTip("Accelerer");
    newact5->setToolTip("Aide");
    newact6->setToolTip("Chronometre");
    newact7->setToolTip("Ajouter une fourmie");
    newact8->setToolTip("Supprimer une fourmie");

    toolbar->addAction(newact1);
    toolbar->addAction(newact2);
    toolbar->addAction(newact3);
    toolbar->addAction(newact4);
    toolbar->addAction(newact5);
    toolbar->addAction(newact6);
    toolbar->addAction(newact7);
    toolbar->addAction(newact8);
  //  raccourci = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")),this);
//connect(raccourci,&QShortcut::triggered,this,&MainWindow::accelereration);
    // création de la scène et de la vue
    //  (paramètres de l'automate = nombre_fourmis, nombre de cases en largeur et hauteur
    vueAutomate = new InterfaceAutomate(4,300,200,this);
    layout->addWidget(vueAutomate);

    // *le timer pour animation
    timerFourmis = new QTimer(this);

    timerFourmis->setInterval(vitesse*20);     // fixe la vitesse initiale de l'animation


    connect(timerFourmis,&QTimer::timeout,vueAutomate,&InterfaceAutomate::NouvelEtat);
    timerFourmis->start();
          // Timer pour une animation plus rapide
    connect(accelerer,&QAction::triggered,this,&MainWindow::accelereration);
    connect(newact4,&QAction::triggered,this,&MainWindow::accelereration);
          //Timer pour Ralentir l'animation
    connect(ralentir,&QAction::triggered,this,&MainWindow::ralentir_m);
    connect(newact3,&QAction::triggered,this,&MainWindow::ralentir_m);
    //Timer pour arreter l'animation
    connect(stop,&QAction::triggered,this,&MainWindow::arret_fourmis);
    connect(newact2,&QAction::triggered,this,&MainWindow::arret_fourmis);

    //Timer pour jouer l'animation
    connect(run,&QAction::triggered,this,&MainWindow::play);
    connect(newact1,&QAction::triggered,this,&MainWindow::play);
    //posible de faire du pas à pas
//    connect(reinitialiser,&QAction::triggered,this,&InterfaceAutomate::NouvelEtat);
//    timerFourmis->start();
connect(newact6,&QAction::triggered,this,&MainWindow::chronometre);
connect(sortir,&QAction::triggered,this,&MainWindow::sortir_quitter);

//connect(reinitialiser,&QAction::triggered,this,&InterfaceAutomate::CreeAutomate);

//Ajouter une fourmis fourmis

connect(newact7,&QAction::triggered,this,&MainWindow::ajouter);
//Supprimer une fourmie
connect(newact8,&QAction::triggered,this,&MainWindow::supprimer);
    // pour forcer réjustement des dimensions au démarrage
    QSize s = rect().size();
    QCoreApplication::postEvent(this,new QResizeEvent(s,s));
//Ajouter des poluants
    connect(poluant,&QAction::triggered,this,&MainWindow::marquage_aleatoire);
    //couleur fourmie
    connect(couleurfourmie,&QAction::triggered,this,&MainWindow::couleur_foumie);

//Couleur Trace
    connect(couleurtrace,&QAction::triggered,this,&MainWindow::couleur_trace);

//Couleur Fond
//    connect(couleurfond,&QAction::triggered,this,&MainWindow::couleur_fond);

    // exemples de méthodes que vous pouvez utilisez pour modifier la représentation graphique
    vueAutomate->SetCouleurFond(QColor(250,250,255));
    vueAutomate->SetCouleurTrace(QColor(00,255,00),1);     // change la couleur des traces de la fourmi indice 1
    vueAutomate->SetCouleurFourmi(QColor(0,0,250),3);       // change la couleur de la fourmi indice 3

    //Bare de status
 barreEtat = new QStatusBar;
 barreEtat = statusBar();

 QProgressBar *progressBar = new QProgressBar();

    label1 = new QLabel(); //créé le Label

    label1->setIndent(3); //indente le texte de 3 pixels

    label2 = new QLabel();//créé un 2° label

    label2->setIndent(3);

    statusBar()->addWidget( label1, 1 );

    statusBar()->addWidget( label2, 1 );

    label1->setText(QVariant(vitesse).toString());





    // autres commandes possibles à tester
    /*  vueAutomate->MarquageAleatoire(3);
        int n =vueAutomate->AjouterFourmi();                // ajoute une fourmi, position aléatoire
        vueAutomate->SetCouleurTrace(QColor(250,0,250),n);  // change la couleur de la trace de la nouvelle fourmi
    */


}

//Création d'une fonction pour accelerer l'automate
void MainWindow::accelereration(){
    //QDialog * monedit = new QDialog(this);
    //monedit->show();
    //monedit->resize(200,400);
    label1->setText(QVariant(vitesse).toString());
    vitesse =vitesse*2;
    timerFourmis->setInterval(10/vitesse);
    if(vitesse==256){
        barreEtat->showMessage(tr("MAXIMUM"),500);}


}
//Fonction pour ralentir les fourmis
void MainWindow::ralentir_m(){
//    QDialog * monedit1 = new QDialog(this);
//    monedit1->show();
//    monedit1->resize(200,400);
vitesse= vitesse*2;
    timerFourmis->setInterval(vitesse);
    label1->setText(QVariant(vitesse/4).toString());
}
//Fonction pour Arreter les fourmis
void MainWindow::arret_fourmis(){
    timerFourmis->stop();
        barreEtat->showMessage("Animation à l'arret");
}
void MainWindow::play(){
    timerFourmis->start();
}
void MainWindow::chronometre(){
//    QMessageBox msgbox;
//    msgbox.setText("");
//    msgbox.exec();
    x = new QWidget;
    x->resize(200,200);
   central_x = new QWidget(x);
//     affiche_chrono = new QLabel(central_x);
//     affiche_chrono->setText("Chronometre:");
//     affiche_chrono->move(20,20);
    x->setWindowTitle("Chronometre");

//    chrono = new QTimer(x);

x->show();
//    var_chrono++;
//    chrono->setInterval(100);
    // Création d'un afficheur LCD de 5 digits maximum
           m_LCD = new QLCDNumber(5, central_x);
           // Création des contrôles de type bouton
           m_Bouton_StartStop = new QPushButton("Start",central_x);
           m_Bouton_Reset = new QPushButton("Reset",central_x);

           // Gestion du layout pour le placement des boutons
           QGridLayout *layout = new QGridLayout(central_x);
           layout->addWidget(m_LCD, 0, 0);
           layout->addWidget(m_Bouton_StartStop, 2,0);
           layout->addWidget(m_Bouton_Reset, 2,1);
           x->setLayout(layout);

           // On met à zéro le compteur représentant le nombre de secondes
           m_Timer_value=0;
           // Création du timer
           m_timer = new QTimer(central_x);
           // À chaque fin d'intervalle, exécution du slot update()
           connect(m_timer, SIGNAL(timeout()), this, SLOT(updatechrono()));
           // On applique un intervalle d'une seconde (1000 ms) entre chaque timeout du timer
           m_timer->setInterval(1000);
           // Sert pour la gestion du bouton "Start" "Stop"
           validStart=true;

           // On connecte les différents signaux et slots
           connect(m_Bouton_StartStop, SIGNAL(clicked(bool)), this, SLOT(click_StartStop(bool)));
           connect(m_Bouton_Reset, SIGNAL(clicked(bool)), this, SLOT(click_Reset(bool)));



    barreEtat->showMessage("helllo");

}
void MainWindow::click_StartStop(bool valid)
 {
     //Si on clique sur "Start"
     if(validStart == true)
     {
         // Affiche "Stop" sur le bouton
         m_Bouton_StartStop->setText("Stop");
         // Permet de savoir que le bouton est en mode "Stop"
         validStart = false;
         // On déclenche le départ du Timer
         m_timer->start();
     }
     // Si on clique sur "Stop"
     else
     {
         // Affiche "Start" sur le bouton
         m_Bouton_StartStop->setText("Start");
         // Permet de savoir que le bouton est en mode "Start"
         validStart = true;
         // On arrête le compteur
         m_timer->stop();
     }
 }
void MainWindow::updatechrono()
   {
       // On incrémente notre compteur de secondes
       m_Timer_value++;
       // On affiche le nombre de secondes écoulées dans le contrôle QLCDNumber
       m_LCD->display(m_Timer_value);
   }

void MainWindow::couleur_foumie(){
    vueAutomate->SetCouleurFourmi(3);
}
void MainWindow::aide_help(){
//crée une fenetre personnalisé
    }
void MainWindow::couleur_trace(){

    vueAutomate->SetCouleurTrace(2);

}


//void MainWindow::couleur_fond(){
//    vueAutomate->SetCouleurFond();
//}
void MainWindow::ajouter()
{
    vueAutomate->AjouterFourmi();
}
void MainWindow::supprimer(){
    vueAutomate->SupprimerFourmi();
}
void MainWindow::sortir_quitter(){
    int reponse = QMessageBox::question (this, "Titre de la fenetre" ,"Voulez vous Fermer la fenetre mere?", QMessageBox::Yes, QMessageBox::No);
    if (reponse == QMessageBox::No)
    {//Conserve la fenetre
    }
    else
    {//fermeture de la fenetre
        this->close();
    }
}
void MainWindow::marquage_aleatoire(){
    vueAutomate->MarquageAleatoire();

}




