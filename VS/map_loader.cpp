#include "display_functions.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>


using namespace std;


const int MapSize = 30;
const int MinResource = 20;
const int MaxResource = 40;

enum class Key {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    B,
    A,
    OTHER
};


enum Biome {
    WATER,
    GRASS,
    RICH_GRASS,
    ROCK,
    LAVA,
    FLOODING_WATER,
};


struct Tile {
    Biome biome;
    float resource;
};


class Map {
public:
    Tile map[MapSize][MapSize];
    bool lakeGeneration = false;

    // Flooding related variables.
    bool isFlooding = false;
    int nbFlood;
    int FloodIndex = 0;
    bool isUnFlooding = false;

<<<<<<< HEAD
<<<<<<< Updated upstream
	void displayMap() {
		for (int i = 0; i < MapSize; ++i) {
			cout << endl;
			for (int j = 0; j < MapSize; ++j) {
				setColorForBiome(map[i][j].biome);
				cout << "\xDB\xDB";
                setColor(7);
			}
		}
	}
=======
    void defaultMap() {
        for (int i = 0; i < MapSize; ++i) {
            for (int j = 0; j < MapSize; ++j) {
                map[i][j].biome = GRASS;
                map[i][j].resource = rand() % (MaxResource - MinResource + 1) + MinResource;
            }
        }
    }

    void displayMap() {
        cout << endl;
        for (int i = 0; i < MapSize; ++i) {
            setColorForBiome(map[i][0].biome);
            centerText("\xDB\xDB", false, MapSize*2);
            for (int j = 1; j < MapSize; ++j) {
                setColorForBiome(map[i][j].biome);
                cout << "\xDB\xDB";
                setColor(7);
            }
            cout << endl;
        }
    }
>>>>>>> Stashed changes
=======
    void defaultMap() {
        for (int i = 0; i < MapSize; ++i) {
            for (int j = 0; j < MapSize; ++j) {
                map[i][j].biome = GRASS;
                map[i][j].resource = rand() % (MaxResource - MinResource + 1) + MinResource;
            }
        }
    }

    void displayMap() {
        for (int i = 0; i < MapSize; ++i) {
            cout << endl;
            for (int j = 0; j < MapSize; ++j) {
                setColorForBiome(map[i][j].biome);
                cout << "\xDB\xDB";
                setColor(7);
            }
        }
    }
>>>>>>> d9f656911a4e8a6da193a06471d49ce8dc7dbb28

    void setColorForBiome(Biome biome) {
        switch (biome) {
        case WATER:
            setColor(3);  // Blue
            break;
        case GRASS:
            setColor(2);  // Green
            break;
        case RICH_GRASS:
            setColor(10); // Light Green
            break;
        case ROCK:
            setColor(8); // Grey
            break;
        case LAVA:
            setColor(4); // Red
            break;
        case FLOODING_WATER:
            setColor(3);
            break;
        }
    }

    void generateWater() {
        int numLakes = rand() % 10 + 5;

        if (numLakes < 15) {
            generateLakes(numLakes);
        }

        if (numLakes == 15 || lakeGeneration) {
            generateLargeWaterBodies();
        }
    }

    void generateLakes(int numLakes) {
        for (int i = 0; i < numLakes; ++i) {
            int x = rand() % MapSize;
            int y = rand() % MapSize;
            map[x][y].biome = WATER;
            generateLakeRadius(x, y, rand() % 3 + 2);
        }
        lakeGeneration = true;
    }

    void generateLakeRadius(int x, int y, int radius) {
        for (int i = -radius; i <= radius; ++i) {
            for (int j = -radius; j <= radius; ++j) {
                int newX = x + i, newY = y + j;
                if (newX >= 0 && newX < MapSize && newY >= 0 && newY < MapSize) {
                    if ((i * i) + (j * j) <= (radius * radius)) {
                        map[newX][newY].biome = WATER;
                    }
                }
            }
        }
    }

    void generateLargeWaterBodies() {
        int numBodies = rand() % 40 + 20;
        for (int i = 0; i < numBodies; ++i) {
            int x = rand() % MapSize;
            int y = rand() % MapSize;
            if (map[x][y].biome != WATER) {
                map[x][y].biome = WATER;
            }
            else {
                --i;
            }
        }
    }

    void generateResources() {
        int numResources = rand() % 100 + 100;
        for (int i = 0; i < numResources; ++i) {
            int x = rand() % MapSize;
            int y = rand() % MapSize;
            if (map[x][y].biome == GRASS) {
                map[x][y].biome = RICH_GRASS;
                map[x][y].resource = 100;
            }
            else {
                --i;
            }
        }
    }

