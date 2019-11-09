#include "hlt/game.hpp"
#include "hlt/constants.hpp"
#include "hlt/log.hpp"

#include <random>
#include <ctime>
#include <string>
#include <deque>
using namespace std;
using namespace hlt;

typedef struct {
  int id;
  int going_home = 0;
  int going_to_a_cell = 0;
  int alreadyGiven = 0;
  int round_assigned = 0;
  int hasToWait = 0;
  int distToHome = 0;
  int goHomeForever = 0;
  Position cell_assigned;
  Direction toBeMade;
} auxiliarShipStruct;


int LeeMap[100][100];
int anyoneGoingHomeForever = 0;
std::unordered_map<EntityId, auxiliarShipStruct> auxShips;
int mycnt = 0;
deque<Position> mypositions;

typedef struct{
  int alreadyGiven = 0;
}mgb;

mgb myGlobalMap[100][100];

void myreset() {
  for(int i = 0; i < 100; i++) {
    for(int j = 0; j < 100; j++) {
      LeeMap[i][j] = 0;
    }
  }
  mypositions.clear();
}

void Lee(int start_x, int start_y, int actual_round, unique_ptr<GameMap>& game_map) {
    Position aux;
    Position reverseAux;
    aux.x = start_x + 1;
    aux.y = start_y;
    reverseAux.x = aux.y;
    reverseAux.y = aux.x;
    reverseAux = game_map->normalize(reverseAux);
    aux.x = reverseAux.y;
    aux.y = reverseAux.x;

    if(LeeMap[aux.x][aux.y] != -1) {
        mypositions.push_back(aux);
        LeeMap[aux.x][aux.y] = actual_round;
    }
    aux.x = start_x - 1;
    aux.y = start_y;
    reverseAux.x = aux.y;
    reverseAux.y = aux.x;
  reverseAux = game_map->normalize(reverseAux);
    aux.x = reverseAux.y;
    aux.y = reverseAux.x;
    if(LeeMap[aux.x][aux.y] != -1) {
        mypositions.push_back(aux);
        LeeMap[aux.x][aux.y] = actual_round;
    }
    aux.x = start_x;
    aux.y = start_y + 1;
    reverseAux.x = aux.y;
    reverseAux.y = aux.x;
    reverseAux = game_map->normalize(reverseAux);
    aux.x = reverseAux.y;
    aux.y = reverseAux.x;
    if(LeeMap[aux.x][aux.y] != -1) {
        mypositions.push_back(aux);
        LeeMap[aux.x][aux.y] = actual_round;
    }
    aux.x = start_x;
    aux.y = start_y - 1;
    reverseAux.x = aux.y;
    reverseAux.y = aux.x;
    reverseAux = game_map->normalize(reverseAux);
    aux.x = reverseAux.y;
    aux.y = reverseAux.x;
    if(LeeMap[aux.x][aux.y] != -1) {
        mypositions.push_back(aux);
        LeeMap[aux.x][aux.y] = actual_round;
    }
    while(!mypositions.empty()) {
        Position top = mypositions.front();
        mypositions.pop_front();
        start_x = top.x;
        start_y = top.y;
        aux.x = start_x + 1;
        aux.y = start_y;
        reverseAux.x = aux.y;
        reverseAux.y = aux.x;
        reverseAux = game_map->normalize(reverseAux);
        aux.x = reverseAux.y;
        aux.y = reverseAux.x;
        if(LeeMap[aux.x][aux.y] == 0 && LeeMap[aux.x][aux.y] != -1) {
            mypositions.push_back(aux);
            LeeMap[aux.x][aux.y]= LeeMap[top.x][top.y] + 1;
        }
        aux.x = start_x - 1;
        aux.y = start_y;
        reverseAux.x = aux.y;
        reverseAux.y = aux.x;
        reverseAux = game_map->normalize(reverseAux);
        aux.x = reverseAux.y;
        aux.y = reverseAux.x;
        if(LeeMap[aux.x][aux.y] == 0 && LeeMap[aux.x][aux.y] != -1) {
            mypositions.push_back(aux);
            LeeMap[aux.x][aux.y]= LeeMap[top.x][top.y] + 1;
        }
        aux.x = start_x;
        aux.y = start_y + 1;
        reverseAux.x = aux.y;
        reverseAux.y = aux.x;
        reverseAux = game_map->normalize(reverseAux);
        aux.x = reverseAux.y;
        aux.y = reverseAux.x;
        if(LeeMap[aux.x][aux.y] == 0 && LeeMap[aux.x][aux.y] != -1) {
            mypositions.push_back(aux);
            LeeMap[aux.x][aux.y]= LeeMap[top.x][top.y] + 1;
        }
        aux.x = start_x;
        aux.y = start_y - 1;
        reverseAux.x = aux.y;
        reverseAux.y = aux.x;
        reverseAux = game_map->normalize(reverseAux);
        aux.x = reverseAux.y;
        aux.y = reverseAux.x;
        if(LeeMap[aux.x][aux.y] == 0 && LeeMap[aux.x][aux.y] != -1) {
            mypositions.push_back(aux);
            LeeMap[aux.x][aux.y]= LeeMap[top.x][top.y] + 1;
        }
    }
}

