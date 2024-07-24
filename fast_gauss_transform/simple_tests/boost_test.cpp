#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>

int main() {
    std::string s = "Boost Libraries";
    boost::to_upper(s);
    std::cout << s << std::endl;
    return 0;
}
