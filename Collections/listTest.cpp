#include "linkedlist.h"
#include <cstdlib>

using namespace std;

static int test()
{
    LinkedList<char>* charList = new LinkedList<char>();
    for(int i=0;i<32;i++) {
        charList->pushBack( (i+'a') );
        printAllList(charList);
    }

    for(int i=0;i<32;i++) {
        charList->unlink(charList->tail);
        cout.flush();
        printAllList(charList);
    }

    LinkedList<int>* intList = new LinkedList<int>();
    for(int i=0;i<32;i++) {
        intList->pushBack( (i) );
        printAllList(intList);
    }

    for(int i=0;i<32;i++) {
        intList->unlink(intList->tail);
        cout.flush();
        printAllList(intList);
    }

    return 0;
}
