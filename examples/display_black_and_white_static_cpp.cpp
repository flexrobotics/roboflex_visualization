#include <iostream>
#include <xtensor/xrandom.hpp>
#include "roboflex_core/core_messages/core_messages.h"
#include "roboflex_core/core_nodes/core_nodes.h"
#include "roboflex_core/util/utils.h"
#include "roboflex_visualization/visualization.h"

using namespace roboflex;

int main()
{
    auto frequency_generator = nodes::FrequencyGenerator(30.0);

    auto random_tensor_creator = nodes::MapFun([](core::MessagePtr /*m*/) {
        xt::xtensor<uint8_t, 2> d = xt::random::randint({480, 640, 2}, 0, 255);
        xt::view(d, xt::range(100, 200), xt::all()) = 0;
        xt::view(d, xt::all(), xt::range(100, 200)) = 128;
        return core::TensorMessage<uint8_t, 2>::Ptr(d);
    });

    auto visualizer = visualization::BlackAndWhiteTV(24.0, 640, 480, "t", {-1,-1}, false, false, "tuned to a dead channel");

    frequency_generator > random_tensor_creator > visualizer;

    frequency_generator.start();
    visualizer.run();
    frequency_generator.stop();

    std::cout << "DONE" << std::endl;
    return 0;
}