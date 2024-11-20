#pragma once

#include <vector>

namespace Nonogram
{
	class Board final
	{
	public:
		using Clue = unsigned char;

		enum class CellState
		{
			EMPTY,
			FILL,
			CROSS
		};

		Board(size_t width, size_t height);
		Board(const Board& board);
		Board(Board&& board) noexcept;

		Board& operator=(const Board& board);
		Board& operator=(Board&& board) noexcept;

		~Board() noexcept;

		size_t width()  const noexcept;
		size_t height() const noexcept;
		size_t size()   const noexcept;

		CellState& operator()(int x, int y);
		const CellState& operator()(int x, int y) const;

		std::vector<Clue>& rowClues(int y);
		const std::vector<Clue>& rowClues(int y) const;

		std::vector<Clue>& colClues(int x);
		const std::vector<Clue>& colClues(int x) const;

		bool validateClues() const noexcept;

		friend class BoardSolver;

	private:
		size_t m_Width, m_Height;
		CellState* m_Cells;

		std::vector<Clue> *m_RowClues, *m_ColClues;
	};
}
