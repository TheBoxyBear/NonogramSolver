#include "BoardSolver.h"

#include "Board.h"

#include <stdexcept>
#include <vector>

using namespace Nonogram;

BoardSolver::BoardSolver(const Board& board)
{
	if (!board.validateClues())
		throw std::invalid_argument("Board has invalid clues.");

	m_Board = board;
}

BoardSolver::BoardSolver(Board&& board)
{
	if (!m_Board.validateClues())
		throw std::invalid_argument("Board has invalid clues.");

	m_Board = std::move(board);
}

bool BoardSolver::solve()
{
	bool solveHorizontal = true;

	std::vector<Board::Clue>* clues = nullptr;
	size_t count = 0, dimSize = 0;

	auto getCell = [&count, &dimSize](Board::CellState* cells, int a, int b) -> Board::CellState&
	{
		return cells[a * dimSize + b];
	};
	auto setSolveMode = [this, &clues, &count, &dimSize, &solveHorizontal](bool horizontal)
	{
		solveHorizontal = horizontal;

		if (horizontal)
		{
			clues = m_Board.m_RowClues;
			count = m_Board.height();
			dimSize = m_Board.width();
		}
		else
		{
			clues = m_Board.m_ColClues;
			count = m_Board.width();
			dimSize = m_Board.height();
		}
	};
	auto solveLine = [this, &getCell, &clues, &count, &dimSize](int lineIndex)
	{
		std::vector<Board::Clue>::const_iterator currentClue = clues[lineIndex].cbegin();
		size_t currentClueTotal = 0;
		for (int cellIndex = 0; cellIndex < dimSize; cellIndex++)
			switch (getCell(m_Board.m_Cells, lineIndex, cellIndex))
			{
				case Board::CellState::EMPTY:
				{
					// Inefficient copies.
					// Clues remain the same so only the cells need copying
					BoardSolver recursiveSolver(m_Board);
					getCell(recursiveSolver.m_Board.m_Cells, lineIndex, cellIndex) = Board::CellState::CROSS;

					if (recursiveSolver.solve())
						return true;

					// Reuse the allocations from this
					getCell(m_Board.m_Cells, lineIndex, cellIndex) = Board::CellState::CROSS;
					return solve();
				}
				case Board::CellState::FILL:
					// Fill after the last clue or exceeded current clue length
					if (currentClue == clues[lineIndex].cend() ||
						currentClueTotal++ > *currentClue)
						return false;
					break;
				case Board::CellState::CROSS:
					// The previous cell was the end of a clue - Move to the next clue
					if (currentClueTotal)
					{
						// Line full with no gaps
						// Verify the length matches the clue
						if (currentClueTotal < *currentClue)
							return false;
						currentClue++;
						currentClueTotal = 0;
					}
					break;
			}

		// Line invalid if there are clues remaining
		return currentClue == clues[lineIndex].cend();
	};

	setSolveMode(true);

	for (int y = 0; y < m_Board.height(); y++)
		if (!solveLine(y))
			return false;

	setSolveMode(false);

	for (int x = 0; x < m_Board.width(); x++)
		if (!solveLine(x))
			return false;

	return true;
}
