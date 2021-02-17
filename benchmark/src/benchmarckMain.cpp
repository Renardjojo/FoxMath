#include "benchmark/benchmark.h"
#include "Vector/Vector.hpp"
#include "Matrix/Matrix.hpp"
#include "Angle/Angle.hpp"

#include "Quaternion/Quaternion.hpp"

#include <stdlib.h>     /* std::rand, std::rand */
#include <time.h>       /* time */

using namespace FoxMath;

#define RAND_FLOAT (float)std::rand()
static void _ (benchmark::State& state){}

static void BM_QuaternionV1(benchmark::State& state) 
{
  for (auto _ : state)
  {
        Vector3<> vec {5.f, 10.f, 6.f};
        Vector3<> axis {0.f, 0.5f, 0.5f};
        axis.normalize();
        Quaternion<>::RotateVector(vec, axis, 3_rad);

        benchmark::DoNotOptimize(vec);
        benchmark::ClobberMemory();
  }
}
// Register the function as a benchmark
BENCHMARK(BM_QuaternionV1);

static void BM_QuaternionV2(benchmark::State& state) 
{
  for (auto _ : state)
  {
        Vector3<> vec {5.f, 10.f, 6.f};
        Vector3<> axis {0.f, 0.5f, 0.5f};
        axis.normalize();
        Quaternion<>::RotateVector2(vec, axis, 3_rad);

        benchmark::DoNotOptimize(vec);
        benchmark::ClobberMemory();
  }
}
// Register the function as a benchmark
BENCHMARK(BM_QuaternionV2);

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
        benchmark::ClobberMemory();
  }
}
// Register the function as a benchmark
BENCHMARK(BM_NewReverseMatrixAtRunTime);

// Define another benchmark
/*
static void BM_OldReverseMatrixAtRunTime(benchmark::State& state)
{
  std::srand (time(NULL));

  for (auto _ : state)
  {
        FoxMath::Mat3 rst { RAND_FLOAT, RAND_FLOAT, RAND_FLOAT, 
                                        RAND_FLOAT, RAND_FLOAT, RAND_FLOAT,
                                        RAND_FLOAT, RAND_FLOAT, RAND_FLOAT};

        rst.inverse(rst);

        benchmark::DoNotOptimize(rst);
        benchmark::ClobberMemory();
  }
}

BENCHMARK(BM_OldReverseMatrixAtRunTime);
*/
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
        const Vec3f translation  (RAND_FLOAT, RAND_FLOAT, RAND_FLOAT);
        const Vec3f rotation     (RAND_FLOAT, RAND_FLOAT, RAND_FLOAT);
        const Vec3f scale        (RAND_FLOAT, RAND_FLOAT, RAND_FLOAT);

        Mat4f<EMatrixConvention::ColumnMajor> rst = Mat4f<EMatrixConvention::ColumnMajor>::createTRSMatrix(translation, rotation, scale);
        benchmark::DoNotOptimize(rst);
        //benchmark::ClobberMemory();
  }
}
// Register the function as a benchmark
BENCHMARK(BM_NewTRSMatrixAtRunTime);
/*
// Define another benchmark
static void BM_OldTRSMatrixAtRunTime(benchmark::State& state)
{
  std::srand (time(NULL));

  for (auto _ : state)
  {
        const FoxMath::Vec3 translation  {RAND_FLOAT, RAND_FLOAT, RAND_FLOAT};
        const FoxMath::Vec3 rotation     {RAND_FLOAT, RAND_FLOAT, RAND_FLOAT};
        const FoxMath::Vec3 scale        {RAND_FLOAT, RAND_FLOAT, RAND_FLOAT};

        FoxMath::Mat4 rst = FoxMath::Mat4::createTRSMatrix(scale, rotation, translation);
        benchmark::DoNotOptimize(rst);
        //benchmark::ClobberMemory();
  }
}

BENCHMARK(BM_OldTRSMatrixAtRunTime);
BENCHMARK(_);*/

static void BM_NewAngle(benchmark::State& state)
{
  std::srand (time(NULL));

  for (auto _ : state)
  {
    FoxMath::Angle<FoxMath::EAngleType::Radian, float> rst(FoxMath::Angle<FoxMath::EAngleType::Degree, float>(RAND_FLOAT));
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
/*
BENCHMARK(BM_OldAngle);
*/


BENCHMARK_MAIN();

