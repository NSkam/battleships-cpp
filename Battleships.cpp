#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <stdlib.h>

using namespace std;


class Tile{

private:
    int X_coordinate; //X coordinate of tile
    int Y_coordinate; //Y coordinate of tile
public:
    enum Tile_type {
        SEA, //~
        SHIP, //s
        HIT, // X
        MISS //o
        };
    Tile_type type;

    // SETTERS AND GETTERS
    void setX(int new_X){
        this->X_coordinate = new_X;
        }

    int getX(){
        return this->X_coordinate;
        }

    void setY(int new_Y){
        this->Y_coordinate = new_Y;
        }

    int getY(){
        return this->Y_coordinate;
        }

    void setType(Tile_type new_type){
        this->type = new_type;
        }

    Tile_type getType(){
        return this->type;
        }

    void draw(bool hidden){

   if(hidden == true){ // If hidden is true the draw method doesnt reveal opponents ships
        switch(this->type){
            case SEA: cout<<"~ "; break;
            case SHIP: cout<<"~ "; break;
            case HIT: cout<<"X "; break;
            case MISS: cout<<"o "; break;
    }} else{
        switch(this->type){
            case SEA: cout<<"~ "; break;
            case SHIP: cout<<"s "; break;
            case HIT: cout<<"X "; break;
            case MISS: cout<<"o "; break;

      }
    }
  }
};

class Board{

private:
    const static int board_X = 14; //The horizontal length of the board
    const static int board_Y = 14;//The vertical length of the board

public:
    Tile Game_Board[board_X][board_Y]; // The Board itself
    bool hidden = false; //True is for opponent's board, false for player's board

    Board(){ //Set the tiles of the board at the start of the game equal to SEA
        for(int i = 0 ; i < board_X ; i++){
            for(int y = 0 ; y < board_Y ; y++){
                Game_Board[i][y].setType(Tile::SEA);
            }
        }
    }

    void drawboards(Board board){ // Draws the Boards for each player(Updates when a ship is placed or one someone shoots)
        cout << " -P L A Y E R-\t\t\t-O P P O N E N T- \n";
        cout << "  0 1 2 3 4 5 6 7 8 9 A B C D\t0 1 2 3 4 5 6 7 8 9 A B C D \n";
        for(int i = 0 ; i < board_X ; i++){
            cout << i << " ";
            for(int y = 0 ; y < board_Y ; y++){
                this->Game_Board[y][i].draw(false);}
            cout << "\t" ;
            for(int y = 0 ; y < board_Y ; y++){
                board.Game_Board[y][i].draw(true);}
            cout << "\n" <<endl;
        }
    }

    bool allShipsSunk(){//Checks if all the ships are sunk
        int counter = 0 ;
        for(int i = 0 ; i < board_X ; i++){
            for(int y = 0 ; y < board_Y ; y++){
                if(this->Game_Board[i][y].type != Tile::SHIP){
                    counter++;
                }else{continue;}
        }}
        if(counter == 196){cout<< "Game Over!";
        return true;}
        else{return false;}
 }

    void placeAllShips();

    //Some Getters
    int getBoardX(){
        return this->board_X;
        }

    int getBoardY(){
        return this->board_Y;
        }
};


class Ship{ //Parent class

private:

    Tile starting_tile; //The starting Tile
    bool orientation; //True = horizontally , false = vertically

public:

    bool getOrientation(){
        return this->orientation;
    }
    void setOrientation(bool new_orientation){
        this->orientation = new_orientation;
    }
};

class Carrier: public Ship{

public:
    int Ship_size = 5;


