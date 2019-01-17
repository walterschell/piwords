#include <trie.h>
#include <string>
#include <list>
#include <iostream>

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

    std::list<int> digits;
    while(num_digits-- > 0)
    {
        digits.push_back(next_val());
    }



    return 0;
}
