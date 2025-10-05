#include "Orders.h"

//Orders implementation
//default constructor
Orders::Orders() {
	player = new Player();

}

//parametrized constructor
Orders::Orders(Player* playr) {
	this->player = playr;
	
}


// copy constructor
Orders::Orders(const Orders& order) {
	player = new Player(*order.player);
}
//destructor
Orders::~Orders() {
	delete player;
	
}

//assignment+stream insertion operator
Orders& Orders::operator=(const Orders& order) {
	if (this != &order) {
		if (this->player != nullptr) {
			delete player;
		}
		this->player = new Player(*order.player);
	}
	return *this;
}
std::ostream& operator<<(std::ostream& os, const Orders& order) {
	os << "These orders belong to: " << order.player;
	return os;
}

Player Orders::getPlayer() const {
		return *player;
	}
void Orders::setPlayer(Player playr) {
	 *player=playr;
}

Orders* Orders::clone() const {
	return new Orders(*this);
}




Deploy::Deploy() : Orders(nullptr) {
}

//parametrized constructor
Deploy::Deploy(Player* playr, Territory* target, int* armynum) {
	this->player = playr;
	this->targ = target;
	this->armyNum = armynum;

}


// copy constructor
Deploy::Deploy(const Deploy& order) {
	player = new Player(*order.player);
	targ = new Territory(*order.targ);
	armyNum = new int(*order.armyNum);
}
//destructor
Deploy::~Deploy() {
	delete player;
	delete targ;
	delete armyNum;

}

//assignment+stream insertion operator
Deploy& Deploy::operator=(const Deploy& order) {
	if (this != &order) {
		if (this->player != nullptr) {
			delete player;
		}
		if (this->targ != nullptr) {
			delete targ;
		}
		if (this->armyNum != nullptr) {
			delete armyNum;
		}
		this->player = new Player(*order.player);
		this->targ = new Territory(*order.targ);
		this->armyNum = new int(*order.armyNum);

	}
	return *this;
}
std::ostream& operator<<(std::ostream& os, const Deploy& order) {
	os << "This is a Deploy order belonging to " << order.player << " to deploy " << order.armyNum << " armies to the territory " << order.targ;
	return os;
}

Player Deploy::getPlayer() const {
	return *player;
}
void Deploy::setPlayer(Player playr) {
	*this->player = playr;
}
Territory Deploy::getTarg() const {
	return *targ;
}
void Deploy::setTarget(Territory targ) {
	*this->targ = targ;
}
int Deploy::getArmynum() const {
	return *armyNum;
}
void Deploy::setArmynum(int armies) {
	*armyNum = armies;
}

bool Deploy::validate() const{
	if (player == nullptr || targ == nullptr || *armyNum<=0) return false;
	return targ->getOwner() == player && player->getArmies() >= armyNum;
}

bool Deploy::execute() const {
	if (!validate()) return false;
	else return true;
}

Deploy* Deploy::clone() const {
	return new Deploy(*this);
}


Advance::Advance() : Orders(nullptr) {
}

//parametrized constructor
Advance::Advance(Player* playr, Territory* target, Territory* source, int* armynum) {
	this->player = playr;
	this->targ = target;
	this->source = source;
	this->armyNum = armynum;

}


// copy constructor
Advance::Advance(const Advance& order) {
	player = new Player(*order.player);
	targ = new Territory(*order.targ);
	source = new Territory(*order.source);
	armyNum = new int(*order.armyNum);

}
//destructor
Advance::~Advance() {
	delete player;
	delete targ;
	delete source;
	delete armyNum;

}

//assignment+stream insertion operator
Advance& Advance::operator=(const Advance& order) {
	if (this != &order) {
		if (this->player != nullptr) {
			delete player;
		}
		if (this->targ != nullptr) {
			delete targ;
		}
		if (this->source != nullptr) {
			delete source;
		}
		if (this->armyNum != nullptr) {
			delete armyNum;
		}
		this->player = new Player(*order.player);
		this->targ = new Territory(*order.targ);
		this->source = new Territory(*order.source);
		this->armyNum = new int(*order.armyNum);

	}
	return *this;
}
std::ostream& operator<<(std::ostream& os, const Advance& order) {
	os << "This is an Advance order belonging to " << order.player << " to Advance " << order.armyNum << " armies to the territory " << order.targ << "from source territory " << order.source;
	return os;
}

Player Advance::getPlayer() const {
	return *player;
}
void Advance::setPlayer(Player playr) {
	*this->player = playr;
}
Territory Advance::getTarg() const {
	return *targ;
}
void Advance::setTarget(Territory targ) {
	*this->targ = targ;
}
Territory Advance::getSource() const {
	return *source;
}
void Advance::setSource(Territory source) {
	*this->source = source;
}

