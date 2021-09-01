#include "Random/Random.hpp"

void Random::initSeed()
{
    std::srand(time(NULL));
}

void Random::initSeed(float seed)
{
    srand(seed);
}

template<typename T = float> 
auto Random::unitValue() -> std::enable_if_t<std::is_floating_point<T>::value, T>
{
    return static_cast <T> (rand()) / static_cast <T> (RAND_MAX);
} 

template<typename T = int> 
auto Random::unitValue() -> std::enable_if_t<std::is_integral<T>::value, T>
{
    return static_cast<T>(rand() % static_cast<T>(2));
}

template<typename T = float>
auto Random::ranged(const T& max) -> std::enable_if_t<std::is_floating_point<T>::value, T>
{
    return max <= std::numeric_limits<T>::epsilon() ? static_cast<T>(0) : static_cast <T> (rand()) / (static_cast <T> (RAND_MAX / max));
}

template<typename T = int>
auto Random::ranged(const T& max) -> std::enable_if_t<std::is_integral<T>::value, T>
{
    return max <= std::numeric_limits<T>::epsilon() ? static_cast<T>(0) : ranged<T>(0, max);
}

template<typename T>
auto Random::ranged(const T& min, const T& max)  -> std::enable_if_t<std::is_floating_point<T>::value, T>
{
    return max - min <= std::numeric_limits<T>::epsilon() ? max : min + static_cast <T> (rand()) /( static_cast <T> (RAND_MAX/(max - min)));
}

template<typename T>
auto Random::ranged(const T& min, const T& max) -> std::enable_if_t<std::is_integral<T>::value, T>
{
    return max - min <= std::numeric_limits<T>::epsilon() ? max : min + static_cast <T> (rand()) / (static_cast <T> (RAND_MAX/(max - min)));
}

template<typename T = float>
Vec2<T> Random::circularCoordinate(const Vec2<T>& center, const T& range)
{
    T randValue = static_cast<T>(rand());
    T scale = unitValue<T>();
    return Vec2<T>{center.x + range * std::cos(randValue) * scale, center.y + range * std::sin(randValue) * scale};
}

template<typename T = float>
Vec2<T> Random::peripheralCircularCoordinate(const Vec2<T>& center, const T& range)
{
    T randValue = static_cast<T>(rand());
    return Vec2<T>{center.x + range * std::cos(randValue), center.y + range * std::sin(randValue)};
}

template<typename T = float>
Vec2<T> Random::unitPeripheralCircularCoordinate()
{
    T randValue = static_cast<T>(rand());
    return Vec2<T>{std::cos(randValue), std::sin(randValue)};
}

template<typename T = float>
Vec3<T> Random::unitPeripheralSphericalCoordonate()
{
    T phi = ranged<T>(static_cast<T>(0), static_cast<T>(PI * static_cast<T>(2)));
    T theta = ranged<T>(static_cast<T>(0), static_cast<T>(PI * static_cast<T>(2)));
    return Vec3<T>{std::sin(phi) * std::cos(theta), std::sin(phi) * std::sin(theta), std::cos(phi)};
}

template<typename T = float>
Vec3<T> Random::sphericalCoordinate(const Vec3<T>& center, const T& range)
{
    return (center + unitPeripheralSphericalCoordonate()) * unitValue<T>() * range;
}

template<typename T = float>
Vec3<T> Random::peripheralSphericalCoordinate(const Vec3<T>& center, const T& range)
{
    return (center + unitPeripheralSphericalCoordonate()) * range;
}

template<typename T = float>
Vec2<T> Random::peripheralSquareCoordinate(const Vec2<T>& center, const T& extX, const T& extY)
{           
    if (unitValue<bool>())
    {
        if (unitValue<bool>())
        {
            return Vec2<T>{center.x -extX, center.y + ranged<T>(-extY, extY)};
        }
        return Vec2<T>{center.x + extX, center.y + ranged<T>(-extY, extY)};
    }

    if (unitValue<bool>())
    {
        return Vec2<T>{center.x + ranged<T>(-extX, extX), center.y - extY};
    }
    return Vec2<T>{center.x + ranged<T>(-extX, extX), center.y + extY};
}

template<typename T = float>
Vec2<T> Random::squareCoordinate(const Vec2<T>& center, const T& extX, const T& extY)
{           
    return Vec2<T>{center.x + ranged<T>(-extX, extX), center.y + ranged<T>(-extY, extY)};
}

template<typename T = float>
Vec2<T> Random::unitPeripheralSquareCoordinate()
{
    return Vec2<T>{unitValue<T>(), unitValue<T>()};
}       

template<typename T = float>
Vec3<T> Random::peripheralCubiqueCoordinate(const Vec3<T>& center, const T& extX, const T& extY, const T& extZ)
{    
    if (unitValue<bool>())
    {
        if (unitValue<bool>())
        {
            return Vec3<T>{center.x -extX, center.y + ranged<T>(-extY, extY), center.z + ranged<T>(-extZ, extZ)};
        }
        return Vec3<T>{center.x + extX, center.y + ranged<T>(-extY, extY), center.z + ranged<T>(-extZ, extZ)};
    }

    if (unitValue<bool>())
    {
        if (unitValue<bool>())
        {
            return Vec3<T>{center.x + ranged<T>(-extX, extX), center.y -extY, center.z + ranged<T>(-extZ, extZ)};
        }
        return Vec3<T>{center.x + ranged<T>(-extX, extX), center.y + extY, center.z + ranged<T>(-extZ, extZ)};
    }

    if (unitValue<bool>())
    {
        return Vec3<T>{center.x + ranged<T>(-extX, extX), center.y + ranged<T>(-extY, extY), center.z -extZ};
    }
    return Vec3<T>{center.x + ranged<T>(-extX, extX), center.y + ranged<T>(-extY, extY), center.z + extZ};
}


template<typename T = float>
Vec3<T> Random::cubiqueCoordinate(const Vec3<T>& center, const T& extX, const T& extY, const T& extZ)
{           
    return Vec3<T>{center.x + ranged<T>(-extX, extX), center.y + ranged<T>(-extY, extY), center.z + ranged<T>(-extZ, extZ)};
}

template<typename T = float>
Vec3<T> Random::unitPeripheralCubiqueCoordinate()
{
    return Vec3<T>{unitValue<T>(), unitValue<T>(), unitValue<T>()};
}

template<typename T = float>
bool Random::ranPercentProba(const T& percent)
{ 
    return ranged<T>(static_cast<T>(0), static_cast<T>(100)) <= percent;
}