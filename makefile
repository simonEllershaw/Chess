OBJ = Rook.o Helper.o Piece.o ChessBoard.o Test.o Position.o

EXE = chess
CXX = g++
CXXFLAGS = -g #-Wall -g -Wextra -MMD

$(EXE): $(OBJ)
	$(CXX) $^ -o $@

%.o:%.cpp makefile
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJ:.o=.d)

clean:
	rm -f $(OBJ) $(EXE) $(OBJ:.o=.d)

.PHONY: clean