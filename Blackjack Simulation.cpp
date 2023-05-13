#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

#define HANDSIMULATIONSHUNDRED 100
#define SIZEOFDECK 52

using namespace std;

void createDeck(vector<int>& deck);
void printingOfDeck(vector<int>& deck);
void deckShuffling(vector<int>& deck);
void cardDealt(vector<int>& deck, vector<int>& hand);
int sumOfDeck(vector<int>& hand);

int main()
{
    std::vector<int> deck_of_cards;
    std::vector<int> hand_of_player;
    std::vector<int> hand_of_dealer;

    // Seed random
    srand(time(NULL));

    int score_of_player = 0;
    int score_of_dealer = 0;
    int number_of_played_hands = 0;

    while (number_of_played_hands < HANDSIMULATIONSHUNDRED)
    {
        cout << "This is game number " << number_of_played_hands << "\n" << endl;
        createDeck(deck_of_cards);
        deckShuffling(deck_of_cards);
        cout << "A new deck is shuffled "
            << endl;
        printingOfDeck(deck_of_cards);

        cardDealt(deck_of_cards, hand_of_player);
        cardDealt(deck_of_cards, hand_of_dealer);
        cardDealt(deck_of_cards, hand_of_player);
        cardDealt(deck_of_cards, hand_of_dealer);

        cout << "New cards are dealt out "
            << endl;
        printingOfDeck(deck_of_cards);

        cout << "Hand of the player: " << endl;
        auto sizeOfPlayerHand = sumOfDeck(hand_of_player);
        cout << "Cards added up equals " << sizeOfPlayerHand << endl;
        cout << "\n"
            << endl;
        printingOfDeck(hand_of_player);

        cout << "Hand of the dealer " << endl;
        auto sizeOfDealerHand = sumOfDeck(hand_of_dealer);
        cout << "Cards added up equals " << sizeOfDealerHand << endl;
        cout << "\n"
            << endl;
        printingOfDeck(hand_of_dealer);

        if (sizeOfPlayerHand == 21)
        {
            cout << "The player wins!" << endl;
        }
        else if (sizeOfPlayerHand < 12)
        {
            for (int i = 0; i < hand_of_player.size(); i++)
            {
                if (hand_of_player[i] == 11)
                {
                    hand_of_player[i] = 1;
                    break;
                }
            }
            while (sizeOfPlayerHand < 12)
            {
                cardDealt(deck_of_cards, hand_of_player);
                sizeOfPlayerHand = sumOfDeck(hand_of_player);
                cout << "Hand of the dealer " << endl;
                cout << sizeOfPlayerHand << endl;
                cout << "\n"
                    << endl;
                printingOfDeck(hand_of_player);
            }
        }
        else
        {
            cout << "The dealer holds" << endl;
        }

        if (sizeOfDealerHand < 16)
        {
            for (int i = 0; i < hand_of_dealer.size(); i++)
            {
                if (hand_of_dealer[i] == 11)
                {
                    hand_of_dealer[i] = 1;
                    break;
                }
            }
            while (sizeOfDealerHand < 16)
            {
                cardDealt(deck_of_cards, hand_of_dealer);
                sizeOfDealerHand = sumOfDeck(hand_of_dealer);
                cout << "Hand of the dealer " << endl;
                cout << sizeOfDealerHand << endl;
                cout << "\n"
                    << endl;
                printingOfDeck(hand_of_dealer);
            }
        }
        else
        {
            cout << "The dealer holds" << endl;
        }

        if (sizeOfPlayerHand > 21)
        {
            cout << "The player loses! Hand lost\n"
                << endl;
            cout << "The dealer wins.\n"
                << endl;
            score_of_dealer++;
        }
        else if (sizeOfDealerHand > 21)
        {
            cout << "The dealer busts! Dealer hand lost" << endl;
            cout << "The player wins!\n"
                << endl;
            score_of_player++;
        }
        else if (sizeOfPlayerHand > sizeOfDealerHand)
        {
            cout << "The player wins!" << endl;
            score_of_player++;
        }
        else if (sizeOfPlayerHand < sizeOfDealerHand)
        {
            cout << "The dealer wins." << endl;
            score_of_dealer++;
        }
        else
        {
            cout << "The hand ends up in a draw." << endl;
        }

        cout << "\n"
            << endl;
        cout << "The score of the player is " << score_of_player << endl;
        cout << "The score of the dealer is " << score_of_dealer << endl;

        // Brand new deck clears for both the player and dealer
        deck_of_cards.clear();
        hand_of_player.clear();
        hand_of_dealer.clear();

        // The number of the hands being played in a gane increases
        number_of_played_hands++;
    }

    if (score_of_player > score_of_dealer)
    {
        cout << "The player wins in the Blackjack simulation " << score_of_player << endl;
    }
    else if (score_of_player < score_of_dealer)
    {
        cout << "The dealer wins in the Blackjack simulation " << score_of_dealer << endl;
    }
    else
    {
        cout << "The simulation between the player and dealer ends in a draw" << endl;
    }

    return 0;
}

// Function that passes the createDeck vector
void createDeck(vector<int>& deck)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j < 14; j++)
        {
            if (j == 1)
            {
                deck.push_back(11);
            }
            else if (j > 10)
            {
                deck.push_back(10);
            }
            else
            {
                deck.push_back(j);
            }
        }
    }
}

// Function that passes the printingOfDeck vector
void printingOfDeck(vector<int>& deck)
{
    for (int i = 0; i < deck.size(); i++)
    {
        std::cout << deck[i] << " ";
    }
    cout << "\n"
        << endl;
}

// Creates a random shuffling of the cards in a deck
void deckShuffling(vector<int>& deck)
{
    random_shuffle(deck.begin(), deck.end());
}

// Deals the cards to the players
void cardDealt(vector<int>& deck, vector<int>& hand)
{
    hand.push_back(deck.back());
    deck.pop_back();
}

int sumOfDeck(vector<int>& hand)
{
    auto sum = reduce(hand.begin(), hand.end());
    return sum;
}