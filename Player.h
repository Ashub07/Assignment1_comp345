#ifndef PLAYER_H
#define PLAYER_H


#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include <iostream>
#include <vector>
#include <string>


class Player{
    private:
        //player name
        std::string* pName;
        //territories
        std::vector<Territory*>* Pterritories;
        //hand of cards
        Deck* deck;
        //list of orders
        OrdersList* order;

    public:
        //default constructor
        Player();
        //parametered constructor
        Player(std::string n, std::vector<Territory*> x, Deck y, OrdersList z);
        //copy constructor
        Player(const Player& other);
        //destructor
        ~Player();

        //getter
        std::string getPName() const;
        std::vector<Territory*> getTerritory() const;
        Deck getDeck() const;
        OrdersList getOrder() const;

        //setter
        void setPName(std::string pName);
        void setTerritory(std::vector<Territory*> Pterritories);
        void setDeck(Deck deck);
        void setOrdersList(OrdersList order);


        //toDefend
        std::vector<Territory*> toDefend(Player p);

        //toAttack
        std::vector<Territory*> toAttack(Player p);

        //issueOrder
        OrdersList issueOrder(Player p);

};

#endif