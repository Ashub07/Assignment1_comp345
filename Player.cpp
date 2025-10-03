#include <iostream>
#include <vector>
#include "Map.h"
#include "Player.h"

using namespace std;

//default constructor
Player::Player(){
    pName = new string;
    Pterritories = new vector<Territory*>;
    deck = new Deck;
    order = new OrdersList;
}

//parametered constructor
Player::Player(string pName1, vector<Territory*> t1, Deck d1, OrdersList o1){
    this->pName = new string (pName1);
    this->Pterritories = new vector<Territory*> (t1);
    this->deck = new Deck (d1);
    this->order = new OrdersList (o1);
}

//copy constructor
Player::Player(const Player& other){
    pName = new string (*other.pName);
    Pterritories = new vector<Territory*> (*other.Pterritories);
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
string Player::getPName() const{
    return *pName;
}

//getter for territory param
vector<Territory*> Player::getTerritory() const{
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
void Player::setPName(string pName){
    *this->pName = pName;
}

//setter for territory
void Player::setTerritory(vector<Territory*> Pterritories){
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
vector<Territory*> toDefend(Player p){

    //initializes player
    Player p1 = p;

    //get territory
    vector<Territory*> t2 = p.getTerritory();

    //create list to store territories that will be defended (50 places at the moment)
    vector<Territory*> defend;

    //goes throught list of territories belonging to player
    for(int i = 0; i<50; i++){
        //store owner name
        string owName = t2[i]->getOwner();

        //selects the territories to defend based on if they belong to the player
        if(owName == p1.getPName()){
            //add the territory to the player defend list
            defend.push_back(t2[i]);
        }
        
    }
    //return the list of defending territories
    return defend;

}

//toattack method that returns a list of territories to attack
vector<Territory*> toAttack(Player p){
//initializes player
    Player p1 = p;

    //get territory
    vector<Territory*> t2 = p.getTerritory();

    //create list to store territories that will be defended (50 places at the moment)
    vector<Territory*> attack;

    //goes throught list of territories belonging to other player
    for(int i = 0; i<50; i++){
        //store owner name
        string owName = t2[i]->getOwner();

        //selects the territories to attack based on if they belong to the player or not
        if(owName != p1.getPName()){
            //add the territory to the player attack list
            attack.push_back(t2[i]);
        }
        
    }
    //return the list of defending territories
    return attack;

}

//issueorder method creates an order object and is put in the players order list
void issueOrder(){

    //creates order object

    //adds the object to the list
    
}

