#ifndef MCTS_H
#define MCTS_H

#include "noeud.h"
#include "game.h"
#include <iostream>

#include <string>


class Mcts{
    public:
        Mcts();
		void playMcts(Noeud &n);
		void updateScore(Noeud *n);

    protected:

    private:
        //Noeud root;
		/*
        double UCT(Noeud &n);
        void selectNode();
        void expansion(Noeud n);
        void backPropagation(Noeud n);
        void simulate(Noeud n);
        */
};

#endif // MCTS_H
