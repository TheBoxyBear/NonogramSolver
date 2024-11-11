#include <NonogramEngine/Board.h>
#include <NonogramEngine/IO/NNParser.h>
#include <NonogramEngine/Utils/rawalloc.h>

#include <iostream>
#include <type_traits>
#include <vector>

using namespace Nonogram;
using namespace Nonogram::IO;

int main()
{
	rawalloc<Board> b;

	Board bb(std::move(b.val()));

	Board board(5, 5);

	board.rowClues(0).push_back(5);
	board.rowClues(1).push_back(2);
	board.rowClues(2).push_back(2);
	board.rowClues(3).push_back(2);
	board.rowClues(4).push_back(2);

	board.colClues(0).push_back(1);
	board.colClues(1).push_back(1);
	board.colClues(1).push_back(1);
	board.colClues(2).push_back(1);
	board.colClues(2).push_back(3);
	board.colClues(3).push_back(3);
	board.colClues(3).push_back(1);
	board.colClues(4).push_back(2);

	std::cout << board.validateClues();

	return 0;
}
