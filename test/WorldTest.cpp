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
    constexpr Phaba::Vector2 kGAcceleration = { 0.0f, -9.8f };

    Phaba::World world(kGAcceleration);

    // TODO Actually bodies should be created with some parameters
    // Like mass, parts, etc
    auto body = world.CreateBody();

    ASSERT_EQ(body.GetVelocity(), Phaba::Vector2(0.0f, 0.0f));

    world.Step(kOneSecond);

    // After one second it will have a velocity equals to acceleration
    constexpr Phaba::Vector2 kVelocityAfterOneSecond = kGAcceleration;

    EXPECT_EQ(body.GetVelocity(), kVelocityAfterOneSecond);
}

TEST(WorldTest, FreeFallAcceleration_TwoSecondsStep_PositionOfBodyChanged)
{
    constexpr Phaba::TimeDelta kTwoSeconds = 2.f;
    constexpr Phaba::Vector2 kGAcceleration = { 0.0f, -9.8f };

    Phaba::World world(kGAcceleration);

    auto body = world.CreateBody();

    // Assume we start at {0, 0}
    ASSERT_EQ(body.GetPosition(), Phaba::Vector2(0.0f, 0.0f));

    world.Step(kTwoSeconds);

    // Calculate by formula:
    // h = g*t^2/2
    constexpr Phaba::Vector2 kPositionAfterTwoSeconds = (kGAcceleration * (kTwoSeconds * kTwoSeconds)) / 2.f;

    EXPECT_EQ(body.GetPosition(), kPositionAfterTwoSeconds);
}