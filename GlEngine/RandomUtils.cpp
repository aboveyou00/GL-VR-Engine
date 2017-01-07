#include "stdafx.h"
#include "RandomUtils.h"
#include <random>

namespace GlEngine
{
    namespace Util
    {
        static std::default_random_engine generator;

        template<>
        float random(float t)
        {
            std::uniform_real_distribution<float> distribution(0, t);
            return distribution(generator);
        }
        template<>
        double random(double t)
        {
            std::uniform_real_distribution<double> distribution(0, t);
            return distribution(generator);
        }
        template<>
        unsigned random(unsigned t)
        {
            assert(t != 0);
            std::uniform_int_distribution<unsigned> distribution(0, t - 1);
            return distribution(generator);
        }
        template<>
        int random(int t)
        {
            std::uniform_int_distribution<int> distribution(0, t - 1);
            return distribution(generator);
        }
    }
}
