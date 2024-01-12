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
        BodyPart(Detail::Engine& engine, unsigned int startIndex, unsigned int endIndex);

    private:
        Detail::Engine& m_engine;
        const unsigned int m_startIndex;
        const unsigned int m_endIndex;
    };
}