// GARobots.cpp
// Taha Zeeshan

#include <iostream>
#include <cstdlib>
using namespace std;

// Class for generating a 10x10 map
class genMap {
public:
    int map[10][10]; // 2D array representing the map
    void newMap();   // Method to generate a new map
    void mapPrint(); // Method to print the map
    int getValue(int i, int j); // Method to get the value at (i, j)
    int changeValue(int i, int j, int k); // Method to change the value at (i, j)
};

// Generates a new map with random obstacles
void genMap::newMap() {
    // Initialize the map with zeros (empty spaces)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            map[i][j] = 0; // Set all positions to 0
        }
    }
    
    // Randomly place 40 obstacles (set to 1) on the map
    for (int i = 0; i < 40; i++) {
        int validChoice = 0; // Flag to ensure valid placement of obstacles
        while (validChoice == 0) {
            int column = rand() % 10; // Random column index
            int row = rand() % 10;    // Random row index

            // If the position is empty, place an obstacle
            if (map[column][row] == 0) {
                map[column][row] = 1;
                validChoice = 1; // Mark as valid choice
            }
        }
    }
}

// Prints the current state of the map
void genMap::mapPrint() {
    cout << "\n   0 1 2 3 4 5 6 7 8 9" << endl; // Column headers
    for (int i = 0; i < 10; i++) {
        cout << i << "  "; // Row header
        for (int j = 0; j < 10; j++) {
            cout << map[i][j] << " "; // Print each cell's value
        }
        cout << endl; // New line for the next row
    }
    cout << endl;
}

// Returns the value at the specified coordinates
int genMap::getValue(int i, int j) {
    return map[i][j]; // Access the map value at (i, j)
}

// Changes the value at the specified coordinates and returns the new value
int genMap::changeValue(int i, int j, int k) {
    return map[i][j] = k; // Update and return the new value
}

// Class for generating genes for a population of robots
class genBot {
public:
    int bots[200][16][5]; // Array for 200 bots, each with 16 genes of 5 values
    void setGenes();      // Method to set genes for the bots
    void genPrint();      // Method to print genes for all bots
    void botPrint(int i); // Method to print genes for a specific bot
    int getValue(int i, int j, int k); // Get gene value
    int changeValue(int i, int j, int k, int n); // Change gene value
};

// Sets random genes for the initial generation of robots
void genBot::setGenes() {
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 4; k++) {
                bots[i][j][k] = rand() % 3; // Genes 0, 1, or 2
            }
            bots[i][j][4] = rand() % 5; // Additional value from 0 to 4
        }
    }
}

// Prints the genes for all bots
void genBot::genPrint() {
    for (int i = 0; i < 200; i++) {
        cout << "bot " << i + 1 << endl; // Print bot number
        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 5; k++) {
                cout << bots[i][j][k] << " "; // Print gene values
            }
            cout << endl; // New line for the next gene
        }
        cout << endl; // Separate bots
    }
}

// Prints the genes for a specific bot
void genBot::botPrint(int i) {
    cout << "bot " << i + 1 << endl; // Print bot number
    for (int j = 0; j < 16; j++) {
        for (int k = 0; k < 5; k++) {
            cout << bots[i][j][k] << " "; // Print gene values
        }
        cout << endl; // New line for the next gene
    }
    cout << endl; // Separate bots
}

// Returns the value of a specific gene for a given bot
int genBot::getValue(int i, int j, int k) {
    return bots[i][j][k]; // Access the gene value
}

// Changes the value of a specific gene for a given bot
int genBot::changeValue(int i, int j, int k, int n) {
    return bots[i][j][k] = n; // Update and return the new gene value
}