int Advance::getArmynum() const {
	return *armyNum;
}
void Advance::setArmynum(int armies) {
	*armyNum = armies;
}

bool Advance::validate() const {
	if (player == nullptr || targ == nullptr || source == nullptr || *armyNum <= 0) return false;
	return targ->getOwner() == player && source->getOwner() == player && player->getArmies() >= armyNum;
}

bool Advance::execute() const {
	if (!validate()) return false;
	else return true;
}

Advance* Advance::clone() const {
	return new Advance(*this);
}



Bomb::Bomb() : Orders(nullptr) {
}

//parametrized constructor
Bomb::Bomb(Player* playr, Territory* target) {
	this->player = playr;
	this->targ = target;


}


// copy constructor
Bomb::Bomb(const Bomb& order) {
	player = new Player(*order.player);
	targ = new Territory(*order.targ);

}
//destructor
Bomb::~Bomb() {
	delete player;
	delete targ;

}

//assignment+stream insertion operator
Bomb& Bomb::operator=(const Bomb& order) {
	if (this != &order) {
		if (this->player != nullptr) {
			delete player;
		}
		if (this->targ != nullptr) {
			delete targ;
		}
		this->player = new Player(*order.player);
		this->targ = new Territory(*order.targ);
		

	}
	return *this;
}
std::ostream& operator<<(std::ostream& os, const Bomb& order) {
	os << "This is a Bomb order belonging to " << order.player << " to Bomb territory " << order.targ;
	return os;
}

Player Bomb::getPlayer() const {
	return *player;
}
void Bomb::setPlayer(Player playr) {
	*player = playr;
}
Territory Bomb::getTarg() const {
	return *targ;
}
void Bomb::setTarget(Territory targ) {
	targ = targ;
}

bool Bomb::validate() const {
	if (player == nullptr || targ == nullptr ) return false;
	return targ->isAdjacent();
}

bool Bomb::execute() const {
	if (!validate()) return false;
	else return true;
}
Bomb* Bomb::clone() const {
	return new Bomb(*this);
}


Blockade::Blockade() : Orders(nullptr) {
}

//parametrized constructor
Blockade::Blockade(Player* playr, Territory* target) {
	this->player = playr;
	this->targ = target;


}


// copy constructor
Blockade::Blockade(const Blockade& order) {
	player = new Player(*order.player);
	targ = new Territory(*order.targ);

}
//destructor
Blockade::~Blockade() {
	delete player;
	delete targ;

}

//assignment+stream insertion operator
Blockade& Blockade::operator=(const Blockade& order) {
	if (this != &order) {
		if (this->player != nullptr) {
			delete player;
		}
		if (this->targ != nullptr) {
			delete targ;
		}
		this->player = new Player(*order.player);
		this->targ = new Territory(*order.targ);


	}
	return *this;
}
std::ostream& operator<<(std::ostream& os, const Blockade& order) {
	os << "This is a Blockade order belonging to " << order.player << " to Blockade territory " << order.targ;
	return os;
}

Player Blockade::getPlayer() const {
	return *player;
}
void Blockade::setPlayer(Player playr) {
	*player = playr;
}
Territory Blockade::getTarg() const {
	return *targ;
}
void Blockade::setTarget(Territory targ) {
	targ = targ;
}

bool Blockade::validate() const {
	if (player == nullptr || targ == nullptr) return false;
	return targ->getOwner() == player;
}

bool Blockade::execute() const {
	if (!validate()) return false;
	else return true;
}
Blockade* Blockade::clone() const {
	return new Blockade(*this);
}


Airlift::Airlift() : Orders(nullptr) {
}

//parametrized constructor
Airlift::Airlift(Player* playr, Territory* target, Territory* source, int* armynum) {
	this->player = playr;
	this->targ = target;
	this->source = source;
	this->armyNum = armynum;

}


// copy constructor
Airlift::Airlift(const Airlift& order) {
	player = new Player(*order.player);
	targ = new Territory(*order.targ);
	source = new Territory(*order.source);
	armyNum = new int(*order.armyNum);

}
//destructor
Airlift::~Airlift() {
	delete player;
	delete targ;
	delete source;
	delete armyNum;

}

//assignment+stream insertion operator
Airlift& Airlift::operator=(const Airlift& order) {
	if (this != &order) {
		if (this->player != nullptr) {
			delete player;
		}
		if (this->targ != nullptr) {
			delete targ;
		}
		if (this->source != nullptr) {
			delete source;
		}
		if (this->armyNum != nullptr) {
			delete armyNum;
		}
		this->player = new Player(*order.player);
		this->targ = new Territory(*order.targ);
		this->source = new Territory(*order.source);
		this->armyNum = new int(*order.armyNum);

	}
	return *this;
}
std::ostream& operator<<(std::ostream& os, const Airlift& order) {
	os << "This is an Airlift order belonging to " << order.player << " to Airlift " << order.armyNum << " armies to the territory " << order.targ << "from source territory " << order.source;
	return os;
}

