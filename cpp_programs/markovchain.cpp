// File:   markovchain.cpp
// Author: Gregory K. Bowne
// Date:   03 MAR 2023
// Time:   01:43:10
// Brief:  This program will help with Markov Chain. The algorithm implemented in this code is a discrete-time Markov chain simulation.
// Specifically, it simulates a continuous-time Markov chain with a discretized time step.  The current implementation generates a new
// random number for each state transition, which can be inefficient for long simulations. 
// This program is C++ 11

#include <iostream>
#include <array>
#include <random>
#include <stdexcept>

// Define the states using enum class for strong typing
enum class State { A, B, C };

// Use std::array for transition matrix and initial probabilities for better type safety
constexpr std::array<std::array<double, 3>, 3> transitionMatrix = {
    std::array<double, 3>{0.2, 0.5, 0.3}, // Transition probabilities from State A
    std::array<double, 3>{0.4, 0.3, 0.3}, // Transition probabilities from State B
    std::array<double, 3>{0.1, 0.6, 0.3}  // Transition probabilities from State C
};

// Use std::array for initial state probabilities
constexpr std::array<double, 3> initialProbabilities = {0.3, 0.4, 0.3};

// Function to generate a random state based on the given probabilities
State getRandomState(const std::array<double, 3>& probabilities, std::mt19937& gen) {
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    double randomValue = dis(gen);

    double cumulativeProbability = 0.0;
    for (size_t i = 0; i < probabilities.size(); ++i) {
        cumulativeProbability += probabilities[i];
        if (randomValue < cumulativeProbability) {
            return static_cast<State>(i);
        }
    }

    throw std::logic_error("Internal error: Invalid state selection logic.");
}

int main() {
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Initialize the current state randomly based on the initial probabilities
    State currentState = getRandomState(initialProbabilities, gen);

    // Simulate the Markov chain for a few steps
    for (int i = 0; i < 10; ++i) {
        std::cout << "Current State: " << static_cast<int>(currentState) << std::endl;

        // Directly access the transition probabilities for the current state
        const auto& row = transitionMatrix[static_cast<int>(currentState)];

        // Generate the next state based on the transition probabilities
        currentState = getRandomState(row, gen);
    }

    return 0;
}
