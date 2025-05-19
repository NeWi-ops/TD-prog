#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdlib>      
#include <ctime>        
#include <functional>   



enum class CardKind {
    Heart,
    Diamond,
    Club,
    Spade,
};

enum class CardValue {
    Two,
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
};

struct Card {
    CardKind kind;
    CardValue value;

    // Opérateur d'égalité
    bool operator==(const Card& other) const {
        return kind == other.kind && value == other.value;
    }

    // Fonction de hachage 
    size_t hash() const {
        return static_cast<size_t>(static_cast<int>(kind)) * 13 + static_cast<int>(value);
    }
};



namespace std {
    template <>
    struct hash<Card> {
        size_t operator()(Card const& card) const {
            return card.hash();
        }
    };
}



std::vector<Card> get_cards(size_t const size) {
    std::vector<Card> cards;
    cards.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        cards.push_back({
            static_cast<CardKind>(rand() % 4),
            static_cast<CardValue>(rand() % 13)
        });
    }
    return cards;
}



std::string card_name(Card const& card) {
    std::string name {};

    unsigned int card_value {(static_cast<unsigned int>(card.value) + 2) % 14};

    if (card_value < 10) {
        name += std::to_string(card_value);
    } else if (card_value == 10) {
        name += "10";
    } else if (card_value == 11) {
        name += 'J';
    } else if (card_value == 12) {
        name += 'Q';
    } else if (card_value == 13) {
        name += 'K';
    } else if (card_value == 1) {
        name += 'A';
    }

    name += " of ";

    switch (card.kind) {
        case CardKind::Heart: name += "Heart"; break;
        case CardKind::Diamond: name += "Diamond"; break;
        case CardKind::Club: name += "Club"; break;
        case CardKind::Spade: name += "Spade"; break;
    }

    return name;
}


int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // initialisation de rand

    std::vector<Card> cards = get_cards(100);
    std::unordered_map<Card, int> card_counts;

    for (const Card& card : cards) {
        card_counts[card]++;
    }

    std::cout << "Répartition des cartes aléatoires :\n";
    std::cout << "-----------------------------------\n";
    for (const auto& [card, count] : card_counts) {
        std::cout << card_name(card) << " : " << count << " fois\n";
    }

    return 0;
}