    bool placeShip(Tile start_tile, bool ship_orientation, Board &board){

        int Tile_X = start_tile.getX();
        int Tile_Y = start_tile.getY();


//We start from the start_tile's coordinates and we change the tiles from
//sea to ship, either vertically or horizontally.
if(Tile_X > board.getBoardX() || Tile_Y > board.getBoardY()){

    cout << "The tile's coordinates must not be higher than the board's size\n" <<endl;

            return false;

}else{

    if(ship_orientation == true){//

    //Placing ship horizontally

      for(int i = 0 ; i<Ship_size ; i++){
        if(board.Game_Board[Tile_X+i][Tile_Y].getType() ==Tile::SHIP){

        cout << "The tile has already a ship on it.Please choose a different one." <<endl;

            return false;

        }
        }
       for(int i = 0 ; i<Ship_size ; i++){
           board.Game_Board[Tile_X+i][Tile_Y].setType(Tile::SHIP);}

            return true;

        }else{
        //Placing Ship vertically
         for(int y = 0 ; y<Ship_size ; y++){
          if(board.Game_Board[Tile_X][Tile_Y+y].getType() ==Tile::SHIP){

           cout << "The tile has already a ship on it.Please choose a different one." <<endl;

            return false;

        }}

        for(int i = 0 ; i<Ship_size ; i++){
           board.Game_Board[Tile_X][Tile_Y+i].setType(Tile::SHIP);}

            return true;


      }
    }
  return true;}
};

class Battleship: public Ship{

public:

    int Ship_size = 4;


    bool placeShip(Tile start_tile, bool ship_orientation, Board &board){

        int Tile_X = start_tile.getX();
        int Tile_Y = start_tile.getY();


//We start from the start_tile's coordinates and we change the tiles from
//sea to ship, either vertically or horizontally.
if(Tile_X > board.getBoardX() || Tile_Y > board.getBoardY()){

    cout << "The tile's coordinates must not be higher than the board's size\n" <<endl;

            return false;

}else{

    if(ship_orientation == true){//

    //Placing ship horizontally

      for(int i = 0 ; i<Ship_size ; i++){
        if(board.Game_Board[Tile_X+i][Tile_Y].getType() ==Tile::SHIP){

        cout << "The tile has already a ship on it.Please choose a different one." <<endl;

            return false;

        }
        }
       for(int i = 0 ; i<Ship_size ; i++){
           board.Game_Board[Tile_X+i][Tile_Y].setType(Tile::SHIP);}
            return true;

        }else{
        //Placing Ship vertically
         for(int i = 0 ; i<Ship_size ; i++){
          if(board.Game_Board[Tile_X][Tile_Y+i].getType() ==Tile::SHIP){

           cout << "The tile has already a ship on it.Please choose a different one." <<endl;

            return false;

        }}

        for(int i = 0 ; i<Ship_size ; i++){
           board.Game_Board[Tile_X][Tile_Y+i].setType(Tile::SHIP);}
            return true;


      }
    }
return true;  }
};

class Cruiser: public Ship{

public:

    int Ship_size = 3;


    bool placeShip(Tile start_tile, bool ship_orientation, Board &board){

        int Tile_X = start_tile.getX();
        int Tile_Y = start_tile.getY();


//We start from the start_tile's coordinates and we change the tiles from
//sea to ship, either vertically or horizontally.
if(Tile_X > board.getBoardX() || Tile_Y > board.getBoardY()){

    cout << "The tile's coordinates must not be higher than the board's size\n" <<endl;

            return false;

}else{

    if(ship_orientation == true){//

    //Placing ship horizontally

      for(int i = 0 ; i<Ship_size ; i++){
        if(board.Game_Board[Tile_X+i][Tile_Y].getType() == Tile::SHIP){

        cout << "The tile has already a ship on it.Please choose a different one." <<endl;

            return false;

        }
        }
       for(int i = 0 ; i<Ship_size ; i++){
           board.Game_Board[Tile_X+i][Tile_Y].setType(Tile::SHIP);}
            return true;

        }else{
        //Placing Ship vertically
         for(int i = 0 ; i<Ship_size ; i++){
          if(board.Game_Board[Tile_X][Tile_Y+i].getType() ==Tile::SHIP){

           cout << "The tile has already a ship on it.Please choose a different one." <<endl;

            return false;

        }}

        for(int i = 0 ; i<Ship_size ; i++){
           board.Game_Board[Tile_X][Tile_Y+i].setType(Tile::SHIP);}
            return true;


      }
    }
  return true;}
};

class Submarine: public Ship{

public:

    int Ship_size = 3;

