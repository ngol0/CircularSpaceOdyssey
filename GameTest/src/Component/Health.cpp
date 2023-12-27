#include "stdafx.h"
#include "Health.h"
#include "GameObject/GameObject.h"
#include "Component/EnemyMovement.h"
#include "Component/EnemySplit.h"
#include "Component/Transform.h"

Health::Health(int health) : health_amount(health)
{
	m_initial_amount = health_amount;
}

void Health::TakeDamage(int damage_amount)
{
	health_amount -= damage_amount;

	if (health_amount <= 0)
	{
		on_die.Notify();

		if (Component::object->HasComponent<EnemyMovement>())
		{
			//reset health and waypoints for enemy when they die
			ResetHealth();
			Component::object->GetComponent<EnemyMovement>().Reset();
		}
		Component::object->Deactivate();

		//if enemies has split behavior, split when it dies
		if (Component::object->HasComponent<EnemySplit>())
		{
			Component::object->GetComponent<EnemySplit>().Split();
		}
	}
}

void Health::ResetHealth()
{
	health_amount = m_initial_amount;
}