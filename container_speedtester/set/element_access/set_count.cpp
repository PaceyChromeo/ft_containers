
#include "../../tester_utils.hpp"
 
#ifndef NAME //Namespace Type to be tested
# define NAME ft
#endif

#ifndef TYPE //type of variable to be tested
# define TYPE int
#endif

int main ( void ){
    NAME::set<TYPE> array_42000__;
    fill_set(array_42000__, 1400);
    for (int i = 0; i < 1000; i++){
        array_42000__.count(i);
    }
}
