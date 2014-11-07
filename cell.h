#ifndef CELL_H
#define CELL_H

class Cell{
public:
  Cell();
  Cell(int row, int col);
  Cell(const Cell& other);

  bool operator==(const Cell&) const;
  bool operator!=(const Cell&) const;

  const Cell& clone();

  void setWinner(int winner);
  void playCell(int newOwner);
  int row = -1;
  int col = -1;
  int owner = 0;
  int winner = 0;
};


#endif // CELL_H
