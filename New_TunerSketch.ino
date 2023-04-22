#include <LiquidCrystal.h> // Include the liquid crystal library
#include <FreqMeasure.h> // Include the frequency measurement library

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Initialize the LCD display

void setup() {
  lcd.begin(16, 2); // Set the LCD display to 16x2
  FreqMeasure.begin(0); // Begin the frequency measurement on pin A0
}

void loop() {
  if (FreqMeasure.available()) { // If a frequency measurement is available
    float frequency = FreqMeasure.read(); // Read the frequency
    float note = 12 * log(frequency / 440) / log(2) + 69; // Convert the frequency to a note number
    int noteNumber = (int) note % 12; // Get the note number modulo 12
    float centsOff = 1200 * log(frequency / (440 * pow(2, noteNumber - 9))) / log(2); // Calculate the number of cents off from A440
    lcd.setCursor(0, 0); // Set the cursor to the first column of the first row
    lcd.print("Herz: "); // Display "Herz: "
    lcd.print(frequency); // Display the frequency
    lcd.setCursor(0, 1); // Set the cursor to the first column of the second row
    lcd.print("Note: "); // Display "Note: "
    lcd.print(getNoteName(noteNumber)); // Display the note name
    lcd.print(getAccidental(centsOff)); // Display the accidental symbol
    lcd.print(getCentsOff(centsOff)); // Display the number of cents off
  }
}

String getNoteName(int noteNumber) { // A function to convert note numbers to note names
  String noteNames[] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"}; // An array of note names
  return noteNames[noteNumber]; // Return the note name for the given note number
}

String getAccidental(float centsOff) { // A function to determine the accidental symbol based on the number of cents off
  if (centsOff < -50) { // If the note is more than 50 cents flat
    return "bb"; // Return double flat
  } else if (centsOff < 0) { // If the note is between 0 and 50 cents flat
    return "b"; // Return flat
  } else if (centsOff > 50) { // If the note is more than 50 cents sharp
    return "#"; // Return sharp
  } else if (centsOff > 0) { // If the note is between 0 and 50 cents sharp
    return "x"; // Return double sharp
  } else { // If the note is exactly in tune
    return ""; // Return nothing
  }
}

String getCentsOff(float centsOff) { // A function to format the number of cents off as a string
  if (centsOff == 0) { // If the note is in tune
    return "  "; // Return two spaces
  } else if (centsOff < 0) { // If the note is flat
    centsOff = abs(centsOff); // Take the absolute value of the number of cents off
    return String((int) centsOff) + "b"; // Return the number of cents off followed by "b" for flat
  } else { // If the note is sharp
    return String((int) centsOff) + "#"; // Return the number of cents off followed by "#" for sharp
  }
}