    bool placeShip(Tile start_tile, bool ship_orientation, Board &board){

        int Tile_X = start_tile.getX();
        int Tile_Y = start_tile.getY();


//We start from the start_tile's coordinates and we change the tiles from
//sea to ship, either vertically or horizontally.
if(Tile_X > board.getBoardX() || Tile_Y > board.getBoardY()){

    cout << "The tile's coordinates must not be higher than the board's size\n" <<endl;

            return false;

}else{

    if(ship_orientation == true){//

    //Placing ship horizontally

      for(int i = 0 ; i<Ship_size ; i++){
        if(board.Game_Board[Tile_X+i][Tile_Y].getType() ==1){

        cout << "The tile has already a ship on it.Please choose a different one." <<endl;

            return false;

        }
        }
       for(int i = 0 ; i<Ship_size ; i++){
           board.Game_Board[Tile_X+i][Tile_Y].setType(Tile::SHIP);}
            return true;

        }else{
        //Placing Ship vertically
         for(int i = 0 ; i<Ship_size ; i++){
          if(board.Game_Board[Tile_X][Tile_Y+i].getType() ==Tile::SHIP){

           cout << "The tile has already a ship on it.Please choose a different one." <<endl;

            return false;

        }}

        for(int i = 0 ; i<Ship_size ; i++){
           board.Game_Board[Tile_X][Tile_Y+i].setType(Tile::SHIP);}
            return true;


      }
    }
  return true;}
};

class Destroyer: public Ship{

public:

    int Ship_size = 2;


