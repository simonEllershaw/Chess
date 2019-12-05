OBJ = Helper.o Piece.o ChessBoard.o Position.o MoveVector.o\
			Rook.o Bishop.o Queen.o King.o Knight.o Pawn.o Test.o Player.o

EXE = chess
CXX = g++
CXXFLAGS = -Wall -g -Wextra -MMD

$(EXE): $(OBJ)
	$(CXX) $^ -o $@

%.o:%.cpp makefile
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJ:.o=.d)

clean:
	rm -f $(OBJ) $(EXE) $(OBJ:.o=.d)

.PHONY: clean
