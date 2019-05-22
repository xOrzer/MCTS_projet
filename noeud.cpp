#include "noeud.h"
#include <iostream>
using namespace std;
Noeud::Noeud()
{
	parent = nullptr;
	scoreNoeud = 0;
	nbIteration = 0;
}

Noeud::Noeud(Noeud const& n)
{
    id = n.id;
    direction = n.direction;

}

float Noeud::getScore(){
	
	return scoreNoeud; 
	
}

void Noeud::setGame(Game copie){
	
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			g.tab[i][j] = copie.tab[i][j];
		}
	}
	
}


void Noeud::setScore(float s){
	scoreNoeud += s;
}

vector<Noeud> Noeud::getChildren(){

    return children;
}

void Noeud::addChild(Noeud n){
    children.push_back(n);
}

void Noeud::setDirection(string s){
    direction = s;
}

int Noeud::getNbChild(){

    return children.size();
}

int Noeud::getNbIt(){
	
	return nbIteration;
}

void Noeud::incrIter(){
    nbIteration++;
}


int Noeud::taille(){
    int compteur = 1;
    for(int i=0; i<(int)children.size(); i++){
        compteur += children[i].taille();
    }
    return compteur;
}

string Noeud::getDirection(){
    return direction;
}


Noeud Noeud::getParent(){
    return *parent;
}

int Noeud::getId(){
    return id;
}

void Noeud::setId(int i){
    id = i;
}


void Noeud::addParent(Noeud *n){
    parent = n;
}



