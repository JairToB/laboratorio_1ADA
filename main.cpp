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
    int n = 10;
    int a[n];
    int min = -100;
    int max = 100;
    for (int i = 0; i < 100; ++i){
        for (int j = 0; j < n; ++j){
            int x = generateRandomNumbers(min, max);
            a[j] = x;
            std::cout << a[j] << std::endl;
        }
        int sumMax_firstW = cubicMaxSub(a, n);
        int sumMax_secondW = quadraticMaxSub(a, n);
        int sumMax_thirdW = kadane(a, n);
        std::cout << "Suma Cubica Maxima: " << sumMax_firstW << std::endl;
        std::cout << "Suma Cuadratica Maxima: " << sumMax_secondW << std::endl;
        std::cout << "Suma Kadane Maxima: " << sumMax_thirdW << std::endl;

        double timeCubic = measureTime(cubicMaxSub, a, n, sumMax_firstW);
        double timeQuadratic = measureTime(quadraticMaxSub, a, n, sumMax_secondW);
        double timeKadane = measureTime(kadane, a, n, sumMax_thirdW);

        std::cout << "Tiempo Cubico = " << timeCubic << " us\n";
        std::cout << "Tiempo Cuadratico = " << timeQuadratic << " us\n";
        std::cout << "Tiempo Kadane = " << timeKadane << " us\n";
        std::cout << std::endl;
    }
    return 0;
}
