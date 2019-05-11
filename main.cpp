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

	int t = 0;
	int t_o = 0;

	void load()
    {
		connect(recipe_add_ing, add_string);
		connect(armor_add_effect, add_string);
		connect(world_obj_add_drop, add_string);
		connect(fight_add_drop, add_string);
		connect(recipeB, edit_bd, 0);
		connect(objB, edit_bd, 1);
		connect(worldB, edit_bd, 2);
		connect(fightB, edit_bd, 3);
		connect(backB, back);
		connect(back_ch_b, hide_close_list, true);
		connect(addB, hide_close_list, false);
		connect(recipe_ch_b, choose, 0);
		connect(obj_res_ch_b, choose, 1);
		connect(obj_weap_ch_b, choose, 2);
		connect(obj_pot_ch_b, choose, 3);
		connect(obj_arm_ch_b, choose, 4);
		connect(world_fon_ch_b, choose, 5);
		connect(world_obj_ch_b, choose, 6);
		connect(world_enemy_ch_b, choose, 7);
		connect(fight_ch_b, choose, 8);
    }

	void choose(int i)
	{
		if (i == 0)
		{
			edit_bd(0);
		}
		else if (i < 5)
		{
			edit_bd(1);
		}
		else if (i < 8)
		{
			edit_bd(2);
		}
		else
		{
			edit_bd(3);
		}
		auto a = obj_list.load("obj.json");
		connect(a.child<Button>("edit_b"), updateObj, i);
		design.update();
	}
	void updateObj(int i)
	{
		editor.select(i);
		editor.show();
		t_o = i;
		design.update();
	}

	void hide_close_list(bool i)
	{
		if (i)
		{
			ch_list.hide();
		}
		else
		{
			ch_list.show();
		}
	}
	void back()
	{
		selector.select(1);
		obj_list.clear();
		editor.hide();
		addB.hide();
		loadOB.hide();
		design.update();
	}
	
	void edit_bd(int i)
	{
		if (t != i || selector.selected()==1)
		{
			t = i;
			addB.show();
			loadOB.show();
			selector.select(0);
			obj_list.clear();
			design.update();
		}
	}
	
	void del_string(DrawObj a)
	{
		if (t == 0)
		{
			recipe_list.remove(a);
		}
		if (t == 1)
		{
			armor_effect_list.remove(a);
		}
		if (t == 2)
		{
			world_obj_drop_list.remove(a);
		}
		if (t == 3)
		{
			fight_drop_list.remove(a);
		}
		design.update();
	}
	void add_string()
	{
		if (t == 0)
		{
			auto a = recipe_list.load("recipe_obj.json");
			connect(a.child<Button>("ing_del_b"), del_string, a);
		}
		if (t == 1)
		{
			auto a = armor_effect_list.load("effect.json");
			connect(a.child<Button>("effect_del_b"), del_string, a);
		}
		if (t == 2)
		{
			auto a = world_obj_drop_list.load("drop.json");
			connect(a.child<Button>("drop_del_b"), del_string, a);
		}
		if (t == 3)
		{
			auto a = fight_drop_list.load("drop.json");
			connect(a.child<Button>("drop_del_b"), del_string, a);
		}
		design.update();
	}
   	
	void process(Input input)
    {
        using namespace gamebase::InputKey;

    }

	/*void update()
	{
		if (t_o == 0)
		{
			for (auto a : recipe_list.all())
			{
				recipe_DB[recipe_id.text].recipe[a.child<TextBox>("ing_name").text].col = a.child<TextBox>("ing_col").text;
				recipe_DB[recipe_id.text].recipe[a.child<TextBox>("ing_name").text].use = a.child<CheckBox>("ing_use").isChecked;
			}
		}
		if (t_o == 1)
		{

		}
		if (t_o == 2)
		{

		}
		if (t_o == 3)
		{

		}
		if (t_o == 4)
		{

		}
		if (t_o == 5)
		{

		}
		if (t_o == 6)
		{

		}
		t_o=-1;
	}
	*/
  
	void save()
    {
        
    }

	//design
	FromDesign(Button, saveB);
	FromDesign(Button, loadB);
	FromDesign(Button, createB);
	FromDesign(Button, addB);
	FromDesign(Button, loadOB);
	FromDesign(Button, recipeB);
	FromDesign(Button, objB);
	FromDesign(Button, worldB);
	FromDesign(Button, fightB);
	FromDesign(Button, backB);
	FromDesign(Button, back_ch_b);
	FromDesign(Button, recipe_add_ing);
	FromDesign(Button, armor_add_effect);
	FromDesign(Button, world_obj_add_drop);
	FromDesign(Button, fight_add_drop);
	FromDesign(Button, recipe_ch_b);
	FromDesign(Button, obj_res_ch_b);
	FromDesign(Button, obj_weap_ch_b);
	FromDesign(Button, obj_pot_ch_b);
	FromDesign(Button, obj_arm_ch_b);
	FromDesign(Button, world_fon_ch_b);
	FromDesign(Button, world_obj_ch_b);
	FromDesign(Button, world_enemy_ch_b);
	FromDesign(Button, fight_ch_b);
	FromDesign(Layout, recipe_list);
	FromDesign(Layout, obj_list);
	FromDesign(Layout, armor_effect_list);
	FromDesign(Layout, world_obj_drop_list);
	FromDesign(Layout, fight_drop_list);
	FromDesign(Layout, ch_list);
	FromDesign(Selector, editor);
	FromDesign(Selector, selector);
	FromDesign(TextBox, recipe_id);
	
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
