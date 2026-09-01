#include<iostream>
#include <random>

int cubicMaxSub(int* a, int n){
    int maxSub = a[0];
    for(int i = 0; i < n; ++i){
        for(int j = i; j < n; ++j){
            int sum = 0;
            for(int k = i; k < j; ++k){
                sum += a[k];
            }
            if(sum > maxSub){
                maxSub = sum;
            }
        }
    }
    return maxSub;
}
int generateRandomNumbers(int minimo, int maximo){
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dist(minimo, maximo);

    return dist(gen);
}
int main(){
    int n = 10;
    int a[n];
    int min = -100;
    int max = 100;
    for (int i = 0; i < n; ++i){
        int x = generateRandomNumbers(min, max);
        a[i] = x;
        std::cout << a[i] << std::endl;
    }
    int sumMax = cubicMaxSub(a, n);
    std::cout << "Suma Maxima: " << sumMax << std::endl;

    return 0;
}
