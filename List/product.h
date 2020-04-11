#ifndef PRODUCT_H
#define PRODUCT_H
#include <QString>

class Product
{
public:
    Product();
    ~Product();
    void setName(QString);
    QString getName();
    void setAmount(int);
    int getAmount();
    void setGuild(int);
    int getGuild();
private:
    QString name;
    int amount;
    int guild;
};

#endif // PRODUCT_H
