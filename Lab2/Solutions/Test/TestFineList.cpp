#include <cstdio>
#include "../Sets/FineList.cpp"

int main() {
    FineList* fl = new FineList();
    fl->add(2);
    fl->add(3);
    fl->add(4);
    fl->add(2);
    fl->add(5);
    fl->add(6);
    fl->add(7);
    fl->printList();
    printf("ctn(%d) = %s", 2, fl->ctn(2) ? "true":"false");
    printf("\n");
    
    fl->rmv(5);
    fl->rmv(6);
    fl->printList();
    printf("ctn(%d) = %s", 5, fl->ctn(5) ? "true":"false");
    printf("\n");
    printf("ctn(%d) = %s", 6, fl->ctn(6) ? "true":"false");
    printf("\n");
    printf("ctn(%d) = %s", 7, fl->ctn(7) ? "true":"false");
    printf("\n");
    
    return 0;
}