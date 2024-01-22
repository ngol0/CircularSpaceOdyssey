#pragma once

/* All the enemy types in the game */
enum class EnemyType
{
	SlowChaseType, //chase the player slowly and explode to cause damage when hit player
	ShootType, //sit still at one waypoint and shoot towards the player
	TwoModeType, //sit still at one waypoint and toggle defense mode on, also shoot at player 
	SplitType, //swarm the center area of the circle and no shooting, split into 2 fast chasing enemies when died
	FastChaseType //chase the player fast and explode to cause damage when hit player
};