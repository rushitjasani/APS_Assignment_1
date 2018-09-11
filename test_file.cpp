#include<bits/stdc++.h>
using namespace std;


int main(){
    FILE* in = fopen("input", "w");
    srand(time(NULL));
    for (long long i = 0; i < 100000000 ; i++)
    	fprintf(in, "%d ", rand()); 
    fclose(in);
    return 0;
}

