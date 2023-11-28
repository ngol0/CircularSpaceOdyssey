#include "stdafx.h"
#include "Health.h"
#include "GameObject/GameObject.h"

Health::Health(int initial_amount) : amount(initial_amount)
{

}

void Health::TakeDamage(int damage_amount)
{
	amount -= damage_amount;

	if (amount <= 0)
	{
		Component::object->Deactivate();
	}
}