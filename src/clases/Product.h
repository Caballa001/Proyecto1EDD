//
// Created by yaxkin on 3/24/26.
//

#ifndef ARBOLES_PRODUCT_H
#define ARBOLES_PRODUCT_H
#include <string>

struct Product
{
    std::string name;
    std::string barcode;
    std::string category;
    std::string expiry_date;
    std::string brand;
    double price;
    int stock;
};


#endif //ARBOLES_PRODUCT_H