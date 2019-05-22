#include "game.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <tuple>
#include <sys/time.h>

using namespace std;

/* ======== Fonctions ======== */

/* Aleatoire entre 2 et 4 */
int DeuxOuQuatre(){

    const int MAX = 100, MIN = 0;
    int alea = (rand() % (MAX - MIN + 1)) + MIN;;

    if(alea < 90)
        return 2;
    else
        return 4;
}

/* ======== Methodes Game ======== */

/* Constructeur */
Game::Game(){
	
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            tab[i][j] = 0;
        }
    }
    
     /* Tirage des al�atoires nombre (entre 2 et 4)*/
    int nbAlea = DeuxOuQuatre();
    int nbAlea2 = 0;
    if (nbAlea == 2)
        nbAlea2 = DeuxOuQuatre();
    else
        nbAlea2 = 2;

    /* Selection premier emplacement */
    int alea1 = rand()%4;
    int alea2 = rand()%4;

    /* Ajout dans le tableau */
    tab[alea1][alea2] = nbAlea;

    /* Selection deuxi�me emplacement */
    int alea3 = rand()%4;
    int alea4 = rand()%4;

    /* On s'assure que ce soit un emplacement diff�rent du premier */
    while(alea3 == alea1 || alea4 == alea2){
        alea3 = rand()%4;
        alea4 = rand()%4;
    }

    /* Ajout dans le tableau */
    tab[alea3][alea4] = nbAlea2;
    
}

Game::Game(const Game & clone){
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			tab[i][j] = clone.tab[i][j];
		}
	}
}

/* Affichage grille de jeu */
void Game::print(){

    cout << " ============== 2048 ============== " << endl << endl;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << "    " << tab[i][j] << "    ";
        }
        cout << endl << endl;
    }
}

/* Initialisation grille de jeu */
void Game::init(){

    for(int i; i<4;i++){
        for(int j=0;j<4;j++){
            tab[i][j]=0;
        }
    }

    /* Tirage des al�atoires nombre (entre 2 et 4)*/
    int nbAlea = DeuxOuQuatre();
    int nbAlea2 = 0;
    if (nbAlea == 2)
        nbAlea2 = DeuxOuQuatre();
    else
        nbAlea2 = 2;

    /* Selection premier emplacement */
    int alea1 = rand()%4;
    int alea2 = rand()%4;

    /* Ajout dans le tableau */
    tab[alea1][alea2] = nbAlea;

    /* Selection deuxi�me emplacement */
    int alea3 = rand()%4;
    int alea4 = rand()%4;

    /* On s'assure que ce soit un emplacement diff�rent du premier */
    while(alea3 == alea1 || alea4 == alea2){
        alea3 = rand()%4;
        alea4 = rand()%4;
    }

    /* Ajout dans le tableau */
    tab[alea3][alea4] = nbAlea2;


}


/* Methodes pratiques */



bool Game::checkWin(){

    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++){
            if(tab[i][j] == 2048)
            {
                return true;
            }
        }
    }
    return false;

}

void Game::clearPossibleMoves(){
    possibleMoves.clear();
}

vector<string> Game::getPossibleMoves(){
    return possibleMoves;
}

void Game::searchPossibleMoves(){

    if(possibleDown())
        possibleMoves.push_back("s");

    if(possibleTop())
        possibleMoves.push_back("z");

    if(possibleLeft())
        possibleMoves.push_back("q");

    if(possibleRight())
        possibleMoves.push_back("d");

}



bool Game::isLost(vector<string> v){
    if(v.size()==0){
        return true;
    }

    return false;
}

void Game::alea(){

    vector <int> nbCaseVide;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(tab[i][j] == 0){
                nbCaseVide.push_back((4*i)+j);
            }
        }//end for j
    }//end for i

    int alea = rand()%nbCaseVide.size();
    int alea2 = DeuxOuQuatre();

    tab[0][nbCaseVide[alea]] = alea2;
}

/* Methode pour le haut */

bool Game::possibleTop(){

    /* D�calage */
    for(int j = 0; j < 4; j++){
        for(int i = 1; i < 4; i++){
            if(tab[i][j] != 0 && tab[i-1][j] == 0)
                return true;
            if(tab[i][j] != 0 && tab[i-1][j] == tab[i][j])
                return true;
            if(tab[i][j] == 0)
                continue;
        }//end for j
    }//end for i

    return false;
}

