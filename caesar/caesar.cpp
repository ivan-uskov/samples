#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>

using namespace std;

using Type = uint8_t;

template <typename T = uint8_t>
void crypt(istream & in, ostream & out, unsigned key)
{
    transform(std::istream_iterator<T>(in), std::istream_iterator<T>(), std::ostream_iterator<T>(out), [key](T v) {
        return T((v + key) % std::numeric_limits<T>::max());
    });
}

template <typename T = uint8_t>
void decrypt(istream & in, ostream & out, unsigned key)
{
    transform(std::istream_iterator<T>(in), std::istream_iterator<T>(), std::ostream_iterator<T>(out), [key](T v) {
        return T((v - key) % std::numeric_limits<T>::max());
    });
}

void analyze(istream & in, ostream & out)
{
    std::string str((std::istreambuf_iterator<char>(cin)),std::istreambuf_iterator<char>());
}

void help(ostream & out)
{
    out << "Caesar Implementation Useage:" << endl;
    out << "~$ caesar crypt <key>" << endl;
    out << "~$ caesar decrypt <key>" << endl;
    out << "~$ caesar analyze" << endl;
    out << "~$ caesar help" << endl;
}

int main(int argc, char* argv[])
{
    if (argc > 2 && argv[1] == string("decrypt"))
    {
        decrypt(cin, cout, stoul(argv[2]));
    }
    else if (argc > 2 && argv[1] == string("crypt"))
    {
        crypt(cin, cout, stoul(argv[2]));
    }
    else if (argc > 1 && argv[1] == string("analyze"))
    {
        analyze(cin, cout);
    }
    else
    {
        help(cout);
    }

    return 0;
}