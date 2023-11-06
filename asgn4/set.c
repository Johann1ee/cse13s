#include "set.h"

#include <stdlib.h>

Set set_empty(void) {
    return 0x00;
}

Set set_universal(void) {
    return 0xff;
}

bool set_member(Set s, int x) {
    Set var;
    var = 1 << x;

    if (s & var) {
        return true;
    } else {
        return false;
    }
}

Set set_insert(Set s, int x) {
    Set var, result;
    var = 1 << x;

    result = s | var;
    return result;
}

Set set_remove(Set s, int x) {
    Set var, result;
    var = ~(1 << x);

    result = s & var;
    return result;
}

Set set_union(Set s, Set t) {
    Set result;

    result = s | t;
    return result;
}

Set set_intersect(Set s, Set t) {
    Set result;

    result = s & t;
    return result;
}

Set set_difference(Set s, Set t) {
    Set result;

    result = s & ~t;
    return result;
}

Set set_complement(Set s) {
    Set result;

    result = ~s;
    return result;
}