    bool placeShip(Tile start_tile, bool ship_orientation, Board &board){

        int Tile_X = start_tile.getX();
        int Tile_Y = start_tile.getY();


//We start from the start_tile's coordinates and we change the tiles from
//sea to ship, either vertically or horizontally.
if(Tile_X > board.getBoardX() || Tile_Y > board.getBoardY()){

    cout << "The tile's coordinates must not be higher than the board's size\n" <<endl;

            return false;

}else{

    if(ship_orientation == true){//

    //Placing ship horizontally

      for(int i = 0 ; i<Ship_size ; i++){
        if(board.Game_Board[Tile_X+i][Tile_Y].getType() ==Tile::SHIP){

        cout << "The tile has already a ship on it.Please choose a different one." <<endl;

            return false;

        }
        }
       for(int i = 0 ; i<Ship_size ; i++){
           board.Game_Board[Tile_X+i][Tile_Y].setType(Tile::SHIP);}
            return true;

        }else{
        //Placing Ship vertically
         for(int i = 0 ; i<Ship_size ; i++){
          if(board.Game_Board[Tile_X][Tile_Y+i].getType() ==Tile::SHIP){

           cout << "The tile has already a ship on it.Please choose a different one." <<endl;

            return false;

        }}

        for(int i = 0 ; i<Ship_size ; i++){
           board.Game_Board[Tile_X][Tile_Y+i].setType(Tile::SHIP);}
            return true;


      }
    }
 return true; }
};

 void Board::placeAllShips(){ //Places all the ships randomly.
     //Create a random seed
    srand(time(NULL));
     //Create the Ships
    Carrier Car;
    Car.setOrientation(rand()%2);
    bool Car_can_be_placed = true;
    bool Car_placed = false;
    Battleship Bat;
    Bat.setOrientation(rand()%2);
    bool Bat_can_be_placed = true;
    bool Bat_placed = false;
    Cruiser Cr;
    Cr.setOrientation(rand()%2);
    bool Cr_can_be_placed = true;
    bool Cr_placed = false;
    Submarine Sub;
    Sub.setOrientation(rand()%2);
    bool Sub_can_be_placed = true;
    bool Sub_placed = false;
    Destroyer Des;
    Des.setOrientation(rand()%2);
    bool Des_can_be_placed = true;
    bool Des_placed = false;

    int num_ships = 0; // Number of ships Placed

while(num_ships < 5){
    //Assign numbers to the Tiles for the ships
    if(Car_placed != true){

            int Car_X = rand()%9;
            int Car_Y = rand()%9;

        if(Car.getOrientation() == true){
        //Placing ship Horizontally
        for(int i = 0 ; i<Car.Ship_size ; i++){
        if(this->Game_Board[Car_X+i][Car_Y].getType() == Tile::SHIP){
                continue;}}
        if(Car_can_be_placed == true){
        for(int i = 0 ; i<Car.Ship_size ; i++){
           this->Game_Board[Car_X+i][Car_Y].setType(Tile::SHIP);}
            num_ships++;
            Car_placed = true;

            }}else{
        //Placing Ship vertically
        for(int i = 0 ; i<Car.Ship_size ; i++){
        if(this->Game_Board[Car_X][Car_Y+i].getType() == Tile::SHIP){
                continue;}}
        if(Car_can_be_placed == true){
        for(int i = 0 ; i<Car.Ship_size ; i++){
           this->Game_Board[Car_X][Car_Y+i].setType(Tile::SHIP);}
            num_ships++;
            Car_placed = true;
}}}

    if(Bat_placed != true){

            int Bat_X = rand()%10;
            int Bat_Y = rand()%10;


        if(Bat.getOrientation() == true){
        //Placing ship Horizontally
        for(int i = 0 ; i<Bat.Ship_size ; i++){
        if(this->Game_Board[Bat_X+i][Bat_Y].getType() == Tile::SHIP){
              continue;}}
        if(Bat_can_be_placed == true){
        for(int i = 0 ; i<Bat.Ship_size ; i++){
           this->Game_Board[Bat_X+i][Bat_Y].setType(Tile::SHIP);}
            num_ships++;
            Bat_placed = true;
            }}else{
        //Placing Ship vertically
        for(int i = 0 ; i<Bat.Ship_size ; i++){
        if(this->Game_Board[Bat_X][Bat_Y+i].getType() ==Tile::SHIP){
               continue;}}
        if(Bat_can_be_placed == true){
        for(int i = 0 ; i<Bat.Ship_size ; i++){
           this->Game_Board[Bat_X][Bat_Y+i].setType(Tile::SHIP);}
            num_ships++;
            Bat_placed = true;
}}}

    if(Cr_placed != true){

            int Cr_X = rand()%11;
            int Cr_Y = rand()%11;

        if(Cr.getOrientation() == true){
        //Placing ship Horizontally
        for(int i = 0 ; i<Cr.Ship_size ; i++){
        if(this->Game_Board[Cr_X+i][Cr_Y].getType() ==Tile::SHIP){
                continue;}}
        if(Cr_can_be_placed == true){
        for(int i = 0 ; i<Cr.Ship_size ; i++){
           this->Game_Board[Cr_X+i][Cr_Y].setType(Tile::SHIP);}
            num_ships++;
            Cr_placed = true;
            }}else{
        //Placing Ship vertically
        for(int i = 0 ; i<Cr.Ship_size ; i++){
        if(this->Game_Board[Cr_X][Cr_Y+i].getType() ==Tile::SHIP){
               continue;}}
        if(Cr_can_be_placed == true){
        for(int i = 0 ; i<Cr.Ship_size ; i++){
           this->Game_Board[Cr_X][Cr_Y+i].setType(Tile::SHIP);}
            num_ships++;
            Cr_placed = true;
}}}

    if(Sub_placed != true){

            int Sub_X = rand()%11;
            int Sub_Y = rand()%11;

        if(Sub.getOrientation() == true){
        //Placing ship Horizontally
        for(int i = 0 ; i<Sub.Ship_size ; i++){
        if(this->Game_Board[Sub_X+i][Sub_Y].getType() ==Tile::SHIP){
                continue;}}
        if(Sub_can_be_placed == true){
        for(int i = 0 ; i<Sub.Ship_size ; i++){
           this->Game_Board[Sub_X+i][Sub_Y].setType(Tile::SHIP);}
            num_ships++;
            Sub_placed = true;
            }}else{
        //Placing Ship vertically
        for(int i = 0 ; i<Sub.Ship_size ; i++){
        if(this->Game_Board[Sub_X][Sub_Y+i].getType() ==Tile::SHIP){
                continue;}}
        if(Sub_can_be_placed == true){
        for(int i = 0 ; i<Sub.Ship_size ; i++){
           this->Game_Board[Sub_X][Sub_Y+i].setType(Tile::SHIP);}
            num_ships++;
            Sub_placed = true;
}}}


    if(Des_placed != true){

            int Des_X = rand()%12;
            int Des_Y = rand()%12;

      if(Des.getOrientation() == true){
        //Placing ship Horizontally
        for(int i = 0 ; i<Des.Ship_size ; i++){
        if(this->Game_Board[Des_X+i][Des_Y].getType() ==Tile::SHIP){
                continue;}}
        if(Des_can_be_placed == true){
        for(int i = 0 ; i<Des.Ship_size ; i++){
           this->Game_Board[Des_X+i][Des_Y].setType(Tile::SHIP);}
            num_ships++;
            Des_placed = true;
            }}else{
        //Placing Ship vertically
        for(int i = 0 ; i<Des.Ship_size ; i++){
        if(this->Game_Board[Des_X][Des_Y+i].getType() ==Tile::SHIP){
                continue;;}}
        if(Des_can_be_placed == true){
        for(int i = 0 ; i<Des.Ship_size ; i++){
           this->Game_Board[Des_X][Des_Y+i].setType(Tile::SHIP);}
            num_ships++;
            Des_placed = true;


}}}
}}



