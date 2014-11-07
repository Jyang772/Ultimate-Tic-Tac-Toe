#include "montebot.h"


void MonteBot::play(Game &game){
  double bestScore = -10000;
  Clone bestMove;

  for(unsigned int i=0; i<this->clones.size();i++){

    int penalty = 1;
    Clone& clone = this->clones[i];

    // Debugging. Figured out that invalid clones generated here
    // for(auto iter = this->clones.begin(); iter != this->clones.end(); iter++){
    //   if(game.currentBoard){
    //     if(iter->boardRow != game.currentBoard->row){
    //       std::cout << "Row assertion failed " << std::endl;
    //       exit(1);
    //     }

    //     if(iter->boardCol != game.currentBoard->col){
    //       std::cout << "Col assertion failed " << std::endl;
    //       exit(1);
    //     }
    //   }
    // }

    if(!clone.clone.currentBoard){
      penalty = 30;
    }

    double score = (clone.weightedWins-clone.weightedLosses*penalty) / (clone.wins + clone.losses + clone.ties); // r: The result of operation is double

    if(score > bestScore){
      bestScore = score;
      bestMove = clone;

      // Debugging best score
      // std::cout << __PRETTY_FUNCTION__ << ": Best score set to : " << bestScore << " for move " <<
      //   bestMove.boardRow << bestMove.boardCol << bestMove.cellRow << bestMove.cellCol<< std::endl;
    }
  }



  game.playCell(bestMove.boardRow, bestMove.boardCol, bestMove.cellRow, bestMove.cellCol);
}

void MonteBot::startCalculation(Game &game){
  std::cout << "MonteBotStartCalculation" << std::endl;

  Move move;
  std::vector<Move> validMoves = game.getValidMoves();
  std::cout << "validMoves.length(): " << validMoves.size() << std::endl;

  // Checking whether all valid moves are really valid
  for(auto iter = validMoves.begin(); iter != validMoves.end(); iter++){
    if(game.currentBoard){
      if(iter->bRow != game.currentBoard->row){
        std::cout << __FUNCTION__ << "Row assertion failed " << std::endl;
        exit(1);
      }
      if(iter->bCol != game.currentBoard->col){
        std::cout << __FUNCTION__ << "Col assertion failed " << std::endl;
        exit(1);
      }
    }
  }

  this->clones.clear();

  for(unsigned int i=0; i<validMoves.size();i++){
    move = validMoves[i];

    // clone = new Game(game); // r: No need for "new" here

    Game gameClone(game);

    gameClone.playCellSilently(move.bRow,move.bCol,move.cRow,move.cCol);

    if(game.currentBoard){
      if(move.bRow != game.currentBoard->row){
        std::cout << __FUNCTION__ << ": Move row assertion failed " << std::endl;
        exit(1);
      }
      if(move.bCol != game.currentBoard->col){
        std::cout << __FUNCTION__ << ": Move col assertion failed " << std::endl;
        exit(1);
      }
    }

    this->clones.push_back(Clone(move.bRow, move.bCol,move.cRow,move.cCol, gameClone, 0,0,0,0));

    if(game.currentBoard){
      if(this->clones.back().boardRow != game.currentBoard->row){
        std::cout << __FUNCTION__ << ": Clone row assertion failed " << std::endl;
        exit(1);
      }
      if(this->clones.back().boardCol != move.bCol){
        std::cout << __FUNCTION__ << ": Clone col assertion failed " << std::endl;
        exit(1);
      }
    }
  }
}

int MonteBot::playOutHidden(Game& game){
  while(!game.finished){
    Move move = getRandomValidMove(game);
    game.playCellSilently(move.bRow,move.bCol,move.cRow,move.cCol);
  }

  return game.winner;
}

Move MonteBot::getRandomValidMove(Game &game){
  std::vector<Move> moves = game.getValidMoves();

  for(auto iter = moves.begin(); iter != moves.end(); iter++){
    if(game.currentBoard){
      if(iter->bRow != game.currentBoard->row){
        std::cout << "Row assertion failed " << std::endl;
        exit(1);
      }
      if(iter->bCol != game.currentBoard->col){
        std::cout << "Col assertion failed " << std::endl;
        exit(1);
      }
    }
  }

  int moveNum = std::rand() % moves.size();

  return moves[moveNum];
}


void MonteBot::calculateAhead(Game &game){

  // std::cout << "MonteBotCalculateAhead" << std::endl; // r:
  std::cout << "----- " << __PRETTY_FUNCTION__ << std::endl;

  for(unsigned int i=0; i<clones.size();i++){
    Clone& move = clones[i];

    //Game *simGame = new Game(move.clone);

    Game simGame(move.clone);
    int winner = this->playOutHidden(simGame);

    double weight = 1;

    if(monteWeightByGameLength){
      //number of moves it took for sim to finish
      double f = simGame.countFilled - game.countFilled;
      //number of moves remaining in game
      double r = 81 - game.countFilled;
      //add a weight such that if the game
      //finishes in 0 moves the weight is 1, if
      //it drags out until the end then it is
      //worth only 1/# moves till the end and
      //anything in between is inversely
      //proportional to the number of moves it
      //takes.
      weight = (r - f) / r;
      //debug(f,r,weight);
    }

    if (winner == 0) {
      move.ties += 1;
    } else
      if(winner == game.currentPlayer){
        move.wins += 1;
        move.weightedWins += 1*weight;
      }  else {
        move.losses +=1;
        move.weightedLosses += 1* weight;
      }
  }
}
