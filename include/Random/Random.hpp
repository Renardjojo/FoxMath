//Project : Engine
//Editing by Gavelle Anthony, Nisi Guillaume, Six Jonathan
//Date : 2020-05-13 - 17 h 14

#ifndef _RANDOM_H
#define _RANDOM_H

#include <cstdlib>
#include <time.h>
#include <type_traits>
#include <algorithm>
#include <limits>

#include "Vector/Vector.hpp"
#include "Macro/Constants.hpp"

namespace FoxMath
{
    class Random
    {
        public:

        #pragma region constructor/destructor

        Random ()					            = delete;
        Random (const Random& other)			= delete;
        Random (Random&& other)				    = delete;
        ~Random ()				                = delete;
        Random& operator=(Random const& other)  = delete;
        Random& operator=(Random && other)		= delete;

        #pragma endregion //!constructor/destructor

        #pragma region methods

        /**
         * @brief Init random seed with the current time
         * 
         */
        static void initSeed();

        /**
         * @brief Initialize random number generator
         * 
         * @param seed The pseudo-random number generator is initialized using the argument passed as seed.
         */
        static void initSeed(float seed);

        /**
         * @brief This will generate a number from 0.0 to 1.0, inclusive.
         * 
         * @tparam floating point type 
         * @return T 
         */
        template<typename T = float> 
        static auto unitValue() -> std::enable_if_t<std::is_floating_point<T>::value, T>;


        /**
         * @brief This will generate a number from 0 to 1, inclusive.
         * 
         * @tparam integral type 
         * @return T 
         */
        template<typename T = int> 
        static auto unitValue() -> std::enable_if_t<std::is_integral<T>::value, T>;

        /**
         * @brief This will generate a number from 0.0 to some arbitrary float, max:
         * 
         * @tparam float 
         * @param max 
         * @return T 
         */
        template<typename T = float>
        static auto ranged(const T& max) -> std::enable_if_t<std::is_floating_point<T>::value, T>;

        template<typename T = int>
        static auto ranged(const T& max) -> std::enable_if_t<std::is_integral<T>::value, T>;

        /**
         * @brief This will generate a number from some arbitrary min to some arbitrary max:
         * 
         * @tparam float 
         * @param min 
         * @param max 
         * @return T 
         */
        template<typename T = float>
        static auto ranged(const T& min, const T& max) -> std::enable_if_t<std::is_floating_point<T>::value, T>;

        template<typename T = int>
        static inline auto ranged(const T& min, const T& max) -> std::enable_if_t<std::is_integral<T>::value, T>;

#pragma region Cicular

        template<typename T = float>
        static Vec2<T> circularCoordinate(const Vec2<T>& center, const T& range);

        template<typename T = float>
        static Vec2<T> peripheralCircularCoordinate(const Vec2<T>& center, const T& range);

        template<typename T = float>
        static Vec2<T> unitPeripheralCircularCoordinate();

#pragma endregion //!Cicular

#pragma region Spherique

        template<typename T = float>
        static Vec3<T> unitPeripheralSphericalCoordonate();

        template<typename T = float>
        static Vec3<T> sphericalCoordinate(const Vec3<T>& center, const T& range);

        template<typename T = float>
        static Vec3<T> peripheralSphericalCoordinate(const Vec3<T>& center, const T& range);


#pragma endregion //!Spherique

#pragma region Square

       template<typename T = float>
        static Vec2<T> peripheralSquareCoordinate(const Vec2<T>& center, const T& extX, const T& extY);

        /**
         * @brief return square coordonate
         * 
         * @tparam float 
         * @param center the center of the square
         * @param extX half saquare extension on x axis
         * @param extY half saquare extension on y axis
         * @return Vec2<T> 
         */
        template<typename T = float>
        static Vec2<T> squareCoordinate(const Vec2<T>& center, const T& extX, const T& extY);

        /**
         * @brief return unit sqare with value between 0 and 1
         * 
         * @tparam float 
         * @return Vec2<T> 
         */
        template<typename T = float>
        static Vec2<T> unitPeripheralSquareCoordinate();

#pragma endregion //!Square

#pragma region Cubique
        

        template<typename T = float>
        static Vec3<T> peripheralCubiqueCoordinate(const Vec3<T>& center, const T& extX, const T& extY, const T& extZ);
        
        /**
         * @brief return cubique coordonate
         * 
         * @tparam float 
         * @param center the center of the square
         * @param extX half saquare extension on x axis
         * @param extY half saquare extension on y axis
         * @param extZ half saquare extension on z axis
         * @return Vec3<T> 
         */
        template<typename T = float>
        static Vec3<T> cubiqueCoordinate(const Vec3<T>& center, const T& extX, const T& extY, const T& extZ);

        /**
         * @brief return unit cubic with value between 0 and 1
         * 
         * @tparam float 
         * @return Vec3<T> 
         */
        template<typename T = float>
        static Vec3<T> unitPeripheralCubiqueCoordinate();

#pragma endregion //!Cubique

        /**
         * @brief return if purcent value is respect in randome case. Inclusive test
         * 
         * @tparam float 
         * @param percent 
         * @return true 
         * @return false 
         */
        template<typename T = float>
        static bool ranPercentProba(const T& percent);

        #pragma endregion //!methods
    };

#include "Random.inl"

} //namespace FoxMath

#endif //_RANDOM_H