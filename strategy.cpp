//function utility(board, last_slot, slot, depth) {

//    // utility() could use the argument "board" to
//    // give move value to slots that cause the *next*
//    // move to loose the game, that is, by forcing the
//    // other player into a move in a sub-board with
//    // 2-in-a-row or something.  Not implemented as yet.

//    var wn = false;  // Did this move cause a win?
//    var score = 0;
//    // return value is [score, wn]

//    var offset = last_slot * 10;

//    for (var idx in WINNING_TRIADS_BY_SLOT[slot]) {
//        var triad = WINNING_TRIADS_BY_SLOT[slot][idx];

//        triad_sum = board[triad[0] + offset]
//                + board[triad[1] + offset] + board[triad[2] + offset];

//        switch (triad_sum) {
//        case  3:
//        case -3:
//            score = board[triad[0]+offset] * VERY_LARGE - depth;
//            wn = true;
//            break;
//        case  2:
//            score += 3000;  // Two in a triad, next move wins for maximizer
//            break;
//        case -2:
//            score -= 3000;  // Two in a triad, next move wins for minimizer
//            break;
//            // 1, -1: could be a single mark, or could be a block.
//            // triad_sum contains -1 if -1 got blocked, 1 if 1 got blocked.
//            // Bitwise-and lets us distinguish between a single mark, and
//            // a two-X, one-O type of position.
//        case  1:
//        case -1:
//            if ((board[triad[0] + offset]
//                 & board[triad[1] + offset]
//                 & board[triad[2] + offset]) != 0) {
//                score -=  triad_sum * 1000;  // blocks a win
//            }
//            break;
//        case  0:  // One of each mark, since player marked slot
//            // Give a point just for monkeying with the other guy.
//            score += board[offset + slot];
//            break;
//        default:
//            break;
//        }
//        if (wn) break;
//    }

//    if (!wn) {
//        // Give it a general preference for middles and
//        // slightly lesser preference for corners, but only
//        // in non-winning positions.
//        // This score has more influence in start game (before all 9 subboards
//        // have a mark) and mid-game (at least 1 mark in all 9 subboards, but
//        // before any subboards have 2-in-a-row).
//        var move = offset + slot;
//        bonus = 7*MIDDLES[move] +  2*CORNERS[move];
//        score += board[move]*bonus;

//        // You could use the value of "slot" to look at the sub-board in
//        // which the next move takes place.  Check for allowing opponent to win
//        // in that sub-board, or to get 2-in-a-row, or to block 2-in-a-row.
//        // Unimplemented.
//    }
//    return [score, wn];
//}









//void TicTacToe::utility(std::vector<int>& board,int currentGrid,int move,int depth){

//        bool win = false;

//        int triad_sum = 0;
//        int score = 0;



//        //for(int i=0; i<9; i++){


//        for(int j=0; j<8; j++){

//            triad_sum = boards[currentGrid][WINNING_TRIADS[j][0]] + boards[currentGrid][WINNING_TRIADS[j][1]] + boards[currentGrid][WINNING_TRIADS[j][2]];


//            switch(triad_sum){

//            case 3:
//            case -3:
//                win = 1;
//                score = boards[currentGrid][WINNING_TRIADS[j][0]] * VERY_LARGE - depth;
//                break;
//            case 2:{
//                score += 3000;
//                qDebug() << "move: " << move << " currentBoard: " << currentGrid;
//                break;
//            }
//            case -2:
//                score -=3000;
//                break;
//            case 1:
//            case -1:{
//                if((boards[currentGrid][WINNING_TRIADS[j][0]] & boards[currentGrid][WINNING_TRIADS[j][1]] & boards[currentGrid][WINNING_TRIADS[j][2]]) != 0){
//                    score -= triad_sum * 1000;}
//                break;
//            }
//            case 0:
//                score += boards[currentGrid][move];
//            default:
//                break;
//            }

//            if(win){
//                break;
//            }

//        }

//        if(!win){


//            if(move == 0 || move == 2 || move == 6 || move == 8)
//                score += 2;
//            else if(move == 4)
//                score += 7;


//        }


//        rets[0] = score;
//        rets[1] = win;

//    }
