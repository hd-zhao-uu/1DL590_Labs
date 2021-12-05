#include <cstdio>
#include "../Sets/CoarseList.cpp"

int main() {
    CoarseList* cl = new CoarseList();
    cl->add(2);
    cl->add(3);
    cl->add(4);
    cl->add(2);
    cl->add(5);
    cl->add(6);
    cl->add(7);
    cl->printList();
    printf("ctn(%d) = %s", 2, cl->ctn(2) ? "true":"false");
    printf("\n");
    
    cl->rmv(5);
    cl->rmv(6);
    cl->printList();
    printf("ctn(%d) = %s", 5, cl->ctn(5) ? "true":"false");
    printf("\n");
    printf("ctn(%d) = %s", 6, cl->ctn(6) ? "true":"false");
    printf("\n");
    printf("ctn(%d) = %s", 7, cl->ctn(7) ? "true":"false");
    printf("\n");
    
    return 0;
}