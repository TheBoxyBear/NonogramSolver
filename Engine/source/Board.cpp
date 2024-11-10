#include "Board.h"

#include <cstring>
#include <functional>
#include <stdexcept>
#include <type_traits>
#include <vector>

using namespace Nonogram;

NonogramBoard::NonogramBoard(size_t width, size_t height) :
	m_Width(width), m_Height(height)
{
	if (!size())
		throw std::invalid_argument("Board size must be at least 1x1.");

	m_Cells    = new CellState[size()];
	m_RowClues = new std::vector<Clue>(height);
	m_ColClues = new std::vector<Clue>(width);
}

NonogramBoard::NonogramBoard(const NonogramBoard& board) :
	m_Width(board.m_Width), m_Height(board.m_Height)
{
	m_Cells = new CellState[size()];
	memcpy(m_Cells, board.m_Cells, size() * sizeof(Clue));

	m_RowClues = new std::vector<Clue>(m_Height);
	m_ColClues = new std::vector<Clue>(m_Width);

	for (int y = 0; y < m_Height; y++)
		m_RowClues[y] = board.m_RowClues[y];
	for (int x = 0; x < m_Width; x++)
		m_ColClues[x] = board.m_ColClues[x];
}

NonogramBoard::NonogramBoard(NonogramBoard&& board) noexcept :
	m_Width(board.m_Width), m_Height(board.m_Height),
	m_Cells(board.m_Cells), m_RowClues(board.m_RowClues), m_ColClues(board.m_ColClues)
{
	board.m_Cells = nullptr;
	board.m_RowClues = nullptr;
	board.m_ColClues = nullptr;
}

NonogramBoard& NonogramBoard::operator=(const NonogramBoard& board)
{
	new (this) NonogramBoard(board);
	return *this;
}

NonogramBoard& NonogramBoard::operator=(NonogramBoard&& board) noexcept
{
	if (this == &board)
		return;

	this->~NonogramBoard();

	new (this) NonogramBoard(std::move(board));
	return *this;
}

NonogramBoard::~NonogramBoard()
{
	if (m_Cells)
		delete[] m_Cells;
	if (m_RowClues)
		delete[] m_RowClues;
	if (m_ColClues)
		delete[] m_ColClues;
}

size_t NonogramBoard::width() const noexcept
{
	return m_Width;
}

size_t NonogramBoard::height() const noexcept
{
	return m_Height;
}

size_t NonogramBoard::size() const noexcept
{
	return m_Width * m_Height;
}

NonogramBoard::CellState& NonogramBoard::operator()(int x, int y)
{
	return m_Cells[y * m_Width + x];
}

const NonogramBoard::CellState& NonogramBoard::operator()(int x, int y) const
{
	return const_cast<NonogramBoard*>(this)->operator()(x, y);
}

std::vector<NonogramBoard::Clue>& NonogramBoard::rowClues(int y)
{
	return m_RowClues[y];
}

const std::vector<NonogramBoard::Clue>& NonogramBoard::rowClues(int y) const
{
	return m_RowClues[y];
}

std::vector<NonogramBoard::Clue>& NonogramBoard::colClues(int x)
{
	return m_ColClues[x];
}

const std::vector<NonogramBoard::Clue>& NonogramBoard::colClues(int x) const
{
	return m_ColClues[x];
}

bool NonogramBoard::validateCluesValid() const noexcept
{
	static auto validateDimension = [](std::vector<Clue>* clues, size_t count, size_t dimSize)
	{
		for (int i = 0; i < count; i++)
			if (clues[i].size())
			{
				// Total from clues - Account for crosses between each clue
				unsigned int total = clues[i].size() - 1;

				for (Clue& clue : clues[i])
				{
					if (clue == 0)
						return false;

					total += clue;
				}

				if (total > dimSize)
					return false;
			}

		return true;
	};

	return
		validateDimension(m_RowClues, m_Height, m_Width) &&
		validateDimension(m_ColClues, m_Width, m_Height);
}
