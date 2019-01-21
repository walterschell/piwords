#include <trie.h>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>

#define PRINT_PROGRESS 1

#include "gen_val.h"

int main(int argc, char ** argv)
{
    size_t num_digits;
    char * file_name;
    char * pi_file_name;
    if(argc == 3)
    {
        num_digits = 10000;
        file_name = argv[2];
        pi_file_name = argv[1];
    }
    else if (argc == 4)
    {
        num_digits = std::stoul(std::string(argv[1]));
        file_name = argv[3];
        pi_file_name = argv[2];
    }
    else {
        std::cerr << "Usage: [digits of pi] <pi file name> <file name>" << std::endl;
        return 1;
    }

    std::vector<int> digits;
    size_t curr_digit = 0;
    int curr_percent = -1;
    int temp_percent;

    std::clog << "Initializing pi..." << std::endl;
    init_vals(pi_file_name);


    std::clog << "Building Values, progress: " << std::endl;
    int good = 1;
    while(curr_digit < num_digits && good)
    {
        digits.push_back(next_val(&good));
        curr_digit++;
        temp_percent = static_cast<int>((static_cast<float>(curr_digit) / num_digits) * 100);
#if PRINT_PROGRESS
        if (curr_percent != temp_percent)
        {
            curr_percent = temp_percent;
            std::clog << "\x1B[1G\x1B[0K" << curr_percent << "%";
            std::clog.flush();
        }
#endif
    }
    deinit_vals();
    std::clog << std::endl;

    std::ifstream inf(file_name);

    if (!inf)
    {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    Trie trie;

    while(inf)
    {
        string word;
        inf >> word;
        std::transform(word.begin(), word.end(),
                       word.begin(), ::tolower);
        trie.add_word(word);
    }
    std::list<Match> matches;
    std::list<TrieNode *> partial_matches;

    match_sequence(digits, 0, matches, partial_matches,
                   trie, 3);



    std::unordered_map<std::string, std::vector<uint64_t>> unique;

    for(auto match : matches)
    {
        if(unique.find(match.word) == unique.end())
        {
            unique[match.word] = {match.index};
        }
        else
        {
            unique[match.word].push_back(match.index);
        }
    }

    std::cout << "Found " << matches.size() << " matches ("
              << unique.size() << " unique)" << std::endl;

    for(auto u : unique)
    {
        auto word = u.first;
        auto indexes = u.second;
        std::cout << "    " << word << " located " << indexes.size() << " times:" << std::endl;
        std::cout << "\t";
        for(auto index : indexes)
        {
            std::cout << index << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::clog << "Done." << std::endl;
    return 0;
}
