#include <gamebase/Gamebase.h>

using namespace gamebase;
using namespace std;

class MyApp : public App
{
	//world obj
	enum world_TypE
	{
		obj,
		fon,
		enemy
	};
	struct world_Dropp
	{
		string name;
		int chance;
	};
	struct world_object
	{
		int hp = 0;
		vector <world_Dropp> drop;
	};
	struct world_RObj
	{
		string rare;
		string file;
		int chance;
		world_TypE type;
		world_object object;
	};

	//recipe obj
	struct RecipeD
	{
		int col;
		bool use;
	};
	struct Recipe
	{
		int col;
		int from;
		map<string, RecipeD> recipe;
	};
    
	//inventor_obj
	enum TypeIt
	{
		armors,
		weapons,
		resources,
		potions
	};
	enum Rarity
	{
		Common,
		Rare,
		Epic,
		Legendary
	};
	struct Potion
	{
		enum Type
		{
			Heal,
			NArmUp,
			MArmUp,
			SpeedUp
		};
		int PowEffects;
		Type type;
		bool isLeft;
		bool active;
		int num;
		bool full() { return num == 15; };
	};
	enum TypeA
	{
		helmet, //0
		chesplat, //1
		leggs, //2
		boots //3
	};
	struct Armor
	{

		TypeA type;
		int def, level;
		Rarity rarity;
		bool active;
	};
	struct Weapon
	{
		enum Type
		{
			sword,
			axe,
			pickaxe
		};
		int dam, level;
		int typeD;
		Type typeW;
		Rarity rarity;
		bool active;
		bool isLeft;

	};
	struct Resource
	{
		int number;
		bool full() { return number == 20; };
	};
	struct Item
	{
		string name;
		string file;
		TypeIt type;
		union
		{
			Armor armor;
			Weapon weapon;
			Resource resource;
			Potion potion;
		} data;
	};

	//enemy
	struct enemyType
	{
		bool active;
		int chance;
		int armN;
		int armM;
		int level;
		int dam;
		int Maxlife = 100;
		int change_miss;
		string file;
		string typeD;
		string type;
		string name;
		int life;
		map<string, int>drop;
	};
	struct enemyDB
	{
		map<string, enemyType> enemy;
	};
	
	//DB
	map<string, enemyDB> fight_DB;
	map<string, Recipe> recipe_DB;
	map<string, Item> obj_DB;
	map<string, map<string, world_RObj>> world_DB;

	void load()
    {
		connect(recipe_add_ing, add_string, 0);
		connect(armor_add_effect, add_string, 1);
		connect(world_obj_add_drop, add_string, 2);
		connect(fight_add_drop, add_string, 3);
		connect(update, edit, false);
    }
	
	void edit(bool i)
	{
		if (i)
		{
			editor.show();
		}
		if (!i)
		{
			editor.hide();
		}
	}

	void del_string(int i,int t)
	{
		if (t == 0)
		{
			recipe_list.get(i);
		}
		if (t == 1)
		{
			armor_effect_list.get(i);
		}
		if (t == 2)
		{
			world_obj_drop_list.get(i);
		}
		if (t == 3)
		{
			fight_drop_list.get(i);
		}
	}
	void add_string(int i)
	{
		if (i == 0)
		{
			auto a = recipe_list.load("recipe_obj.json");
			connect(a.child<Button>("ing_del_b"), del_string, recipe_list.height - 1, i);
		}
		if (i == 1)
		{
			auto a = armor_effect_list.load("effect.json");
		}
		if (i == 2)
		{
			auto a = world_obj_drop_list.load("drop.json");
		}
		if (i == 3)
		{
			auto a = fight_drop_list.load("drop.json");
		}
	}
   	
	void process(Input input)
    {
        using namespace gamebase::InputKey;

    }

    void move()
    {
        
    }

	//design
	FromDesign(Button, save);
	FromDesign(Button, Load);
	FromDesign(Button, create);
	FromDesign(Button, add);
	FromDesign(Button, update);
	FromDesign(Button, recipe_add_ing);
	FromDesign(Button, armor_add_effect);
	FromDesign(Button, world_obj_add_drop);
	FromDesign(Button, fight_add_drop);
	FromDesign(Layout, recipe_list);
	FromDesign(Layout, armor_effect_list);
	FromDesign(Layout, world_obj_drop_list);
	FromDesign(Layout, fight_drop_list);
	FromDesign(Selector, editor);
	
};

int main(int argc, char** argv)
{
    MyApp app;
    app.setConfig("WoK_new_objectConfig.json");
    app.setDesign("Design.json");
    if (!app.init(&argc, argv))
        return 1;
    app.run();
    return 0;
}