int main() {
    unsigned seed;
    seed = time(0); // Seed the random number generator
    srand(seed);

    genMap map; // Create a new map instance
    genBot gen; // Create a new robot generator instance
    gen.setGenes(); // Set genes for the robots

    int avgScores[6]; // Array to store average scores for each generation

    for (int p = 0; p < 6; p++) { // Loop through generations
        int botScores[200][2]; // Array to hold scores for each bot

        for (int i = 0; i < 200; i++) {
            map.newMap(); // Generate a new map

            int power = 5; // Initial power level
            int score = 0; // Score tracker
            int n = 0, s = 0, e = 0, w = 0; // Direction flags
            int m; // Movement variable

            int column = rand() % 10; // Random starting column
            int row = rand() % 10;    // Random starting row

            // Main loop for bot movement based on power
            while (power > 0) {
                // Check for boundaries
                if (row == 0) { n = 1; }
                if (row == 9) { s = 1; }
                if (column == 0) { w = 1; }
                if (column == 9) { e = 1; }

                // If the bot lands on a resource, increase power and score
                if (map.getValue(row, column) == 1) {
                    power += 5; // Increase power
                    score += 5; // Increase score
                }

                map.changeValue(row, column, 0); // Mark the position as visited

                // Update direction flags based on nearby resources
                if (map.getValue(row - 1, column) == 1) { n = 2; }
                if (map.getValue(row + 1, column) == 1) { s = 2; }
                if (map.getValue(row, column + 1) == 1) { e = 2; }
                if (map.getValue(row, column - 1) == 1) { w = 2; }

                // Determine the next movement based on gene values
                for (int j = 0; j < 16; j++) {
                    if (n == gen.getValue(i, j, 0) && s == gen.getValue(i, j, 1) && s == gen.getValue(i, j, 2) && s == gen.getValue(i, j, 3)) {
                        m = gen.getValue(i, j, 4); // Get movement direction
                    } else {
                        m = gen.getValue(i, 15, 4); // Default to the last gene
                    }
                }

                // If no movement direction is assigned, randomly choose a direction
                if (m == 0) {
                    m = rand() % 4 + 1; // Random direction
                }

                // Move the bot based on the determined direction
                if (m == 1 && row != 0) {
                    row--; // Move north
                } else if (m == 2 && row != 9) {
                    row++; // Move south
                } else if (m == 3 && column != 0) {
                    column--; // Move west
                } else if (m == 4 && column != 9) {
                    column++; // Move east
                } else {
                    row = row + 0; // Stay in place
                    column = column + 0;
                }

                power--; // Decrease power after each move
            }

            // Store score and bot index for sorting
            botScores[i][0] = score;
            botScores[i][1] = i;
            cout << "Bot #"<< p <<"_"<< i + 1 << " harvested " << score << " power." << endl; // Output score
        }
        cout << endl;

        // Sorts botScores based on power harvested while maintaining bot numbers
        qsort(botScores, 200, sizeof(*botScores),
            [](const void *botScoresg1, const void *botScoresg2) -> int {
                int const *lhs = static_cast<int const*>(botScoresg1);
                int const *rhs = static_cast<int const*>(botScoresg2);
                return (lhs[0] < rhs[0]) ? -1
                    : ((rhs[0] < lhs[0]) ? 1
                    : (lhs[1] < rhs[1] ? -1
                    : ((rhs[1] < lhs[1] ? 1 : 0))));
            });

        // Creating new generation based on scores
        int tempGen[200][16][5]; // Temporary storage for new generation

        for (int i = 0; i < 100; i = i + 2) {
            for (int j = 0; j < 8; j++) {
                for (int k = 0; k < 5; k++) {
                    tempGen[i][j][k] = gen.getValue(botScores[i + 99][1], j, k); // Inherit genes
                    tempGen[i + 1][j][k] = gen.getValue(botScores[i + 100][1], j, k);
                }
            }
            for (int j = 8; j < 16; j++) {
                for (int k = 0; k < 5; k++) {
                    tempGen[i][j][k] = gen.getValue(botScores[i + 100][1], j, k); // Inherit genes
                    tempGen[i + 1][j][k] = gen.getValue(botScores[i + 99][1], j, k);
                }
            }
        }

        // Copy genes of the remaining bots to the new generation
        for (int i = 100; i < 200; i++) {
            for (int j = 0; j < 16; j++) {
                for (int k = 0; k < 5; k++) {
                    tempGen[i][j][k] = gen.getValue(botScores[i][1], j, k);
                }
            }
        }

        // Update the current generation with new genes
        for (int i = 0; i < 200; i++) {
            for (int j = 0; j < 16; j++) {
                for (int k = 0; k < 5; k++) {
                    gen.changeValue(i, j, k, tempGen[i][j][k]);
                }
            }
        }

        // Calculate the total power harvested by all bots
        int totalPower = 0;
        for (int i = 0; i < 200; i++) {
            totalPower += botScores[i][0];
        }

        // Store the average score for the generation
        avgScores[p] = (totalPower / 200);
    }

    // Output the average scores for each generation
    cout << "************************************" << endl << endl;
    for (int i = 0; i < 6; i++) {
        cout << "The average power for gen " << i << " was " << avgScores[i] << endl;
    }

    cout << "\nEND"; // End of the program
    return 0; // Successful completion
}
