/*

	game_window.h
	Tuesday, June 6, 1995 3:36:27 PM- rdm created.

*/

void initialize_game_window(void);

void draw_interface(void);
void update_interface(short time_elapsed);
void scroll_inventory(short dy);

void mark_ammo_display_as_dirty(void);
void mark_shield_display_as_dirty(void);
void mark_oxygen_display_as_dirty(void);
void mark_weapon_display_as_dirty(void);
void mark_player_inventory_screen_as_dirty(short player_index, short screen);
void mark_player_inventory_as_dirty(short player_index, short dirty_item);
void mark_interface_collections(boolean loading);
void mark_player_network_stats_as_dirty(short player_index);

void set_interface_microphone_recording_state(boolean state);
