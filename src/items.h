/*
ITEMS.H
Thursday, April 6, 1995 1:06:42 PM  (Jason')
*/

/* ---------- constants */

enum /* item types (class) */
{
	_weapon,
	_ammunition,
	_powerup,
	_item,
	_weapon_powerup,
	_ball,

	NUMBER_OF_ITEM_TYPES,
	_network_statistics= NUMBER_OF_ITEM_TYPES // Used in game_window.c
};

enum /* item types */
{
	_i_knife,
	_i_magnum,
	_i_magnum_magazine,
	_i_plasma_pistol,
	_i_plasma_magazine,
	_i_assault_rifle,
	_i_assault_rifle_magazine,
	_i_assault_grenade_magazine,
	_i_missile_launcher,
	_i_missile_launcher_magazine,
	_i_invisibility_powerup,
	_i_invincibility_powerup,
	_i_infravision_powerup,
	_i_alien_shotgun,
	_i_alien_shotgun_magazine,
	_i_flamethrower,
	_i_flamethrower_canister,
	_i_extravision_powerup,
	_i_oxygen_powerup,
	_i_energy_powerup,
	_i_double_energy_powerup,
	_i_triple_energy_powerup,
	_i_shotgun,
	_i_shotgun_magazine,
	_i_spht_door_key,
	_i_uplink_chip,

	BALL_ITEM_BASE,
	_i_light_blue_ball= BALL_ITEM_BASE,
	_i_red_ball,
	_i_violet_ball,
	_i_yellow_ball,
	_i_brown_ball,
	_i_orange_ball,
	_i_blue_ball, // heh heh
	_i_green_ball,

	_i_smg,
	_i_smg_ammo,

	NUMBER_OF_DEFINED_ITEMS
};

/* ---------- prototypes/ITEMS.C */

short new_item(struct object_location *location, short item_type);

void calculate_player_item_array(short player_index, short type, short *items, short *counts, short *array_count);
void get_header_name(char *buffer, short type);
void get_item_name(char *buffer, short item_id, boolean plural);
boolean new_item_in_random_location(short item_type);
short count_inventory_lines(short player_index);
void swipe_nearby_items(short player_index);

void mark_item_collections(boolean loading);
short get_item_kind(short item_id);

boolean unretrieved_items_on_map(void);
boolean item_valid_in_current_environment(short item_type);

void trigger_nearby_items(short polygon_index);
short find_player_ball_color(short player_index); /* returns the color of the ball or NONE if they don't have one */

short get_item_shape(short item_id);
boolean try_and_add_player_item(short player_index, short type);

/* Returns NONE if this player is not carrying a ball */
short find_player_ball_color(short player_index);