Direction makeDirections(int final_x, int final_y, int my_initial_value, int my_initial_round , unique_ptr<GameMap>& game_map) {
    Position aux;
    Position reverseAux;
    vector<Direction> aux_answer;


    while(my_initial_value > my_initial_round) {
        aux.x = final_x + 1;
        aux.y = final_y;
        reverseAux.x = aux.y;
        reverseAux.y = aux.x;
        reverseAux = game_map->normalize(reverseAux);
        aux.x = reverseAux.y;
        aux.y = reverseAux.x;
        int ok = 1;
        if(LeeMap[aux.x][aux.y] == (my_initial_value - 1) && ok) {
          final_x = aux.x;
          final_y = aux.y;
          aux_answer.push_back(Direction::NORTH);
          ok = 0;
        }
        aux.x = final_x - 1;
        aux.y = final_y;
        reverseAux.x = aux.y;
        reverseAux.y = aux.x;
        reverseAux = game_map->normalize(reverseAux);
        aux.x = reverseAux.y;
        aux.y = reverseAux.x;
        if(LeeMap[aux.x][aux.y] == (my_initial_value - 1) && ok) {
          final_x = aux.x;
          final_y = aux.y;
          aux_answer.push_back(Direction::SOUTH);
          ok = 0;
        }
        aux.x = final_x;
        aux.y = final_y + 1;
        reverseAux.x = aux.y;
        reverseAux.y = aux.x;
        reverseAux = game_map->normalize(reverseAux);
        aux.x = reverseAux.y;
        aux.y = reverseAux.x;
        if(LeeMap[aux.x][aux.y] == (my_initial_value - 1) && ok) {
          final_x = aux.x;
          final_y = aux.y;
          aux_answer.push_back(Direction::WEST);
          ok = 0;
        }
        aux.x = final_x;
        aux.y = final_y - 1;
        reverseAux.x = aux.y;
        reverseAux.y = aux.x;
        reverseAux = game_map->normalize(reverseAux);
        aux.x = reverseAux.y;
        aux.y = reverseAux.x;
        if(LeeMap[aux.x][aux.y] == (my_initial_value - 1) && ok) {
          final_x = aux.x;
          final_y = aux.y;
          aux_answer.push_back(Direction::EAST);
          ok = 0;
        }
        my_initial_value--;
    }
    myreset();
    for(int i = 0; i < aux_answer.size(); i++) {
      Direction thisDirection = aux_answer[i];
      if(thisDirection == Direction::NORTH) {
        log::log("North");
      }
      if(thisDirection == Direction::SOUTH) {
        log::log("South");
      }
      if(thisDirection == Direction::WEST) {
        log::log("West");
      }
      if(thisDirection == Direction::EAST) {
        log::log("East");
      }
      if(thisDirection == Direction::STILL) {
        log::log("Still");
      }
    }
    return aux_answer[aux_answer.size() - 1];
}

