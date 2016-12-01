#include "item.h"

item::item() {
	type = ITEM_TYPE_NONE;
}

item::~item() {
	type = ITEM_TYPE_NONE;
}

void item::setType(ITEM_TYPE type) {
	this->type = type;
}

void item::setName(std::string name) {
	this->name = name;
}

void item::setDamage(unsigned int damage) {
	this->damage = damage;
}

void item::setAmount(unsigned int amount) {
	this->amount = amount;
}

const ITEM_TYPE& item::getType() { return type; }
const std::string& item::getName() { return name; }
const unsigned int& item::getDamage() { return damage; }
const unsigned int& item::getAmount() { return amount; }