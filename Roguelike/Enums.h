#pragma once

enum class direction { left, right, up, down, no_direction };
enum class state_of_game { lost, completed_level, error, file_error };
enum class menu_options { play, leaderboards, end };
enum class pause_options { continue_game, end };
enum class character_class { fighter, ranger, wizard, none };
enum class tile_type { floor, wall, stairs, none };
enum class pickup_type { coins, diamond, potion, none };
enum class projectile_type { melee, arrow, aimedshot, fireball, flurry, lightning, stun, none };
enum class unit_type { player, zombie, skeleton, skeleton_archer, none };