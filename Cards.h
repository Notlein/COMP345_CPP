#pragma once

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using std::ostream;
using std::string;
using std::vector;

// Declaration of deck size, deck contains 25 cards.
const int sizeDeck = 25;

class Card {
public:
  Card();
  ~Card();

  Card(string s);
  Card &operator=(const Card &c);
  Card(const Card &c);

  friend ostream &operator<<(ostream &out, const Card &Card);

  string *getCard();
  void setCard(string s);
  string *card_type;
};

class Deck : public Card {

public:
  string draw();

  Deck();
  ~Deck();
  Deck(Card *card);

  Deck &operator=(const Deck &d);

  Deck(const Deck &d);

  friend ostream &operator<<(ostream &out, const Deck &Deck);

  void genDeck();

  void displayDeck(string arr[]);

  string arrDeck[sizeDeck];
  vector<Card *> deck;
};

class Hand : Deck {
public:
  Hand();
  ~Hand();

  Hand &operator=(const Hand &h);

  Hand(const Hand &h);

  friend ostream &operator<<(ostream &out, const Hand &Hand);

  void set_card(string);

  int displayNumOfCards();

  void displayHandCards();

  void play(Deck *deck, string s, int index);

  void displayVec(vector<string *> *vec);

  void return_to_Deck(Deck *deck, string s);

  string arrHand[sizeDeck];
};

void testCards();
