#include "BitcoinExchange.hpp"
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

BitcoinExchange::BitcoinExchange(void){};
BitcoinExchange::BitcoinExchange(BitcoinExchange const &copy) : _db(copy._db){};
BitcoinExchange::BitcoinExchange(std::string const dbname) {
  if (!isValidDbname(dbname))
    throw std::invalid_argument("BitcoinExchange was given an invalid DB name");
  loadFile(&BitcoinExchange::processDbEntry, dbname, ",");
};
BitcoinExchange::~BitcoinExchange(void){};

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &copy) {
  _db = copy._db;
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

void BitcoinExchange::processInputFile(std::string const filename) {
  loadFile(&BitcoinExchange::processInputEntry, filename, " | ");
};

bool BitcoinExchange::isValidDbname(std::string const &dbname) const {
  std::string::size_type delimiter_position;
  std::string extension;

  delimiter_position = dbname.rfind(".");
  if (delimiter_position == std::string::npos)
    return false;
  extension = dbname.substr(delimiter_position);
  if (extension != ".csv")
    return false;
  return true;
};

bool BitcoinExchange::isValidDate(std::string const &date) const {
  struct std::tm tmp;

  if (!strptime(date.c_str(), "%Y-%m-%d", &tmp))
    return false;
  return true;
};

void BitcoinExchange::processDbEntry(entry_type const &entry) {
  if (!isValidDate(entry.first))
    throw std::invalid_argument("BitcoinExchange invalid date on DB entry " +
                                entry.first);
  _db[entry.first] = entry.second;
};

void BitcoinExchange::processInputEntry(entry_type const &entry) {
  double multiply;

  if (!isValidDate(entry.first))
    throw std::invalid_argument("BitcoinExchange invalid date on input entry " +
                                entry.first);
  if (entry.second < 0 || entry.second > 1000)
    throw std::invalid_argument(
        "BitcoinExchange invalid value on input entry " + entry.first);
  multiply = _db.lower_bound(entry.first)->second * entry.second;
  if (_db.find(entry.first) != _db.end())
    multiply = _db[entry.first] * entry.second;
  std::cout << entry.first << " => " << entry.second << " = " << multiply
            << std::endl;
};

void BitcoinExchange::loadFile(line_processor callback, std::string const &name,
                               std::string const &separator) {
  entry_type currentEntry;
  std::ifstream file(name);
  std::string line;

  if (file.rdstate() & file.failbit)
    throw std::invalid_argument("BitcoinExchange was given inexistent " + name);
  std::getline(file, line);
  for (; std::getline(file, line);) {
    try {
      currentEntry = loadFileEntry(line, separator);
      (this->*callback)(currentEntry);
    } catch (std::invalid_argument const &e) {
      std::cout << e.what() << line << std::endl;
    }
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
    throw std::invalid_argument("BitcoinExchange entry miss separator ");

  date = line.substr(0, index);
  valueText = line.substr(index + separator.length());
  stream = std::istringstream(valueText);
  stream >> std::noskipws >> value;
  if (stream.rdstate() ^ stream.eofbit || stream.rdstate() & stream.failbit)
    throw std::invalid_argument("BitcoinExchange invalid value ");
  return std::make_pair(date, value);
};
