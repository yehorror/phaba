#pragma once

#include "GenericScene/GenericScene.hpp"

namespace Playground
{
    class Demo1 : public GenericScene
    {
    public:
        Demo1();

    private:
        void OnRender() override;

    private:
        Shape m_boxShape;
        Shape m_floorShape;
    };
}