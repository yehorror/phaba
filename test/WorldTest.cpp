#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "World/World.hpp"

constexpr float kEpsilon = 0.0001f;

bool operator== (const Phaba::Vector2 lhs, const Phaba::Vector2 rhs)
{
    return glm::length(Phaba::Vector2(lhs - rhs)) < kEpsilon;
}

TEST(WorldTest, WorldCanBeCreated)
{
    Phaba::World world;
}

TEST(WorldTest, FreeFallAcceleration_OneSecondStep_VelocityOfBodyChanged)
{
    constexpr Phaba::TimeDelta kOneSecond = 1.f;

    Phaba::World world(Phaba::Vector2{ 0.0f, -9.8f });

    // TODO Actually bodies should be created with some parameters
    // Like mass, parts, etc
    auto& body = world.CreateBody();

    ASSERT_EQ(body.GetVelocity(), Phaba::Vector2(0.0f, 0.0f));

    world.Step(kOneSecond);

    EXPECT_EQ(body.GetVelocity(), Phaba::Vector2(0.0f, -9.8f));
}