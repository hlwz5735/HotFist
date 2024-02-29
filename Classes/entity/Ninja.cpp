//
//  Ninja.cpp
//  HelloCpp
//
//  Created by 田子桐 on 14-8-21.
//
//

#include "cocostudio/Armature.h"
#include "Ninja.h"

USING_NS_CC;

bool Ninja::init()
{
	if (!Enemy::init())
	{
		return false;
	}
	hp = 500;
	view = 5*32;
	enemyState = EnemyState::STADINGBY;
	//初始化精灵动画
	initSprite();
	initViewRect();
	speedX = 1.5;
	return true;
}
void Ninja::initBlock()
{
	m_block = Rect(
                         getPositionX(),
                         getPositionY(),
                         m_sprite->getContentSize().width - 5,
                         m_sprite->getContentSize().height);
}
void Ninja::initSprite()
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Ninja0.png", "Ninja0.plist", "Ninja.ExportJson");
	// 这里直接使用Nivida ，而此信息保存在 Nivida.ExportJson 中，与其创建的项目属性相对应
	m_sprite = Armature::create("Ninja");
	// 设置当前运行动画的索引，一个“工程”可以建立多个动画
	m_sprite->getAnimation()->play("Stand");
	// 设置位置信息
	m_sprite->setPosition(Point(25,0));
	// 添加到容器，当前运行的场景之中
	this->addChild(m_sprite);
}
void Ninja::hurt()
{
	if (this->getState() != EntityState::HURT)
	{
		this->setState(EntityState::HURT);
		velocityX = 0;
		if (inTheAirFlag)
		{
			airHurt();
		}
		else
		{
			float tempRand = AXRANDOM_0_1();
			//在头部防御和腹部防御之间随机出一个
			if (tempRand < 0.5f)
			{
				headHurt();
			}
			else
			{
				flankHurt();
			}
		}
	}
}
void Ninja::headHurt()
{
	m_sprite->getAnimation()->play("HeadHurt");
	this->scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::doHurt), 0.33f);
	m_sprite->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Ninja::hurtCallBack));
}
void Ninja::flankHurt()
{
	m_sprite->getAnimation()->play("FlankHurt");
	this->scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::doHurt), 0.33f);
	m_sprite->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Ninja::hurtCallBack));
}
void Ninja::airHurt()
{
	if (faceto)
	{
		velocityX = 2;
	}
	else
	{
		velocityX = -2;
	}
	velocityY = 5;
	m_sprite->getAnimation()->play("FlankHurt");
	this->scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::doHurt),0.33f);
	m_sprite->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Ninja::hurtCallBack));
}
void Ninja::doHurt(float dt)
{
	setState(EntityState::NORMAL);
	m_sprite->getAnimation()->play("Stand");
}
void Ninja::hurtCallBack(Armature* armature, MovementEventType type, const char *name)
{
	if (strcmp(name,"FlankDefence") == 0 || strcmp(name,"HeadDefence") == 0)
	{
		switch (type)
		{
            case COMPLETE:
                setState(EntityState::NORMAL);
                armature->getAnimation()->play("Stand");
                break;
            default:
                break;
		}
	}
}
void Ninja::attack()
{
	if (getState() ==  EntityState::NORMAL||getState() == EntityState::WALKING)
	{
		if (getState() != EntityState::ATTACKING)
		{
			setState(EntityState::ATTACKING);
			if (this->enemyState != EnemyState::ATTACK)
			{
				enemyState = EnemyState::ATTACK;
			}
			velocityX = 0;
			if (inTheAirFlag)
			{
				airAttack();
			}
			else
			{
				groundAttack();
			}
		}
	}
}
void Ninja::refresh(float dt)
{
	this->setState(EntityState::NORMAL);
	enemyState = EnemyState::STADINGBY;
	m_sprite->getAnimation()->play("Stand");
}
void Ninja::setAttackRect(float dt)
{
	auto rect = Rect(
			getPositionX() - 40,
			getPositionY() + 16,
			m_sprite->getContentSize().width - 10,
			m_sprite->getContentSize().height - 10
	);
	if (faceto)
	{
		rect.origin.x -= 40;
	}
	else
	{
		rect.origin.x += 40;
	}
	this->m_attack = AttackRect(rect, force, false);
}
void Ninja::Dart()
{
	m_sprite->getAnimation()->play("Dart"); 
	this->scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::setAttackRect), 0.6f);
	scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::refresh), 0.4f);
}
void Ninja::Hurt_in_theAir()
{
	m_sprite->getAnimation()->play("Hurt_in_theAir");
	this->scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::setAttackRect), 0.6f);
	scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::refresh), 0.4f);
}
void Ninja::Boomerang()
{
	m_sprite->getAnimation()->play("Boomerang");
	this->scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::setAttackRect), 0.6f);
	scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::refresh), 0.4f);
}
void Ninja::airAttack()
{
	;
}
void Ninja::groundAttack()
{
	int attackIndex = static_cast<int>(AXRANDOM_0_1() * 100);
	if (attackIndex <= 30)
	{
		Dart();
	}
	else if (attackIndex <= 65)
	{
		Hurt_in_theAir();
	}
	else
	{
		Boomerang();
	}
}