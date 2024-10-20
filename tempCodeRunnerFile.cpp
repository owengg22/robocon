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
        this->speed = 2; 
    }

   
    void move_towards_end() {
        while (pos != end) {
            char best_move = calculate_ik(); 
            move(best_move);
            log_position();  
            if (pos == end) {
                cout << "Robot berhasil mencapai tujuan dalam " << time << " menit.\n";
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
                cout << "Robot nabrak, silahkan diperbaiki.\n";
            } else {
                pos.first = new_x;
                pos.second = new_y;
                interact(cell);
                time += speed;
            }
        } else {
            cout << "Robot nabrak, silahkan diperbaiki.\n";
        }
    }

    void interact(char cell) {
        switch (cell) {
            case 'M':
                mechanic = true;
                cout << "Bertemu dengan mekanik, siap membasmi rintangan.\n";
                break;
            case 'E':
                speed = 1; // kecepatan meningkat
                cout << "Bertemu dengan electrical, kecepatan roda naik menjadi 200%.\n";
                break;
            case 'P':
                cout << "Hi Programmer.\n";
                break;
            case 'O':
                time *= 2; // waktu dikali dua
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
        cout << "Robot telah berjalan selama " << time << " menit.\n";
    }


    void log_position() {
        ofstream logFile("robot_log.txt", ios::app);
        if (logFile.is_open()) {
            logFile << "Posisi robot: (" << pos.first << ", " << pos.second << ") - Waktu: " << time << " menit.\n";
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
    // Membaca peta dari file (file peta harus sudah ada di direktori yang sama)
    vector<vector<char>> map_grid = Robot::read_map_from_file("map.txt");

    // Inisialisasi robot di posisi awal (0, 0) dan tujuan di (2, 3) (posisi harus disesuaikan dengan peta)
    pair<int, int> start = {0, 0};
    pair<int, int> end = {2, 3};

    Robot robot(map_grid, start, end);

    // Menggerakkan robot ke tujuan menggunakan Inverse Kinematics
    robot.move_towards_end();

    // Cek status akhir robot
    robot.check_status();
    robot.print_time();

    return 0;
}
