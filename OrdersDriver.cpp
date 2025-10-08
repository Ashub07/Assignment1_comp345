#include "Orders.h"
#include <iostream>
#include <vector>

void testOrdersList() {
	//create orders
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

	OrdersList* ordli1 = new OrdersList();


	//create player
	Player* p1 = new Player("Joe", territories, d1, *ordli1);

	std::vector<Territory*> territories2;
	Territory* t11 = new Territory("T1", "C1", "Joee", 2, 1, nullptr);
	territories.push_back(t1);
	Territory* t22 = new Territory("T2", "C2", "Joee", 3, 2, nullptr);
	territories.push_back(t2);
	Territory* t33 = new Territory("T3", "C1", "Lilyy", 2, 3, nullptr);
	territories.push_back(t3);
	Territory* t44 = new Territory("T4", "C2", "Joee", 1, 4, nullptr);
	territories.push_back(t4);

	//create deck
	std::vector<Card*> cards2;
	Card* c11 = new Card(cardType::Bomb);
	cards1.push_back(c1);
	Card* c22 = new Card(cardType::Diplomacy);
	cards1.push_back(c2);
	Card* c33 = new Card(cardType::Airlift);
	cards1.push_back(c3);

	Deck d11(cards1);

	OrdersList* ordli2 = new OrdersList();


	//create player
	Player* p2 = new Player("Joee", territories, d1, *ordli2);


	//create Orders
	int num2 = 2;
	int* num = &num2;
	Deploy* dep=new Deploy(p2, t11, num);
	Blockade* blk = new Blockade(p2, t22);
	Advance* adv = new Advance(p2, t11, t1, num);
	Airlift* air = new Airlift(p2, t11, t22, num);
	Bomb* bom = new Bomb(p2, t33);
	Negotiate* neg = new Negotiate(p2, p1);
	Airlift* air2 = new Airlift(p1, t11, t22, num);
	Advance* adv2 = new Advance(p1, t1, t2, num);
	Orders* ord = new Orders(p1);

	//OrdersList method tests
	ordli2->add(dep);
	ordli2->add(blk);
	ordli2->add(adv);
	ordli2->add(air);
	ordli2->add(bom);
	ordli2->add(neg);
	ordli1->add(air2);
	ordli1->add(adv2);
	ordli1->add(ord);
	std::cout << *ordli2;
	std::cout << *ordli1;


}


int main() {
	std::cout << "OrdersList test: ";
	testOrdersList();


	return 0;
}