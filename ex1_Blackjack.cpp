#include <iostream>

using namespace std;

//Blackjack

enum class Color {
	//Deklaracja kolorów kart
	Heart = 0,
	Diamond,
	Spade,
	Club,

	Number
};

void Print(Color color) {
	//Wypisywanie koloru karty
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
	//Deklaracja wartości kart
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
	//Wypisywanie wartości karty
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
	//Klasa buduje i reprezentuje karte
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

	// operator>
	// operator<

private:
	Color m_color = Color::Heart;
	Value m_value = Value::Two;
};

class Deck {
	//Tworzenie talii kart, tasowanie i rozdawanie
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
	//Reka gracza - wyswietlanie kart i zwracanie wartosci punktowej
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
		cout << "Twoje karty to:" << endl;
		for (int i = 0; i < NumberOfCards; ++i) {
			p_Hand[i].PrintCard();
			cout << endl;
		}
		cout << "Lacznie masz: " << AmountOfPoints() << endl;
	}
private:
	Card p_Hand[52];
	int NumberOfCards = 0;
};

class DealerHand {
	//Reka krupiera - wyswietlanie kart i zwracanie wartosci punktowej
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
		cout << "Karty krupiera to:" << endl;
		for (int i = 0; i < NumberOfCards; ++i) {
			d_Hand[i].PrintCard();
			cout << endl;
		}
		cout << "Lacznie masz: " << DealersAmountOfPoints() << endl;
	}

private:
	Card d_Hand[52];
	int NumberOfCards = 0;
};

class Game {
	//Logika calej gry
public:
	void GameStart() {
		deck.Shuffle();
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
		cout << endl << "Tura gracza:" << endl;
		if (p_hand.AmountOfPoints() < 21) {
			cout << "Czy chcesz dobrac karte(Hit) czy zostajesz na tym co masz(Stand)?";
			cin >> ans;
			while (true) {
				for (int i = 0; i < ans.length(); i++) {
					ans[i] = tolower(ans[i]);
				}
				if (ans == "hit") {
					p_hand.AddPlayerHand(deck);
					p_hand.Print();
					if (p_hand.AmountOfPoints() > 21) {
						cout << "Bust! Przekroczyles 21 punktow.";
						return;
					}
					if (p_hand.AmountOfPoints() == 21) {
						cout << "Blackjack! Masz dokladnie 21 punktow.";
						return;
					}
				}
				else if (ans == "stand") {
					return;
				}
				else {
					cout << "Bledna komenda.";
					cin >> ans;
				}
				cout << "Dobierasz czy zostajesz? (Hit or Stand):";
				cin >> ans;
			}
		}
		cout << "Wow, Blackjack! Masz 21 punktow.";
	}
	void DealersTurn() {
		if (p_hand.AmountOfPoints() <= 21) {
			cout << endl << "Tura Krupiera: " << endl;
			while (d_hand.DealersAmountOfPoints() < 17) {
				d_hand.AddDealerHand(deck);
				d_hand.Print();
			}
			if (d_hand.DealersAmountOfPoints() > 21) {
				cout << "Bust ze strony Krupiera!";
			}
		}
	}
	void GameState() {
		if (p_hand.AmountOfPoints() > 21) {
			cout << "Przegrana gracza!";
			return;
		}
		else if (d_hand.DealersAmountOfPoints() > 21) {
			cout << "Wygrales! Krupier przekroczyl 21 punktow.";
			return;
		}
		else if (p_hand.AmountOfPoints() > d_hand.DealersAmountOfPoints()) {
			cout << "Wygrales! Masz wiecej punktow od Krupiera.";
			return;
		}
		else if (p_hand.AmountOfPoints() < d_hand.DealersAmountOfPoints()) {
			cout << "Przegrales! Krupier ma wiecej punktow od ciebie";
			return;
		}
		else {
			cout << "Remis!";
		}
	}
private:
	Deck deck;
	Hand p_hand;
	DealerHand d_hand;

};

int main() {
	Game game;
	string ans;
	cout << "Witamy w naszym kasynie!\nNa razie dostepny jest tylko BlackJack, czy chcialbys zagrac? (Tak/Nie): ";
	cin >> ans;
	for (int i = 0; i < ans.length(); i++) {
		ans[i] = tolower(ans[i]);
	}
	if (ans == "tak") {
		game.GameStart();
	}
	else {
		cout << "Szkoda, zapraszamy nastepnym razem";
	}
	return 0;
}

