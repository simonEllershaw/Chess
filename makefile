OBJ = Player.o Helper.o Piece.o ChessBoard.o Position.o MoveVector.o\
			Rook.o Bishop.o Queen.o King.o Knight.o Pawn.o
MAINOBJ = ChessMain.o
TESTOBJ = Test.o

TESTEXE = test
EXE = chess
CXX = g++
CXXFLAGS = -Wall -g -Wextra -MMD

$(EXE): $(OBJ) $(MAINOBJ)
	$(CXX) $^ -o $@

$(TESTEXE): $(OBJ) $(TESTOBJ)
	$(CXX) $^ -o $@

%.o:%.cpp makefile
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJ:.o=.d)

clean:
	rm -f *.exe *.o *.d

.PHONY: clean
