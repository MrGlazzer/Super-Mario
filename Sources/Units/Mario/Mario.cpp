#include "Mario.h"
#include "Sources/Map/Map.h"


Mario::Mario() : _JumpTimer(0.f), _IsImpulse(false) {}

Mario::~Mario() {}

void Mario::Update(float diff)
{
    sf::Int8 horizontalMoveDirection = 0;

    //< Horizontal Move
    {
        auto isMoved = false;
        if (IsLeft() || IsRight())
        {
            //< if both buttons are clamped, we don't move.
            isMoved = !(IsLeft() && IsRight());
            if (isMoved)
                horizontalMoveDirection = IsRight() ? 1 : -1;

            if (horizontalMoveDirection > 0)
            {
                _Velocity.x = std::min(_Velocity.x + MARIO_ACCELERATION * diff, MARIO_WALK_SPEED);
            }
            else
            {
                _Velocity.x = std::max(_Velocity.x - MARIO_ACCELERATION * diff, -MARIO_WALK_SPEED);
            }
        }

        //< Acceleration: after stopping, Mario does not immediately stop, he goes part of the way in sliding.
        if (!isMoved)
        {
            if (_Velocity.x > 0.f)
            {
                _Velocity.x = std::max(0.f, _Velocity.x - MARIO_ACCELERATION * diff);
            }
            else if (_Velocity.x < 0.f)
            {
                _Velocity.x = std::min(0.f, _Velocity.x + MARIO_ACCELERATION * diff);
            }
        }

        auto temp = GetPosition();
        temp.x += _Velocity.x;
        sf::Uint32 collisionMask = 0;

        if (sCollisionMgr->IsCollision(GetMap(), temp, { ObjectType::Collision, ObjectType::Block, ObjectType::Pipe }, collisionMask))
        {
            if (_Velocity.x > 0.f)
            {
                SetPositionX((float)CELL_SIZE * (ceil((_Velocity.x + GetPositionX()) / (float)CELL_SIZE) - 1.f));
            }
            else if (_Velocity.x < 0.f)
            {
                SetPositionX((float)CELL_SIZE * (1.f + floor((_Velocity.x + GetPositionX()) / (float)CELL_SIZE)));
            }

            _Velocity.x = 0.f;
        }
        else
        {
            SetPosition(temp);
        }
    }

    //< Vertical Move
    {
        auto temp = GetPosition();
        temp.y += 1.f;

        if (IsUp())
        {
            sf::Uint32 collisionMask = 0;
            if (sCollisionMgr->IsCollision(GetMap(), temp, { ObjectType::Collision, ObjectType::Block, ObjectType::Pipe }, collisionMask))
            {
                if (!_Velocity.y)
                    _Velocity.y = MARIO_JUMP_SPEED;
            }
            else
            {
                _Velocity.y = std::min(_Velocity.y + GRAVITY * diff, 8.f);
            }

            if (_JumpTimer > 0.1f && !_IsImpulse)
            {
                _IsImpulse = true;
                _Velocity.y += MARIO_JUMP_SPEED / 1.6f;
            }

            _JumpTimer += diff;
        }
        else
        {
            _Velocity.y = std::min(_Velocity.y + GRAVITY * diff, 8.f);
            _JumpTimer = 0.f;
            _IsImpulse = false;
        }

        temp = GetPosition();
        temp.y += _Velocity.y;
        sf::Uint32 collisionMask = 0;

        if (sCollisionMgr->IsCollision(GetMap(), temp, { ObjectType::Collision, ObjectType::Block, ObjectType::Pipe }, collisionMask))
        {
            if (_Velocity.y < 0.f)
            {
                SetPositionY((float)CELL_SIZE * (1.f + floor((_Velocity.y + GetPositionY()) / (float)CELL_SIZE)));
            }
            else if (_Velocity.y > 0.f)
            {
                SetPositionY((float)CELL_SIZE * (ceil((_Velocity.y + GetPositionY()) / (float)CELL_SIZE) - 1.f));
            }

            _Velocity.y = 0.f;
        }
        else
        {
            SetPosition(temp);
        }
    }

    if (_Velocity.y != 0.f)
    {
        GetAnimationHandler()->Jump(_Velocity.x < 0.f);
    }
    else if (_Velocity.x != 0.f)
    {
        if (horizontalMoveDirection > 0 && _Velocity.x < 0.f ||
            horizontalMoveDirection < 0 && _Velocity.x > 0.f)
        {
            GetAnimationHandler()->Sliding(_Velocity.x < 0.f);
        }
        else
        {
            GetAnimationHandler()->Walk(_Velocity.x < 0.f);
        }
    }
    else
    {
        GetAnimationHandler()->Idle();
    }

    if (auto map = GetMap())
    {
        auto offsetX = Clamp(GetPositionX() - (float)SCREEN_WIDTH / 2.f, 0.f, (map->GetWidth() * (float)CELL_SIZE) - SCREEN_WIDTH);
        SetPositionX(Clamp(GetPositionX(), 0.f, std::min(GetPositionX(), (map->GetWidth() - 1) * (float)CELL_SIZE)));
        SetPositionY(Clamp(GetPositionY(), 0.f, std::min(GetPositionY(), (map->GetHeight() - 1) * (float)CELL_SIZE)));
        map->SetCameraOffsetX(offsetX);
    }
}