void setLeeMap(unique_ptr<GameMap>& game_map) {
  for(int i = 0; i < game_map->height; i++) {
    for(int j = 0; j < game_map->width; j++) {
      if(game_map->cells[i][j].is_occupied()) {
        LeeMap[i][j] = -1;
      } else {
        LeeMap[i][j] = 0;
      }
    }
  }
}

void afisare(unique_ptr<GameMap>& game_map) {
  for(int i = 0; i < game_map->height; i++) {
    string aux;
    for(int j = 0; j < game_map->width; j++) {
      if(LeeMap[i][j] < 10 && LeeMap[i][j] >= 0) {
        aux += "00";
      } else {
        if(LeeMap[i][j] < 100) {
          aux += "0";
        }
      }
      aux += to_string(LeeMap[i][j]);
      aux += " ";
    }
    log::log(aux);
  }
}

Direction giveDirection(unique_ptr<GameMap>& game_map, int round, Position final_position_chosed, shared_ptr<Ship> ship) {
  Position myship(ship->position.x, ship->position.y);
  myship = game_map->normalize(myship);
  final_position_chosed = game_map->normalize(final_position_chosed);
  if(auxShips[ship->id].hasToWait) {
    auxShips[ship->id].hasToWait = 0;
    return Direction::STILL;
  }

  Direction thisDirection;
  setLeeMap(game_map);
  LeeMap[myship.y][myship.x] = round ;
  Lee(myship.y,myship.x, round + 1, game_map);

  if(LeeMap[final_position_chosed.y][final_position_chosed.x] != 0 && LeeMap[final_position_chosed.y][final_position_chosed.x] != -1) {
    int aux_value = LeeMap[final_position_chosed.y][final_position_chosed.x];
    thisDirection = makeDirections(final_position_chosed.y, final_position_chosed.x, LeeMap[final_position_chosed.y][final_position_chosed.x],round , game_map);
  } else {
    thisDirection = game_map->naive_navigate(ship, final_position_chosed);
    if(thisDirection == Direction::STILL) {
      Position auxPos;
      auxPos.x = myship.x + 1;
      auxPos.y = myship.y;
      auxPos = game_map->normalize(auxPos);
      if(!game_map->cells[auxPos.y][auxPos.x].is_occupied()) {
        auxShips[ship->id].hasToWait = 1;
        thisDirection = Direction::EAST;
      }
      auxPos.x = myship.x - 1;
      auxPos.y = myship.y;
      auxPos = game_map->normalize(auxPos);

      if(!game_map->cells[auxPos.y][auxPos.x].is_occupied()) {
        auxShips[ship->id].hasToWait = 1;
        thisDirection = Direction::WEST;
      }
      auxPos.x = myship.x ;
      auxPos.y = myship.y + 1;
      auxPos = game_map->normalize(auxPos);

      if(!game_map->cells[auxPos.y][auxPos.x].is_occupied()) {
        auxShips[ship->id].hasToWait = 1;
        thisDirection = Direction::SOUTH;
      }
      auxPos.x = myship.x ;
      auxPos.y = myship.y - 1;
      auxPos = game_map->normalize(auxPos);
      if(!game_map->cells[auxPos.y][auxPos.x].is_occupied()) {
        auxShips[ship->id].hasToWait = 1;
        thisDirection = Direction::NORTH;
      }
    }
    myreset();
  }
  if(thisDirection == Direction::NORTH) {
    log::log("GOING NORTH");
  }
  if(thisDirection == Direction::SOUTH) {
    log::log("GOING SOUTH");
  }
  if(thisDirection == Direction::WEST) {
    log::log("GOING WEST");
  }
  if(thisDirection == Direction::EAST) {
    log::log("GOING EAST");
  }
  if(thisDirection == Direction::STILL) {
    log::log("GOING STILL");
  }
  return thisDirection;
}

