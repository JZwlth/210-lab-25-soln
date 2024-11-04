#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <set>
#include <list>
#include <iomanip>

using namespace std;

const int NUM_RUNS = 15;
const int STRUCTURES = 3;
const int ROWS = 4, COLS = 3;
const int W1 = 10;

int main() {
    long long cum_results[ROWS][COLS] = {0}; // Cumulative results over runs
    string labels[] = {"Read", "Sort", "Insert", "Delete"};

    for (int run = 0; run < NUM_RUNS; ++run) {
        vector<string> data_vector;
        list<string> data_list;
        set<string> data_set;
        long long results[ROWS][COLS] = {0}; // Results for this run

        // Testing for READ operations
        for (int i = 0; i < STRUCTURES; i++) {
            ifstream fin("codes.txt");
            string cd;
            auto start = chrono::high_resolution_clock::now();
            switch(i) {
                case 0: {  // Read into a vector
                    while (fin >> cd)
                        data_vector.push_back(cd);
                    break;
                }
                case 1: {  // Read into a list
                    while (fin >> cd)
                        data_list.push_back(cd);
                    break;
                }
                case 2: {  // Read into a set
                    while (fin >> cd)
                        data_set.insert(cd);
                    break;
                }
            }
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            results[0][i] = duration.count();
            fin.close();
        }
        // Testing for SORT operations
        for (int i = 0; i < STRUCTURES; i++) {
            auto start = chrono::high_resolution_clock::now();
            switch(i) {
                case 0: {  // Sort a vector
                    sort(data_vector.begin(), data_vector.end());
                    break;
                }
                case 1: {  // Sort a list
                    data_list.sort();
                    break;
                }
                case 2: {  // Can't sort a set, so time is 0
                    break;
                }
            }
            auto end = chrono::high_resolution_clock::now();
            long long duration = 0;
            if (i != 2) // For vector and list, calculate duration
                duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
            results[1][i] = duration;
        }

        // Testing for INSERT operations
        for (int i = 0; i < STRUCTURES; i++) {
            int ind_v = data_vector.size() / 2;
            int ind_l = data_list.size() / 2;
            auto start = chrono::high_resolution_clock::now();
            switch(i) {
                case 0: {  // Insert into a vector
                    data_vector.insert(data_vector.begin() + ind_v, "TESTCODE");
                    break;
                }
                case 1: {  // Insert into a list
                    auto it = data_list.begin();
                    advance(it, ind_l);
                    data_list.insert(it, "TESTCODE");
                    break;
                }
                case 2: {  // Insert into a set
                    data_set.insert("TESTCODE");
                    break;
                }
            }
            case 2: {  // insert into a set
                data_set.insert("TESTCODE");
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                results[2][i] = duration.count();
                break;
            }
        }
    }

  // Testing for DELETE operations
        for (int i = 0; i < STRUCTURES; i++) {
            // Select a target value in the vector 
            int ind = data_vector.size() / 2;
            string target_v = data_vector[ind];

            // Select a target value in the list
            auto it1 = data_list.begin();
            advance(it1, ind);
            string target_l = *it1;

            // Select a target value in the set
            auto it2 = data_set.begin();
            advance(it2, ind);
            string target_s = *it2;
            
            auto start = chrono::high_resolution_clock::now();
            switch(i) {
                case 0: {  // Delete by value from vector
                    data_vector.erase(remove(data_vector.begin(), data_vector.end(), target_v), data_vector.end());
                    break;
                }
                case 1: {  // Delete by value from list
                    data_list.remove(target_l);
                    break;
                }
                case 2: {  // Delete by value from set
                    data_set.erase(target_s);
                    break;
                }
            }
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            results[3][i] = duration.count();
        }

        // Add results to cumulative results
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                cum_results[i][j] += results[i][j];
            }
        }
    }

    // Compute average results
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cum_results[i][j] /= NUM_RUNS;
        }
    }
    

    return 0;
}