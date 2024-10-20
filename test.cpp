#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

class Robot {
private:
    vector<vector<char>> map_grid;
    pair<int, int> pos;
    pair<int, int> end;
    int time;  
    bool mechanic;
    int speed; 
public:

    Robot(vector<vector<char>> map_grid, pair<int, int> start, pair<int, int> end) {
        this->map_grid = map_grid;
        this->pos = start;
        this->end = end;
        this->time = 0;
        this->mechanic = false;
        this->speed = 120;  
    }

 
    void move_towards_end() {
        while (pos != end) {
            char best_move = calculate_ik();
            move(best_move);
            log_position();
            if (pos == end) {
                cout << "Robot berhasil mencapai tujuan dalam " << time << " detik.\n";
                break;
            }
        }
    }

  
    char calculate_ik() {
        int deltaX = end.first - pos.first;
        int deltaY = end.second - pos.second;

        if (abs(deltaX) > abs(deltaY)) {
            return (deltaX > 0) ? 'D' : 'U'; 
        } else {
            return (deltaY > 0) ? 'R' : 'L';  
        }
    }

    
    void move(char direction) {
        int new_x = pos.first;
        int new_y = pos.second;

        
        if (direction == 'U') new_x--;
        else if (direction == 'D') new_x++;
        else if (direction == 'L') new_y--;
        else if (direction == 'R') new_y++;

        if (new_x >= 0 && new_x < map_grid.size() && new_y >= 0 && new_y < map_grid[0].size()) {
            char cell = map_grid[new_x][new_y];

         
            if (cell == 'x' && !mechanic) {
                cout << "Robot nabrak rintangan, tidak bisa lewat.\n";
            } else {
                pos.first = new_x;
                pos.second = new_y;
                interact(cell);
                time += speed;  
            }
        } else {
            cout << "Robot keluar dari peta, silahkan diperbaiki.\n";
        }
    }


    void interact(char cell) {
        switch (cell) {
            case 'M':
                mechanic = true;
                cout << "Bertemu dengan mekanik, siap membasmi rintangan.\n";
                break;
            case 'E':
                speed = 60; 
                cout << "Bertemu dengan electrical, kecepatan roda naik menjadi 200%.\n";
                break;
            case 'P':
                cout << "Hi Programmer.\n";
                break;
            case 'O':
                time *= 2; 
                cout << "Bertemu dengan official, diajak ngonten bareng.\n";
                break;
        }
    }

    
    void check_status() {
        if (pos == end) {
            cout << "Robot berhasil mencapai tujuan.\n";
        } else {
            cout << "Robot gagal mencapai tujuan.\n";
        }
    }

    
    void print_time() {
        cout << "Robot telah berjalan selama " << time << " detik.\n";
    }

    
    void log_position() {
        ofstream logFile("robot_log.txt", ios::app);
        if (logFile.is_open()) {
            logFile << "Posisi robot: (" << pos.first << ", " << pos.second << ") - Waktu: " << time << " detik.\n";
            logFile.close();
        } else {
            cout << "Tidak bisa membuka file log.\n";
        }
    }

    
    static vector<vector<char>> read_map_from_file(const string& fileName) {
        vector<vector<char>> map;
        ifstream mapFile(fileName);
        if (mapFile.is_open()) {
            string line;
            while (getline(mapFile, line)) {
                vector<char> row(line.begin(), line.end());
                map.push_back(row);
            }
            mapFile.close();
        } else {
            cout << "Tidak bisa membuka file peta.\n";
        }
        return map;
    }
};

int main() {
    
    vector<vector<char>> map_grid = Robot::read_map_from_file("map.txt");

  
    pair<int, int> start = {0, 0};
    pair<int, int> end = {2, 3};

    Robot robot(map_grid, start, end);

  
    robot.move_towards_end();

   
    robot.check_status();
    robot.print_time();

    return 0;
}
