 #include <iostream>
 #include <vector>
 #include "Player.h"
 #include "Map.h"

using namespace std;

void testPlayer(){

  //get territories
  std::vector<Territory*> territories;
  Territory* t1 = new Territory("T1", "C1", "Joe", 2, 1, nullptr);
  territories.push_back(t1);
  Territory* t2 = new Territory("T2", "C2", "Joe", 3, 2, nullptr);
  territories.push_back(t2);
  Territory* t3 = new Territory("T3", "C1", "Lily", 2, 3, nullptr);
  territories.push_back(t3);
  Territory* t4 = new Territory("T4", "C2", "Joe", 1, 4, nullptr);
  territories.push_back(t4);

  //create deck
  std::vector<Card*> cards1;
  Card* c1 = new Card(cardType::Bomb);
  cards1.push_back(c1);
  Card* c2 = new Card(cardType::Diplomacy);
  cards1.push_back(c2);
  Card* c3 = new Card(cardType::Airlift);
  cards1.push_back(c3);

  Deck d1(cards1);

  //create orderlist
  OrdersList ordli1;

  //create player
  Player p1 = Player("Joe",territories, d1, ordli1);
  

  //todefend method
  p1.toDefend(p1);

  //toattack method
  p1.toAttack(p1);

  //issue order
  p1.issueOrder(p1);
}

int main(){
  cout<<"-----Player Driver Test-----";
  testPlayer();
  return 0;
}