void Game::decalageTop(){

    int k = 0;
    /* D�calage */
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++){

            if(tab[i][j] != 0 && i == 0){
                k++;
            }

            if(tab[i][j] != 0 && i != 0){
                tab[k][j] = tab[i][j];
                if(i != k)
                    tab[i][j] = 0;
                k++;
            }
        }//end for j
        k=0;
    }//end for i
}

void Game::additionTop(){
    /* Addition */
    for(int j = 0; j < 4; j++){
        if(tab[0][j] == tab[1][j] && tab[0][j] == tab[2][j] && tab[0][j] == tab[3][j]){
            int nb = tab[0][j] + tab[0][j];
            tab[0][j] = nb;
            tab[1][j] = nb;
            tab[2][j] = 0;
            tab[3][j] = 0;
            score += 2*nb;
            continue;
        }

        for(int i = 0; i < 3; i++){
            if(tab[i][j] != 0){
                if(tab[i+1][j] == tab[i][j]){
                    tab[i][j] = (tab[i+1][j] + tab[i][j]);
                    tab[i+1][j] = 0;
                    score += tab[i][j];
                    break;
                }
            }
        }//end for j
    }//end for i
}

void Game::top(){

    bool test = false;
    test = possibleTop();

    if(test){
        decalageTop();
        additionTop();
        decalageTop();
        alea();
    }
    else{
        cout<<"Mouvement imposssible !"<<endl;
    }
}


/* Methode pour le bas */
bool Game::possibleDown(){

    /* D�calage */
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 3; i++){
            if(tab[i][j] != 0 && tab[i+1][j] == 0)
                return true;
            if(tab[i][j] != 0 && tab[i+1][j] == tab[i][j])
                return true;
            if(tab[i][j] == 0)
                continue;
        }//end for j
    }//end for i

    return false;
}

void Game::decalageDown(){
    int k = 3;
    /* D�calage */
    for(int j = 3; j >= 0; j--){
        for(int i = 3; i >= 0; i--){

            if(tab[i][j] != 0 && i == 3){
                k--;
            }

            if(tab[i][j] != 0 && i != 3){
                tab[k][j] = tab[i][j];
                if(i != k)
                    tab[i][j] = 0;
                k--;
            }
        }//end for j
        k=3;
    }//end for i
}

void Game::additionDown(){
    /* Addition */
    for(int j = 3; j >= 0; j--){
        if(tab[0][j] == tab[1][j] && tab[0][j] == tab[2][j] && tab[0][j] == tab[3][j]){
            int nb = tab[0][j] + tab[0][j];
            tab[0][j] = 0;
            tab[1][j] = 0;
            tab[2][j] = nb;
            tab[3][j] = nb;
            score += 2*nb;
            continue;
        }

        for(int i = 3; i >= 0; i--){
            if(tab[i][j] != 0){
                if(tab[i-1][j] == tab[i][j]){
                    tab[i][j] = (tab[i-1][j] + tab[i][j]);
                    tab[i-1][j] = 0;
                    score += tab[i][j];
                    break;
                }
            }
        }//end for j
    }//end for i
}

void Game::down(){
    bool test = false;
    test = possibleDown();

    if(test){
        decalageDown();
        additionDown();
        decalageDown();
        alea();
    }
    else{
        cout<<"Mouvement imposssible !"<<endl;
    }
}


/* Methode pour la droite */

bool Game::possibleRight(){

    /* D�calage */
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            if(tab[i][j] != 0 && tab[i][j+1] == 0)
                return true;
            if(tab[i][j] != 0 && tab[i][j+1] == tab[i][j])
                return true;
            if(tab[i][j] == 0)
                continue;
        }//end for j
    }//end for i

    return false;
}

void Game::decalageRight(){
    int k = 3;
    /* D�calage */
    for(int i = 3; i >= 0; i--){
        for(int j = 3; j >= 0; j--){

            if(tab[i][j] != 0 && j == 3){
                k--;
            }

            if(tab[i][j] != 0 && j != 3){
                tab[i][k] = tab[i][j];
                if(j != k)
                    tab[i][j] = 0;
                k--;
            }
        }//end for j
        k=3;
    }//end for i
}

