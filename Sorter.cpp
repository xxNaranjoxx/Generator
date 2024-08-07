#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "PagedArray.h"

void quickSort(PagedArray& arr, int left, int right);
void insertionSort(PagedArray& arr, int n);
void bubbleSort(PagedArray& arr, int n);

int main(int argc, char* argv[]) {
    if (argc != 7) {
        std::cerr << "Usage: " << argv[0] << " -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITHM>" << std::endl;
        return 1;
    }

    std::string inputPath = argv[2];
    std::string outputPath = argv[4];
    std::string algorithm = argv[6];

    PagedArray arr(inputPath, 4096);

    auto start = std::chrono::high_resolution_clock::now();

    if (algorithm == "QS") {
        quickSort(arr, 0, arr.size() - 1);
    } else if (algorithm == "IS") {
        insertionSort(arr, arr.size());
    } else if (algorithm == "BS") {
        bubbleSort(arr, arr.size());
    } else {
        std::cerr << "Invalid algorithm. Use QS, IS, or BS." << std::endl;
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    arr.save(outputPath);

    std::cout << "Sorting completed in " << duration.count() << " seconds." << std::endl;
    std::cout << "Algorithm used: " << algorithm << std::endl;
    std::cout << "Page faults: " << arr.getPageFaults() << std::endl;
    std::cout << "Page hits: " << arr.getPageHits() << std::endl;

    return 0;
}

void quickSort(PagedArray& arr, int left, int right) {
    if (left < right) {
        int pivot = arr[right];
        int i = left - 1;

        for (int j = left; j < right; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }

        std::swap(arr[i + 1], arr[right]);

        quickSort(arr, left, i);
        quickSort(arr, i + 2, right);
    }
}

void insertionSort(PagedArray& arr, int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
    }
}

void bubbleSort(PagedArray& arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}
