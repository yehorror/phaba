#pragma once

namespace Phaba
{
    namespace Detail
    {
        class Engine;
    }
        
    class BodyPart
    {
    public:
        BodyPart(Detail::Engine& engine, unsigned int index);

    private:
        Detail::Engine& m_engine;
        const unsigned int m_index;
    };
}