#include <iostream>

#include "../src/Engine.h"

using namespace WMB;

void PrintArray(int** arr, int w, int h)
{
    for (int i = 0; i < h; i += 1)
    {
        for (int j = 0; j < w; j += 1)
        {
            std::cout << arr[i][j];
        }
        std::cout << "\n";
    }
}

void ModifyArray(int** arr, int w, int h)
{
    //int* test = (*(arr + ((h / 2) - 1)) + ((w / 2) - 1));
    int** test = (arr + ((h / 2) - 1));
    (*(test - 1))[w/2 - 2] = 2;
    test[0][w/2] = 1;
    PrintArray(arr, w, h);
}

int main(int argc, const char* argv[]) {
    std::cout << "Hello, World!\n";

    const int w = 10;
    const int h = 10;
    int** arr;

    arr = new int* [h];
    for (int i = 0; i < h; i += 1)
    {
        arr[i] = new int[w];
        for (int j = 0; j < w; j += 1)
        {
            arr[i][j] = 0;
        }
    }

    ModifyArray(arr, w, h);

    Engine e;

    return 0;
}