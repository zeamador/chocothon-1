/*
EFFECTS.H
Saturday, June 18, 1994 10:44:10 PM
*/

/* ---------- effect structure */

enum /* effect types */
{
	_effect_rocket_explosion,
	_effect_rocket_contrail,
	_effect_grenade_explosion,
	_effect_grenade_contrail,
	_effect_bullet_ricochet,
	_effect_alien_weapon_ricochet,
	_effect_flamethrower_burst,
	_effect_fighter_blood_splash,
	_effect_player_blood_splash,
	_effect_civilian_blood_splash,
	_effect_assimilated_civilian_blood_splash,
	_effect_enforcer_blood_splash,
	_effect_compiler_bolt_minor_detonation,
	_effect_compiler_bolt_major_detonation,
	_effect_compiler_bolt_major_contrail,
	_effect_fighter_projectile_detonation,
	_effect_fighter_melee_detonation,
	_effect_hunter_projectile_detonation,
	_effect_hunter_spark,
	_effect_minor_fusion_detonation,
	_effect_major_fusion_detonation,
	_effect_major_fusion_contrail,
	_effect_fist_detonation,
	_effect_minor_defender_detonation,
	_effect_major_defender_detonation,
	_effect_defender_spark,
	_effect_trooper_blood_splash,
	_effect_water_lamp_breaking,
	_effect_lava_lamp_breaking,
	_effect_sewage_lamp_breaking,
	_effect_alien_lamp_breaking,
	_effect_metallic_clang,
	_effect_teleport_object_in,
	_effect_teleport_object_out,
	_effect_small_water_splash,
	_effect_medium_water_splash,
	_effect_large_water_splash,
	_effect_large_water_emergence,
	_effect_small_lava_splash,
	_effect_medium_lava_splash,
	_effect_large_lava_splash,
	_effect_large_lava_emergence,
	_effect_small_sewage_splash,
	_effect_medium_sewage_splash,
	_effect_large_sewage_splash,
	_effect_large_sewage_emergence,
	_effect_small_goo_splash,
	_effect_medium_goo_splash,
	_effect_large_goo_splash,
	_effect_large_goo_emergence,
	_effect_minor_hummer_projectile_detonation,
	_effect_major_hummer_projectile_detonation,
	_effect_durandal_hummer_projectile_detonation,
	_effect_hummer_spark,
	_effect_cyborg_projectile_detonation,
	_effect_cyborg_blood_splash,
	_effect_minor_fusion_dispersal,
	_effect_major_fusion_dispersal,
	_effect_overloaded_fusion_dispersal,
	_effect_sewage_yeti_blood_splash,
	_effect_sewage_yeti_projectile_detonation,
	_effect_water_yeti_blood_splash,
	_effect_lava_yeti_blood_splash,
	_effect_lava_yeti_projectile_detonation,
	_effect_yeti_melee_detonation,
	_effect_juggernaut_spark,
	_effect_juggernaut_missile_contrail,
	_effect_small_jjaro_splash,
	_effect_medium_jjaro_splash,
	_effect_large_jjaro_splash,
	_effect_large_jjaro_emergence,
	_effect_vacuum_civilian_blood_splash,
	_effect_assimilated_vacuum_civilian_blood_splash,
	NUMBER_OF_EFFECT_TYPES
};

#define MAXIMUM_EFFECTS_PER_MAP 64

/* uses SLOT_IS_USED(), SLOT_IS_FREE(), MARK_SLOT_AS_FREE(), MARK_SLOT_AS_USED() macros (0x8000 bit) */

struct effect_data /* 16 bytes */
{
	short type;
	short object_index;

	word flags; /* [slot_used.1] [unused.15] */

	short data; /* used for special effects (effects) */
	short delay; /* the effect is invisible and inactive for this many ticks */

	short unused[11];
};

/* ---------- globals */

extern struct effect_data *effects;

/* ---------- prototypes/EFFECTS.C */

short new_effect(world_point3d *origin, short polygon_index, short type, angle facing);
void update_effects(void); /* assumes ∂t==1 tick */

void remove_all_nonpersistent_effects(void);
void remove_effect(short effect_index);

void mark_effect_collections(short type, boolean loading);

void teleport_object_in(short object_index);
void teleport_object_out(short object_index);

#ifdef DEBUG
struct effect_data *get_effect_data(short effect_index);
#else
#define get_effect_data(i) (effects+(i))
#endif
