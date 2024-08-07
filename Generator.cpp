#include <iostream>
#include <fstream>
#include <random>
#include <cstring>

using namespace std;

void generate_file(const string & size, const string & output_path) {
    size_t num_integers;
    if (size == "SMALL") {
        num_integers = (512 * 1024 * 1024) / sizeof(int);
    } else if (size == "MEDIUM") {
        num_integers = (1 * 1024 * 1024 * 1024) / sizeof(int);
    } else if (size == "LARGE") {
        num_integers = (2 * 1024 * 1024 * 1024) / sizeof(int);
    } else {
        cerr << "Invalid size parameter. Use SMALL, MEDIUM, or LARGE." << endl;
        return;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist;

    ofstream outfile(output_path, ios::binary);
    if (!outfile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    for (size_t i = 0; i < num_integers; ++i) {
        int random_number = dist(gen);
        outfile.write(reinterpret_cast<const char*>(&random_number), sizeof(int));
    }
    outfile.close();
    cout << "File generated successfully: " << output_path << endl;
}//generate_file

int main(int argc, char* argv[]) {
    if (argc != 5 || strcmp(argv[1], "--size") != 0 || strcmp(argv[3], "--output") != 0) {
        cerr << "Use: .\generator --size <SIZE> --output <OUTPUT FILE PATH>" << endl;
        return 1;
    }
    string size = argv[2];
    string output_path = argv[4];
    generate_file(size, output_path);
    return 0;
}//Main
