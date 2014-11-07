#ifndef MOVE_H
#define MOVE_H


struct Move{
    Move(){}
    Move(int bRow,int bCol,int cRow,int cCol){
        this->bRow = bRow;
        this->bCol = bCol;
        this->cRow = cRow;
        this->cCol = cCol;
    }

    int bRow;
    int bCol;
    int cRow;
    int cCol;
};

#endif // MOVE_H
