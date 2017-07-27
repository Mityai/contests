#include "testlib.h"

std::string upper(std::string sa)
{
    for (size_t i = 0; i < sa.length(); i++)
        if ('a' <= sa[i] && sa[i] <= 'z')
            sa[i] = sa[i] - 'a' + 'A';
    return sa;
}

int main(int argc, char * argv[])
{
    setName("TAK or NIE (case insensetive)");
    registerTestlibCmd(argc, argv);

    std::string ja = upper(ans.readWord());
    std::string pa = upper(ouf.readWord());

    if (pa != "TAK" && pa != "NIE")
        quitf(_pe, "TAK or NIE expected, but %s found", pa.c_str());

    if (ja != "TAK" && ja != "NIE")
        quitf(_fail, "TAK or NIE expected in answer, but %s found", ja.c_str());

    if (ja != pa)
        quitf(_wa, "expected %s, found %s", ja.c_str(), pa.c_str());

    quitf(_ok, "answer is %s", ja.c_str());
}
