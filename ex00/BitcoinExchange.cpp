#include "BitcoinExchange.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

BitcoinExchange::BitcoinExchange(void) : _filename(""), _dbname("data.csv"){};
BitcoinExchange::BitcoinExchange(BitcoinExchange const &copy)
    : _filename(copy._filename), _dbname(copy._dbname){};
BitcoinExchange::BitcoinExchange(std::string const filename,
                                 std::string const dbname)
    : _filename(filename), _dbname(dbname) {
  if (!isValidDbname())
    throw std::invalid_argument("BitcoinExchange was given an invalid DB name");
  loadFile(&BitcoinExchange::processDbEntry, _dbname, ",");
};
BitcoinExchange::~BitcoinExchange(void){};

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &copy) {
  _filename = copy._filename;
  return *this;
};

BitcoinExchange::db_type::const_iterator const
BitcoinExchange::begin(void) const {
  return _db.cbegin();
};

BitcoinExchange::db_type::const_iterator const
BitcoinExchange::end(void) const {
  return _db.cend();
};

bool BitcoinExchange::isValidDbname(void) const {
  std::string::size_type delimiter_position;
  std::string extension;

  delimiter_position = _dbname.rfind(".");
  if (delimiter_position == std::string::npos)
    return false;
  extension = _dbname.substr(delimiter_position);
  if (extension != ".csv")
    return false;
  return true;
};

void BitcoinExchange::processDbEntry(entry_type const &entry) {
  _db[entry.first] = entry.second;
};

void BitcoinExchange::processInputEntry(entry_type const &entry){};

void BitcoinExchange::loadFile(line_processor callback, std::string const &name,
                               std::string const &separator) {
  entry_type currentEntry;
  std::ifstream file(name);
  std::string line;

  if (file.rdstate() & file.failbit)
    throw std::invalid_argument("BitcoinExchange was given inexistent " + name);
  std::getline(file, line);
  for (; std::getline(file, line);) {
    currentEntry = loadFileEntry(line, separator);
    (this->*callback)(currentEntry);
  }
  file.close();
};

BitcoinExchange::entry_type
BitcoinExchange::loadFileEntry(std::string const &line,
                               std::string const &separator) const {
  std::string::size_type index;
  std::istringstream stream;
  std::string date;
  std::string valueText;
  double value;

  index = line.find(separator);
  if (index == std::string::npos)
    throw std::invalid_argument("BitcoinExchange entry miss separator " + line);

  date = line.substr(0, index);
  valueText = line.substr(index + 1);
  stream = std::istringstream(valueText);
  stream >> std::noskipws >> value;
  if (stream.rdstate() ^ stream.eofbit || stream.rdstate() & stream.failbit)
    throw std::invalid_argument("BitcoinExchange invalid value " + line);
  return std::make_pair(date, value);
};
