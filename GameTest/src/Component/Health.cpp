#include "stdafx.h"
#include "Health.h"
#include "GameObject/GameObject.h"
#include "Component/EnemyMovement.h"

Health::Health(int health) : amount(health)
{
	initial_amount = amount;
}

void Health::TakeDamage(int damage_amount)
{
	amount -= damage_amount;

	if (amount <= 0)
	{
		on_die.Notify();

		if (Component::object->HasComponent<EnemyMovement>())
		{
			//reset health and waypoints for enemy when they die
			ResetHealth();
			Component::object->GetComponent<EnemyMovement>().Reset();
		}
		Component::object->Deactivate();
	}
}

void Health::ResetHealth()
{
	amount = initial_amount;
}