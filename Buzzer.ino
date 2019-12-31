const int buzzerPin = 5;

int buzzerMelodyWork[][2] = {{7000, 50}, {0, 0}};
int buzzerMelodyBreak[][2] = {{7000, 50}, {0, 150}, {7000, 50}, {0, 0}};
int buzzerMelodyLongBreak[][2] = {{7000, 50}, {0, 150}, {7000, 50}, {0, 150}, {7000, 50}, {0, 0}};
int (*buzzerCurrentMelody)[2] = NULL;
int buzzerCurrentNote = 0;
unsigned long buzzerNoteStarted = 0;

void buzzerInit() {
}

void buzzerUpdate() {
  if (!buzzerCurrentMelody)
    return;

  unsigned long now = millis();
  if (now - buzzerNoteStarted > buzzerCurrentMelody[buzzerCurrentNote][1]) {
    buzzerPlayNote(buzzerCurrentMelody, ++buzzerCurrentNote);
  }

}

void buzzerPlayNote(int (*melody)[2], int note) {
  int freq = melody[note][0];
  int dur = melody[note][1];

  if (dur == 0) {
    noTone(buzzerPin);
    buzzerCurrentMelody = NULL;
    return;
  }

  buzzerNoteStarted = millis();
  if (freq)
    tone(buzzerPin, freq, dur);
  else
    noTone(buzzerPin);
}

void buzzerWork() {
  buzzerCurrentMelody = buzzerMelodyWork;
  buzzerCurrentNote = 0;
  buzzerPlayNote(buzzerCurrentMelody, buzzerCurrentNote);
}

void buzzerBreak() {
  buzzerCurrentMelody = buzzerMelodyBreak;
  buzzerCurrentNote = 0;
  buzzerPlayNote(buzzerCurrentMelody, buzzerCurrentNote);
}

void buzzerLongBreak() {
  buzzerCurrentMelody = buzzerMelodyLongBreak;
  buzzerCurrentNote = 0;
  buzzerPlayNote(buzzerCurrentMelody, buzzerCurrentNote);
}
