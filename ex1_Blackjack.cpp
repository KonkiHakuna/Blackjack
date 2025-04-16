#include <iostream>

using namespace std;

// Blackjack

enum class Color {
	// Declaration of card colors
	Heart = 0,
	Diamond,
	Spade,
	Club,

	Number
};

void Print(Color color) {
	//  Printing card colors
	switch (color) {
	case Color::Heart:
		cout << "Heart";
		break;
	case Color::Diamond:
		cout << "Diamond";
		break;
	case Color::Spade:
		cout << "Spade";
		break;
	case Color::Club:
		cout << "Club";
		break;
	default:
		cout << "none";
	}
}

enum class Value {
	// Declaration of card values
	Two = 0,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Ace,

	Number
};

void Print(Value value) {
	// Printing card values
	switch (value)
	{
	case Value::Two:
		cout << "Two";
		break;
	case Value::Three:
		cout << "Three";
		break;
	case Value::Four:
		cout << "Four";
		break;
	case Value::Five:
		cout << "Five";
		break;
	case Value::Six:
		cout << "Six";
		break;
	case Value::Seven:
		cout << "Seven";
		break;
	case Value::Eight:
		cout << "Eight";
		break;
	case Value::Nine:
		cout << "Nine";
		break;
	case Value::Ten:
		cout << "Ten";
		break;
	case Value::Jack:
		cout << "Jack";
		break;
	case Value::Queen:
		cout << "Queen";
		break;
	case Value::King:
		cout << "King";
		break;
	case Value::Ace:
		cout << "Ace";
		break;
	default:
		cout << "none";
	}

}

class Card {
	// Building and representing a card
public:
	friend class Game;
	friend class Hand;
	friend class Deck;
	friend class DealerHand;

	Card() = default;
	Card(Color color, Value value) : m_color(color), m_value(value) {}

	void PrintCard()
	{
		Print(m_color);
		cout << " ";
		Print(m_value);
	}

private:
	Color m_color = Color::Heart;
	Value m_value = Value::Two;
};

class Deck {
	// Building a deck of cards, shuffling and dealing cards
public:
	friend class Game;
	friend class Hand;
	friend class DealerHand;

	Deck() {
		Initialize();
	}

	void Initialize() {
		int index = 0;
		for (int i = 0; i < (int)Color::Number; ++i)
		{
			for (int j = 0; j < (int)Value::Number; ++j)
			{
				m_cards[index].m_color = (Color)i;
				m_cards[index].m_value = (Value)j;
				++index;
			}
		}

		m_size = index;
	}

	void Print() {
		for (int i = 0; i < m_size; ++i)
		{
			m_cards[i].PrintCard();
			cout << endl;
		}
	}

	void Shuffle() {
		srand(time(NULL));

		for (int i = 0; i < m_size; ++i) {
			int index = rand() % m_size;
			swap(m_cards[i], m_cards[index]);
		}
	}

	Card Deal() {
		Card result = m_cards[m_size - 1];
		m_size--;
		return result;
	}

	int GetSize() {
		return m_size;
	}

private:
	Card m_cards[52];
	int m_size = 0;
};

class Hand {
	// Player's hand - displaying cards and returning points
public:
	friend class Game;
	void AddPlayerHand(Deck& deck) {
		p_Hand[NumberOfCards] = deck.Deal();
		NumberOfCards++;
	}
	int AmountOfPoints() {
		int SumOfPoints = 0;
		int AceCount = 0;
		for (int i = 0; i < NumberOfCards; i++) {
			if ((p_Hand[i].m_value) < Value::Jack) {
				SumOfPoints = SumOfPoints + (int)(p_Hand[i].m_value) + 2;
			}
			else if (((p_Hand[i].m_value) > Value::Ten) and ((p_Hand[i].m_value) != Value::Ace)) {
				SumOfPoints = SumOfPoints + 10;
			}
			else {
				SumOfPoints = SumOfPoints + 11;
				AceCount++;
			}
		}
		while ((AceCount > 0 and SumOfPoints > 21)) {
			SumOfPoints = SumOfPoints - 10;
			AceCount--;

		}
		return SumOfPoints;
	}
	void Print() {
		cout << "\nYour cards are: " << endl;
		for (int i = 0; i < NumberOfCards; ++i) {
			p_Hand[i].PrintCard();
			cout << endl;
		}
		cout << "Total points: " << AmountOfPoints() << endl;
	}
	void Reset() {
		NumberOfCards = 0;
	}

private:
	Card p_Hand[52];
	int NumberOfCards = 0;
};

