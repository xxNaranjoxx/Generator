#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H

#include <vector>
#include <string>

class PagedArray {
public:
    PagedArray(const std::string& filePath, size_t pageSize);
    ~PagedArray();

    int& operator[](size_t index);
    void save(const std::string& filePath);
    size_t size() const;
    size_t getPageFaults() const;
    size_t getPageHits() const;

private:
    size_t pageSize;
    size_t numPages;
    size_t totalSize;
    std::string filePath;
    std::vector<int*> pages;
    std::vector<bool> pageLoaded;
    std::vector<size_t> pageIndices;
    size_t pageFaults;
    size_t pageHits;

    void loadPage(size_t pageIndex);
    void unloadPage(size_t pageIndex);
};

#endif // PAGEDARRAY_H
