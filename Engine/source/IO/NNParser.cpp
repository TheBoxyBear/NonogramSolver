#include "IO/NNParser.h"

#include "Board.h"

#include <filesystem>
#include <fstream>
#include <string>

using namespace Nonogram;
using namespace Nonogram::IO;

void NNParser::Parse(const std::filesystem::path& path, rawalloc<Board>& out)
{
	enum DataRegion
	{
		META,
		ROWS,
		COLS
	};

	std::string line;
	std::fstream stream(path.c_str(), std::ios::in);

	DataRegion region = META;

	size_t
		width  = 0,
		height = 0;

	while (std::getline(stream, line))
	{
		std::stringstream lineStream(line);

		switch (region)
		{
			case ROWS:

				break;
			case COLS:
				break;
			case META:
				if (line == "width")
					lineStream >> width;
				else if (line == "height")
					lineStream >> height;
				else if (line == "rows")
					region = ROWS;
				else if (line == "columns")
					region = COLS;
				break;
		}

		out = Board(width, height);
	}
}

void NNParser::Serialize(const Board& board, const std::filesystem::path& path)
{

}
