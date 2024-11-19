#pragma once

#include "Board.h"
#include "Utils/rawalloc.h"

namespace Nonogram
{
	class BoardSolver
	{
	public:
		BoardSolver(const Board& board);
		BoardSolver(Board&& board);

		BoardSolver(const BoardSolver& solver) = delete;

		bool solve();

	private:
		Board m_Board = rawalloc<Board, false>().val();
	};
}
