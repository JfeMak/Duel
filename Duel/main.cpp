#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // For rand
#include <ctime> // For time (Generates actual random numbers)

#include "Duelist.h" // For enemies & other duelists

using namespace std;

void displayMoves (int level);
void duelImage (string name, double playerHealth, double playerMaxHealth, double enemyHealth, double enemyMaxHealth);
void useMove (bool &moveUsed, double &attack, double &defense, double &speed, int &level, Duelist *opponent);
int summonType (int summonChoice);
int yesOrNo (string yesNo);

void displayMoves (int level) {
	
	cout << endl;
	
	cout << "a - Attack" << endl;
	if (level > 10) {
		cout << "s - Strength" << endl;
	}
	if (level > 25) {
		cout << "p - Protect" << endl;
	}
	if (level > 50) {
		cout << "g - Agility" << endl;
	}
	cout << "x - Surrender" << endl;
	cout << endl;
}

void duelImage (string name, long double playerHealth, long double playerMaxHealth, long double enemyHealth, long double enemyMaxHealth) {
	int count {};
	cout << "\n" << name << ":                                        Enemy:" << endl;
	cout << "|";
	for (int i = 0; i < (playerHealth * 20) / playerMaxHealth; i++) {
		cout << "=";
		count ++;
	}
	for (int i = 0; i < 20 - count; i++) {
		cout << " ";
	}
	cout << "|      X      |";
	count = 0;
	for (int i = 0; i < (enemyHealth * 20) / enemyMaxHealth; i++) {
		count ++;
	}
	for (int i = 0; i < 20 - count; i++) {
		cout << " ";
	}
	for (int i = 0; i < (enemyHealth * 20) / enemyMaxHealth; i++) {
		cout << "=";
	}
	cout << "|" << endl;
	cout << "                            /                            " << endl;
	cout << "          O                 /                 O          " << endl;
	cout << "         /|\\|>>>            /            <<<|/|\\       " << endl;
	cout << "         / \\                /                / \\       " << endl;
	cout << "                            X                            \n" << endl;
}

void useMove (bool &surrender, bool &moveUsed, long double &attack, long double &defense, long double &speed, int &level, Duelist *opponent) {
	string duelMove;
	long double dmg = (attack - opponent->getDefense());
	cin >> duelMove;
	if (duelMove == "a") {
		if (dmg > 0) {
			opponent->damage(attack);
			cout << "\nYou inflicted " << (attack - opponent->getDefense()) << " damage on the enemy\n" << endl;
		} else {
			cout << "\nThe opponent's armor is too strong! You couldn't deal any damage!\n" << endl;
		}
		moveUsed = true;
	} else if (duelMove == "s" && level == 10) {
		attack *= 1.25;
		cout << "Your speed was increased by 25%\n" << endl;
		moveUsed = true;
	} else if (duelMove == "p" && level == 25) {
		defense *= 1.25;
		cout << "Your defense was increased by 25%\n" << endl;
		moveUsed = true;
	} else if (duelMove == "g" && level == 50) {
		speed *= 1.25;
		cout << "Your speed was increased by 25%\n" << endl;
		moveUsed = true;
	} else if (duelMove == "x") {
		surrender = true;
		moveUsed = true;
	}else {
		cout << "Sorry, invalid move.\n" << endl;
	}
}

int summonType (int summonChoice) { // -1 = Invalid; 0 = Coins only; 1 = Coins & Gems; 2 = Gems only
	if (summonChoice >= 1 && summonChoice <= 3) {
		return 0;
	} else if (summonChoice >= 4 && summonChoice <= 7) {
		return 1;
	} else if (summonChoice >= 8 && summonChoice <= 10) {
		return 2;
	} else {
		return -1;
	}
}

int yesOrNo (string yesNo) {
	if (yesNo == "Y" || yesNo == "y") {
		return 0;
	} else if (yesNo == "N" || yesNo == "n") {
		return 1;
	} else {
		return -1;
	}
}

