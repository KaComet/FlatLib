#ifndef FLATLIB_HAPPYLUT_H
#define FLATLIB_HAPPYLUT_H

#include <iostream>
#include <array>

namespace HappyLUT {
// Evaluator:
//   output_Type is the output type of the LUT's function (int, double, ect.)
//   step_Type is the type of the step (int, double, ect.)
    template<class output_Type, class step_Type>
    class Evaluator {
    public:
        typedef output_Type outType;
        typedef step_Type stepType;

        // Returns the number of values the evaluator can output.
        // Used for determining the number of values in a LUT.
        constexpr virtual std::size_t size() {
            return 0;
        };

        // Returns the first step in the evaluator.
        constexpr virtual step_Type start() {
            return step_Type();
        };

        // Returns the last step in the evaluator.
        constexpr virtual step_Type end() {
            return step_Type();
        };

        // Takes a step value and returns the next step value in the evaluator.
        constexpr virtual step_Type next(step_Type now) {
            return step_Type();
        };

        // Takes a step value and returns the output of the evaluator's function.
        constexpr virtual output_Type calculate(stepType now) {
            return output_Type();
        };

    protected:
        // Calculates the last step in the evaluator.
        constexpr virtual step_Type endCalc() {
            return step_Type();
        };
    };

// EvaluateLUT:
//  Using a Generator, EvaluateLUT returns an evaluated lookup table.
    template<class Generator>
    constexpr auto EvaluateLUT(Generator generator) {
        using zeug = typename Generator::outputType;
        using stepType = typename Generator::stepType;
        std::array<zeug, generator.size()> lut{};
        stepType now = generator.start();
        std::size_t i = 0;
        while (now != generator.end()) {
            lut[i] = generator.calculate(now);
            now = generator.next(now);
            i++;
        }

        return lut;
    }

// Linear Generator:
//     Used for eveluating a LUT's function over a linear range of values. Starting at startInc, which
//   is included in the range. Ending at or less then the endInc, which is included in the range if
//   the step size allows the last value of the range to land on endInc. The step size determines the
//   distance between values of the LUT.
//     O is the output type of the LUT's function (int, double, ect.) S is the type of the step (int, double, ect.)
    template<class O, class S, S startInc, S endInc, S stepSize = 1>
    class LinearGenerator : public Evaluator<O, S> {
    public:
        typedef O outputType;
        typedef S stepType;

        const stepType endValue = endCalc();
        const bool isIncreasing = (endInc >= startInc);

        constexpr std::size_t size() override {
            return ((endInc - startInc) / stepSize) + 1;
        };

        constexpr stepType start() override {
            return startInc;
        }

        constexpr stepType end() override {
            return endValue + stepSize;
        };

        constexpr stepType next(stepType now) override {
            stepType naiveNext = isIncreasing ? (now + stepSize) : (now - stepSize);

            return naiveNext;
        };

        // Takes a step value and returns the output of the evaluator's function. Override this
        // with a function that outputs its result using the your desired function!
        constexpr outputType calculate(stepType now) override {
            return outputType();
        };

    protected:
        constexpr stepType endCalc() override {
            S e = (endInc - startInc) / stepSize;

            return e * stepSize;
        }
    };
}

#endif //FLATLIB_HAPPYLUT_H
