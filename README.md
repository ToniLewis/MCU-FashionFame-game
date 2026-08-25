# Mix & Match Runway

An interactive Arduino Uno fashion-game prototype built in Wokwi. Players use physical-style buttons to select outfit categories, then press **Confirm** to evaluate the combination. The system returns instant visual, audio, and serial feedback.

## Live Simulation

[Open the Wokwi simulation](https://wokwi.com/projects/473290527385806849)

## Project Overview

Mix & Match Runway demonstrates a hardware/software interface using an Arduino Uno simulation. Five pushbuttons represent clothing-selection controls:

- **Top**
- **Bottom**
- **Shoes**
- **Accessory**
- **Confirm**

Each category button cycles through two choices. When the player presses Confirm, the Arduino evaluates the current outfit against built-in style rules and reports either a good match or a style clash.

## Hardware

- Arduino Uno
- 5 pushbuttons
- RGB LED
- Piezo buzzer

## Pin Map

| Component | Arduino Uno pin |
|---|---:|
| Top button | D2 |
| Bottom button | D3 |
| Shoes button | D4 |
| Accessory button | D5 |
| Confirm button | D6 |
| Buzzer | D8 |
| RGB LED red channel | D9 |
| RGB LED green channel | D10 |
| RGB LED blue channel | D11 |
| RGB LED common cathode | GND |

The buttons use `INPUT_PULLUP`: each button connects its assigned digital pin to GND. A button press is therefore read as `LOW`.

## Features

- Software-debounced button input
- Two selectable choices per outfit category
- Outfit state tracking
- Confirm-button validation for complete outfits
- Good-match and style-clash rules
- RGB LED feedback: green for a good match, red for a clash, blue for incomplete selections
- Buzzer feedback with different tones
- Score counter that persists during the session
- Consecutive winning-streak tracker
- Serial Monitor status messages for testing and debugging

## Style Rules

The current firmware awards a good match for either of these combinations:

1. **Choice 1** Top + **Choice 1** Bottom + **Choice 1** Shoes
2. **Choice 2** Top + **Choice 2** Bottom + **Choice 2** Accessory

Each good match earns 10 points. A clash keeps the existing score but resets the winning streak.

## How to Run

1. Open the [Wokwi simulation](https://wokwi.com/projects/473290527385806849).
2. Click the green Play button.
3. Open the Serial Monitor.
4. Press each category button to cycle between Choice 1 and Choice 2.
5. Select Top, Bottom, Shoes, and Accessory.
6. Press Confirm to evaluate the outfit.

## Expected Behavior

A successful round prints a result similar to:

```text
----- RESULT -----
Round: 1
Outfit: Top=1 | Bottom=1 | Shoes=1 | Accessory=1
GOOD MATCH! +10 points
Total score: 10
Winning streak: 1
```

A non-matching round prints:

```text
STYLE CLASH! Try another combination.
Total score: 20
Winning streak reset to 0.
```

## Repository Layout

```text
mix-match-runway/
├── firmware/
│   ├── sketch.ino
│   └── diagram.json
├── screenshots/
│   ├── circuit-overview.png
│   ├── good-match-result.png
│   └── style-clash-result.png
└── README.md
```

## Skills Demonstrated

- Arduino programming in C/C++
- Digital input/output and pin mapping
- Software debounce and event handling
- State management and rule-based scoring
- RGB LED and buzzer output control
- Hardware simulation with Wokwi
- Debugging through Serial Monitor output

## Future Improvements

- Replace numeric choices with named clothing/color options
- Add more outfit combinations and scoring rules
- Store a persistent leaderboard in a CSV file through a connected backend
- Connect a physical Arduino over USB using the same serial-message design
- Add a Python backend to evaluate rules outside the microcontroller
