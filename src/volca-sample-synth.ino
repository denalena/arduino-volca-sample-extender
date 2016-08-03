#include <Arduino.h>
#include "bach.h"

#define KVS_CC_SPEED        43
#define KVS_CC_PITCH        44

#define KVS_LOWEST_NOTE     NOTE_C3
#define KVS_HIGHEST_NOTE    NOTE_C7

#define PITCH_BEND_IN_MIN   32
#define PITCH_BEND_IN_MAX   96

#define PITCH_BEND_OUT_MIN  60
#define PITCH_BEND_OUT_MAX  70

#define DRUM_CHANNEL        15
#define PARTS               10

int parts[PARTS] = {
      NOTE_C0,
      NOTE_CS0,
      NOTE_D0,
      NOTE_DS0,
      NOTE_E0,
      NOTE_F0,
      NOTE_FS0,
      NOTE_G0,
      NOTE_GS0,
      NOTE_A0,
  };

int notes[49] = {
        16, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        //19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,             // 2nd octave
        32, 35, 38, 41, 43, 45, 48, 51, 52, 56, 59, 61,             // 3rd octave
        64, 67, 69, 72, 75, 77, 80, 83, 85, 88, 91, 94,             // 4th octave
        96, 97, 99, 100, 102, 103, 104, 106, 107, 108, 109, 111,    // 5th octave
        112
};

int channel = 0;

void setup() {
  Midi::init();
}

void loop() {
    Midi::receive();

    if (Midi::isNoteOn()) {
        channel = Midi::getChannel();

        if (channel >= 0 && channel <= PARTS) {
            playNote();
        }

        if (channel == DRUM_CHANNEL) {
            playSample();
        }
    }

    if (Midi::isPitchBend()) {
        transformPitchBend();
    }

    Midi::send();
}

void playNote() {
    int note = Midi::getNote();

    if (note >= KVS_LOWEST_NOTE && note <= KVS_HIGHEST_NOTE) {
        int idx = note - KVS_LOWEST_NOTE;
        int speed = notes[idx];

        Midi::sendCC(KVS_CC_SPEED, speed, channel);
    } else {
        Midi::discard();
    }
}

void playSample() {
    int note = Midi::getNote();
    int root = Notes::getRootNote(note);

    if (root < PARTS) {
        channel = root;
        Midi::setChannel(root);
    } else {
        Midi::discard();
    }
}

void transformPitchBend() {
    int pitch = map(Midi::data[2], PITCH_BEND_IN_MIN, PITCH_BEND_IN_MAX, PITCH_BEND_OUT_MIN, PITCH_BEND_OUT_MAX);

    Midi::sendCC(KVS_CC_PITCH, pitch, channel);
    Midi::discard();
}
