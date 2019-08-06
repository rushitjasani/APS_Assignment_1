#include<bits/stdc++.h>
using namespace std;


int main(){
    FILE* in = fopen("input", "w");
    srand(time(NULL));
    fprintf(in, "%d ", 1000000 ); 
    for (long long i = 0; i < 1000000 ; i++)
    	fprintf(in, "%d ", rand());

    for (long long i = 0; i < 100 ; i++)
    	fprintf(in, "%d ", 1 + (rand()) % (1000000) ); 
    fclose(in);
    return 0;
}