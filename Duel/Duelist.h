#ifndef _DUELIST_H_
#define _DUELIST_H_

class Duelist
{
private:
	long double health {};
	long double attack {};
	long double defense {};
	long double speed {};
	
	long double currentHealth {};
	
	int xpReward {};
	int coinReward {};
	int gemReward {};
public:

	Duelist (long double hp, long double atk, long double def, long double spd, int xpRwrd, int cnRwrd, int gmRwrd = 0) 
		: health {hp}, currentHealth {hp}, attack {atk}, defense {def},
		speed {spd}, xpReward {xpRwrd}, coinReward {cnRwrd}, gemReward {gmRwrd} {
	}
	void damage (long double dmg) {
		currentHealth -= (dmg - defense);
	}
	
	long double getCurrentHealth () {
		return currentHealth;
	}
	
	long double getHealth () {
		return health;
	}
	long double getAttack () {
		return attack;
	}
	long double getDefense () {
		return defense;
	}
	long double getSpeed () {
		return speed;
	}
	int getXpReward () {
		return xpReward;
	}
	int getCoinReward () {
		return coinReward;
	}
	int getGemReward () {
		return gemReward;
	}
};

#endif // _DUELIST_H_
