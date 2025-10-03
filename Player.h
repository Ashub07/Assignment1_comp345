#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"
#include <iostream>
#include <vector>

class Player{
    private:
        //player name
        string* pName;
        //territories
        vector<Territory*>* Pterritories;
        //hand of cards
        Deck* deck;
        //list of orders
        OrdersList* order;

    public:
        //default constructor
        Player();
        //parametered constructor
        Player(string n, vector<Territory*> x, Deck y, OrdersList z);
        //copy constructor
        Player(const Player& other);
        //destructor
        ~Player();

        //getter
        string getPName() const;
        vector<Territory*> getTerritory() const;
        Deck getDeck() const;
        OrdersList getOrder() const;

        //setter
        void setPName(string pName);
        void setTerritory(vector<Territory*> Pterritories);
        void setDeck(Deck deck);
        void setOrdersList(OrdersList order);


        //toDefend
        vector<Territory*> toDefend(Player p);

        //toAttack
        vector<Territory*> toAttack(Player p);

        //issueOrder

};

#endif