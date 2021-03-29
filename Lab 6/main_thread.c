#include <math.h>
#include <stdio.h>
int sroots[];
void square_roots(){
    for(int i = 0; i < 99; i ++){
        sroots[i] = (int)sqrt(i);
    }
}
int main(){
    square_roots();
    for(int i = 0; i < 100; i ++ ){
        printf("[%d] = %d\n",i,sroots[i]);
    }
    return 0;
}