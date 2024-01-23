#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "World/World.hpp"

TEST(BodyBuilderTest, SetInitialPosition_PositionIsSetAfterBodyCreation)
{
    constexpr Phaba::Vector2 kInitialPosition = { 1.2f, 3.f };

    Phaba::World world({});

    auto body = world.MakeBodyBuilder()
        .Position(kInitialPosition)
        .Build();

    EXPECT_EQ(body.GetPosition(), kInitialPosition);
}

TEST(BodyBuilderTest, SetInitialAngle_AngleIsSetAfterBodyCreation)
{
    constexpr float kInitialAngle = 3.14f;

    Phaba::World world({});

    auto body = world.MakeBodyBuilder()
        .Angle(kInitialAngle)
        .Build();

    EXPECT_EQ(body.GetAngle(), kInitialAngle);
}