void Game::additionRight(){
    /* Addition */
    for(int i = 3; i >= 0; i--){
        if(tab[i][0] == tab[i][1] && tab[i][0] == tab[i][2] && tab[i][0] == tab[i][3]){
            int nb = tab[i][0] + tab[i][0];
            tab[i][0] = 0;
            tab[i][1] = 0;
            tab[i][2] = nb;
            tab[i][3] = nb;
            score += 2*nb;
            continue;
        }

        for(int j = 3; j >= 0; j--){
            if(tab[i][j] != 0){
                if(tab[i][j-1] == tab[i][j]){
                    tab[i][j] = (tab[i][j-1] + tab[i][j]);
                    tab[i][j-1] = 0;
                    score += tab[i][j];
                    break;
                }
            }
        }//end for j
    }//end for i
}

void Game::right(){
    bool test = false;
    test = possibleRight();

    if(test){
        decalageRight();
        additionRight();
        decalageRight();
        alea();
    }
    else{
        cout<<"Mouvement imposssible !"<<endl;
    }
}


/* Methode pour la gauche */

bool Game::possibleLeft(){

    /* D�calage */
    for(int i = 0; i < 4; i++){
        for(int j = 1; j < 4; j++){
            if(tab[i][j] != 0 && tab[i][j-1] == 0)
                return true;

            if(tab[i][j] != 0 && tab[i][j-1] == tab[i][j])
                return true;

            if(tab[i][j] == 0)
                continue;
        }//end for j
    }//end for i

    return false;
}

void Game::decalageLeft(){
    int k = 0;
    /* D�calage */
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){

            if(tab[i][j] != 0 && j == 0){
                k++;
            }

            if(tab[i][j] != 0 && j != 0){
                tab[i][k] = tab[i][j];
                if(j != k)
                    tab[i][j] = 0;
                k++;
            }
        }//end for j
        k=0;
    }//end for i
}

void Game::additionLeft(){
    /* Addition */
    for(int i = 0; i < 4; i++){
        if(tab[i][0] == tab[i][1] && tab[i][0] == tab[i][2] && tab[i][0] == tab[i][3]){
            int nb = tab[i][0] + tab[i][0];
            tab[i][0] = nb;
            tab[i][1] = nb;
            tab[i][2] = 0;
            tab[i][3] = 0;
            score += 2*nb;
            continue;
        }

        for(int j = 0; j < 3; j++){
            if(tab[i][j] != 0){
                if(tab[i][j+1] == tab[i][j]){
                    tab[i][j] = (tab[i][j+1] + tab[i][j]);
                    tab[i][j+1] = 0;
                    score += tab[i][j];
                    break;
                }
            }
        }//end for j
    }//end for i
}

void Game::left(){
    bool test = false;
    test = possibleLeft();

    if(test){
        decalageLeft();
        additionLeft();
        decalageLeft();
        alea();
    }
    else{
        cout<<"Mouvement imposssible !"<<endl;
    }
}

void Game::press_touch_auto(string touch){

    if(touch == "z"){
        top();
    }
    else if(touch == "s"){
        down();
    }
    else if(touch == "q"){
        left();
    }
    else if(touch == "d"){
        right();
    }
}

int Game::getScore(){
    return score;
}

int Game::getHighest(){
    int highest = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(tab[i][j] > highest){
                highest = tab[i][j];
            }
        }
    }
    return highest;
}

void Game::initScore(){
    score = 0;
}


auto Game::randomAI(){
    bool win = false;
    bool lost = false;
    int alea = 0;
    initScore();
    do{

        searchPossibleMoves();

        if(getPossibleMoves().size()!=0){
            if(getPossibleMoves().size()>1){
                alea = rand() % getPossibleMoves().size();
                press_touch_auto(getPossibleMoves()[alea]);
            }else{
                press_touch_auto(getPossibleMoves()[0]);
            }
        }
        lost = isLost(getPossibleMoves());
        win = checkWin();

        clearPossibleMoves();

    }while(win == false && lost == false);

    return std::make_tuple(getHighest(), getScore());

}

float Game::playAI(int nb){

    int bestScore = 0;
    int bestHighest = 0;
    std::tuple<int, int> summary (0,0);
    struct timeval time;

    gettimeofday(&time,NULL);

    srand((time.tv_sec * 1000) + (time.tv_usec / 1000));

    for(int i = 0; i<nb; i++){
        //init();

        summary = randomAI();

        if(std::get<0>(summary) > bestHighest)
            bestHighest = std::get<0>(summary);
        if(std::get<1>(summary) > bestScore)
            bestScore = std::get<1>(summary);

    }

    cout<< "Plus grande valeur atteinte : " << bestHighest <<endl << "Meilleur score : " << bestScore<<endl;
	return bestScore;
}


