#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "World/World.hpp"

constexpr float kEpsilon = 0.0001f;

TEST(WorldTest, WorldCanBeCreated)
{
    Phaba::World world;
}

TEST(WorldTest, FreeFallAcceleration_OneSecondStep_VelocityOfBodyChanged)
{
    constexpr Phaba::TimeDelta kOneSecond = 1.f;
    constexpr Phaba::Vector2 kGAcceleration = { 0.0f, -9.8f };

    Phaba::World world(kGAcceleration);

    auto body = world.MakeBodyBuilder().Build();

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

    auto body = world.MakeBodyBuilder().Build();

    // Assume we start at {0, 0}
    ASSERT_EQ(body.GetPosition(), Phaba::Vector2(0.0f, 0.0f));

    world.Step(kTwoSeconds);

    // Calculate by formula:
    // h = g*t^2/2
    constexpr Phaba::Vector2 kPositionAfterTwoSeconds = (kGAcceleration * (kTwoSeconds * kTwoSeconds)) / 2.f;

    EXPECT_EQ(body.GetPosition(), kPositionAfterTwoSeconds);
}

TEST(WorldTest, FreeFallAcceleration_StaticBody_TwoSecondsStep_PositionOfBodyHasntChanged)
{
    constexpr Phaba::TimeDelta kTwoSeconds = 2.f;
    constexpr Phaba::Vector2 kGAcceleration = { 0.0f, -9.8f };

    Phaba::World world(kGAcceleration);

    auto body = world.MakeBodyBuilder()
        .Type(Phaba::BodyType::kStatic)
        .Build();

    // Assume we start at {0, 0}
    ASSERT_EQ(body.GetPosition(), Phaba::Vector2(0.0f, 0.0f));

    world.Step(kTwoSeconds);

    EXPECT_EQ(body.GetPosition(), Phaba::Vector2(0.0f, 0.0f));
}


TEST(WorldTest, DISABLED_FreeFallAcceleration_SceneHasFloorAndABox_BoxBouncesOffOfTheFloor)
{
    /*
                ***
                ***     <- it should 'bounce'-off of the floor

        ***********************

    */
    constexpr Phaba::TimeDelta k100ms = 0.100f;
    constexpr Phaba::Vector2 kGAcceleration = { 0.0f, -2.f };

    Phaba::World world(kGAcceleration);

    constexpr Phaba::Vector2 s_floorVertices[] = {
        {-5.f,  0.2f},
        { 5.f,  0.2f},
        { 5.f, -0.2f},
        {-5.f, -0.2f}
    };

    constexpr Phaba::Vector2 s_boxVertices[] = {
        {-1.0,  1.0},
        { 1.0,  1.0},
        { 1.0, -1.0},
        {-1.0, -1.0}
    };

    auto floorPart = world.CreateBodyPart(s_floorVertices);
    auto floor = world.MakeBodyBuilder()
        .Type(Phaba::BodyType::kStatic)
        .Position(Phaba::Vector2{ 0.f, -1.f })
        .Part(floorPart)
        .Build();

    auto boxPart = world.CreateBodyPart(s_boxVertices);
    auto box = world.MakeBodyBuilder()
        .Type(Phaba::BodyType::kDynamic)
        .Position(Phaba::Vector2{ 0.f, 0.5f })
        .Part(boxPart)
        .Build();

    ASSERT_EQ(box.GetVelocity(), Phaba::Vector2(0.0f, 0.0f));

    for (int i = 0; i < 10; ++i)
    {
        world.Step(k100ms);
    }

    const auto velocityAfterFall = box.GetVelocity();
    EXPECT_GT(velocityAfterFall.y, 0.f);
}