#include <iostream>
#include <fstream>
#include <random>
#include <filesystem>
#include <string>
#include <vector>

using string = std::string;

// a file where added knowledge is stored
const string STORAGE_FILE = string(std::getenv("HOME")) + "/.config/bfortune/storage.txt";

// adds a new entry to the storage
int addEntry(string entry) {
    // opening a storage file in read mode to find next id
    std::ifstream file(STORAGE_FILE);
    if (!file.is_open()) {
        std::cerr << "could not open a storage file" << std::endl;
        return 1;
    }

    unsigned next_id = 1;
    string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            next_id++;            
        }
    }

    file.close();

    // now ready to write new text to the file
    std::ofstream infile(STORAGE_FILE, std::ios::app);

    if (!infile.is_open()) {
        std::cerr << "could not open a storage file" << std::endl;
        return 1;
    }

    infile << entry << '\n';

    file.close();

    return 0;
}

std::vector<string> loadEntries() {
    std::vector<string> entries;

    std::ifstream file(STORAGE_FILE);

    if (!file.is_open()) {
        std::cerr << "could not open a storage file" << std::endl;
        return entries;
    }

    string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            entries.push_back(line);
        }
    }

    return entries;
}

int showEntry() {
    std::vector<string> entries = loadEntries();

    if (entries.empty()) {
        std::cout << "sadly, there is nothing to show \n";
        return 1;
    }
    
    // generating and printing random entry
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, entries.size() - 1);
    string out = entries[dis(gen)];
    
    // formatting for "cowsay" nice output
    std::replace(out.begin(), out.end(), '\n', ' ');

    std::cout << out << '\n';
    
    return 0;
}

int main(int argc, char* argv[]) {
    std::filesystem::create_directories(std::filesystem::path(STORAGE_FILE).parent_path());

    // create the file if it doesn't exist
    std::ofstream ensureFile(STORAGE_FILE, std::ios::app);
    ensureFile.close();

    if (argc == 1) {
        showEntry();
    } else if (std::string(argv[1]) == "add" && argc >= 3) {
        addEntry(argv[2]);
    } else {
        std::cout << "Usage:\n";
        std::cout << "  bfortune           - print random quote\n";
        std::cout << "  bfortune add \"...\" - add quote\n";
    }
    return 0;
}