    void generateVolcano() {
        int x = (rand() % MapSize);
        int y = (rand() % MapSize);
        map[x][y].biome = LAVA;
        map[x][y].resource = 0;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0)
                    continue;
                int newX = x + dx;
                int newY = y + dy;
                if (newX >= 0 && newX < MapSize && newY >= 0 && newY < MapSize) {
                    map[newX][newY].biome = ROCK;
                    map[newX][newY].resource = 0;
                }
            }
        }
    }

    void StartFlooding() // Fonctionne pas pour le moment
    {
        nbFlood = (rand() % 3) + 2;
        FloodIndex = 0;
        isFlooding = true;
    }

    void StartUnFlooding() {
        isUnFlooding = true;
    }

    void ContinueFlooding() {
        int nbFloodedTiles = 40;
        if (FloodIndex < nbFlood) {
            for (int i = 0; i < nbFloodedTiles; i++) {
                int x = (rand() % MapSize);
                int y = (rand() % MapSize);
                if (map[x][y].biome != WATER && map[x][y].biome != ROCK && map[x][y].biome != LAVA && map[x][y].biome != FLOODING_WATER) {
                    map[x][y].biome = FLOODING_WATER;
                    map[x][y].resource /= 2;
                }
                else {
                    i--;
                }
            }
        }
        else {
            isFlooding = false;
        }
        FloodIndex++;
    }

    void startGeneration() {
        defaultMap();
        generateWater();
        generateResources();
        generateVolcano();
        displayMap();
    }

    void checkTile() {
        int x, y;
        cout << "Enter coordinates to check a Tile (x y): ";
        cin >> x >> y;
        if (x < 0 || x >= MapSize || y < 0 || y >= MapSize) {
            cout << "Invalid coordinates!" << endl;
            return;
        }

        clearScreen();
        cout << "Tile [" << x << "][" << y << "] Info:" << endl;
        switch (map[x][y].biome) {
        case WATER:
            cout << "Biome: Water" << endl;
            break;
        case FLOODING_WATER:
            cout << "Biome: Water" << endl;
            break;
        case GRASS:
            cout << "Biome: Grass" << endl;
            break;
        case RICH_GRASS:
            cout << "Biome: Rich Grass" << endl;
            break;
        }
        cout << "Remaining resources: " << map[x][y].resource << endl;
        displayMap();
    }

    void nextDay() {

        if (isFlooding) {
            ContinueFlooding();
        }
        for (int i = 0; i < MapSize; ++i) {
            for (int j = 0; j < MapSize; ++j) {
                map[i][j].resource += 5;
            }
        }
    }
};

Map map;

bool gameOver = false;

bool isValidInteger(string value) {
    if (value.empty()) {
        cout << "Invalid input! Please enter an integer value." << endl;
        return false;
    }

    for (char c : value) {
        if (!isdigit(c)) {
            cout << "Invalid input! Please enter an integer value." << endl;
            return false;
        }
    }

    int intValue = stoi(value);

    if (intValue < 0 || intValue > 6) {
        cout << "Invalid input! Valid coordinates are in range 0 to 6." << endl;
        return false;
    }

    return true;
}

bool konamiCode(const vector<Key>& inputs) {
    const vector<Key> konamiCode = { Key::UP, Key::UP, Key::DOWN, Key::DOWN, Key::LEFT, Key::RIGHT, Key::LEFT, Key::RIGHT, Key::B, Key::A };

    if (inputs.size() < konamiCode.size()) {
        return false;
    }

    for (size_t i = 0; i < konamiCode.size(); ++i) {
        if (inputs[i] != konamiCode[i]) {
            return false;
        }
    }
    return true;
}

void cheat() {
    vector<Key> inputs;

    while (true) {
        Key key = Key::OTHER;
        int input = _getch();

        if (input == 224) {
            switch (_getch()) {
            case 72: key = Key::UP; break;
            case 80: key = Key::DOWN; break;
            case 75: key = Key::LEFT; break;
            case 77: key = Key::RIGHT; break;
            }
        }
        else if (input == 'b' || input == 'B') {
            key = Key::B;
        }
        else if (input == 'a' || input == 'A') {
            key = Key::A;
        }

        if (key != Key::OTHER) {
            inputs.push_back(key);
        }

        if (!konamiCode(inputs)) {
            cout << "Incorrect sequence. Code cancelled." << endl;
            break;
        }
        else if (inputs.size() == 10) {
            cout << "Konami Code detected!" << endl;
            break;
        }
    }
}

void displayMenu() {
    int choice;
    string input;
    cout << endl << endl << endl;
    cout << "1 - Pass a day" << endl;
    cout << "2 - Check a tile" << endl;
    cout << "3 - Quit" << endl;
<<<<<<< HEAD
<<<<<<< Updated upstream
=======
    cout << "Temporary Command : " << endl;
    cout << "4 - Flood map" << endl;
    cout << "5 - Wake volcano (not working)" << endl;
    cout << "6 - Earthquake (not working" << endl;
>>>>>>> d9f656911a4e8a6da193a06471d49ce8dc7dbb28
    cin >> choice;
=======
    cout << "Temporary Command : " << endl;
    cout << "4 - Flood map" << endl;
    cout << "5 - Wake volcano (not working)" << endl;
    cout << "6 - Earthquake (not working)" << endl;

    while (true) {
        cin >> input;
        if (input == "cheat") {
            cheat();
        }
        else {
            if (isValidInteger(input)) {
                choice = stoi(input);
                break;
            }
        }
    }
>>>>>>> Stashed changes

    switch (choice) {
    case 1:
        map.nextDay();
        break;
    case 2:
        map.checkTile();
        break;
    case 3:
        gameOver = true;
        break;
    case 4:
        map.StartFlooding();
        map.nextDay();
        break;


    default:
        break;
    }
}


void startGame() {
    clearScreen();
    srand((unsigned)time(NULL));
    map.startGeneration();

    while (!gameOver) {
        clearScreen();
        displayLittleTitle();
        map.displayMap();
        displayMenu();
    }
}