#include "Cards.h"

/**
 *
 * @author Giwon Lee - 40160453
 * @date 2022.10.2 Tuesday
 *
 */

#include <ctime>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string arr[30];
static int dynamicDeckSize = sizeDeck;

// Default Constructor
Card::Card()
{
  // cout << "Card object" << endl;
}

// Default Destructor
Card::~Card() {}

Card::Card(string s) { *card_type = s; }

// Copy Constructor
Card::Card(const Card &c) { this->card_type = new string(*(c.card_type)); }

// Assignment operators
Card &Card ::operator=(const Card &c)
{
  this->card_type = new string(*(c.card_type));
  return *this;
}

// Stream insertion operator
std::ostream &operator<<(std::ostream &os, const Card &c)
{
  return os << "The card type is: " << c.card_type << endl;
}

// Returns a card type.
string *Card::getCard()
{
  return this->card_type;
}

// Setting a card to Card class manually.
void Card::setCard(string s)
{
  this->card_type = &s;
}

// Default Constructor
Deck::Deck()
{
  // cout << "Deck object" << endl;
}

Deck::~Deck()
{
  // Default Destructor
}

// Copy Constructor
Deck::Deck(const Deck &d) { this->deck = *new vector<Card *>(d.deck); }

// Assignment Opeartor
Deck &Deck ::operator=(const Deck &d)
{
  this->deck = *new vector<Card *>(d.deck);
  int size = sizeof(d.arrDeck) / sizeof(string);
  for (int i = 0; i < size; i++)
  {
    this->arrDeck[i] = d.arrDeck[i];
  }

  return *this;
}

// Stream insertion operator
std::ostream &operator<<(std::ostream &os, const Deck &d)
{
  cout << "How many cards are in a deck: " << endl;
  return os << d.deck.capacity() << " and " << d.arrDeck << endl;
}

// The deck is generated five cards each.
void Deck::genDeck()
{

  for (int i = 0; i < sizeDeck; i++)
  {

    if (i < 5)
    {
      string s = "Bomb";
      arrDeck[i] = s;
    }
    else if (i < 10 && i > 4)
    {
      string s1 = "Reinforcement";
      arrDeck[i] = s1;
    }
    else if (i < 15 && i > 9)
    {
      string s2 = "Blockade";
      arrDeck[i] = s2;
    }
    else if (i < 20 && i > 14)
    {
      string s3 = "Airlift";
      arrDeck[i] = s3;
    }
    else
    {
      string s4 = "Diplomacy";
      arrDeck[i] = s4;
    }
  }


  cout << "Deck is Generated." << endl;
}
// Display the current deck
void Deck::displayDeck(string arr[])
{
  cout << "Deck has " << dynamicDeckSize << " cards:" << endl;
  for (int i = 0; i < dynamicDeckSize; i++)
  {
    cout << "\t" << i + 1 << ": " << *(arr + i) << endl;
  }
}

// Draw one of the cards from the deck.
string Deck::draw()
{
  if (dynamicDeckSize == 0)
  {
    cout << "Deck is empty now, you can no longer draw the cards" << endl;
    return NULL;
  }

  srand(time(NULL));

  int v1 = (rand() % dynamicDeckSize);
  cout << "At " << v1 << ": " << arrDeck[v1] << endl;

  string tempCard = arrDeck[v1];

  for (int i = 0; i < dynamicDeckSize - 1; i++)
  {
    arrDeck[i] = arrDeck[i + 1];
  }
  dynamicDeckSize--;
  return tempCard;
}

// Hand default constructor
Hand::Hand()
{
  // cout << "Deck object" << endl;
}

Hand::~Hand()
{
  // Default Destructor
}

// Copy constructor of a hand class
Hand::Hand(const Hand &h)
{
  int size = sizeof(h.arrHand) / sizeof(string);
  for (int i = 0; i < size; i++)
  {
    this->arrHand[i] = h.arrHand[i];
  }
}

// Assignment operator of hand class
Hand &Hand ::operator=(const Hand &h)
{
  int size = sizeof(h.arrHand) / sizeof(string);
  for (int i = 0; i < size; i++)
  {
    this->arrHand[i] = h.arrHand[i];
  }
  return *this;
}

// Static number of cards that one hand has.
static int numCardsHand = 0;

// Display hand cards
void Hand::displayHandCards()
{
  cout << "Hand object has Cards:" << endl;
  for (int i = 0; i < numCardsHand; i++)
  {
    cout << "\t" << i + 1 << " " << arrHand[i] << endl;
  }
}

// set the card of a hand.
void Hand::set_card(string s)
{
  arrHand[numCardsHand] = s;
  numCardsHand++;
}

// display how many cards a hand has
void Hand::displayNumOfCards()
{
  cout << "Currently has " << numCardsHand << " cards." << endl;
}
// use one of the cards in the hand and return it to the deck.`
void Hand::play(Deck *deck, string s, int index)
{
  cout << "Your card is: " << s << endl;

  // This function member returns a card to the Deck.
  return_to_Deck(deck, s);
  arrHand[index] = "";

  for (int i = index; i < numCardsHand; i++)
  {
    if (index == numCardsHand)
    {
      numCardsHand--;
      return;
    }
    arrHand[i] = arrHand[i + 1];
  }
  numCardsHand--;
}

// Returns a card to the deck.
void Hand::return_to_Deck(Deck *deck, string s)
{
  cout << "Card  " << s << " return back to the deck." << endl;

  deck->arrDeck[dynamicDeckSize] = s;
  dynamicDeckSize++;
}


// A freefunction that tests the methods.
void testCards()
{
  Deck d;

  d.genDeck();

  cout << endl;
  Hand h;

  srand((int)time(0));

  int v1 = rand() % 10 + 1;
  cout << "Hand will draw " << v1 << " times." << endl;
  for (int i = 0; i < v1; i++)
  {
    h.set_card(d.draw());
  }
  cout << endl;

  while (true)
  {
    if (numCardsHand == 0)
    {
      cout << "You do not have the card(s) in your hand. \n";
      break;
    }
    h.displayHandCards();
    cout << "Which card do you want to play: " << endl;
    cout << "Enter 0 to quit." << endl;
    int index;
    cin >> index;
    if (index == 0)
    {
      cout << "You entered 0. \n";
      break;
    }
    h.play(&d, h.arrHand[index - 1], index - 1);
  }

  cout << endl;
  h.displayHandCards();
  cout << endl;
  d.displayDeck(d.arrDeck);
};
