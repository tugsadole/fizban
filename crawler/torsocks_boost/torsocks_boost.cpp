#include "torsocks_boost.hpp"

OnionEntry::OnionEntry() {
    std::cout << "Constructing onion entry\n";
}

OnionEntry::~OnionEntry() {
    std::cout << "Deconstructing onion entry\n";
}


OnionPool::OnionPool()
{
    std::cout << "Constructing onion pool\n";
}

OnionPool::~OnionPool()
{
    std::cout << "Destructing onion pool\n";
}