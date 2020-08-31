#include "benchmark/benchmark.h"
#include "Vector/Vector.hpp"
#include "Matrix/Matrix.hpp"
#include "Angle/Angle.hpp"

#include "mat.hpp"
#include "vec.hpp"

#include <stdlib.h>     /* std::rand, std::rand */
#include <time.h>       /* time */

using namespace FoxMath::Matrix;
using namespace FoxMath::Vector;
using namespace FoxMath::Angle;

#define RAND_FLOAT (float)std::rand()
static void _ (benchmark::State& state){}

static void BM_NewReverseMatrixAtCompileTime(benchmark::State& state) 
{
  for (auto _ : state)
  {
        constexpr SquareMatrix<3, float, EMatrixConvention::ColumnMajor> matConstColumnMajorSqrt (  2.f, 1.f, 3.f, 
                                                                                                    4.f, 2.f,-1.f,
                                                                                                    2.f,-1.f, 1.f);

        SquareMatrix<3, float, EMatrixConvention::ColumnMajor> rst = matConstColumnMajorSqrt.getReverse();

        benchmark::DoNotOptimize(rst);
        //benchmark::ClobberMemory();
  }
}
// Register the function as a benchmark
BENCHMARK(BM_NewReverseMatrixAtCompileTime);

static void BM_NewReverseMatrixAtRunTime(benchmark::State& state) 
{
  std::srand (time(NULL));

  for (auto _ : state)
  {
        SquareMatrix<3, float, EMatrixConvention::ColumnMajor> rst (  RAND_FLOAT, RAND_FLOAT, RAND_FLOAT, 
                                                                      RAND_FLOAT, RAND_FLOAT, RAND_FLOAT,
                                                                      RAND_FLOAT, RAND_FLOAT, RAND_FLOAT);

        rst.reverse();

        benchmark::DoNotOptimize(rst);
        //benchmark::ClobberMemory();
  }
}
// Register the function as a benchmark
BENCHMARK(BM_NewReverseMatrixAtRunTime);

// Define another benchmark
static void BM_OldReverseMatrixAtRunTime(benchmark::State& state)
{
  std::srand (time(NULL));

  for (auto _ : state)
  {
        Engine::Core::Maths::Mat3 rst { RAND_FLOAT, RAND_FLOAT, RAND_FLOAT, 
                                        RAND_FLOAT, RAND_FLOAT, RAND_FLOAT,
                                        RAND_FLOAT, RAND_FLOAT, RAND_FLOAT};

        rst.inverse(rst);

        benchmark::DoNotOptimize(rst);
        //benchmark::ClobberMemory();
  }
}

BENCHMARK(BM_OldReverseMatrixAtRunTime);

BENCHMARK(_);

static void BM_NewTRSMatrixAtCompileTime(benchmark::State& state) 
{
  std::srand (time(NULL));
  
  for (auto _ : state)
  {
        constexpr SquareMatrix<3, float, EMatrixConvention::ColumnMajor> matConstColumnMajorSqrt = SquareMatrix<3, float, EMatrixConvention::ColumnMajor>::identity();

        constexpr Vec3f translation (3.f, 5.f, 6.f);
        constexpr Vec3f rotation (1.f, 0.f, 0.f);
        constexpr Vec3f scale (3.f, 5.f, 6.f);

        SquareMatrix<3, float, EMatrixConvention::ColumnMajor> rst =  matConstColumnMajorSqrt.createScaleMatrix(scale) * 
                                                                      matConstColumnMajorSqrt.createRotationArroundAxisMatrix(rotation, 60_deg) *
                                                                      matConstColumnMajorSqrt.createScaleMatrix(scale);
        benchmark::DoNotOptimize(rst);
        //benchmark::ClobberMemory();
  }
}
// Register the function as a benchmark
BENCHMARK(BM_NewTRSMatrixAtCompileTime);

static void BM_NewTRSMatrixAtRunTime(benchmark::State& state) 
{
  std::srand (time(NULL));

  for (auto _ : state)
  {
        SquareMatrix<3, float, EMatrixConvention::ColumnMajor> matConstColumnMajorSqrt;
        matConstColumnMajorSqrt.generateIdentity();

        const Vec3f translation  (RAND_FLOAT, RAND_FLOAT, RAND_FLOAT);
        const Vec3f rotation     (RAND_FLOAT, RAND_FLOAT, RAND_FLOAT);
        const Vec3f scale        (RAND_FLOAT, RAND_FLOAT, RAND_FLOAT);

        SquareMatrix<3, float, EMatrixConvention::ColumnMajor> rst =  SquareMatrix<3, float, EMatrixConvention::ColumnMajor>::createScaleMatrix(scale) * 
                                                                      SquareMatrix<3, float, EMatrixConvention::ColumnMajor>::createRotationArroundAxisMatrix(rotation.getNormalized(), FoxMath::Angle::Angle<FoxMath::Angle::EAngleType::Radian, float>(RAND_FLOAT)) *
                                                                      SquareMatrix<3, float, EMatrixConvention::ColumnMajor>::createScaleMatrix(scale);
        benchmark::DoNotOptimize(rst);
        //benchmark::ClobberMemory();
  }
}
// Register the function as a benchmark
BENCHMARK(BM_NewTRSMatrixAtRunTime);

// Define another benchmark
static void BM_OldTRSMatrixAtRunTime(benchmark::State& state)
{
  std::srand (time(NULL));

  for (auto _ : state)
  {
        Engine::Core::Maths::Mat3 matConstColumnMajorSqrt();

        const Engine::Core::Maths::Vec3 translation  {RAND_FLOAT, RAND_FLOAT, RAND_FLOAT};
        const Engine::Core::Maths::Vec3 rotation     {RAND_FLOAT, RAND_FLOAT, RAND_FLOAT};
        const Engine::Core::Maths::Vec3 scale        {RAND_FLOAT, RAND_FLOAT, RAND_FLOAT};

        Engine::Core::Maths::Mat3 rst =   Engine::Core::Maths::Mat3::createScaleMatrix(scale) *
                                          Engine::Core::Maths::Mat3::createRotationArroundAxisMatrix(rotation.getNormalize(), RAND_FLOAT) *
                                          Engine::Core::Maths::Mat3::createScaleMatrix(scale);
        benchmark::DoNotOptimize(rst);
        //benchmark::ClobberMemory();
  }
}

BENCHMARK(BM_OldTRSMatrixAtRunTime);
BENCHMARK(_);

static void BM_NewAngle(benchmark::State& state)
{
  std::srand (time(NULL));

  for (auto _ : state)
  {
    FoxMath::Angle::Angle<FoxMath::Angle::EAngleType::Radian, float> rst(FoxMath::Angle::Angle<FoxMath::Angle::EAngleType::Degree, float>(RAND_FLOAT));
    float rstRad = static_cast<float>(rst);
    
    benchmark::DoNotOptimize(rstRad);
    //benchmark::ClobberMemory();
  }
}

BENCHMARK(BM_NewAngle);

static void BM_OldAngle(benchmark::State& state)
{
  std::srand (time(NULL));

  for (auto _ : state)
  {
    float rstRad = RAND_FLOAT *  M_PI / 180.f;

    benchmark::DoNotOptimize(rstRad);
    //benchmark::ClobberMemory();
  }
}

BENCHMARK(BM_OldAngle);



BENCHMARK_MAIN();

