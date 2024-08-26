#include "gxhash.h"

#include <benchmark/benchmark.h>
#include <cstddef>
#include <cstdint>

constexpr char test_string[] =
    "18626f80e795d6e359ad-1718-4319-9dd5-b23fce1a51736f7c5150-0ef0-43ef-a0b9-"
    "f3c41a9c3c054b608f15-9b6d-4967-ac9f-78f729f0a19cd5990bdd-d841-4155-8bd8-"
    "0ae711f69c16f889f1b5-ecfe-4fb2-bba2-b63ce5b73f1489f40481-e583-474d-9a2a-"
    "1905f463e9a7214f32bb-895c-4bfd-8fe3-4a10a15694bcf97c62b7-ea46-461b-bc11-"
    "360124da22d0855df3e1-94ac-432c-976a-7ff09c69467ee3f9be7f-ccc1-44c5-9200-"
    "4f6e3d3a20c151901eb8-e058-437f-8daf-0f18ef022bf44f93715d-7f85-4439-9169-"
    "506fbd514322c1bf9822-d098-461d-a8a7-0dfd038d1b4bd342d751-4963-46eb-9875-"
    "642ad3c03e0e7b923421-2712-47e4-9c93-68e80d3be232879e3d3c-f9b6-4e11-b493-"
    "edecc20e15ee45eeefd7-fe2c-44fd-b140-ecfb9efd89bccfe19cd2-ded7-4a9f-94a6-"
    "cd082f445fc38c4739ce-8255-4464-a522-71b4107d83231d451aba-49f5-4381-a4b5-"
    "515191d4c3d3ef3359c5-4319-4c38-be01-479383a968aab46211ae-a35d-48c8-a62a-"
    "521b297a3f1ab1c7f2aa-dc17-42c9-b710-f78c60be83bb6719086b-c06d-418a-8446-"
    "015ff9eec588ebc71f3a-5d20-48fc-9701-0a8f968765ca8107a3bf-c196-42c8-9cdc-"
    "09b7479509560c487552-356a-4ce9-93d9-f1865bd8ecdc4b657887-d5f9-4e8e-a9b7-"
    "c9b65cfb79162ffe4843-078e-4b0e-9c67-7b0e288954ef4216684e-c8e0-4e68-a136-"
    "f0daa4518f7e5bf4b884-fa0f-4363-89a1-0c2cc9fde7722716f059-844f-4f5f-a2f9-"
    "88342831982e6674de68-0065-4c45-860f-a8fa5a5a459bbb2aba10-2759-4304-a560-"
    "3d2854744789f1b0df5d-04a8-4d50-a6a1-1555ed7099de9d774ae1-af11-4eee-9ff8-"
    "1905f463e9a7214f32bb-895c-4bfd-8fe3-4a10a15694bcf97c62b7-ea46-461b-bc11-"
    "360124da22d0855df3e1-94ac-432c-976a-7ff09c69467ee3f9be7f-ccc1-44c5-9200-"
    "4f6e3d3a20c151901eb8-e058-437f-8daf-0f18ef022bf44f93715d-7f85-4439-9169-"
    "506fbd514322c1bf9822-d098-461d-a8a7-0dfd038d1b4bd342d751-4963-46eb-9875-"
    "642ad3c03e0e7b923421-2712-47e4-9c93-68e80d3be232879e3d3c-f9b6-4e11-b493-"
    "edecc20e15ee45eeefd7-fe2c-44fd-b140-ecfb9efd89bccfe19cd2-ded7-4a9f-94a6-"
    "cd082f445fc38c4739ce-8255-4464-a522-71b4107d83231d451aba-49f5-4381-a4b5-"
    "515191d4c3d3ef3359c5-4319-4c38-be01-479383a968aab46211ae-a35d-48c8-a62a-"
    "521b297a3f1ab1c7f2aa-dc17-42c9-b710-f78c60be83bb6719086b-c06d-418a-8446-"
    "015ff9eec588ebc71f3a-5d20-48fc-9701-0a8f968765ca8107a3bf-c196-42c8-9cdc-"
    "09b7479509560c487552-356a-4ce9-93d9-f1865bd8ecdc4b657887-d5f9-4e8e-a9b7-"
    "c9b65cfb79162ffe4843-078e-4b0e-9c67-7b0e288954ef4216684e-c8e0-4e68-a136-"
    "f0daa4518f7e5bf4b884-fa0f-4363-89a1-0c2cc9fde7722716f059-844f-4f5f-a2f9-"
    "88342831982e6674de68-0065-4c45-860f-a8fa5a5a459bbb2aba10-2759-4304-a560-"
    "3d2854744789f1b0df5d-04a8-4d50-a6a1-1555ed7099de9d774ae1-af11-4eee-9ff8-"
    "0f396aa8a4cb09cb0c9e-0b0f-49e8-9696-d395e3d922ce8f2d7cf1-94cc-49de-a4fc-"
    "8efc5521bcfdeacb96cc-6b06-4e31-b1f9-3f767084aa57151e924d-2efe-4a54-8651-";

constexpr int ITER = 1000;

void BM_gxhash(benchmark::State &state) {
  auto str = std::string_view(test_string, state.range(0));

  size_t len = str.length();
  size_t bytes = 0;

  for (auto s : state) {
    for (int i = 0; i < ITER; i++) {
      auto hash = gxhash::gxhash32(
          reinterpret_cast<const uint8_t *>(str.data()), len, 0);
      benchmark::DoNotOptimize(hash);
      bytes += len;
    }
  }
  state.SetBytesProcessed(bytes);
}

BENCHMARK(BM_gxhash)
    ->Arg(5)
    ->Arg(7)
    ->Arg(17)
    ->Arg(29)
    ->Arg(47)
    ->Arg(77)
    ->Arg(120)
    ->Arg(147)
    ->Arg(349)
    ->Arg(679)
    ->Arg(1440)
    ->Arg(sizeof(test_string) - 1);

BENCHMARK_MAIN();