bool checkIfOp(int is, int js, int iff, int jff, unique_ptr<GameMap>& game_map, shared_ptr<Player> me ) {
  int contor = 0;
  for(int i = is; i <= iff; i++) {
    for(int j = js; j <= jff; j++) {
      Position normalized_position;
      normalized_position.x = i;
      normalized_position.y = j;
      normalized_position = game_map->normalize(normalized_position);
      if(game_map->cells[normalized_position.x ][normalized_position.y].is_occupied()) {
        int ok = 1;
        for(const auto& ship_iterator : me->ships) {
            shared_ptr<Ship> ship = ship_iterator.second;
            if(ship->position.x == me->shipyard->position.x && ship->position.y == me->shipyard->position.y && auxShips[ship->id].goHomeForever == 0) {
              ok = 0;
            }
        }
        if(ok) {
          contor++;
        }
      }
    }
  }
  if(contor > 2 && contor < 6) {
    return 1;
  }
  return 0;
}

Position calculateMaximumHaliteCellinRange(unique_ptr<GameMap>& game_map, shared_ptr<Ship> ship, int radius, int round, shared_ptr<Player> me ) {
  double maxim = 0;
  Position final_position_chosed;
  myreset();
  Position myship;
  myship.y = ship->position.y;
  myship.x = ship->position.x;
//  myship = game_map->normalize(myship);
  Lee(myship.y , myship.x, 0, game_map);
  //afisare();
  log::log("Ship ID: " + to_string(ship->id));
  for(int i = 0; i < game_map->height; i++) {
    for(int j = 0; j < game_map->width; j++) {
      Position normalized_position1(i, j);
    //  normalized_position1 = game_map->normalize(normalized_position1);
      if(i == 16 && j == 16) {
        log::log(to_string(i) + " " + to_string(j) + " " + to_string(game_map->cells[i][j].halite));
      }
      if(game_map->calculate_distance(ship->position, normalized_position1) != 0) {
      //  log::log("Intru aici");
        double myhalite = (double) game_map->cells[i][j].halite;
        double mydistance = (double) LeeMap[i][j];
        if(i == 16 && j == 16) {
          log::log(to_string(mydistance));
          log::log(to_string((myhalite * myhalite)  / (mydistance * mydistance)));
          log::log(to_string(maxim));
        }
        if((myhalite * myhalite)  / (mydistance * mydistance)> maxim && myGlobalMap[i][j].alreadyGiven == 0 && mydistance != 0) {
          maxim =(myhalite * myhalite)  / (mydistance * mydistance);
          final_position_chosed.y = i;
          final_position_chosed.x = j;
          log::log("GameMapPos: " + to_string(i) + " " + to_string(j) + " Halite: " + to_string(game_map->cells[i][j].halite) + " Distance: " + to_string(mydistance));
        }
      }
    }
  }
  if(maxim == 0) {
    return calculateMaximumHaliteCellinRange(game_map, ship, radius + 1, round, me);
  } else {
    myGlobalMap[final_position_chosed.y][  final_position_chosed.x ].alreadyGiven = 1;
    myreset();
    return final_position_chosed;
  }
}

