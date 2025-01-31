#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <xxhash.h>

using namespace std;

// Function to read domain names from the CSV file
vector<string> readDomainsFromCSV(const string &filename)
{
    vector<string> domains;
    ifstream file(filename);
    string line;

    if (!file.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        return domains;
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        string domain;

        // Read the first column (domain name)
        if (getline(ss, domain, ','))
        {
            domains.push_back(domain);
        }
    }

    file.close();
    return domains;
}

// Function to hash a domain name using xxHash64
uint64_t hashDomain(const string &domain)
{
    return XXH64(domain.c_str(), domain.size(), 0); // Seed is set to 0
}

int main()
{
    string inputFilename = "final_15million.csv";
    string outputFilename = "hashed_domains_big.txt";

    // Read domains from the input CSV file
    vector<string> domains = readDomainsFromCSV(inputFilename);

    // Open the output file for writing the hashed domains
    ofstream outputFile(outputFilename);
    if (!outputFile.is_open())
    {
        cerr << "Failed to open output file: " << outputFilename << endl;
        return 1;
    }

    // Hash each domain and write the hash to the output file
    int domainCount = 0;
    const int maxDomains = 150000; // Limit the number of domains processed
    for (const auto &domain : domains)
    {
        if (domainCount >= maxDomains)
            break;

        uint64_t hash = hashDomain(domain);
        outputFile << hash << endl; // Write only the hash to the file
        domainCount++;
    }

    outputFile.close();

    cout << "Hashed domains written to: " << outputFilename << endl;
    return 0;
}