Player Airlift::getPlayer() const {
	return *player;
}
void Airlift::setPlayer(Player playr) {
	*this->player = playr;
}
Territory Airlift::getTarg() const {
	return *targ;
}
void Airlift::setTarget(Territory targ) {
	*this->targ = targ;
}
Territory Airlift::getSource() const {
	return *source;
}
void Airlift::setSource(Territory source) {
	*this->source = source;
}

int Airlift::getArmynum() const {
	return *armyNum;
}
void Airlift::setArmynum(int armies) {
	*armyNum = armies;
}

bool Airlift::validate() const {
	if (player == nullptr || targ == nullptr || source == nullptr || *armyNum <= 0) return false;
	return targ->getOwner() == player && source->getOwner() == player && player->getArmies() >= armyNum;
}

bool Airlift::execute() const {
	if (!validate()) return false;
	else return true;
}
Airlift* Airlift::clone() const {
	return new Airlift(*this);
}


Negotiate::Negotiate() : Orders(nullptr) {
}

//parametrized constructor
Negotiate::Negotiate(Player* playr, Player* target) {
	this->player = playr;
	this->targ = target;


}


// copy constructor
Negotiate::Negotiate(const Negotiate& order) {
	player = new Player(*order.player);
	targ = new Player(*order.targ);

}
//destructor
Negotiate::~Negotiate() {
	delete player;
	delete targ;

}

//assignment+stream insertion operator
Negotiate& Negotiate::operator=(const Negotiate& order) {
	if (this != &order) {
		if (this->player != nullptr) {
			delete player;
		}
		if (this->targ != nullptr) {
			delete targ;
		}
		this->player = new Player(*order.player);
		this->targ = new Player(*order.targ);


	}
	return *this;
}
std::ostream& operator<<(std::ostream& os, const Negotiate& order) {
	os << "This is a Negotiate order belonging to " << order.player << " to Negotiate Player " << order.targ;
	return os;
}

Player Negotiate::getPlayer() const {
	return *player;
}
void Negotiate::setPlayer(Player playr) {
	*this->player = playr;
}
Player Negotiate::getTarget() const{
	return *targ;
}
void Negotiate::setTarget(Player targ) {
	*this->targ = targ;
}

bool Negotiate::validate() const {
	if (player == nullptr || targ == nullptr) return false;
	return targ != player;
}

bool Negotiate::execute() const {
	if (!validate()) return false;
	else return true;
}
Negotiate* Negotiate::clone() const {
	return new Negotiate(*this);
}




//constructors
OrdersList::OrdersList() { }

//copy constructor
OrdersList::OrdersList(const OrdersList& order) {
	for (int i = 0; i < order.orders->size(); i++) {
		Orders* ord = order.orders->at(i)->clone();
		this->orders->push_back(ord);
	}

}


//destructor
OrdersList::~OrdersList() {
	while (!orders->empty())
		delete orders->back();
}

//assignment+stream insertion operator
OrdersList& OrdersList::operator=(const OrdersList& order) {
	while (!orders->empty())
		delete orders->back();
	for (int i = 0; i < order.orders->size(); i++) {
		Orders* ord = order.orders->at(i)->clone();
		this->orders->push_back(ord);
	}
	return *this;
}


std::ostream& operator<<(std::ostream& os, const OrdersList& order) {
	os << "Orders: ";
	for (int i = 0; i < order.orders->size(); i++) {
		os << *order.orders->at(i) << ", ";
	}
	os << ".";
	return os;
}


//getters
std::vector<Orders*> OrdersList::getOrders() const {
	return *orders;
}
//setters
void OrdersList::setOrders(std::vector<Orders*> orderss) {
	*this->orders = orderss;
}



//methods needed:
void OrdersList::add(Orders* order) {
	this->orders->push_back(order);
}

void OrdersList::remove(Orders* order) {
	for (int i = 0; i < orders->size(); i++) {
		if (order==orders->at(i)){
			orders->erase(orders->begin() + i);
			break;
		}	
	}
}

void OrdersList::move(Orders* order1, Orders* order2) {
	int p1 = -1;
	int p2 = -1;
	for (int i = 0; i < orders->size(); i++) {
		if (order1 == orders->at(i)) 
			p1=i;
		if (order2 == orders->at(i))
			p2=i;
		if (p1 > -1 && p2 > -1) {
			Orders* temp = orders->at(p1);
			orders->at(p1) = order2;
			orders->at(p2) = temp;

			delete temp;

			break;
		}
	}
}
