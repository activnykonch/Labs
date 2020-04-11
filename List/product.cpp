#include "product.h"

Product::Product()
{

}

Product::~Product()
{

}

void Product::setName(QString str)
{
 name = str;
}

QString Product::getName(){
    return name;
}

void Product::setAmount(int value)
{
    amount = value;
}

int Product::getAmount(){
    return amount;
}

void Product::setGuild(int value)
{
    guild = value;
}

int Product::getGuild(){
    return guild;
}
