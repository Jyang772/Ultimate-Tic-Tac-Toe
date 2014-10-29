//for(int j=0; j<8; j++){

//    triad_sum = boards[currentGrid][WINNING_TRIADS[j][0]] + boards[currentGrid][WINNING_TRIADS[j][1]] + boards[currentGrid][WINNING_TRIADS[j][2]];
//    qDebug() << "triad_sum: " << triad_sum;


//    switch(triad_sum){

//    case 3:
//    case -3:
//    {
//        win = 1;
//        score = boards[currentGrid][WINNING_TRIADS[j][0]] * VERY_LARGE - depth;
//        qDebug() << "MOVE__: " << move << endl;
//        break;
//    }
//    case 2:{
//        score += 3000;
//        break;
//    }
//    case -2:
//        score -=3000;
//        break;
//    case 1:
//    case -1:{
//        if((boards[currentGrid][WINNING_TRIADS[j][0]] & boards[currentGrid][WINNING_TRIADS[j][1]] & boards[currentGrid][WINNING_TRIADS[j][2]]) != 0){
//            score -= triad_sum * 1000;
//        }            break;
//    }
//    case 0:{
//        score += boards[currentGrid][move];
//    }
//    default:
//        break;
//    }

//    if(win){
//        break;
//    }
//}


//qDebug() << "RRScore: " << score;

//if(!win){

//    //Corners:
////        int bonus = 2*(boards[currentGrid][0] + boards[currentGrid][2] + boards[currentGrid][6] + boards[currentGrid][8]);
////        if(boards[currentGrid][4] == EMPTY)
////        bonus += 7*(boards[currentGrid][4]);

////        score += boards[currentGrid][move] * bonus;
//    qDebug() << "RScore: " << score;
//    int bonus = 0;
//    if(move == 0 || move == 2 || move == 6 || move == 8){
//        bonus += 2*boards[currentGrid][move];
//    }
//    if(move == 4){
//        bonus += 7*boards[currentGrid][move];
//    }

//    qDebug() << "Bonus: " << bonus;
//    qDebug() << "Slot: " << move;
//    qDebug() << "Move: " << currentGrid;
//    qDebug() << "board[move]: " << boards[currentGrid][move];
//    score += boards[currentGrid][move]*bonus;
//    qDebug() << "RScore: " << score;
//}


//rets[0] = score;
//rets[1] = win;

//}


//ACHIEVEMENT
//int numElements = BY_SLOT[move][0];

//for(int i=1; i<=numElements; i++){

//    for(int j=0; j<numElements; j++){
//    triad_sum += boards[currentGrid][WINNING_TRIADS[BY_SLOT[move][i]][j]];
//    }
//    qDebug() << "i: " << i;
//    qDebug() << "triad_sum: " << triad_sum;
//    triad_sum = 0;
//}
