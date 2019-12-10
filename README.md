# Chess

A C++ implementation of chess using the object orientated programming paradigm with a particular focus on inheritance.

### To run

Compile given test programme using `make` and then running the `chess.exe` that is created

Compile the more extensive test programme using `make test` and running the resulting `test.exe`

To interface with the game:
  1. #include"ChessBoard.h"
  2. Create a ChessBoard object (e.g. `ChessBoard cb = ChessBoard()`)
  3. Call submit move (e.g. `cb.submitMove("A2", "A3")`)
  4. Reset using `cb.resetBoard()`
  5. Can also output current state of the board to an ostream using `<<`

### Features

On submit move the successful move will be outputted to the command line or the rule of chess broken (see test programme)

Castling has been implemented

Check, stalemate and checkmate are all detected

### Sample Output

```console
A new chess game is started!
White's Pawn moves from E2 to E4
Black's Pawn moves from E7 to E5
White's Knight moves from G1 to F3
Black's Knight moves from B8 to C6
White's Knight moves from B1 to C3
Black's Knight moves from G8 to F6
White's Bishop moves from F1 to C4
Black's Pawn moves from D7 to D6
White's Knight moves from F3 to G5
Black's Bishop moves from C8 to G4
White's Bishop moves from C4 to F7 taking Black's Pawn
Black is in check
Black's King moves from E8 to E7
White's Knight moves from C3 to D5
Black is in check
Black's Knight moves from F6 to D5 taking White's Knight
White's Queen moves from D1 to G4 taking Black's Bishop
Black's Knight moves from D5 to F6
White's Queen moves from G4 to E6
Black is in checkmate
 ________________________
8|BR|  |  |BQ|  |BB|  |BR|
 ________________________
7|BP|BP|BP|  |BK|WB|BP|BP|
 ________________________
6|  |  |BH|BP|WQ|BH|  |  |
 ________________________
5|  |  |  |  |BP|  |WH|  |
 ________________________
4|  |  |  |  |WP|  |  |  |
 ________________________
3|  |  |  |  |  |  |  |  |
 ________________________
2|WP|WP|WP|WP|  |WP|WP|WP|
 ________________________
1|WR|  |WB|  |WK|  |  |WR|
  A  B  C  D  E  F  G  H
```


### Future Development

Implement en passant and pawn promotion

Create a GUI to make the game human playable

Add a computer player
