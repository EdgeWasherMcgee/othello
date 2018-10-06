#include <iostream>
#include <fstream>
#include <cstring>

class board{ //Low teir class that makes manages the file. This is the only function that is supposed to write to the othello-board file.
    private: //Initializing things that has to be made before the public functions
        char fileInp[1];
        std::string txtfile;
        std::fstream f;
    public:
        board(std::string txtfile, bool empty){
            this->txtfile = txtfile;
            f.open(this->txtfile, std::ios::out | std::ios::in | std::ios::binary );
            if (empty){
                initBoard();
            }
            if (!f){
                std::cout << "Opening file failed" << std::endl;
            }
        }
        board() : board("oBoard.txt", true){
        }
        ~board(){
            f.close();
        }
        void setP(int x, int y, char val){ //Is supposed to make you able to assign a place on a board as another value.
            int pos = x + y * 8;
            f.seekp(pos);
            f.put(val);
        }
        char getP(int x, int y){ //Is supposed to return the value that is on the given place on the othello board.
            int pos = x + y * 8;
            f.seekg(pos);
            f.read(fileInp, 1);
            char valAscii = fileInp[0];
            return valAscii;
        }
        void printFile(){ //Is supposed to print the whole board
            for (int i = 0; i < 64; i++){
                std::printf("%c", getP(i % 8, i / 8));
            }
            std::cout << std::endl;
        }

        bool is_allowed(){
            bool allowed = true;
            f.seekg(0, std::ios::end);
            if (f.tellg() != 64){
                allowed = false;
            }
            for (int i = 0; i < 64; i++){
                if (getP(i%8, i/8) > PLAYER_2 or getP(i%8, i/8) < NO_PLAYER){
                    allowed = false;
                }
            }
            return allowed;
        }

    private:
        void initBoard(){ //Is supposed to fill the board with 0's
            f.seekp(0, std::ios::beg);
            char initFile[64];
            for (int i = 0; i < 64; i++){
                initFile[i] = '0';
            }
            f.write(initFile, 64);
        }
};

class othello_controller{
    private:
        board* brd;
        typedef enum player {NO_PLAYER = '0', PLAYER_1 = '1', PLAYER_2 = '2'} PLAYER;
    public:
        othello_controller(std::string name){
            brd = new board(name, true);
        }
        othello_controller(): othello_controller("oBoard.txt"){
        }

        void test1(){

        } 

    private:

        int layable(PLAYER player, int x, int y){
            int switches = 0;
            if (occupied(x, y)){
                return 0;
            }
            switches = switches + check(player, x, y, 0, -1);
            switches = switches + check(player, x, y, 1, -1);
            switches = switches + check(player, x, y, 1, 0);
            switches = switches + check(player, x, y, 1, 1);
            switches = switches + check(player, x, y, 0, 1);
            switches = switches + check(player, x, y, -1, 1);
            switches = switches + check(player, x, y, -1, 0);
            switches = switches + check(player, x, y, -1, -1);
            
            return switches;
        }
        
        PLAYER invPlayer(PLAYER player){
            if (player == PLAYER_2){
                return PLAYER_1;
            }
            else if (player == PLAYER_1){
                return PLAYER_2;
            }
            else{
                return NO_PLAYER;
            }
        }

        bool occupied(int x, int y){ //Returns true if the position value is the same as NO_PLAYER, and false if it is any other value
            if (not brd->getP(x, y)){
                return true;
            }
            return false;
        }

        int check(PLAYER player,int x, int y, int stepx, int stepy){
            int c = 0;
            while (true){
                x = x + stepx;
                y = y + stepy;
                if (out_of_bounds(x, y) or brd->getP(x, y) == NO_PLAYER){
                    break;
                }
                if (brd->getP(x, y) == player){
                    return c;
                }
                c++;
            }
            return 0;
        }

        bool out_of_bounds(int x, int y){
            if (x > 7 or x < 0 or y > 7 or y < 0){
                return false;
            }
            else return true;
        }

        int check_diags(int x, int y){
            
        }

        //char* tileSwitch(int x, int y, enum* player){
        //    return *'0'; 
        //}
};
//void test(){
//    board brd;
//    brd.printFile();
//    brd.setP(0, 3, '1');
//    std::cout << brd.getP(0,3) << std::endl;
//    brd.setP(3, 3,'2');
//    brd.setP(7, 7, '8');
//    brd.printFile();
//}
//


int main(int argc, char* argv[]){
    othello_controller oc("oBoard.txt");
    oc.test1();
    return 0;
}
