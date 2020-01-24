#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

using Type = uint8_t;

template <typename T = uint8_t>
void crypt(istream & in, ostream & out, int key)
{
    transform(std::istream_iterator<T>(in), std::istream_iterator<T>(), std::ostream_iterator<T>(out), [key](T v) {
        return T((v + key) % std::numeric_limits<T>::max());
    });
}

template <typename T = uint8_t>
void decrypt(istream & in, ostream & out, int key)
{
    transform(std::istream_iterator<T>(in), std::istream_iterator<T>(), std::ostream_iterator<T>(out), [key](T v) {
        return T((v - key) % std::numeric_limits<T>::max());
    });
}

void analyze(istream & in, ostream & out)
{
    static const map<char, double> LATTER_FREQUENCY = {
            {'a', 8.17}, {'b', 1.49}, {'c', 2.78}, {'d', 4.25},
            {'e', 12.70}, {'f', 2.23}, {'g', 2.02}, {'h', 6.09},
            {'i', 6.97}, {'j', 0.15}, {'k', 0.77}, {'l', 4.03},
            {'m', 2.41}, {'n', 6.75}, {'o', 7.51}, {'p', 1.93},
            {'q', 0.10}, {'r', 5.99}, {'s', 6.33}, {'t', 9.06},
            {'u', 2.76}, {'v', 0.98}, {'w', 2.36}, {'x', 0.15},
            {'y', 1.97}, {'z', 0.07}
    };

    std::string str(std::istreambuf_iterator<char>(in), {});

    map<char, double> inputFreq;
    for (auto ch : str)
    {
        if (LATTER_FREQUENCY.find(ch) != LATTER_FREQUENCY.end())
        {
            if (inputFreq.find(ch) == inputFreq.end())
            {
                inputFreq[ch] = 0.0;
            }

            inputFreq[ch] += 1.0;
        }
    }

    auto strSize = str.size();
    for (auto & p : inputFreq)
    {
        p.second = (p.second / strSize) * 100.0;
    }

    double normalDiff = 0.25;
    map<int, int> keys;
    for (auto p : inputFreq)
    {
        for (auto const sp : LATTER_FREQUENCY)
        {
            auto lowerCh = tolower(p.first);
            if (p.second >= (sp.second - normalDiff) && p.second <= (sp.second + normalDiff))
            {
                auto key = abs(lowerCh - sp.first);
                if (keys.find(key) == keys.end())
                {
                    keys[key] = 0;
                }

                keys[key] += 1;
            }
        }
    }

    auto key = std::max_element(keys.begin(), keys.end(), [](auto lhs, auto rhs) {
        return lhs.second < rhs.second;
    });

    if (key != keys.end())
    {
        out << "Detected key: " << key->first <<  endl << endl;
    }
    else
    {
        out << "key not found :(" << endl;
    }
}

void help(ostream & out)
{
    out << "Caesar Implementation Usage:" << endl;
    out << "~$ caesar crypt <key>" << endl;
    out << "~$ caesar decrypt <key>" << endl;
    out << "~$ caesar analyze" << endl;
    out << "~$ caesar help" << endl;
}

int main(int argc, char* argv[])
{
    if (argc > 2 && argv[1] == string("decrypt"))
    {
        decrypt(cin, cout, stoi(argv[2]));
    }
    else if (argc > 2 && argv[1] == string("crypt"))
    {
        crypt(cin, cout, stoi(argv[2]));
    }
    else if (argc > 1 && argv[1] == string("analyze"))
    {
        if (argc > 2)
        {
            ifstream in(argv[2]);
            analyze(in, cout);
        }
        else
        {
            analyze(cin, cout);
        }
    }
    else
    {
        help(cout);
    }

    return 0;
}