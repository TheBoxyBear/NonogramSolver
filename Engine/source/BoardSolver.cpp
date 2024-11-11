#include "BoardSolver.h"

#include "Board.h"

#include <stdexcept>
#include <vector>

using namespace Nonogram;

BoardSolver::BoardSolver(Board& board)
	: m_Board(board)
{
	if (!board.validateClues())
		throw std::invalid_argument("Board has invalid clues.");
}

bool BoardSolver::validateBoardState() const noexcept
{
	static auto validateDimension = [this](
		std::vector<Board::Clue>* clues, size_t count, size_t dimSize)
	{
		auto getCell = [this, clues, dimSize](int a, int b)
		{
			return m_Board.m_Cells[a * dimSize + b];
		};

		for (int lineIndex = 0; lineIndex < count; lineIndex++)
		{
			std::vector<Board::Clue>::const_iterator currentClue = clues[lineIndex].cbegin();
			size_t currentClueTotal = 0;

			for (int cellIndex = 0; cellIndex < dimSize; cellIndex++)
				switch (getCell(lineIndex, cellIndex))
				{
					case Board::CellState::EMPTY:
						// Could be considered incoherent by considering partially resolved clues
						// Ignored for now, only impacts performance
						return true;
					case Board::CellState::FILL:
						if (currentClue == clues[lineIndex].cend() ||
							currentClueTotal++ > *currentClue)
							return false;
						break;
					case Board::CellState::CROSS:
						// If the previous cell was filled - Move to the next clue
						if (currentClueTotal)
						{
							// Check line incomplete
							if (currentClueTotal < *currentClue)
								return false;

							currentClue++;
							currentClueTotal = 0;
						}
						break;
				}
		}

		return true;
	};

	return true;
}
