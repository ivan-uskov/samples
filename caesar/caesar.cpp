#include <iostream>
#include <functional>

using namespace std;

void crypt(istream & in, ostream & out)
{
    std::string str((std::istreambuf_iterator<char>(cin)),std::istreambuf_iterator<char>());
}

void decrypt(istream & in, ostream & out)
{

}

void help(ostream & out)
{

}

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        if (argv[1] == "decrypt")
        {
            decrypt(cin, cout);
        }
        else if (argv[1] != "crypt")
        {
            crypt(cin, cout);
        }
        else
        {
            help(cout);
        }
    }
    else
    {
        crypt(cin, cout);
    }

    return 0;
}