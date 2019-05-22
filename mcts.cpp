#include "mcts.h"
#include <iostream>
#include <sys/time.h>


using namespace std;


Mcts::Mcts()
{
	//yes
}

void Mcts::updateScore(Noeud *n){
		
	Noeud* courant = n;
	float s = n->getScore();
	cout<<"score de n = "<<n->getScore()<<endl;
	
	while(courant->parent != nullptr){
		cout<<courant->getScore()<<endl;
		courant->parent->setScore(s);
		courant->parent->incrIter();
		courant = courant->parent;
	}
	
}




void Mcts::playMcts(Noeud &n){
	
	Game newGame(n.g);
	newGame.print();
	n.g.print();
	
	
	n.incrIter();
	n.setGame(newGame);
	
	//n.g.print();
	
	cout<<n.getScore()<<endl;
	
	newGame.searchPossibleMoves();
	
	Noeud * courant = &n;
		
	for(int i=0; i<(int)newGame.getPossibleMoves().size(); i++){
		/* Creation du noeud */
		
		Noeud newNode;
        newNode.setDirection(newGame.getPossibleMoves()[i]);
        Noeud* node = new Noeud(newNode);
        node->addParent(courant);
        courant->addChild(newNode);
        node->setGame(courant->g);
        
        /* On joue une fois */
        node->g.press_touch_auto(newGame.getPossibleMoves()[i]);
        cout<<"-----g!:smlkdjlfkgds---------"<<i<<endl;
		//node->g.print();
        /* On copie la grille et fini la partie */
        Game copie(node->g);
        node->setScore(node->g.playAI(1));
        node->incrIter();
        node->setGame(copie);
        updateScore(node);
        
        cout<<"score parent = "<<node->parent->getScore()<<endl;
        cout<<"nbit noeud = "<<node->getNbIt()<<endl;
        cout<<"nbit parent = "<<node->parent->getNbIt()<<endl;
		node->g.print();
	}
}



/*
Noeud Mcts::selectNode(){

   
}



void Mcts::expansion(Noeud n){}


void Mcts::backPropagation(Noeud n){}


void Mcts::simulate(Noeud n){}




double Mcts::UCT(Noeud &n){

    double nodeWinScore = n.getNbWin();
    int nbVisit = n.getNbVisit();

    if(nbVisit == 0){
        return Integer.MAX_VALUE;
    }

    return ((double) nodeWinScore / (double) nbVisit) + 1.41 * Math.sqrt(Math.log(totalVisit) / (double) nbVisit);

}

*/
