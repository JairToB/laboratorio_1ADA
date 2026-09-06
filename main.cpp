#include<iostream>
#include <random>
#include <algorithm>
#include <chrono>

int cubicMaxSub(int* a, int n){
    int maxSub = a[0];
    for (int i = 0; i < n; ++i){
        for (int j = i; j < n; ++j){
            int sum = 0;
            for (int k = i; k <= j; ++k){
                sum += a[k];
            }
            if (sum > maxSub){
                maxSub = sum;
            }
        }
    }
    return maxSub;
}

int quadraticMaxSub(int* a, int n){
    int maxSub = a[0];
    for (int i = 0; i < n; ++i){
        int sum = 0;
        for (int j = i; j < n; ++j){
            sum += a[j];
            if (sum > maxSub){
                maxSub = sum;
            }
        }
    }
    return maxSub;
}

int kadane(int* a, int n){
    int here = a[0];
    int global = a[0];
    for (int i = 1; i < n; ++i){
        here = std::max(a[i], here + a[i]);
        global = std::max(global, here);
    }
    return global;
}

int generateRandomNumbers(int minimo, int maximo){
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dist(minimo, maximo);

    return dist(gen);
}

double measureTime(int (*algo)(int*, int), int* a, int n, int& result) {
    auto start = std::chrono::high_resolution_clock::now();
    result = algo(a, n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> elapsed = end - start;
    return elapsed.count();
}

int main(){
    int a[8000];
    int min = -1000;
    int max = 1000;
    for(int i = 1000; i <= 8000; i *= 2){
        for (int j = 0; j < i; ++j){
            int x = generateRandomNumbers(min, max);
            a[j] = x;
        }
        int sumMax_firstW;
        int sumMax_secondW;
        int sumMax_thirdW;

        double timeCubic = measureTime(cubicMaxSub, a, i, sumMax_firstW);
        double timeQuadratic = measureTime(quadraticMaxSub, a, i, sumMax_secondW);
        double timeKadane = measureTime(kadane, a, i, sumMax_thirdW);

        std::cout << "Suma Cubica Maxima: " << sumMax_firstW << " Tiempo Cubico = " << timeCubic << " us\n";
        std::cout << "Suma Cuadratica Maxima: " << sumMax_secondW << " Tiempo Cuadratico = " << timeQuadratic << " us\n";
        std::cout << "Suma Kadane Maxima: " << sumMax_thirdW << " Tiempo Kadane = " << timeKadane << " us\n";
        std::cout << std::endl;

    }
        return 0;
}

