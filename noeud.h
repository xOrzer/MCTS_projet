#ifndef NOEUD_H
#define NOEUD_H

#include <vector>
#include "game.h"


#include <string>
#include <vector>

using namespace std;


class Noeud
{
    public:
        Noeud();
        Noeud(Noeud const& n);
        
        Game g;
        
        float scoreNoeud;
		
		void incrIter();
		int getNbIt();
        int getId();
        void setId(int i);
        void addChild(Noeud n);
        void addParent(Noeud *n);
		void setScore(float s);
		float getScore();
        Noeud getParent();
        void setDirection(string s);
        int taille();
        int getNbChild();
        string getDirection();
        vector<Noeud> getChildren();
        void setGame(Game g);
        
        Noeud* parent;

        






    protected:

    private:

		int nbIteration;
        int id;
        string direction;
        vector <Noeud> children;


};

#endif // NOEUD_H
