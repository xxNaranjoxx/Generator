#include "PagedArray.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

PagedArray::PagedArray(const std::string& filePath, size_t pageSize)
    : filePath(filePath), pageSize(pageSize), pageFaults(0), pageHits(0) {
    std::ifstream inFile(filePath, std::ios::binary | std::ios::ate);
    if (!inFile) {
        std::cerr << "Error opening file for reading: " << filePath << std::endl;
        std::exit(1);
    }

    totalSize = inFile.tellg();
    numPages = (totalSize + pageSize - 1) / pageSize;

    pages.resize(4, nullptr);
    pageLoaded.resize(4, false);
    pageIndices.resize(4, -1);
}

PagedArray::~PagedArray() {
    for (int* page : pages) {
        if (page != nullptr) {
            delete[] page;
        }
    }
}

int& PagedArray::operator[](size_t index) {
    size_t pageIndex = index / pageSize;
    size_t offset = index % pageSize;

    for (size_t i = 0; i < 4; ++i) {
        if (pageLoaded[i] && pageIndices[i] == pageIndex) {
            ++pageHits;
            return pages[i][offset];
        }
    }

    loadPage(pageIndex);
    ++pageFaults;

    for (size_t i = 0; i < 4; ++i) {
        if (pageIndices[i] == pageIndex) {
            return pages[i][offset];
        }
    }

    std::cerr << "Error: Page not loaded correctly." << std::endl;
    std::exit(1);
}

void PagedArray::loadPage(size_t pageIndex) {
    size_t slot = std::rand() % 4;
    if (pageLoaded[slot]) {
        unloadPage(slot);
    }

    pages[slot] = new int[pageSize];
    pageIndices[slot] = pageIndex;
    pageLoaded[slot] = true;

    std::ifstream inFile(filePath, std::ios::binary);
    inFile.seekg(pageIndex * pageSize * sizeof(int));
    inFile.read(reinterpret_cast<char*>(pages[slot]), pageSize * sizeof(int));
}

void PagedArray::unloadPage(size_t slot) {
    std::ofstream outFile(filePath, std::ios::binary | std::ios::in | std::ios::out);
    outFile.seekp(pageIndices[slot] * pageSize * sizeof(int));
    outFile.write(reinterpret_cast<const char*>(pages[slot]), pageSize * sizeof(int));
    delete[] pages[slot];
    pages[slot] = nullptr;
    pageLoaded[slot] = false;
    pageIndices[slot] = -1;
}

void PagedArray::save(const std::string& filePath) {
    for (size_t i = 0; i < 4; ++i) {
        if (pageLoaded[i]) {
            unloadPage(i);
        }
    }

    std::ifstream inFile(this->filePath, std::ios::binary);
    std::ofstream outFile(filePath, std::ios::binary);
    outFile << inFile.rdbuf();
}

size_t PagedArray::size() const {
    return totalSize / sizeof(int);
}

size_t PagedArray::getPageFaults() const {
    return pageFaults;
}

size_t PagedArray::getPageHits() const {
    return pageHits;
}
