#include "Cards.h"
#include "Player.h"
#include "Orders.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <random>


//local helpers--------------------

namespace {
std::mt19937& rng(){ //Used to generate random numbers for stuff like drawing random cards from the deck
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
    }


    //used for printing
    const char* to_string(cardType t){
        switch(t){
                case cardType::Bomb:          return "Bomb";
                case cardType::Reinforcement: return "Reinforcement";
                case cardType::Blockade:      return "Blockade";
                case cardType::Airlift:       return "Airlift";
                case cardType::Diplomacy:     return "Diplomacy";
                default:                      return "Unknown";
        }
    }
}

//Card

Card::Card(cardType t) : type(new cardType (t)){}  //Construct a Card by allocating the cardType on the heap

Card::Card(const Card& other) : type(new cardType(*other.type)) {} //copy construc of a card by deep copy of the enum value

Card& Card::operator=(const Card& other) {  //Copy assign a card by deep-copying a fresh enum value and replacing owned pointer.
    if (this != &other) {
        auto* fresh = new cardType(*other.type); // allocate first
        delete type;                              // release old
        type = fresh;                             // take ownership of fresh
    }
    return *this;
}

Card::~Card(){ //destructor to free allocated value on the heap
    delete type;
}

//getter of the enum value
cardType Card::getType() const {
    return *type;
}

Orders* Card::toOrder(Player& p) const {  //create new order for a player add correct parameter
    switch (*type) {
        case cardType::Bomb:          return new Bomb();
        case cardType::Blockade:      return new Blockade();
        case cardType::Airlift:       return new Airlift();
        case cardType::Diplomacy:     return new Negotiate();
        case cardType::Reinforcement: return new Deploy();
        default:                      return nullptr;
    }
}

//Create proper order, add it to OrdersList, remove card from hand and return it to the deck
void Card::play(Player& p,Deck& d,Hand& h){

    //Create order
    Orders* o=toOrder(p);
    if (!o){
        std::cerr <<"[Card::play] Could not create order for card type: "
                  << to_string(*type) << "\n";
        
        return;
    }

    //Add order to the list
     OrdersList* list = p.getOrder();
    if (!list) {
        //if Player has no OrdersList, avoid leaking the order
        std::cerr << "[Card::play] Player has no OrdersList; dropping order.\n";
        delete o;
        return;
    }
    list->add(o);

        //remove card from hand
     if (!h.remove(this)) {
        // If not found, we still continue: we must restore a consistent state
        std::cerr << "[Card::play] Card not found in hand (already removed?).\n";
    }

    // return the same card object to the deck (Ownership goes to the deck again)
    d.addBack(this);
}


//Hand

// Construct empty Hand, allocate the vector on the heap
Hand::Hand() : cards_(new std::vector<Card*>) {}

// Copy-construct a Hand: deep-copy every owned Card (clone each Card object).
Hand::Hand(const Hand& other) : cards_(new std::vector<Card*>) {
    cards_->reserve(other.cards_->size());
    for (Card* c : *other.cards_) {
        cards_->push_back(new Card(*c)); // clone (deep copy)
    }
}

// Copy-assign a Hand: build a fresh deep copy first, then replace old contents safely.
Hand& Hand::operator=(const Hand& other) {
    if (this != &other) {
        auto* fresh = new std::vector<Card*>;
        fresh->reserve(other.cards_->size());
        for (Card* c : *other.cards_) {
            fresh->push_back(new Card(*c)); // clone each card
        }
        // Delete our currently owned cards and the old vector
        for (Card* c : *cards_) delete c;
        delete cards_;
        // Install the fresh deep copy
        cards_ = fresh;
    }
    return *this;
}

// Destructor: delete all owned Card* still in the hand, then delete the vector itself.
Hand::~Hand() {
    for (Card* c : *cards_)   delete c;
    delete cards_;
}

// Add a card: push pointer; Hand becomes the owner of the card.
void Hand::add(Card* c) {
    if (c) cards_->push_back(c);
}

// Remove a specific card pointer from the hand (no deletion).
// Returns true if removed; false if the pointer wasn't found.
bool Hand::remove(Card* c) {
    if (!c) return false;
    auto it = std::find(cards_->begin(), cards_->end(), c);
    if (it == cards_->end()) return false;
    cards_->erase(it);
    return true;
}

// Expose const view of the internal vector (read-only).
const std::vector<Card*>* Hand::cards() const {
    return cards_;
}


//Deck

// Construct empty Deck, allocate the vector on the heap
Deck::Deck() : cards_(new std::vector<Card*>) {}

// Copy-construct a Deck: deep-copy every owned Card (clone each Card object).
Deck::Deck(const Deck& other) : cards_(new std::vector<Card*>) {
    cards_->reserve(other.cards_->size());
    for (Card* c : *other.cards_) {
        cards_->push_back(new Card(*c)); // clone (deep copy)
    }
}

Deck::Deck(const std::vector<Card*>& cards) : cards_(new std::vector<Card*>) {
    cards_->reserve(cards.size());
    for (Card* c : cards) {
        cards_->push_back(new Card(*c));  // deep copy each Card
    }
}

// Copy-assign a Deck: build a fresh deep copy first, then replace old contents safely.
Deck& Deck::operator=(const Deck& other) {
    if (this != &other) {
        auto* fresh = new std::vector<Card*>;
        fresh->reserve(other.cards_->size());
        for (Card* c : *other.cards_) {
            fresh->push_back(new Card(*c)); // clone each card
        }
        // Delete our currently owned cards and the old vector
        for (Card* c : *cards_) delete c;
        delete cards_;
        // Install the fresh deep copy
        cards_ = fresh;
    }
    return *this;
}

// Destructor: delete all owned Card* still in the deck, then delete the vector itself.
Deck::~Deck() {
    for (Card* c : *cards_) delete c;
    delete cards_;
}

// Draw a random card from the deck, remove it from this container,
// and add it to the target hand (ownership moves to Hand).
// Returns the drawn Card* so the caller can log/inspect it.
Card* Deck::draw(Hand& targetHand) {
    if (cards_->empty()) {
        std::cerr << "[Deck::draw] Deck is empty.\n";
        return nullptr;
    }

    // Choose a random index uniformly from [0, size-1] size of deck is derived from vector size
    std::uniform_int_distribution<size_t> dist(0, cards_->size() - 1);
    size_t idx = dist(rng());

    // Get the pointer at that index
    Card* picked = cards_->at(idx);

    // Remove it from the deck (ownership leaves Deck)
    cards_->erase(cards_->begin() + static_cast<std::ptrdiff_t>(idx));

    // Add to the hand (ownership goes to Hand)
    targetHand.add(picked);

    return picked;
}

// Return a card to the deck (ownership moves to Deck).
void Deck::addBack(Card* c) {
    if (c) cards_->push_back(c);
}

// Number of cards currently in the deck.
size_t Deck::size() const {
    return cards_->size();
}

//printing purposes
std::ostream& operator<<(std::ostream& os, const Card& c) {
    os << "Card(" << to_string(c.getType()) << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Deck& d) {
    os << "Deck[" << d.size() << "]: { ";
    for (const Card* c : *d.cards_) os << *c << " ";
    os << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Hand& h) {
    os << "Hand[" << h.cards()->size() << "]: { ";
    for (const Card* c : *h.cards()) os << *c << " ";
    os << "}";
    return os;
}








