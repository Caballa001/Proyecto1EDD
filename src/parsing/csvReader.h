//
// Created by yaxkin on 3/25/26.
//

#ifndef ARBOLES_CVSREADER_H
#define ARBOLES_CVSREADER_H
#include <string>
#include <vector>
#include "clases/Product.h"


std::vector<std::string> splitCSVLine(const std::string& line);

std::vector<Product> parseCSV(std::string& content);

std::vector<Product> loadFile(std::string& path);

std::vector<Product> csvReader();

#endif //ARBOLES_CVSREADER_H