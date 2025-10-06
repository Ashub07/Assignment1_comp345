#include <iostream>
#include <vector>
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include <string>



//default constructor
Player::Player(){
    pName = new std::string;
    Pterritories = new std::vector<Territory*>;
    deck = new Deck;
    order = new OrdersList;
}

//parametered constructor
Player::Player(std::string pName1, std::vector<Territory*> t1, Deck d1, OrdersList o1){
    this->pName = new std::string (pName1);
    this->Pterritories = new std::vector<Territory*> (t1);
    this->deck = new Deck (d1);
    this->order = new OrdersList (o1);
}

//copy constructor
Player::Player(const Player& other){
    pName = new std::string (*other.pName);
    Pterritories = new std::vector<Territory*> (*other.Pterritories);
    deck = new Deck (*other.deck);
    order = new OrdersList (*other.order);
}

//destructor
Player::~Player(){
    delete pName;
    delete Pterritories;
    delete deck;
    delete order;
}

//getter for player name
std::string Player::getPName() const{
    return *pName;
}

//getter for territory param
std::vector<Territory*> Player::getTerritory() const{
    return *Pterritories;
}

//getter for deck param
Deck Player::getDeck() const{
    return *deck;
}

//getter for orderes list param
OrdersList Player::getOrder() const{
    return *order;
}

//setter for player name
void Player::setPName(std::string pName){
    *this->pName = pName;
}

//setter for territory
void Player::setTerritory(std::vector<Territory*> Pterritories){
    *this->Pterritories = Pterritories;
}

//setter for deck
void Player::setDeck(Deck deck){
    *this->deck = deck;
}

//setter for orders list
void Player::setOrdersList(OrdersList order){
    *this->order = order;
}

//todefend method that returns a list of territories to defend
std::vector<Territory*> Player::toDefend(Player p){

    //get territory
    std::vector<Territory*> t2 = p.getTerritory();

    //create list to store territories that will be defended (50 places at the moment)
    std::vector<Territory*> defend;

    //goes throught list of territories belonging to player
    for(int i = 0; i<t2.size(); i++){
        //store owner name
        std::string owName = t2[i]->getOwner();

        //selects the territories to defend based on if they belong to the player
        if(owName == p.getPName()){
            //add the territory to the player defend list
            defend.push_back(t2[i]);
        }
        
    }
    //return the list of defending territories
    return defend;

}

//toattack method that returns a list of territories to attack
std::vector<Territory*> Player::toAttack(Player p){

    //get territory
    std::vector<Territory*> t2 = p.getTerritory();

    //create list to store territories that will be defended (50 places at the moment)
    std::vector<Territory*> attack;

    //goes throught list of territories belonging to other player
    for(int i = 0; i<t2.size(); i++){
        //store owner name
        std::string owName = t2[i]->getOwner();

        //selects the territories to attack based on if they belong to the player or not
        if(owName != p.getPName()){
            //add the territory to the player attack list
            attack.push_back(t2[i]);
        }
        
    }
    //return the list of defending territories
    return attack;

}

//issueorder method creates an order object and is put in the players order list
OrdersList Player::issueOrder(Player p){

    //get player order list
    Player* p1 = &p;

    //get player order list
    OrdersList ol1 = p.getOrder();

    //creates order object
    Orders or2(p1);
    //adds the object to the list
    ol1.add(&or2);
    
}

