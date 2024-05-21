#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

int main() {
    std::string name("Maneesh");

    std::string full_name;

    // back_inserter: container must support "push_back"
    // similarly there are other inserters
    std::copy(name.cbegin(), name.cend(), std::back_inserter(full_name));

    const char* cname = "Sutar";

    std::copy(cname, cname + 5, std::back_inserter(full_name));

    std::cout << full_name << std::endl;

    *full_name.begin()       = 'T';
    *(full_name.begin() + 2) = 'A';

    *(full_name.end() - 1)                  = 'B';
    *(full_name.end())                      = 'C';
    *(full_name.begin() + full_name.size()) = 'D';  // equivalent to full_name.end()
    *(full_name.end() + 1)                  = 'E';

    std::cout << full_name << std::endl;
    printf("%s\n", full_name.c_str());
}