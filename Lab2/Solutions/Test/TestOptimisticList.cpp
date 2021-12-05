#include <cstdio>
#include "../Sets/OptimisticList.cpp"

int main() {
    OptimisticList* ol = new OptimisticList();
    ol->add(2);
    ol->add(3);
    ol->add(4);
    ol->add(2);
    ol->add(5);
    ol->add(6);
    ol->add(7);
    ol->printList();
    printf("ctn(%d) = %s", 2, ol->ctn(2) ? "true":"false");
    printf("\n");
    
    ol->rmv(5);
    ol->rmv(6);
    ol->printList();
    printf("ctn(%d) = %s", 5, ol->ctn(5) ? "true":"false");
    printf("\n");
    printf("ctn(%d) = %s", 6, ol->ctn(6) ? "true":"false");
    printf("\n");
    printf("ctn(%d) = %s", 7, ol->ctn(7) ? "true":"false");
    printf("\n");
    
    return 0;
}