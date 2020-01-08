#include <iostream>

typedef unsigned short int usi;
class item {
				/*
				 * class item explain a something item what player may use
				 */
};
class chest {
				/*
				 * loot box who will spawn on map and drop weapon/items/money
				 */
};
class enemy {
				unsigned int _health; //max in ariphmetical progresson of lvl
				usi damage; //proporcional lvl * coefficient
				usi lvl; //max 1000 start at 1 and exp to next lvl expands in ariphmetical progression start by 100
				//types:
				//crawler cant jump
				//mage fire fireballs
				//solder buffed health
				//druid regen enemy health in range
				//necromant summon skeletons
				//skeleton big damage small health
};
class player {
				/*          skills
				 * limit break:
				 * multiply damage mana and jump height
				 * mana *4
				 * jump height *2
				 * damage *5
				 * mana full mana storage
				 * punch:
				 * deal damage on one enemy
				 * dont use mana
				 * power splash:
				 * mana 30
				 * aye skill who deal splash damage
				 */
    usi _health; //max 30000 default 100 regenerate only by poisions
				usi _max_health; //upgradable
				usi damage; //upgradable max 36000 default 5
				usi jump_height; //upgradable max 200 default 2 you may set custom height in limit
				usi mana; //upgradable max 36000 default 100 regen 1/10 of mana storage / player.lvl * 5
				usi max_mana;
				unsigned int exp_to_next_lvl;
				unsigned int current_exp;
				unsigned int money; //max 18,000,000 default 0
				item items[10]; //upgradable like inventory min 10 max 50
				unsigned int limit_break_time; //unlocking at 20 lvl default 3sec
				usi lvl; //max 1000 def 1 exp to next lvl expands in ariphmetical progression start by 100
				usi exp_gain; //upgadable
				public:
				void expand(int count); //expand inventory size
}	;
class light {
				/*
				 * torchs or electric lamp maby lava
				 * flashlight - player
				 */
};
class spawner {
				/*
				 * spawn specific item or different enemy type
				 */
};
class Trap {
				/*
				 * deal damage to all entities
				 * at begin forces a player to drop money then deal damage
				 */
};
class Totem {
				/*
				 * give time buffs
				 * i dont know how do it
				 */
};
class Platform {
				/*
				 * map tile type
				 */
};
class FlyingPlatform : public Platform {
				/*
				 * specific type of platform who may moving in axis
				 */
};
class map {
				/*
				 * many platforms
				 */
};
				
int main() {
								player p;
								
								return 0;
}