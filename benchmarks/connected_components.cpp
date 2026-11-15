#include <bimg/core/image2d.hpp>
#include <bimg/core/neighborhoods/c4.hpp>
#include <bimg/core/neighborhoods/c8.hpp>
#include <bimg/io/imread.hpp>
#include <bimg/labeling/connected_components.hpp>

#include <benchmark/benchmark.h>

#include <filesystem>
#include <print>

using namespace bimg;

static constexpr const char* BENCHMARK_IMAGES_DIR = "/home/baptou/Pictures/databases/condat/gray";
static constexpr int         NUMBER_OF_ITERATIONS = 10;
static constexpr auto        TIME_UNIT            = benchmark::kMillisecond;

static std::vector<std::filesystem::path> benchmark_images;

static void load_benchmark_images()
{
  try
  {
    for (const auto entry : std::filesystem::directory_iterator(BENCHMARK_IMAGES_DIR))
    {
      benchmark_images.emplace_back(entry.path());
    }
  }
  catch (const std::filesystem::filesystem_error& e)
  {
    std::print(stderr, "Load directory error: {}", e.what());
    std::exit(1);
  }
}

static void build_arguments(benchmark::Benchmark* b)
{
  load_benchmark_images();
  for (int i = 0; i < benchmark_images.size(); i++)
  {
    b->Arg(i);
  }
}

class ConnectedComponentsFixture : public benchmark::Fixture
{
public:
  void SetUp(benchmark::State& state)
  {
    const int image_id = state.range(0);
    io::imread(benchmark_images[image_id].c_str(), m_img);
  }

protected:
  image2d<std::uint8_t> m_img;
};

struct BMConnectedComponentsC4 : public ConnectedComponentsFixture
{
  void run(benchmark::State& state)
  {
    for (auto _ : state)
      labelling::connected_components(m_img, c4);
  }
};

struct BMConnectedComponentsC8 : public ConnectedComponentsFixture
{
  void run(benchmark::State& state)
  {
    for (auto _ : state)
      labelling::connected_components(m_img, c8);
  }
};

BENCHMARK_DEFINE_F(BMConnectedComponentsC4, BMConnectedComponentsC4)(benchmark::State& state)
{
  run(state);
}

BENCHMARK_DEFINE_F(BMConnectedComponentsC8, BMConnectedComponentsC8)(benchmark::State& state)
{
  run(state);
}

BENCHMARK_REGISTER_F(BMConnectedComponentsC4, BMConnectedComponentsC4)
    ->Apply(build_arguments)
    ->Iterations(NUMBER_OF_ITERATIONS)
    ->Unit(TIME_UNIT);

BENCHMARK_REGISTER_F(BMConnectedComponentsC8, BMConnectedComponentsC8)
    ->Apply(build_arguments)
    ->Iterations(NUMBER_OF_ITERATIONS)
    ->Unit(TIME_UNIT);

BENCHMARK_MAIN();