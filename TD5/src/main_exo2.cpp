#include <iostream>
#include <numeric>
#include <functional>
#include <random>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>



std::vector<float> probabilities_from_count(std::vector<int> const& counts){
    
    int total = std::accumulate(counts.begin(), counts.end(), 0);
    if (total == 0) return std::vector<float>(counts.size(), 0.0f);
    std::vector<float> probabilities;

    for (int count : counts) {
        probabilities.push_back(static_cast<float>(count) / total);
    }
    
    return probabilities;

}

const std::vector<int> expected_insect_counts {
    75, 50, 100, 20, 400, 150, 60, 10, 40, 90, 5
};

enum class Insect {
    ClassicBee, Ladybug, Butterfly, Dragonfly, Ant,
    Grasshopper, Beetle, Wasp, Caterpillar, Spider, GuimielBee
};

const std::vector<Insect> insect_values {
    Insect::ClassicBee, Insect::Ladybug, Insect::Butterfly, Insect::Dragonfly,
    Insect::Ant, Insect::Grasshopper, Insect::Beetle, Insect::Wasp,
    Insect::Caterpillar, Insect::Spider, Insect::GuimielBee
};

const std::unordered_map<Insect, std::string> insect_to_string {
    {Insect::ClassicBee, "ClassicBee"}, {Insect::Ladybug, "Ladybug"},
    {Insect::Butterfly, "Butterfly"}, {Insect::Dragonfly, "Dragonfly"},
    {Insect::Ant, "Ant"}, {Insect::Grasshopper, "Grasshopper"},
    {Insect::Beetle, "Beetle"}, {Insect::Wasp, "Wasp"},
    {Insect::Caterpillar, "Caterpillar"}, {Insect::Spider, "Spider"},
    {Insect::GuimielBee, "GuimielBee"}
};

std::vector<std::pair<Insect, int>> get_insect_observations(
    const size_t number_of_observations,
    std::vector<float> const& insect_probabilities,
    const unsigned int seed = std::random_device{}()) {
    // Create a random engine with a given seed
    std::default_random_engine random_engine(seed);

    auto randInsectIndex { std::bind(std::discrete_distribution<size_t>{insect_probabilities.begin(), insect_probabilities.end()}, random_engine) };
    
    std::vector<std::pair<Insect, int>> observations {};
    observations.reserve(number_of_observations);

    for(size_t i {0}; i < number_of_observations; ++i) {
        size_t const random_insect_index { randInsectIndex() };
        Insect const random_insect { insect_values[random_insect_index] };
        
        //If we have already seen the same insect, increment the count on the last observation
        auto& previous_observation { observations.back() };
        if(previous_observation.first == random_insect) {
            previous_observation.second++;
            i -= 1;
        } else {
            observations.push_back({random_insect, 1});
        }
    }

    return observations;
}


int main() {


    std::vector<float> probabilities = probabilities_from_count(expected_insect_counts);
    size_t num_observations = 10000;
    // unsigned int seed = 33;
    std::vector<std::pair<Insect, int>> observations = get_insect_observations(num_observations, probabilities); //seed);

    std::unordered_map<Insect, int> insect_counts;
    for (const auto& observation : observations) {
        insect_counts[observation.first] += observation.second;
    }

    std::cout << "\n Résultats des observations (" << num_observations << " insectes observés) \n";
    std::cout << "---------------------------------------------------\n";
    for (const auto& [insect, count] : insect_counts) {
        std::cout << insect_to_string.at(insect) << " : " << count << " individus\n";
    }


    std::cout << "Probabilités normalisées :\n";
    for (float prob : probabilities) {
        std::cout << prob << " ";
    }
    std::cout << std::endl;

    return 0;
}
