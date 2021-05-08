//
// Created by Necromant on 08.05.2021.
//

#pragma once

#include "GameObject.hpp"

class LevelBlock : public GameObject {
public:
	enum class BlockState {
		Alive,
		Destroy,
		Died
	};

public:
	explicit LevelBlock(const unsigned& block_id = 0);
	virtual ~LevelBlock() override = default;

	const unsigned& getLevelId() const;

	void destroyAnimation(float dt);
	void setState(const BlockState& state);
	const BlockState& getState() const;
private:
	unsigned int m_block_id;
	BlockState m_state;
};