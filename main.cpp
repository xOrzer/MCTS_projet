#include <iostream>
#include "game.h"
#include "noeud.h"
#include "mcts.h"
#include <string>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>


using namespace std;

string press_touch(Game &game){
    string press;
    cout<<"Press une touche : ";
    cin>>press;
    if(press == "z"){
        game.top();
        return "z";
    }
    else if(press == "s"){
        game.down();
        return "s";
    }
    else if(press == "q"){
        game.left();
        return "q";
    }
    else if(press == "d"){
        game.right();
        return "d";
    }
    else if(press == "x"){
        return "x";
    }
    else{
        while(press != "q" || press != "d" || press != "s" || press != "z"){
            cout<<"Press q or d or s or z fdp : ";
            cin>>press;

            if(press == "z"){
                game.top();
                return "z";
            }
            else if(press == "s"){
                game.down();
                return "s";
            }
            else if(press == "q"){
                game.left();
                return "q";
            }
            else if(press == "d"){
                game.right();
                return "d";
            }
            else if(press == "x"){
                return "x";
            }
        }
    }
    return "x";
}

void play(){

    bool win = false;
    bool lost = false;

    Game g;
    g.init();

    string enh = "";
    g.print();

    do{
        g.clearPossibleMoves();

        enh = press_touch(g);
        g.print();
        win = g.checkWin();
        g.searchPossibleMoves();

        lost = g.isLost(g.getPossibleMoves());

    }while(win == false || lost == false);

    if(win){
        cout<<"GG t'as gagné !"<<endl;
    }

}

void playArbre(){

    bool win = false;
    bool lost = false;
    int nbCoup = 0;
    int id = 2;
    //vector<Noeud>tabNode;

    Game g;
    g.init();

    string enh = "";
    g.print();


    Noeud n;
    n.setId(1);
    //tabNode.push_back(n);
    Noeud* courant = &n;

    do{
        g.clearPossibleMoves();

        enh = press_touch(g);
        g.print();

        Noeud newNode;
        newNode.setId(id);
        newNode.setDirection(enh);
        Noeud* node = new Noeud(newNode);
        node->addParent(courant);


        //tabNode.push_back(node);
        courant->addChild(newNode);

        //Noeud* tmp = &node;


        cout<<"id du parent "<< node->getParent().getId()<<endl;
        cout<<"id du courant "<< courant->getId()<<endl;
        cout<<"id du noeud actuel: "<< node->getId()<<endl;


        cout<<"direction du parent: "<< node->getParent().getDirection()<<endl;
        cout<<"direction du courant: "<< courant->getDirection()<<endl;
        cout<<"direction du noeud actuel: "<< node->getDirection()<<endl;

        //courant->addChild(tabNode[tabNode.size()-1]);

        cout<<"nombre d'enfant de la racine : "<<n.getNbChild()<<endl;
        cout<<"nombre d'enfant du parent : "<<courant->getNbChild()<<endl;

        if(courant->getId() == 1){
            cout<<"Courant est bien la racine"<<endl;
        }else if(courant->getId() == 2){
            cout<<"Courant est le deuxieme noeud"<<endl;
        }else if(courant->getId() == 3){
            cout<<"Courant est le troisieme noeud"<<endl;
        }




        courant = node;

        win = g.checkWin();
        g.searchPossibleMoves();
        lost = g.isLost(g.getPossibleMoves());

        nbCoup++;
        id++;

        cout<<"nb coup : "<<nbCoup<<endl;

        if(nbCoup == 4)
            break;

    }while(win == false || lost == false);


    if(win){
        cout<<"GG t'as gagné !"<<endl;
    }

}



void testArbre(){

    Noeud arbre;
    Noeud n1;
    Noeud n2;
    Noeud n3;

    arbre.setId(12);

    n3.addParent(&n2);
    n1.addParent(&arbre);
    n2.addParent(&arbre);

    n2.addChild(n3);
    arbre.addChild(n1);
    arbre.addChild(n2);
    cout<<"taille de l'arbre : "<< arbre.taille() <<endl;

    if(n2.getParent().getId() == arbre.getId())
    {
        cout<<"ca marche !!!!"<<endl;
    }

}

void playAI(){
    Game g;
	int nb;

    cout<<"Nombre de répétition ? ";
    cin>>nb;
    g.playAI(nb);
}

void initSeed(){
	
	struct timeval time;

    gettimeofday(&time,NULL);

    srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
		
}

int main()
{
	initSeed();
	
   //playAI();
   
   
	
	Mcts mcts;
	Noeud n;
	
	mcts.playMcts(n);

    //playArbre();


    return 0;
}
