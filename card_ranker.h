#ifndef CARD_RANKER_H
#define CARD_RANKER_H

#include <vector>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <array>
#include <utility>
#include <tuple>

using namespace std;

using CARD = std::pair<char, char>;
using CARD_VEC = std::vector<CARD>;

enum class Cards_Rank_Set
{
    NoPair  = 0,
    OnePair = 1,
    TwoPair = 2,
    Trips   = 3,
    Straight= 4,
    Flush	= 5,
    FlHouse = 6,
    Quads	= 7,
    StFlush = 8,
};

template <typename T, size_t N>
std::vector<std::array<T, N>> Combination(const std::vector<T> &v)
{
    assert(N <= v.size());

    std::vector<bool> bitset(N, 1);
    bitset.resize(v.size(), 0);

    std::array<T, N> in_array;
    std::vector<std::array<T, N>> arr_list;

    do
    {
        size_t counter = 0;
        for (std::size_t i = 0; i != bitset.size(); ++i)
        {
            if (bitset[i])
            {
                in_array[counter] = v[i];
                ++counter;
            }
        }

        arr_list.push_back(in_array);

    } while (std::prev_permutation(bitset.begin(), bitset.end()));

    return arr_list;
}


class card_ranker
{
  public:
    card_ranker(const CARD_VEC &hand_A, const CARD_VEC &hand_B, const CARD_VEC &board);
    card_ranker(CARD_VEC &&hand_A, CARD_VEC &&hand_B, CARD_VEC &&board);
    
    card_ranker(const card_ranker& rank) = delete;
    card_ranker(card_ranker&& rank) = delete;

    card_ranker &operator=(const card_ranker &rhs) = delete;
    card_ranker &operator=(card_ranker &&other) = delete;

    void process();

  private:
    std::pair<int, int> rank_cards(const CARD_VEC& hand, const CARD_VEC& board);
    void output_result(const std::pair<int, int>& score_A, const std::pair<int, int>& score_B);
    std::pair<int, int> calculate_score(std::vector<CARD>& card_vec);

    CARD_VEC _hand_A;
    CARD_VEC _hand_B;
    CARD_VEC _board;
};

card_ranker::card_ranker(const CARD_VEC &hand_A, const CARD_VEC &hand_B, const CARD_VEC &board)
    : _hand_A(hand_A), _hand_B(hand_B), _board(board)
{
}

card_ranker::card_ranker(CARD_VEC &&hand_A, CARD_VEC &&hand_B, CARD_VEC &&board)
    : _hand_A(std::move(hand_A)), _hand_B(std::move(hand_B)), _board(std::move(board))
{
}

void card_ranker::process()
{
    // test the rules, and output the results
    std::pair<int, int> score_A = rank_cards(_hand_A, _board);
    std::pair<int, int> score_B = rank_cards(_hand_B, _board);

    output_result(score_A, score_B);
}

std::pair<int, int> card_ranker::rank_cards(const CARD_VEC& hand, const CARD_VEC& board)
{
    std::vector<std::array<CARD, 2>> hand_list = Combination<CARD, 2>(hand);
    std::vector<std::array<CARD, 3>> board_list = Combination<CARD, 3>(board);

    // for test the output
    /*
    for (auto& hand: hand_list)
    {
        cout << hand[0].first << hand[0].second << '\t' << hand[1].first << hand[1].second << endl;
    }
    */

    int hi = -1000;
    int low = 1000;
    
    for (size_t i = 0; i < hand_list.size(); i++)
    {
        for (size_t j = 0; j < board_list.size(); j++)
        {
            std::vector<CARD> my_cards;            

            std::copy(hand_list[i].begin(), hand_list[i].end(), std::back_inserter(my_cards));
            std::copy(board_list[j].begin(), board_list[j].end(), std::back_inserter(my_cards));

            std::pair<int, int> score = calculate_score(my_cards);    
            if (score.first > hi)
                hi = score.first;
                
            if (score.second < low)
                low = score.second;
        }
    }

    return {hi, low};
}

std::pair<int, int> card_ranker::calculate_score(std::vector<CARD>& card_vec)
{
    // to do , but no time

    return {0, 0};
}

void card_ranker::output_result(const std::pair<int, int>& score_A, const std::pair<int, int>& score_B)
{
    // to do
}

#endif
