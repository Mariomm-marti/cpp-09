#ifndef CPP_09_EX00_BITCOIN_EXCHANGE_HPP_
#define CPP_09_EX00_BITCOIN_EXCHANGE_HPP_
#pragma once

#ifndef __CPP09_DEBUG_
#define __CPP09_DEBUG_ false
#endif

#include <map>
#include <string>

class BitcoinExchange {
public:
  typedef std::map<std::string, double> db_type;
  typedef std::pair<std::string, double> entry_type;
  typedef void (BitcoinExchange::*line_processor)(entry_type const &entry);

private:
  db_type _db;

  BitcoinExchange(void);

  bool isValidDbname(std::string const &dbname) const;
  bool isValidDate(std::string const &date) const;
  void processDbEntry(entry_type const &entry);
  void processInputEntry(entry_type const &entry);
  void loadFile(line_processor callback, std::string const &name,
                std::string const &separator = ",");
  entry_type loadFileEntry(std::string const &line,
                           std::string const &separator) const;

public:
  BitcoinExchange(BitcoinExchange const &copy);
  BitcoinExchange(std::string const dbname);
  ~BitcoinExchange(void);

  BitcoinExchange &operator=(BitcoinExchange const &copy);
  db_type::const_iterator const begin(void) const;
  db_type::const_iterator const end(void) const;

  void processInputFile(std::string const filename);
};

#endif
