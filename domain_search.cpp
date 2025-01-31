#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <xxhash.h>
#include <algorithm>

using namespace std;

// Function to read hashed domains from the text file
vector<uint64_t> readHashedDomains(const string& filename) {
    vector<uint64_t> hashedDomains;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return hashedDomains;
    }

    while (getline(file, line)) {
        if (!line.empty()) {
            hashedDomains.push_back(stoull(line));
        }
    }
    file.close();
    return hashedDomains;
}

// Function to hash a domain name using xxHash64
uint64_t hashDomain(const string& domain) {
    return XXH64(domain.c_str(), domain.size(), 0); // Seed is set to 0
}

// Function to search for a domain hash in the list
bool searchDomainHash(const vector<uint64_t>& hashedDomains, uint64_t targetHash) {
    return binary_search(hashedDomains.begin(), hashedDomains.end(), targetHash);
}
//THIS IS FOR TESTING COMMAND. ENTER THE DOMAIN NAME TO SEARCH FOR IN THE COMMAND LINE
// int main(int argc, char* argv[]) {
//     // Get test domain from command line or use default
//     string testDomain = (argc > 1) ? argv[1] : "google";
//     string filename = "hashed_domains_big.txt";
    
//     vector<uint64_t> hashedDomains = readHashedDomains(filename);
    
//     if (hashedDomains.empty()) {
//         cerr << "No hashed domains were loaded from the file." << endl;
//         return 1;
//     }
    
//     sort(hashedDomains.begin(), hashedDomains.end());
    
//     uint64_t testHash = hashDomain(testDomain);
//     bool found = searchDomainHash(hashedDomains, testHash);
    
//     cout << (found ? "1" : "0") << endl;
    
//     return 0;
// }
//THIS IS FOR GETTING INPUT FROM THE USER
int main() {
    string filename = "hashed_domains_small.txt";
    
    // Read the hashed domains from file
    vector<uint64_t> hashedDomains = readHashedDomains(filename);
    
    if (hashedDomains.empty()) {
        cerr << "No hashed domains were loaded from the file." << endl;
        return 1;
    }

    // Sort the vector for binary search
    sort(hashedDomains.begin(), hashedDomains.end());

    while (true) {
        string inputDomain;
        cout << "\nEnter a domain name to search (or 'quit' to exit): ";
        getline(cin, inputDomain);

        if (inputDomain == "quit") {
            cout << "Exiting program." << endl;
            break;
        }

        // Hash the input domain
        uint64_t inputHash = hashDomain(inputDomain);
        cout << "Generated hash for input domain: " << inputHash << endl;

        // Search for the hash
        if (searchDomainHash(hashedDomains, inputHash)) {
            cout << "SUCCESS: Domain '" << inputDomain << "' was found in the list!" << endl;
        } else {
            cout << "NOT FOUND: Domain '" << inputDomain << "' is not in the list." << endl;
        }
    }

    return 0;
}

// #include <iostream>
// #include <fstream>
// #include <string>
// #include <vector>
// #include <xxhash.h>
// #include <algorithm>
// #include <sys/resource.h>
// #include <unistd.h>

// using namespace std;

// // Function to get current memory usage in MB
// double getCurrentMemoryUsage() {
//     struct rusage usage;
//     if (getrusage(RUSAGE_SELF, &usage) == 0) {
//         return usage.ru_maxrss / 1024.0; // Convert KB to MB
//     }
//     return 0.0;
// }

// // Function to calculate vector's memory usage
// size_t calculateVectorMemory(const vector<uint64_t>& vec) {
//     return vec.capacity() * sizeof(uint64_t) + sizeof(vec);
// }

// vector<uint64_t> readHashedDomains(const string& filename) {
//     double memBefore = getCurrentMemoryUsage();
//     vector<uint64_t> hashedDomains;
    
//     ifstream file(filename);
//     string line;
    
//     if (!file.is_open()) {
//         cerr << "Failed to open file: " << filename << endl;
//         return hashedDomains;
//     }
    
//     // Reserve space to avoid reallocations
//     hashedDomains.reserve(15000000); // Adjust based on expected size
    
//     while (getline(file, line)) {
//         if (!line.empty()) {
//             hashedDomains.push_back(stoull(line));
//         }
//     }
//     file.close();
    
//     double memAfter = getCurrentMemoryUsage();
//     cout << "Memory usage for loading hashes: " << (memAfter - memBefore) << " MB" << endl;
//     cout << "Vector memory allocation: " << calculateVectorMemory(hashedDomains) / (1024.0 * 1024.0) << " MB" << endl;
//     cout << "Number of hashes loaded: " << hashedDomains.size() << endl;
    
//     return hashedDomains;
// }

// uint64_t hashDomain(const string& domain) {
//     return XXH64(domain.c_str(), domain.size(), 0);
// }

// bool searchDomainHash(const vector<uint64_t>& hashedDomains, uint64_t targetHash) {
//     return binary_search(hashedDomains.begin(), hashedDomains.end(), targetHash);
// }

// int main() {
//     cout << "Initial memory usage: " << getCurrentMemoryUsage() << " MB" << endl;
    
//     string filename = "hashed_domains_big.txt";
//     const string testDomain = "example.com";
    
//     double memBefore = getCurrentMemoryUsage();
    
//     vector<uint64_t> hashedDomains = readHashedDomains(filename);
    
//     if (hashedDomains.empty()) {
//         cerr << "No hashed domains were loaded from the file." << endl;
//         return 1;
//     }
    
//     cout << "Memory before sorting: " << getCurrentMemoryUsage() << " MB" << endl;
    
//     sort(hashedDomains.begin(), hashedDomains.end());
    
//     cout << "Memory after sorting: " << getCurrentMemoryUsage() << " MB" << endl;
    
//     uint64_t testHash = hashDomain(testDomain);
//     bool found = searchDomainHash(hashedDomains, testHash);
    
//     double memAfter = getCurrentMemoryUsage();
//     cout << "Peak memory usage: " << memAfter << " MB" << endl;
//     cout << "Total memory increase: " << (memAfter - memBefore) << " MB" << endl;
//     cout << "Result: " << (found ? "Found" : "Not found") << endl;
    
//     return 0;
// }