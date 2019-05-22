#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>

class Game
{
    public:
        Game();
        Game(const Game & clone);
        void print();
        void init();
        void top();
        void down();
        void left();
        void right();
        void press_touch_auto(std::string touch);
        std::vector<std::string> getPossibleMoves();
        void searchPossibleMoves();
        void clearPossibleMoves();
        bool checkWin();
        bool isLost(std::vector<std::string> v);
        int getScore();
        int getHighest();
        void initScore();
        auto randomAI();
        float playAI(int nb);
        int tab[4][4];



    protected:


    private:
        
        std::vector<std::string> possibleMoves;
        int score = 0;
        int nbPlayed = 0;

        bool possibleTop();
        void decalageTop();
        void additionTop();

        bool possibleDown();
        void decalageDown();
        void additionDown();

        bool possibleRight();
        void decalageRight();
        void additionRight();

        bool possibleLeft();
        void decalageLeft();
        void additionLeft();


        void alea();
};

#endif // GAME_H
