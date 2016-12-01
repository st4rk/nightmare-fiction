#ifndef _ITEM_H_
#define _ITEM_H_

#include <iostream>

enum ITEM_TYPE {
	ITEM_TYPE_NONE,
	ITEM_TYPE_GUN,
	ITEM_TYPE_KEY,
	ITEM_TYPE_BULLET
};

class item {
public:
	item();
	~item();

	const ITEM_TYPE& getType();
	const std::string& getName();
	const unsigned int& getDamage();
	const unsigned int& getAmount();

	void setType(ITEM_TYPE type);
	void setName(std::string name);
	void setDamage(unsigned int damage);
	void setAmount(unsigned int amount);

private:
	std::string name;
	ITEM_TYPE type;
	unsigned int damage;
	unsigned int amount;
};





#endif