int chooseDirection(Direction random_direction, unique_ptr<GameMap>& game_map, vector<Command>& command_queue, shared_ptr<Ship> ship) {

  Position myship(ship->position.x, ship->position.y);
  myship = game_map->normalize(myship);
  if(random_direction == Direction::NORTH) {
    Position auxPos;
    auxPos.y = myship.y - 1;
    auxPos.x = myship.x;
    auxPos = game_map->normalize(auxPos);
    if(game_map->cells[auxPos.y][auxPos.x].is_occupied()) {
      log::log("north-still");
      command_queue.push_back(ship->stay_still());
      return 0;
    } else {
      log::log("just north");
      command_queue.push_back(ship->move(Direction::NORTH));
      game_map->cells[auxPos.y][auxPos.x].mark_unsafe(ship);
      game_map->cells[myship.y][myship.x].ship.reset();
      return 1;
    }
  }
  if(random_direction == Direction::SOUTH) {
    Position auxPos;
    auxPos.y = myship.y + 1;
    auxPos.x = myship.x;
    auxPos = game_map->normalize(auxPos);
    if(game_map->cells[auxPos.y][auxPos.x].is_occupied()) {
      log::log("south-still");
      command_queue.push_back(ship->stay_still());
      return 0;
    } else {
      log::log("just south");
      command_queue.push_back(ship->move(Direction::SOUTH));
      game_map->cells[auxPos.y][auxPos.x].mark_unsafe(ship);
      game_map->cells[myship.y][myship.x].ship.reset();
      return 1;
    }
  }
  if(random_direction == Direction::EAST) {
    Position auxPos;
    auxPos.y = myship.y;
    auxPos.x = myship.x + 1;
    auxPos = game_map->normalize(auxPos);
    if(game_map->cells[auxPos.y][auxPos.x].is_occupied()) {
      log::log("east-still");
      command_queue.push_back(ship->stay_still());
      return 0;
    } else {
      log::log("just east");
      command_queue.push_back(ship->move(Direction::EAST));
      game_map->cells[auxPos.y][auxPos.x].mark_unsafe(ship);
      game_map->cells[myship.y][myship.x].ship.reset();
      return 1;
    }
  }
  if(random_direction == Direction::WEST) {
    Position auxPos;
    auxPos.y = myship.y;
    auxPos.x = myship.x - 1;
    auxPos = game_map->normalize(auxPos);
    if(game_map->cells[auxPos.y][auxPos.x].is_occupied()) {
      log::log("west-still");
      command_queue.push_back(ship->stay_still());
      return 0;
    } else {
      log::log("just west");
      command_queue.push_back(ship->move(Direction::WEST));
      game_map->cells[auxPos.y][auxPos.x].mark_unsafe(ship);
      game_map->cells[myship.y][myship.x].ship.reset();
      return 1;
    }
  }
  if(random_direction == Direction::STILL) {
    log::log("just still");
    command_queue.push_back(ship->stay_still());
    return 1;
  }
}