class DealerHand {
	// Dealer's hand - displaying cards and returning points
public:
	void AddDealerHand(Deck& deck) {
		d_Hand[NumberOfCards] = deck.Deal();
		NumberOfCards++;
	}
	int DealersAmountOfPoints() {
		int SumOfPoints = 0;
		int AceCount = 0;
		for (int i = 0; i < NumberOfCards; i++) {
			if ((d_Hand[i].m_value) < Value::Jack) {
				SumOfPoints = SumOfPoints + (int)(d_Hand[i].m_value) + 2;
			}
			else if (((d_Hand[i].m_value) > Value::Ten) and ((d_Hand[i].m_value) != Value::Ace)) {
				SumOfPoints = SumOfPoints + 10;
			}
			else {
				SumOfPoints = SumOfPoints + 11;
				AceCount++;
			}
		}
		while ((AceCount > 0 and SumOfPoints > 21)) {
			SumOfPoints = SumOfPoints - 10;
			AceCount--;

		}
		return SumOfPoints;
	}
	void Print() {
		cout << "Dealer's cards: " << endl;
		for (int i = 0; i < NumberOfCards; ++i) {
			d_Hand[i].PrintCard();
			cout << endl;
		}
		cout << "Total points: " << DealersAmountOfPoints() << endl << endl;
	}
	void Reset() {
		NumberOfCards = 0;
	}

private:
	Card d_Hand[52];
	int NumberOfCards = 0;
};

class Game {
	// Logic of the entire game
public:
	void GameStart() {
		deck.Shuffle();
		p_hand.Reset();
		d_hand.Reset();
		p_hand.AddPlayerHand(deck);
		p_hand.AddPlayerHand(deck);
		d_hand.AddDealerHand(deck);
		p_hand.Print();
		cout << endl;
		d_hand.Print();
		PlayersTurn();
		DealersTurn();
		GameState();

	}
	void PlayersTurn() {
		string ans;
		cout << endl << "Player's turn:" << endl;
		if (p_hand.AmountOfPoints() < 21) {
			cout << "Do you want to draw a card (Hit) or stay with your current hand (Stand)? ";
			cin >> ans;
			while (true) {
				for (int i = 0; i < ans.length(); i++) {
					ans[i] = tolower(ans[i]);
				}
				if (ans == "hit") {
					p_hand.AddPlayerHand(deck);
					p_hand.Print();
					if (p_hand.AmountOfPoints() > 21) {
						cout << "Bust! You've exceeded 21 points.";
						return;
					}
					if (p_hand.AmountOfPoints() == 21) {
						cout << "Wow! Exactly 21 points.";
						return;
					}
				}
				else if (ans == "stand") {
					return;
				}
				else {
					cout << "Invalid command. Try again: \n";
				}
				cout << "Hit or stand? ";
				cin >> ans;
			}
		}
		cout << "Wow, Blackjack! You've got exactly 21 points. ";
	}
	void DealersTurn() {
		if (p_hand.AmountOfPoints() <= 21) {
			cout << endl << "Dealer's turn: " << endl;
			while (d_hand.DealersAmountOfPoints() < 17) {
				d_hand.AddDealerHand(deck);
				d_hand.Print();
			}
		}
	}
	void GameState() {
		if (p_hand.AmountOfPoints() > 21) {
			cout << "You lost!";
			return;
		}
		else if (d_hand.DealersAmountOfPoints() > 21) {
			cout << "You won! Dealer busted.\n";
			return;
		}
		else if (p_hand.AmountOfPoints() > d_hand.DealersAmountOfPoints()) {
			cout << "You won! You have more points than dealer.\n";
			return;
		}
		else if (p_hand.AmountOfPoints() < d_hand.DealersAmountOfPoints()) {
			cout << "You lost! Dealer has more points than you.\n";
			return;
		}
		else {
			cout << "It's a tie!\n";
		}
	}
private:
	Deck deck;
	Hand p_hand;
	DealerHand d_hand;

};

int main() {
	// Main function
	Game game;
	string ans;
	bool play = true;

	cout << "Welcome to my Blackjack game!\nWould you like to play a round? (Yes/No) ";
	cin >> ans;
	for (int i = 0; i < ans.length(); i++) {
		ans[i] = tolower(ans[i]);
	}
	while (ans != "yes" and ans != "no") {
		cout << "Invalid command. Try again: \n";
		cin >> ans;
		for (int i = 0; i < ans.length(); i++) {
			ans[i] = tolower(ans[i]);
		}
	}
	if (ans == "no") {
		cout << "Alright, see you next time!";
		return 0;
	}
	while (play) {
		game.GameStart();
		cout << endl << "\nWould you like to play again? (Yes/No) ";
		cin >> ans;
		for (int i = 0; i < ans.length(); i++) {
			ans[i] = tolower(ans[i]);
		}
		while (ans != "yes" and ans != "no") {
			cout << "Invalid command. Try again: \n";
			cin >> ans;
			for (int i = 0; i < ans.length(); i++) {
				ans[i] = tolower(ans[i]);
			}
		}
		if (ans == "no") {
			cout << "Alright, see you next time!";
			play = false;
		}
	}
	return 0;
}

