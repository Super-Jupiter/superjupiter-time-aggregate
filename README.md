# SuperJupiter TimeAggregate

Fixed-period observation summaries with explicit empty buckets and coverage.

**Version 0.1.1: evolving preview. Hardware validation pending.**

Original MIT-licensed portable C++11 by [SuperJupiter](https://www.superjupiter.net).
No mandatory service, hidden clock reads, network calls or heap allocation in the core.

## What it does

Buckets start at the first accepted timestamp and are half-open [start,start+period).
push returns Completed when an observation enters a later bucket; takeCompleted reads the last completed bucket.
Skipped empty buckets are counted, not fabricated as measurements. Consume Completed results before another push.
Coverage is first-to-last finite observation span divided by period, not continuous sensing proof.
Invalid observations are counted and retained in bucket totals; means use finite samples only. No time weighting.

## Install

PlatformIO exact release (after registry publication):

```ini
lib_deps = superjupiter/SuperJupiterTimeAggregate@0.1.1
```

Arduino: use the versioned [GitHub release ZIP](https://github.com/Super-Jupiter/superjupiter-time-aggregate/releases/tag/v0.1.1).
Library Manager registration and index propagation are separate steps; check the official index before relying on IDE availability.

## Example

```cpp
#include <SuperJupiterTimeAggregate.h>
using namespace superjupiter::time_aggregate;
int main() {
TimeAggregate minutes(60000);
minutes.push(20,0);minutes.push(21,1000);minutes.push(22,60000);
Summary previous;
minutes.takeCompleted(previous);
return 0;
}

```

For Arduino, open `examples/Minimal`. It uses synthetic data only.
Results are deliberately local so applications can inspect outcomes before adding I/O.

## CMake

```cmake
add_subdirectory(path/to/superjupiter-time-aggregate)
target_link_libraries(your_app PRIVATE SuperJupiter::TimeAggregate)
```

For an installed package use `find_package(SuperJupiterTimeAggregate 0.1 CONFIG REQUIRED)`.
Top-level CMake builds tests/examples; a subproject does not enable developer tools by default.

## Documentation and verification

- [API and boundaries](https://github.com/Super-Jupiter/superjupiter-time-aggregate/blob/v0.1.1/docs/API.md)
- [Tests](https://github.com/Super-Jupiter/superjupiter-time-aggregate/blob/v0.1.1/tests/test.cpp)
- [Validation status](https://github.com/Super-Jupiter/superjupiter-time-aggregate/blob/v0.1.1/docs/VALIDATION.md)
- [Shared conventions](https://github.com/Super-Jupiter/superjupiter-time-aggregate/blob/v0.1.1/docs/CONVENTIONS.md)
- [Migration policy](https://github.com/Super-Jupiter/superjupiter-time-aggregate/blob/v0.1.1/docs/MIGRATION.md)

```sh
cmake -S . -B build/cmake
cmake --build build/cmake
ctest --test-dir build/cmake --output-on-failure
python3 tools/check_release.py --tag v0.1.1
```

Keep raw observations and their provenance in your application. Derived results are not physical truth.
Do not use fast-math or finite-math-only compiler assumptions. AVR double may have float precision.
Software tests, board compilation and physical validation are reported separately.

## Fits the SuperJupiter measurement portfolio

Complements [SensorQuality](https://github.com/Super-Jupiter/superjupiter-sensor-quality) and
[SampleWindow](https://github.com/Super-Jupiter/superjupiter-sample-window) without a required dependency.
Each component can be used independently. Domain models, customer data and proprietary applications are excluded.

## Support and licence

MIT. Report reproducible bugs through repository issues; private security reports: info@superjupiter.net.
Include version, configuration, inputs, expected and observed behaviour. No credentials or private customer data.


## Compatibility review 0.1.1

This patch includes independent regression tests and a reviewed [interoperability contract](https://github.com/Super-Jupiter/superjupiter-time-aggregate/blob/v0.1.1/docs/INTEROPERABILITY.md). Hardware validation pending.

- Removed unused duplicated math helpers and unnecessary includes.
- Valid long consecutive intervals cross buckets and wraps correctly; stable means and explicit numeric validity retain accurate finite counts.
