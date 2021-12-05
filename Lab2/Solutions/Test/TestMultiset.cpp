#include <cstdio>
#include "../Sets/Multiset.cpp"

int main() {
    Multiset* ms = new Multiset();
    ms->add(2);
    ms->add(2);
    ms->add(4);
    ms->add(2);
    ms->add(5);
    ms->add(6);
    ms->add(4);
    ms->printList();
    printf("num of %d = %d", 2, ms->ctn(2));
    printf("\n");
    
    ms->rmv(5);
    ms->rmv(6);
    ms->printList();
    return 0;
}