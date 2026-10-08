#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>

// Class to perform basic Digital Signal Processing operations
class SignalProcessor {
private:
    std::vector<double> signal;

public:
    SignalProcessor(const std::vector<double>& inputSignal) : signal(inputSignal) {}

    // Moving Average Filter to reduce noise
    std::vector<double> movingAverageFilter(size_t windowSize) const {
        std::vector<double> filtered;
        if (windowSize == 0 || windowSize > signal.size()) return filtered;

        for (size_t i = 0; i <= signal.size() - windowSize; ++i) {
            double sum = 0.0;
            for (size_t j = 0; j < windowSize; ++j) {
                sum += signal[i + j];
            }
            filtered.push_back(sum / windowSize);
        }
        return filtered;
    }

    // Calculate Root Mean Square (RMS) of the signal
    double calculateRMS() const {
        if (signal.empty()) return 0.0;
        double sumSquares = 0.0;
        for (double val : signal) {
            sumSquares += val * val;
        }
        return std::sqrt(sumSquares / signal.size());
    }

    // Find peak values in the signal above a given threshold
    std::vector<double> detectPeaks(double threshold) const {
        std::vector<double> peaks;
        for (size_t i = 1; i < signal.size() - 1; ++i) {
            if (signal[i] > signal[i - 1] && signal[i] > signal[i + 1] && signal[i] >= threshold) {
                peaks.push_back(signal[i]);
            }
        }
        return peaks;
    }
};

int main() {
    // Sample noisy sine wave data
    std::vector<double> rawSignal = {0.1, 0.8, 1.2, 0.9, 0.2, -0.7, -1.1, -0.6, 0.3, 1.1, 0.4};

    SignalProcessor processor(rawSignal);

    double rms = processor.calculateRMS();
    std::cout << "Signal RMS Value: " << rms << std::endl;

    auto filteredSignal = processor.movingAverageFilter(3);
    std::cout << "Filtered Signal (Window Size 3): ";
    for (double val : filteredSignal) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    auto peaks = processor.detectPeaks(0.8);
    std::cout << "Detected Peaks (Threshold 0.8): ";
    for (double peak : peaks) {
        std::cout << peak << " ";
    }
    std::cout << std::endl;

    return 0;
}
