#include <pie\unicode.hh>

using namespace pie;

int main( )
{
    char16 x[ 17 ] = u"Hello, Мир! 🍼🦆";
    char08 y[ 24 ] = { };

    unicode::convert( y, x, trail );
    
    return 0;
}