//
// Created by Necromant on 08.05.2021.
//

#include "game/LevelBlock.hpp"

LevelBlock::LevelBlock(const unsigned& block_id):
m_block_id(block_id),
m_state(BlockState::Alive)
{
}

void LevelBlock::destroyAnimation(float dt)
{
	color.alpha -= dt;
	m_sprite.setColor(color);
	if(color.alpha <= 0)
		m_state = BlockState::Died;
}

void LevelBlock::setState(const LevelBlock::BlockState& state)
{
	m_state = state;
}

const LevelBlock::BlockState& LevelBlock::getState() const
{
	return m_state;
}

const unsigned& LevelBlock::getLevelId() const
{
	return m_block_id;
}