class Player{

  private:

    string player_name;
    bool is_human;
    int total_shots = 0;
    int total_misses = 0;
    int sucs_shots = 0; //Successful shots
    int rep_shots = 0; //Repeated shots - shots in tiles that there were already shots

  public:

    Board Player_Board;

    //Setters and Getters

    void setPlayer_N(string new_name){
        this->player_name = new_name;
        }

    string getPlayer_N(){
        return this->player_name;
        }

    void setTotal_S(int new_total){
        this->total_shots = new_total;
        }

    int getTotal_S(){
        return this->total_shots;
        }

    void setTotal_M(int new_total){
        this->total_misses = new_total;
        }

    int getTotal_M(){
        return this->total_misses;
        }

    void setSuccess_s(int new_total){
        this->sucs_shots = new_total;
        }

    int getSuccess_s(){
        return this->sucs_shots;
        }

    void setRep_s(int new_total){
        this->rep_shots = new_total;
        }

    int getRep_s(){
        return this->rep_shots;
        }

     void setHuman(bool human){
        this->is_human = human;

     }

     bool getHuman(){
        return this->is_human;
     }

    void placeAllShips(){ //Places all ships Randomly
        this->Player_Board.placeAllShips();
    }

    //Places Carrier according to coordinates
    bool placeShip(Carrier ship_to_be_placed, Tile starting_tile){

        bool ship_placed;
        bool ship_to_be_placed_orientation = ship_to_be_placed.getOrientation();

        ship_placed = ship_to_be_placed.placeShip(starting_tile,ship_to_be_placed_orientation,this->Player_Board);

        if(ship_placed != true){
            cout << "Ship placement was unsuccessful\n" << endl;
            return ship_placed;
        }
        else {
            cout << "Ship was placed successfully\n" <<endl;
            return ship_placed;
        }
    }

    //Places Battleship according to coordinates
    bool placeShip(Battleship ship_to_be_placed, Tile starting_tile){

        bool ship_placed;
        bool ship_to_be_placed_orientation = ship_to_be_placed.getOrientation();

        ship_placed = ship_to_be_placed.placeShip(starting_tile,ship_to_be_placed_orientation,this->Player_Board);

        if(ship_placed != true){
            cout << "Ship placement was unsuccessful\n" << endl;
            return ship_placed;
        }
        else {
            cout << "Ship was placed successfully\n" <<endl;
            return ship_placed;
        }
    }

    //Places Cruiser according to coordinates
    bool placeShip(Cruiser ship_to_be_placed, Tile starting_tile){

        bool ship_placed;
        bool ship_to_be_placed_orientation = ship_to_be_placed.getOrientation();

        ship_placed = ship_to_be_placed.placeShip(starting_tile,ship_to_be_placed_orientation,this->Player_Board);

        if(ship_placed != true){
            cout << "Ship placement was unsuccessful\n" << endl;
            return ship_placed;
        }
        else {
            cout << "Ship was placed successfully\n" <<endl;
            return ship_placed;
        }
    }

