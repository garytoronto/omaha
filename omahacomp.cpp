// omahacomp
// g++ -std=c++14 omahacomp.cpp -o omahacomp
// compiled and run successfully in Linux Mint 19

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "card_ranker.h"

using namespace std;

CARD_VEC parse_string(const string& line, int num, const string& type_str)
{
    string item;

    size_t pos = line.find(type_str);
    std::string str = line.substr(pos + 6, 3 * num - 1);  

    CARD_VEC card_vec(num);
    std::stringstream ss(str);
    
    for_each(card_vec.begin(), card_vec.end(), [&](auto& card){ss >> item; card.first = item[0]; card.second = item[1];});  
    return card_vec;
}

std::tuple< CARD_VEC, CARD_VEC, CARD_VEC > parse_line(string& line)
{
    CARD_VEC hand_A(4);
    CARD_VEC hand_B(4);
    CARD_VEC board(5);

    std::replace( line.begin(), line.end(), '-', ' ');

    hand_A = parse_string(line, 4, "HandA:");
    hand_B = parse_string(line, 4, "HandB:");
    board = parse_string(line, 5, "Board:");

    return {hand_A, hand_B, board};
}

int main(int argc, char **argv)
{
    if (argc < 3)
        cout << "error" << endl;

    ifstream in(argv[1]);
    ofstream out(argv[2]);

    string line;

    std::vector<CARD> hand_A(4);
    std::vector<CARD> hand_B(4);
    std::vector<CARD> board(5);

    while (std::getline(in, line))
    {
        //cout << line << endl;
        auto ret = parse_line(line);
        hand_A = std::get<0>(ret);
        hand_B = std::get<1>(ret);
        board  = std::get<2>(ret);

        card_ranker ranker(std::move(hand_A), std::move(hand_B), std::move(board));           
        ranker.process();
    }

    return 0;
}
