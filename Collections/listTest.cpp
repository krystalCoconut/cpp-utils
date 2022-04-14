#include "linkedlist.h"
#include <cstdlib>

using namespace std;

int main(int argi,char** argsv)
{
    LinkedList<char>* charList = new LinkedList<char>();
    for(int i=0;i<32;i++) {
        charList->pushBack( (i+'a') );
        printAllList(charList);
    }

    for(int i=0;i<32;i++) {
        charList->remove(charList->tail);
        cout.flush();
        printAllList(charList);
    }

    LinkedList<int>* intList = new LinkedList<int>();
    for(int i=0;i<32;i++) {
        intList->pushBack( (i) );
        printAllList(intList);
    }

    for(int i=0;i<32;i++) {
        intList->remove(intList->tail);
        cout.flush();
        printAllList(intList);
    }

    return 0;
}