int main() {
	
	// Player Data
		
		// Rank
		string Name {""};
		int RankPts {0};
		bool OnLeaderboard {false};
		// Level
		int Level {1};
		int XP {0};
		int XpToLevelUp {10};
		// Stats
			// Base stats (Increased when duelist levels up)
			long double baseHealth {20}; // +2 When level up
			long double baseAttack {4}; // +0.2 When level up
			long double baseDefense {0}; // +0.1 When level up
			long double baseSpeed {5}; // +1 When level Up
			// Gear multiplier (From summoner)
			long double armorMultiplier {1};
			long double weaponMultiplier {1};
			long double shieldMultiplier {1};
			long double bootsMultiplier {1};
			// Set Stats
			long double Health {baseHealth * armorMultiplier}; // baseHealth * armorMultiplier
			long double Attack {baseAttack * weaponMultiplier}; // baseAttack * weaponMultiplier
			long double Defense {baseDefense * shieldMultiplier}; // baseDefense * shieldMultiplier 
			long double Speed {baseSpeed * bootsMultiplier}; // baseSpeed * bootsMultiplier
			// Duel stats (Can be changed when opponent attacks)
			long double duelHealth {baseHealth * armorMultiplier};
			long double duelAttack {baseAttack * weaponMultiplier};
			long double duelDefense {baseDefense * shieldMultiplier};
			long double duelSpeed {baseSpeed * bootsMultiplier};
		// Currency
		int Coins {10000}; // Earned by defeating other duelists or monsters (Common currency)
		int Gems {10000}; // Winning a duelist tournament or beating a boss (Rare currency) 
	
	// Summoner
		
		/*
		 * Rarities
		 * 1. Inferior (1x - 5x) 100 coins
		 * 2. Common (3x - 8x) 500 coins
		 * 3. Uncommon (6x - 10x) 1000 coins
		 * 4. Rare (9x - 20x) 5000 coins or 25 gems
		 * 5. Royal (18x - 30x) 15000 coins or 75 gems
		 * 6. Superior (27x - 40x) 40000 coins or 200 gems
		 * 7. Epic (36x - 50x) 100000 coins or 500 gems
		 * 8. Divine (50x - 75x) 1000 gems
		 * 9. Legendary (75x - 95x) 5000 gems
		 * 10. Mythical (90x - 100x) 10000 gems
		 */
		 
		vector <double> summonerMin {1, 3, 6, 9, 18, 27, 36, 50, 75, 90};
		vector <double> summonerMax {5, 8, 10, 20, 30, 40, 50, 75, 95, 100};
		vector <int> summonerCoinCost {100, 500, 1000, 5000, 15000, 40000, 100000};
		vector <int> summonerGemCost {25, 75, 200, 500, 1000, 5000, 10000};
		vector <string> summonerName {"Inferior", "Common", "Uncommon", "Rare", "Royal",
			"Superior", "Epic", "Divine", "Legendary", "Mythical"};
		
	// Tournament (Coming soon)
		/*
		 * Leagues
		 * 1. Skilled
		 * 		Hp: 800 - 1000
		 * 		Attack: 80 - 100
		 * 		Defense: 40 - 50
		 * 		Speed: 400 - 500
		 * 
		 * 2. Professional
		 * 		Hp: 1500 - 2000
		 * 		Attack: 150 - 200
		 * 		Defense: 75 - 100
		 * 		Speed: 750 - 1000
		 * 3. Master
		 * 		Hp: 3000 - 4000
		 * 		Attack: 300 - 400
		 * 		Defense: 150 - 200
		 * 		Speed: 1500 - 2000
		 * 4. King
		 * 		Hp: 5000 - 7500
		 * 		Attack: 500 - 750
		 * 		Defense: 250 - 375
		 * 		Speed: 2500 - 3750
		 * 5. Deity
		 * 		Hp: 10000 - 15000
		 * 		Attack: 1000 - 1500
		 * 		Defense: 500 - 750
		 * 		Speed: 5000 - 7500
		 * 
		 * Ranks:
		 * 1. Champion (10W)
		 * 2. Rival (9W)
		 * 3. Challenger (8W)
		 * 4. Competitor (6W - 7W)
		 * 5. Contestant (0W - 5W)
		 */
		
	
	// Top Players
	vector <string> TopDuelists {"BlockyBall", "_Archangel", "MasterRckt", "CsmsNebula", "o0O CS O0o",
		"Pev_Dorito", "Dorito_Pev", " |3 U Z Z ", "Duelist|||", "0987654321"};
	vector <int> TopRankPoints {1161320, 1117777, 1114422, 1111437, 1111111,
		777777, 777770, 369369, 333333, 123456};
	
	// Gear
	vector <string> GearName {"Armor", "Weapon", "Shield", "Boots"};
	vector <string> GearPrefix {"", "A(n) ", "A(n) ", ""};
	
	string command {""};
	string yesNo {""};
	bool surrender {false};
	int difficulty {1000001};
	int randomNum {};
	bool originalName {false};
	bool usedMove {false};
	int summonChoice {};
	bool enoughCurrency {false};
	int currencyType {}; // 0 = Coins; 1 = Gems
	int typeOfGear {}; // 0 = Armor; 1 = Weapon; 2 = Shield; 3 = Boots
	
	srand(time(nullptr));
	
	cout << "=============================" << endl;
	cout << " ~ o 0 O [ D U E L ] O 0 o ~ " << endl;
	cout << " =-=-=-= Version 1.0 =-=-=-= " << endl;
	cout << "=============================" << endl;
	
	
	
	do {
		originalName = true;
		cout << "\nEnter your username (Must be 10 characters!): ";
		getline(cin, Name);
		for (auto x : TopDuelists) {
			if (Name == x) {
				originalName = false;
			}
		}
		
		if (!originalName) {
			cout << "Please enter an original username" << endl;
		}
		if (Name.length() != 10) {
			cout << "Make sure your username is at exactly 10 characters" << endl;
		}
		cout << endl;
	} while (Name.length() != 10 || originalName == false);
	
	cout << "\nThanks for registering, " << Name << "! \nBegin your journey to become the best Duelist using ,help to get the list of all commands\n" << endl;
	
	
	while (command != ",exit") {
		getline(cin, command);
		
		if (command == ",help") {
			cout << "\n===================" << endl;
			cout << "= C o m m a n d s =" << endl;
			cout << "===================\n" << endl;
			cout << ",duel - A duel against a random opponent" << endl;
			cout << ",duelmoves - A list of the possible moves that you can use in a duel" << endl;
			cout << ",bossbattle - A test of the skills you've learned (Coming Soon)" << endl;
			cout << ",tournament - Take part in a duelist tournament of 1024! (Coming Soon)" << endl;
			cout << ",profile - Look at your own stats" << endl;
			cout << ",ranklb - Look at the top global duelists" << endl;
			cout << ",summon - Summon gear that improves your stats. Multiplier is determined by rarity" << endl;
			cout << ",changelog - Take a look at the most recent updates" << endl;
			cout << ",help - Takes you to this page" << endl;
			cout << ",exit - End your journey" << endl;
			cout << endl;
		} else if (command == ",changelog") {
			cout << "\n=====================" << endl;
			cout << "= C h a n g e l o g =" << endl;
			cout << "=====================\n" << endl;
			cout << "v0.1 - 7/10/2020 - Game created & basic commands" << endl;
			cout << "v0.2 - 7/13/2020 - Added the ,duelmoves command" << endl;
			cout << "v0.3 - 7/13/2020 - ,duel command now works!" << endl;
			cout << "v0.4 - 7/14/2020 - Added the ,ranklb command" << endl;
			cout << "v0.5 - 7/14/2020 - Fixed the \"Invalid command popping up for newlines\" & increased duel max difficulty" << endl;
			cout << "v0.6 - 7/14/2020 - Added ,summoninfo and ,profile command and fixed the leveling error" << endl;
			cout << "v0.7 - 7/15/2020 - Fixed some display errors and reduced the amount of extra code" << endl;
			cout << "v0.8 - 8/15/2020 - Merged ,summoninfo and ,summon" << endl;
			cout << "v0.9 - 8/17/2020 - The BETA version of the summoner is out! Try it with ,summon" << endl;
			cout << "v1.0 - 8/17/2020 - The STABLE version of the summoner is out! Additionally, ,profile & ,duel command bug fixes\n\t\t with a new duel move! x - Surrender" << endl;
			cout << endl;
		} else if (command == ",duelmoves") {
			cout << "\n=======================" << endl;
			cout << "= D u e l   M o v e s =" << endl;
			cout << "=======================\n" << endl;
			cout << "a - Attack - Damages opponent" << endl;
			cout << "s - Strength - Increases your attack stat (Unlocked at lvl. 10)" << endl;
			cout << "p - Protect - Increases your defense stat (Unlocked at lvl. 25)" << endl;
			cout << "g - Agility - Increases your speed stat (Unlocked at lvl. 50)" << endl;
			cout << "x - Surrender - Forfeits battle. Only cowards will use this move." << endl;
			cout << "\nNOTE: Moves are case-sensitive" << endl;
			cout << endl;
		} else if (command == ",duel") {
			cout << "\n===========" << endl;
			cout << "= D u e l =" << endl;
			cout << "===========\n" << endl;
			do {
				cout << "Choose the difficulty of your opponent in the range [1, 1000000]: ";
				cin >> difficulty;
				if (difficulty <= 0 || difficulty >= 1000000) {
					cout << "Make sure the difficulty is in the range [1, 1000000]" << endl;
				}
			} while (difficulty <= 0 || difficulty >= 1000000);
			randomNum = rand() % (difficulty * 2);
			Duelist *enemy = new Duelist(15 + ((2 + randomNum) * difficulty),
				3 + ((2 + randomNum) * difficulty) / 10,
				0 + ((2 + randomNum) * difficulty) / 20,
				4 + ((2 + randomNum) * difficulty) / 2,
				difficulty * 2,
				difficulty); //(double hp, double atk, double def, int spd, int xpRwrd, int cnRwrd)
			
			while (duelHealth > 0 && enemy->getCurrentHealth() > 0 && !surrender) {
				
				duelImage(Name, duelHealth, Health, enemy->getCurrentHealth(), enemy->getHealth());
				
				if (duelSpeed > enemy->getSpeed()) { // Player is faster than enemy
					displayMoves(Level);
					while (usedMove == false) {
						useMove(surrender, usedMove, duelAttack, duelDefense, duelSpeed, Level, enemy);
					}
					if (enemy->getCurrentHealth() > 0) {
						long double dmg = (enemy->getAttack() - duelDefense);
						if (dmg > 0) {
							duelHealth -= (enemy->getAttack() - duelDefense);
							cout << "\nEnemy inflicted " << (enemy->getAttack() - duelDefense) << " damage on you.\n" << endl;
						} else {
							cout << "\nYour armor is too strong! Enemy couldn't deal any damage!\n" << endl; 
						}
					}
				} else if (duelSpeed < enemy->getSpeed()) { // Enemy is faster than player
					long double dmg = (enemy->getAttack() - duelDefense);
					if (dmg > 0) {
						duelHealth -= (enemy->getAttack() - duelDefense);
						cout << "\nEnemy inflicted " << (enemy->getAttack() - duelDefense) << " damage on you.\n" << endl;
					} else {
						cout << "\nYour armor is too strong! Enemy couldn't deal any damage!\n" << endl; 
					}
					if (duelHealth > 0) {
						displayMoves(Level);
						while (usedMove == false) {
							useMove(surrender, usedMove, duelAttack, duelDefense, duelSpeed, Level, enemy);
						}
					}
				} else { // Player & Enemy have the same speed 
					randomNum = rand() % 2;
					
					if (randomNum == 1) { // Player attacks first
						displayMoves(Level);
						while (usedMove == false) {
							useMove(surrender, usedMove, duelAttack, duelDefense, duelSpeed, Level, enemy);
						}
						if (enemy->getCurrentHealth() > 0) {
							duelHealth -= (enemy->getAttack() - duelDefense);
							cout << "\nEnemy inflicted " << (enemy->getAttack() - duelDefense) << " damage on you.\n" << endl;
						}
					} else { // Enemy attacks first
						duelHealth -= (enemy->getAttack() - duelDefense);
						cout << "\nEnemy inflicted " << (enemy->getAttack() - duelDefense) << " damage on you.\n" << endl;
						if (duelHealth > 0) {
							displayMoves(Level);
							while (usedMove == false) {
								useMove(surrender, usedMove, duelAttack, duelDefense, duelSpeed, Level, enemy);
							}
						}
					}
				}
				usedMove = false;
				
				if (duelHealth <= 0 || surrender) {
					cout << "You lost the duel :c\n" << endl;
				} else if (enemy->getCurrentHealth() <= 0) {
					cout << "You won the duel! :D" << endl;
					XP += enemy->getXpReward();
					Coins += enemy->getCoinReward();
					cout << "You gained " << enemy->getXpReward() << " XP and " << enemy->getCoinReward() << " coins! :O\n" << endl;
				}
			} 
			duelHealth = Health;
			duelAttack = Attack;
			duelDefense = Defense;
			duelSpeed = Speed;
			delete enemy;
		} else if (command == ",profile") {
			int count {};
			cout << "\n=================" << endl;
			cout << "= P r o f i l e =" << endl;
			cout << "=================\n" << endl;
			
			cout << "\n-----------------" << endl;
			cout << "- G e n e r a l -" << endl;
			cout << "-----------------\n" << endl;
			
			cout << "Name: " << Name << endl;
			cout << "Coins: " << Coins << endl;
			cout << "Gems: " << Gems << endl;
			cout << "Level: " << Level << endl;
			cout << "Xp: (" << XP << "/" << XpToLevelUp << ")" << endl;
			cout << "[";
			for (int i = 0; i < (XP * 20) / XpToLevelUp; i++) {
				cout << "=";
				count++;
			}
			for (int i = 0; i < 20 - count; i++) {
				cout << " ";
			}
			cout << "]" << endl;
			
			cout << "\n-------------" << endl;
			cout << "- S t a t s -" << endl;
			cout << "-------------\n" << endl;
			
			cout << "Rank Points: " << RankPts << endl;
			
			cout << "\nBase Health: " << baseHealth << endl;
			cout << "Base Attack: " << baseAttack << endl;
			cout << "Base Defense: " << baseDefense << endl;
			cout << "Base Speed: " << baseSpeed << endl;
			
			cout << "\nArmor Multiplier: " << armorMultiplier << endl;
			cout << "Weapon Multiplier: " << weaponMultiplier << endl;
			cout << "Shield Multiplier: " << shieldMultiplier << endl;
			cout << "Boots Multiplier: " << bootsMultiplier << endl;
			
			cout << "\nHealth: " << Health << endl;
			cout << "Attack: " << Attack << endl;
			cout << "Defense: " << Defense << endl;
			cout << "Speed: " << Speed << endl;
			cout << endl;
		} else if (command == ",ranklb") {
			cout << "\n===========================" << endl;
			cout << "= T o p   D u e l i s t s =" << endl;
			cout << "===========================\n" << endl;
			for (int i = 0; i < 10; i ++) {
				if (RankPts > TopRankPoints.at(i) && !OnLeaderboard) {
					cout << (i + 1) << ". " << Name << endl;
					cout << "\tRank Points: " << RankPts << endl;
					OnLeaderboard = true;
					i++;
				}
				if (i == 10) {
					break;
				}
				if (OnLeaderboard) {
					cout << (i + 1) << ". " << TopDuelists.at(i - 1) << endl;
					cout << "\tRank Points: " << TopRankPoints.at(i - 1) << endl;
				} else {
					cout << (i + 1) << ". " << TopDuelists.at(i) << endl;
					cout << "\tRank Points: " << TopRankPoints.at(i) << endl;
				}
			}
			cout << endl;
		} else if (command == ",summon") {
			cout << "\n===============" << endl;
			cout << "= S u m m o n =" << endl;
			cout << "===============\n" << endl;
			cout << "1. Inferior" << endl;
			cout << "\t1x - 5x" << endl;
			cout << "\t100 Coins" << endl;
			cout << "2. Common" << endl;
			cout << "\t3x - 8x" << endl;
			cout << "\t500 Coins" << endl;
			cout << "3. Uncommon" << endl;
			cout << "\t6x - 10x" << endl;
			cout << "\t1000 Coins" << endl;
			cout << "4. Rare" << endl;
			cout << "\t9x - 20x" << endl;
			cout << "\t5000 Coins or 25 Gems" << endl;
			cout << "5. Royal" << endl;
			cout << "\t18x - 30x" << endl;
			cout << "\t15000 Coins or 75 Gems" << endl;
			cout << "6. Superior" << endl;
			cout << "\t27x - 40x" << endl;
			cout << "\t40000 Coins or 200 Gems" << endl;
			cout << "7. Epic" << endl;
			cout << "\t36x - 50x" << endl;
			cout << "\t100000 Coins or 500 Gems" << endl;
			cout << "8. Divine" << endl;
			cout << "\t50x - 75x" << endl;
			cout << "\t1000 Gems" << endl;
			cout << "9. Legendary" << endl;
			cout << "\t75x - 95x" << endl;
			cout << "\t5000 Gems" << endl;
			cout << "10. Mythical" << endl;
			cout << "\t90x - 100x" << endl;
			cout << "\t10000 Gems" << endl;
			cout << endl;
			
			cout << "\nNote: If you do not equip the summoned gear, you will be recompensed with 1/4 of the original cost" << endl;
			
			cout << "\nWhich summoner would you like to use? (1-10): ";
			cin >> summonChoice;
			
			if (summonType(summonChoice) == 0) {
				if (Coins  >= summonerCoinCost.at(summonChoice - 1)) {
					currencyType = 0;
					enoughCurrency = true;
				}
			} else if (summonType(summonChoice) == 1) {
				do {
				cout << "\nWhich currency would you like to use? (0 = Coins; 1 = Gems): ";
				cin >> currencyType;
				} while (currencyType != 0 && currencyType != 1);
				
				if (currencyType == 0) {
					if (Coins >= summonerCoinCost.at(summonChoice - 1)) {
						enoughCurrency = true;
					}
				} else if (currencyType == 1) {
					if (Gems >= summonerGemCost.at(summonChoice - 4)) {
						enoughCurrency = true;
					}
				}
			} else if (summonType(summonChoice) == 2) {
				if (Gems >= summonerGemCost.at(summonChoice - 4)) {
					currencyType = 1;
					enoughCurrency = true;
				}
			}
			
			if (enoughCurrency) {
				
				cout << "\nAre you sure? (Y/N): ";
				cin >> yesNo;
				
				if (yesOrNo(yesNo) == 0) {
					if (currencyType == 0) {
						Coins -= summonerCoinCost.at(summonChoice - 1);
					} else {
						Gems -= summonerGemCost.at(summonChoice - 4);
					}
					
					randomNum = (rand() % static_cast<int>(summonerMax.at(summonChoice - 1) - summonerMin.at(summonChoice - 1) + 1)) + summonerMin.at(summonChoice - 1);
					typeOfGear = rand() % 4;
					
					cout << GearPrefix.at(typeOfGear) << summonerName.at(summonChoice - 1) << " " << GearName.at(typeOfGear) << " with " << randomNum << " DP appeared from the summoner." << endl;
					
					do {
						cout << "\nWould you like to equip it? (Y/N): ";
						cin >> yesNo;
						if (yesOrNo(yesNo) == -1) {
							cout << "Invalid response" << endl;
						}
					} while (yesOrNo(yesNo) == -1);
					
					if (yesOrNo(yesNo) == 0) {
						switch(typeOfGear) {
							case 0:
								armorMultiplier = randomNum;
								break;
							case 1:
								weaponMultiplier = randomNum;
								break;
							case 2:
								shieldMultiplier = randomNum;
								break;
							case 3:
								bootsMultiplier = randomNum;
								break;
						}
						cout << "\nGear equipped!\n" << endl;
					} else {
						if (currencyType == 0) {
							Coins += (summonerCoinCost.at(summonChoice - 1) / 4);
							cout << "\nYou were recompensed with " << (summonerCoinCost.at(summonChoice - 1) / 4) << " coins.\n" << endl;
						} else {
							Gems -= (summonerGemCost.at(summonChoice - 4) / 4);
							cout << "\nYou were recompensed with " << (summonerGemCost.at(summonChoice - 4) / 4) << " gems.\n" << endl;
						}
					}
				}
			} else {
					cout << "\nSorry, you don't have enough currency to summon " << summonerName.at(summonChoice - 1) << " gear.\n" << endl;
			}
			
			Health = baseHealth * armorMultiplier;
			Attack = baseAttack * weaponMultiplier; 
			Defense = baseDefense * shieldMultiplier; 
			Speed = baseSpeed * bootsMultiplier; 
			
			duelHealth = Health;
			duelAttack = Attack;
			duelDefense = Defense;
			duelSpeed = Speed;
			
			cout << "\nYou exited the summoning area.\n" << endl;
			enoughCurrency = false; // For the reset
			
		} else if (command == ",exit") {
			cout << Name << "'s journey has ended." << endl;
		} else {
			if (!(command == "")) {
				cout << "Invalid command\n" << endl;
			}
		}
		
		if (XP >= XpToLevelUp) {
			cout << "Wow! You leveled up to level " << ++Level << "! :)\n" << endl;
			XP = XpToLevelUp - XP;
			baseHealth += 2;
			baseAttack += 0.2;
			baseDefense += 0.1;
			baseSpeed += 1;
			
			Health = baseHealth * armorMultiplier;
			Attack = baseAttack * weaponMultiplier; 
			Defense = baseDefense * shieldMultiplier; 
			Speed = baseSpeed * bootsMultiplier; 
			
			duelHealth = Health;
			duelAttack = Attack;
			duelDefense = Defense;
			duelSpeed = Speed;
			XpToLevelUp *= 2;
		}
	}
	
	cout << endl;
	return 0;
}
