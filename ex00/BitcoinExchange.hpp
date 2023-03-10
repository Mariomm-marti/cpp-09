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

private:
  db_type _db;
  std::string _filename;
  std::string _dbname;

  BitcoinExchange(void);

  bool isValidDbname(void) const;
  void loadDatabase(void);
  void loadFileEntry(std::string const &line,
                     std::string const &separator = ",");

public:
  BitcoinExchange(BitcoinExchange const &copy);
  BitcoinExchange(std::string const filename, std::string const dbname);
  ~BitcoinExchange(void);

  BitcoinExchange &operator=(BitcoinExchange const &copy);
  db_type::const_iterator const begin(void) const;
  db_type::const_iterator const end(void) const;
};

#endif