int main(int argc, char* argv[]) {
    unsigned int rng_seed;
    if (argc > 1) {
        rng_seed = static_cast<unsigned int>(stoul(argv[1]));
    } else {
        rng_seed = static_cast<unsigned int>(time(nullptr));
    }
    mt19937 rng(rng_seed);

    Game game;
    GameMap *myGameMap = game.game_map.get();

    long long overallHalite = 0;

    for(int i = 0 ; i < myGameMap->height; i++) {
      for(int j = 0; j < myGameMap->width; j++) {
        overallHalite += myGameMap->cells[i][j].halite;
      }
    }
    long long cells = myGameMap->height * myGameMap->width;
    long long halitePerCell = overallHalite / cells + 1;
    long long boats = halitePerCell * (cells / 4 + 1);
    boats = boats / 4300;
    log::log(to_string(boats));
    // At this point "game" variable is populated with initial map data.
    // This is a good place to do computationally expensive start-up pre-processing.
    // As soon as you call "ready" function below, the 2 second per turn timer will start.
    game.ready("FFT");

    log::log("Successfully created bot! My Player ID is " + to_string(game.my_id) + ". Bot rng seed is " + to_string(rng_seed) + ".");
    for (;;) {
        game.update_frame();
        shared_ptr<Player> me = game.me;
        unique_ptr<GameMap>& game_map = game.game_map;
        vector<Command> command_queue;

        for(const auto& ship_iterator : me->ships) {
          shared_ptr<Ship> ship = ship_iterator.second;
          auto search = auxShips.find(ship->id);

          if(search == auxShips.end()) {
            auxiliarShipStruct auxShip;
            auxShip.id = ship->id;
            auxShips[ship->id] = auxShip;
          }
        }

        if(game_map->cells[me->shipyard->position.y][me->shipyard->position.x].is_occupied()) {
          int ok = 1;
          for(const auto& ship_iterator : me->ships) {
              shared_ptr<Ship> ship = ship_iterator.second;
              if(ship->position.x == me->shipyard->position.x && ship->position.y == me->shipyard->position.y && auxShips[ship->id].goHomeForever == 0) {
                ok = 0;
              }
          }
          if(ok) {
            game_map->cells[me->shipyard->position.y][me->shipyard->position.x].ship.reset();
          }
        }

        for(int i = 0; i < game_map->height; i++) {
          for(int j = 0; j < game_map->width; j++) {
            if(game_map->cells[i][j].is_occupied()) {
              int ok = 1;
              for(const auto& ship_iterator : me->ships) {
                  shared_ptr<Ship> ship = ship_iterator.second;
                  if(ship->position.x == j && ship->position.y == i) {
                    ok = 0;
                  }
              }
              if(ok) {
                game_map->cells[i][j].ship.reset();
              }
            }
          }
        }

        for(const auto& ship_iterator : me->ships) {
            shared_ptr<Ship> ship = ship_iterator.second;
            Position myship(ship->position.x, ship->position.y);
            Position myshipyard(me->shipyard->position.x, me->shipyard->position.y);
            myship = game_map->normalize(myship);
            myshipyard = game_map->normalize(myshipyard);

            myreset();
            LeeMap[myship.y][myship.x] = 0 ;
            Lee(myship.y, myship.x, 1, game_map);

            // se marcheaza momentul de intoarcere acasa pentru o barca
            if((LeeMap[myshipyard.y][myshipyard.x] + game.turn_number + LeeMap[myshipyard.y][myshipyard.x]* 16 / 10) >= constants::MAX_TURNS) {
              auxShips[ship->id].goHomeForever = 1;
              auxShips[ship->id].going_home = 0;
              auxShips[ship->id].going_to_a_cell = 0;
              anyoneGoingHomeForever = 1;
            }
            myreset();

            if(auxShips[ship->id].going_home == 0 && auxShips[ship->id].going_to_a_cell == 0 && auxShips[ship->id].goHomeForever == 0) {
              if((ship->halite > 750 && game_map->cells[ship->position.y][ship->position.x ].halite < 10) || (ship->halite > 900)) {
                if(ship->halite > 900) {
                      myGlobalMap[auxShips[ship->id].cell_assigned.y][auxShips[ship->id].cell_assigned.x].alreadyGiven = 0;
                }
                auxShips[ship->id].going_home = 1;
                Position myship(ship->position.x, ship->position.y);
                Position myshipyard(me->shipyard->position.x, me->shipyard->position.y);
                myship = game_map->normalize(myship);
                myshipyard = game_map->normalize(myshipyard);
                setLeeMap(game_map);
                LeeMap[myship.y][myship.x] = game.turn_number ;
                Lee(myship.y, myship.x, game.turn_number + 1, game_map);

                if(LeeMap[myshipyard.y][myshipyard.x] != 0 && LeeMap[myshipyard.y][myshipyard.x] != -1) {
                  auxShips[ship->id].toBeMade = makeDirections(myshipyard.y, myshipyard.x, LeeMap[myshipyard.y][myshipyard.x] ,game.turn_number , game_map);
                } else {
                  auxShips[ship->id].toBeMade = Direction::STILL;
                  myreset();
                }
                Direction random_direction = auxShips[ship->id].toBeMade;
                int ok = chooseDirection(random_direction, game_map, command_queue, ship);
              } else {
                if(game_map->cells[ship->position.y][ship->position.x ].halite < 10) {
                  auxShips[ship->id].going_to_a_cell = 1;
                  Position choice = calculateMaximumHaliteCellinRange(game_map, ship, 1, game.turn_number, me);
                  auxShips[ship->id].cell_assigned.x = choice.x;
                  auxShips[ship->id].cell_assigned.y = choice.y;
                  auxShips[ship->id].toBeMade = giveDirection(game_map, game.turn_number, choice, ship);
                  chooseDirection(auxShips[ship->id].toBeMade, game_map, command_queue, ship);
                } else {
                  game_map->cells[ship->position.y][ship->position.x].mark_unsafe(ship);
                  command_queue.push_back(ship->stay_still());
                }
              }
            } else {
              if((ship->halite < game_map->cells[ship->position.y][ship->position.x].halite / 10 || game_map->cells[ship->position.y][ship->position.x].halite >= 100) && (ship->halite < 900)) {
                command_queue.push_back(ship->stay_still());
                if(ship->halite + game_map->cells[ship->position.y][ship->position.x].halite / 10 > 600 && auxShips[ship->id].going_to_a_cell == 1 && auxShips[ship->id].goHomeForever == 0) {
                  auxShips[ship->id].going_to_a_cell = 0;
                  auxShips[ship->id].going_home = 1;
                  myGlobalMap[auxShips[ship->id].cell_assigned.y][auxShips[ship->id].cell_assigned.x].alreadyGiven = 0;
                }
              } else {
                if(auxShips[ship->id].going_to_a_cell && auxShips[ship->id].goHomeForever == 0) {
                  if(ship->position.x == auxShips[ship->id].cell_assigned.x && ship->position.y == auxShips[ship->id].cell_assigned.y) {
                    auxShips[ship->id].going_to_a_cell = 0;
                    command_queue.push_back(ship->stay_still());
                  } else {
                    auxShips[ship->id].toBeMade = giveDirection(game_map, game.turn_number, auxShips[ship->id].cell_assigned, ship);
                    chooseDirection(auxShips[ship->id].toBeMade, game_map, command_queue, ship);
                  }
                } else {
                  if(ship->position.x == me->shipyard->position.x && ship->position.y == me->shipyard->position.y) {
                    if(auxShips[ship->id].goHomeForever == 0) {
                      auxShips[ship->id].going_home = 0;
                      auxShips[ship->id].going_to_a_cell = 1;
                      Position choice = calculateMaximumHaliteCellinRange(game_map, ship, 1, game.turn_number, me);
                      auxShips[ship->id].cell_assigned.x = choice.x;
                      auxShips[ship->id].cell_assigned.y = choice.y;
                      auxShips[ship->id].toBeMade = giveDirection(game_map, game.turn_number, choice, ship);
                      chooseDirection(auxShips[ship->id].toBeMade, game_map, command_queue, ship);
                    }
                  } else {
                    Position myshipyard(me->shipyard->position.x, me->shipyard->position.y);
                    auxShips[ship->id].toBeMade = giveDirection(game_map, game.turn_number, myshipyard, ship);
                    chooseDirection(auxShips[ship->id].toBeMade, game_map, command_queue, ship);
                  }
                }
              }
            }
          }

        if(me->ships.size() < 22 &&  (constants::MAX_TURNS * 3 / 4 > game.turn_number ) && !game_map->cells[me->shipyard->position.y][me->shipyard->position.x].is_occupied() && me->halite > 1000 && anyoneGoingHomeForever == 0) {
          command_queue.push_back(me->shipyard->spawn());
          shared_ptr<Ship> ship;
          game_map->cells[me->shipyard->position.y][me->shipyard->position.x].mark_unsafe(ship);
          auxiliarShipStruct auxship;
          auxship.id = mycnt;
          mycnt++;
        }

        if (!game.end_turn(command_queue)) {
            break;
        }
    }
    return 0;
}
