/* Copyright © Artur Maziarek MMXXI
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */
#include <FileSource.hpp>

FileSource::FileSource(std::string fileName, size_t lineChunkSize, int chunks) :
  fileName{fileName},
  lineChunkSize{lineChunkSize},
  chunks{chunks},
  isParsingSizeLimited{false},
  isBufferEmpty{false, false},
  isbufferEmptyIterator{0}
{
  if (chunks != 0)
  {
    isParsingSizeLimited = true;
  }
  file.open(fileName, std::ifstream::in);
  advance();
}

std::vector<std::string> FileSource::getData()
{
  return std::move(lineChunk);
}

bool FileSource::isEmpty() const
{
  return isBufferEmpty[isbufferEmptyIterator & 1];
}

void FileSource::advance()
{
  std::string line;
  for (size_t i = 0; (i < lineChunkSize) && std::getline(file, line, '\n'); i++)
  {
    lineChunk.push_back(std::move(line));
  }
  chunks--;

  bool isEndOfFile = file.eof();
  bool areChunksOver = (isParsingSizeLimited && (chunks <= 0));
  isBufferEmpty[(isbufferEmptyIterator++) & 1] = isEndOfFile || areChunksOver;
}
