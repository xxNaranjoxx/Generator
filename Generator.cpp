#include <iostream>
#include <fstream>
#include <random>
#include <string>

enum SizeOption {
    SMALL,
    MEDIUM,
    LARGE
};

SizeOption getSizeOption(const std::string& sizeStr) {
    if (sizeStr == "SMALL") return SMALL;
    if (sizeStr == "MEDIUM") return MEDIUM;
    if (sizeStr == "LARGE") return LARGE;
    throw std::invalid_argument("Invalid size option");
}

std::size_t getFileSize(SizeOption size) {
    switch (size) {
        case SMALL: return 512 * 1024 * 1024; // 512 MB
        case MEDIUM: return 1024 * 1024 * 1024; // 1 GB
        case LARGE: return 2048 * 1024 * 1024; // 2 GB
        default: throw std::invalid_argument("Invalid size option");
    }
}

void generateBinaryFile(const std::string& filePath, std::size_t sizeInBytes) {
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile) {
        throw std::ios_base::failure("Failed to open output file");
    }

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    std::size_t numIntegers = sizeInBytes / sizeof(int);
    for (std::size_t i = 0; i < numIntegers; ++i) {
        int randomInt = dist(mt);
        outFile.write(reinterpret_cast<const char*>(&randomInt), sizeof(randomInt));
    }
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " -size <SIZE> -output <OUTPUT FILE PATH>\n";
        return 1;
    }

    std::string sizeStr = argv[2];
    std::string outputFilePath = argv[4];

    try {
        SizeOption sizeOption = getSizeOption(sizeStr);
        std::size_t fileSize = getFileSize(sizeOption);
        generateBinaryFile(outputFilePath, fileSize);
        std::cout << "File generated successfully: " << outputFilePath << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

