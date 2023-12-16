#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "World/World.hpp"

constexpr float kEpsilon = 0.0001f;

void ExpectVectorsEqual(Phaba::Vector2 lhs, Phaba::Vector2 rhs)
{
    EXPECT_FLOAT_EQ(glm::length(Phaba::Vector2(lhs - rhs)), 0.f);
}

void AssertVectorsEqual(Phaba::Vector2 lhs, Phaba::Vector2 rhs)
{
    ASSERT_FLOAT_EQ(glm::length(Phaba::Vector2(lhs - rhs)), 0.f);
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
    auto body = world.CreateBody();

    AssertVectorsEqual(body.GetVelocity(), Phaba::Vector2{ 0.0f, 0.0f });

    world.Step(kOneSecond);

    ExpectVectorsEqual(body.GetVelocity(), Phaba::Vector2{ 0.0f, -9.8f });
}