    //Places Submarine according to coordinates
    bool placeShip(Submarine ship_to_be_placed, Tile starting_tile){

        bool ship_placed;
        bool ship_to_be_placed_orientation = ship_to_be_placed.getOrientation();

        ship_placed = ship_to_be_placed.placeShip(starting_tile,ship_to_be_placed_orientation,this->Player_Board);

        if(ship_placed != true){
            cout << "Ship placement was unsuccessful\n" << endl;
            return ship_placed;
        }
        else {
            cout << "Ship was placed successfully\n" <<endl;
            return ship_placed;
        }
    }

    //Places Destroyer according to coordinates
    bool placeShip(Destroyer ship_to_be_placed, Tile starting_tile){

        bool ship_placed;
        bool ship_to_be_placed_orientation = ship_to_be_placed.getOrientation();

        ship_placed = ship_to_be_placed.placeShip(starting_tile,ship_to_be_placed_orientation,this->Player_Board);

        if(ship_placed != true){
            cout << "Ship placement was unsuccessful\n" << endl;
            return ship_placed;
        }
        else {
            cout << "Ship was placed successfully\n" <<endl;
            return ship_placed;
        }
    }

    //Fires a Shot at target tile
    void fire(Board &enemy_board, Tile target_tile){

        //Get target tile coordinates
        int Target_X = target_tile.getX();
        int Target_Y = target_tile.getY();

    switch(enemy_board.Game_Board[Target_X][Target_Y].getType()){

        case Tile::SHIP :
            if(this->getHuman()){ cout << "Hit\n";}
             enemy_board.Game_Board[Target_X][Target_Y].setType(Tile::HIT);
             this->setTotal_S(this->getTotal_S()+1);
             this->setSuccess_s(this->getSuccess_s()+1);
             break;


        case Tile::SEA :
            if(this->getHuman()){cout << "MISS\n";}
             enemy_board.Game_Board[Target_X][Target_Y].setType(Tile::MISS);
             this->setTotal_S(this->getTotal_S()+1);
             this->setTotal_M(this->getTotal_M()+1);
             break;


        case Tile::HIT :
            if(this->getHuman()){cout << "Already hit\n";}
             this->setTotal_S(this->getTotal_S()+1);
             this->setRep_s(this->getRep_s()+1);
             break;


        case Tile::MISS :
            if(this->getHuman()){cout << "Already miss\n";}
             this->setTotal_S(this->getTotal_S()+1);
             this->setRep_s(this->getRep_s()+1);
             break;

    }
}

        void getStats(){

        cout << "Player's Name\t" << this->getPlayer_N() <<"\n" << endl;
        cout << "Total Shots\t" << this->getTotal_S() <<"\n" << endl;
        cout << "Total Misses\t" << this->getTotal_M() <<"\n" << endl;
        cout << "Successful Shots\t" << this->getSuccess_s() <<"\n" << endl;
        cout << "Repeated Shots\t" << this->getRep_s() <<"\n" << endl;

        }
};

class Game{

public:

//Gets Tile Input from Player
    Tile getInput(){

        Tile Input_Tile;
        int x_coordinate = 0;
        int y_coordinate = 0;

        while(1){

        cout << "Please enter the coordinates: " <<endl;
        cin >> x_coordinate >> y_coordinate ;

        if (!(x_coordinate <= 14 && y_coordinate <= 14)){
        cout<<"The coordinates need to be less or equal than 14(board size = 14)" <<endl;
        }else{
        break;
        }
}
    Input_Tile.setX(x_coordinate);
    Input_Tile.setY(y_coordinate);
    return Input_Tile;
}

//Gets Random Input
    Tile getRandInput(){
        srand(time(NULL));
        Tile Rand_Tile;
        int x_coordinate = rand()%14;
        int y_coordinate = rand()%14;

        Rand_Tile.setX(x_coordinate);
        Rand_Tile.setY(y_coordinate);
        return Rand_Tile;
    }

