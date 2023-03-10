#include "BitcoinExchange.hpp"
#include <fstream>
#include <ios>
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
  loadDatabase();
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

void BitcoinExchange::loadFileEntry(std::string const &line,
                                    std::string const &separator) {
  std::string::size_type index;
  std::istringstream stream;
  std::string date;
  std::string valueText;
  double value;

  index = line.find(separator);
  if (index == std::string::npos)
    throw std::invalid_argument("BitcoinExchange entry miss colon " + line);

  date = line.substr(0, index);
  valueText = line.substr(index + 1);
  stream = std::istringstream(valueText);
  stream >> std::noskipws >> value;
  if (stream.rdstate() ^ stream.eofbit || stream.rdstate() & stream.failbit)
    throw std::invalid_argument("BitcoinExchange invalid value " + line);

  _db[date] = value;
};

void BitcoinExchange::loadDatabase(void) {
  std::ifstream database(_dbname);
  std::string line;

  if (database.rdstate() & database.failbit)
    throw std::invalid_argument("BitcoinExchange was given inexistent DB");
  std::getline(database, line);
  for (; std::getline(database, line);)
    loadFileEntry(line);
};
