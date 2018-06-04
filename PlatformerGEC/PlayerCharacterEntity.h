#pragma once
#include "CharacterEntity.h"
class PlayerCharacterEntity : public CharacterEntity
{
public:

	virtual void Init();
	virtual void Destroy();

public:
	PlayerCharacterEntity(){}
};

