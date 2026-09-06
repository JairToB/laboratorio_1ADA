#include <iostream>
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
    int n = 100000000;
    int* a = new int[n];
    int min = -1000;
    int max = 1000;

    for (int j = 0; j < n; ++j){
        int x = generateRandomNumbers(min, max);
        a[j] = x;
    }

    int sumMax_thirdW;

    double timeKadane = measureTime(kadane, a, n, sumMax_thirdW);

    std::cout << "Suma Kadane Maxima: " << sumMax_thirdW << " Tiempo Kadane = " << timeKadane << " us\n";
    std::cout << std::endl;

    delete[] a;
    return 0;
}