    bool getOrientation(){

        char orientation;
        cout << "Is the orientation of the ship Horizontal(H) or Vertical(V)? ";
        cin >> orientation;

        if(orientation == 'H'){ return true;}
        else { return false;}

    }

        bool randomPlace(){

        char yes_or_no;
        cin >> yes_or_no;

        if(yes_or_no == 'Y'){ return true;}
        else { return false;}

    }


};

    int main(){

        Game Game;//The Game
        Player Human_Player;//User
        Human_Player.setHuman(true);
        Player Cpu_Player; //CPU
        Cpu_Player.setHuman(false);
        Tile fire_tile;//Tile for fire coordinates

        //Random or Not random placement
        cout << "Do you want your ships to be placed randomly? Y/N\n" <<endl;
        bool answer = Game.randomPlace();
        if(answer == true){Human_Player.placeAllShips();}
        else{//Placement of Each Ship

                            //Carrier
            cout <<"Enter the starting coordinates and the orientation of the Carrier. " <<endl;
            Tile Carrier_tile = Game.getInput();
            Carrier_tile.setType(Tile::SHIP);
            bool Carrier_orientation = Game.getOrientation();
            Carrier Car;
            Car.setOrientation(Carrier_orientation);
            Human_Player.placeShip(Car,Carrier_tile);

                            //Battleship
            cout <<"Enter the starting coordinates and the orientation of the Battleship. " <<endl;
            Tile Battleship_tile = Game.getInput();
            Battleship_tile.setType(Tile::SHIP);
            bool Battleship_orientation = Game.getOrientation();
            Battleship Bat;
            Bat.setOrientation(Battleship_orientation);
            Human_Player.placeShip(Bat, Battleship_tile);

                            //Cruiser
            cout <<"Enter the starting coordinates and the orientation of the Cruiser. " <<endl;
            Tile Cruiser_tile = Game.getInput();
            Cruiser_tile.setType(Tile::SHIP);
            bool Cruiser_orientation = Game.getOrientation();
            Cruiser Cr;
            Cr.setOrientation(Cruiser_orientation);
            Human_Player.placeShip(Cr, Cruiser_tile);

                            //Submarine
            cout <<"Enter the starting coordinates and the orientation of the Submarine. " <<endl;
            Tile Submarine_tile = Game.getInput();
            Submarine_tile.setType(Tile::SHIP);
            bool Submarine_orientation = Game.getOrientation();
            Submarine Sub;
            Sub.setOrientation(Submarine_orientation);
            Human_Player.placeShip(Sub, Submarine_tile);

                            //Destroyer
            cout <<"Enter the starting coordinates and the orientation of the Destroyer. " <<endl;
            Tile Destroyer_tile = Game.getInput();
            Destroyer_tile.setType(Tile::SHIP);
            bool Destroyer_orientation = Game.getOrientation();
            Destroyer Des;
            Des.setOrientation(Destroyer_orientation);
            Human_Player.placeShip(Des, Destroyer_tile);
        }

        //Cpu Random Ship Placement
          Sleep(2000);
          Cpu_Player.placeAllShips();

        Human_Player.Player_Board.drawboards(Cpu_Player.Player_Board);

        //MAIN GAME LOOP
        while(1){

        //Firing Phase
            fire_tile = Game.getInput();
            Human_Player.fire(Cpu_Player.Player_Board, fire_tile);
            fire_tile = Game.getRandInput();
            Cpu_Player.fire(Human_Player.Player_Board, fire_tile);


        //Drawing the Board Phase
            Human_Player.Player_Board.drawboards(Cpu_Player.Player_Board);

            if(Human_Player.Player_Board.allShipsSunk() || Cpu_Player.Player_Board.allShipsSunk())
            {
                break;
            }

        }

    //  End Game Screen

    if(Cpu_Player.Player_Board.allShipsSunk()){

        cout << "\nYOU WIN!!!\n" <<endl;
        }
        else if(Human_Player.Player_Board.allShipsSunk()){
            cout << "\nYOU LOSE!!!\n" <<endl;
        }else{
            cout << "error, need fixing\n" <<endl;
        }

        //Display Stats Screen
        Human_Player.getStats();


        int a;
        cin >> a;
        return 0;
}
