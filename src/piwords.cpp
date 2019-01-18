#include <trie.h>
#include <string>
#include <list>
#include <iostream>
#include <fstream>

#include "gen_val.h"

int main(int argc, char ** argv)
{
    size_t num_digits;
    char * file_name;
    if(argc == 2)
    {
        num_digits = 10000;
        file_name = argv[1];
    }
    else if (argc == 3)
    {
        num_digits = std::stoul(std::string(argv[1]));
        file_name = argv[2];
    }
    else {
        std::cerr << "Usage: [digits of pi] <file name>" << std::endl;
        return 1;
    }

    std::vector<int> digits;
    while(num_digits-- > 0)
    {
        digits.push_back(next_val());
    }

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
        trie.add_word(word);
    }
    std::list<Match> matches;
    std::list<TrieNode *> partial_matches;

    match_sequence(digits, 0, matches, partial_matches,
                   trie, 3);

    std::cout << "Found " << matches.size() << " matches." << std::endl;

    for(auto match : matches)
    {
        std::cout << match.index << ": " << match.word << std::endl;
    }

    std::cout << std::endl;

    return 0;
}
