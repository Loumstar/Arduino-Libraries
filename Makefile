CC = gcc
CFLAGS = -Wall -pedantic

EXECUTABLES = testReharmoniser testIntComplex testDoubleComplex testPitchDetection

ARDUINO = arduino-cli compile
BOARD = --fqbn arduino:avr:mega:cpu=atmega2560

ARDUINO_SKETCHES = arduinoIntComplex arduinoDoubleComplex arduinoPitchDetection

UNITTEST_DIR = ./C-UnitTest/

WAVE_FILE_DIR = ./reharmoniser/tests/Write-WAV-File/
WAVE_FILE_OBJECT_FILES = endianness.o wave_header.o wave.o wave_file.o
WAVE_FILE_OBJECT_FILES_FULL_PATH = $(patsubst %,$(WAVE_FILE_DIR)%,$(WAVE_FILE_OBJECT_FILES))

# EXECUTABLES

testReharmoniser: reharmoniser.test.o reharmoniser.o midi.o
	$(CC) $(CFLAGS) -o testReharmoniser $(WAVE_FILE_OBJECT_FILES_FULL_PATH) reharmoniser.test.o reharmoniser.o midi.o

testIntComplex: int_complex.test.o int_complex.o $(UNITTEST_DIR)unittest.o
	$(CC) $(CFLAGS) -o testIntComplex int_complex.test.o int_complex.o $(UNITTEST_DIR)unittest.o

testDoubleComplex: double_complex.test.o double_complex.o $(UNITTEST_DIR)unittest.o
	$(CC) $(CFLAGS) -o testDoubleComplex double_complex.test.o double_complex.o $(UNITTEST_DIR)unittest.o

testPitchDetection: pitch_detection.test.o pitch_detection.o peaks_correlation.o peaks_analyser.o fourier_transform.o frequency_bin_typedef.o int_complex.o double_complex.o $(UNITTEST_DIR)/unittest.o
	$(CC) $(CFLAGS) -o testPitchDetection pitch_detection.test.o pitch_detection.o peaks_correlation.o peaks_analyser.o fourier_transform.o frequency_bin_typedef.o int_complex.o double_complex.o $(UNITTEST_DIR)/unittest.o


# OBJECT FILES

# BASIC LIBRARIES
reharmoniser.o: reharmoniser/reharmoniser.c
	$(CC) $(CFLAGS) -c reharmoniser/reharmoniser.c

int_complex.o: int_complex/int_complex.c
	$(CC) $(CFLAGS) -c int_complex/int_complex.c

double_complex.o: double_complex/double_complex.c
	$(CC) $(CFLAGS) -c double_complex/double_complex.c

midi.o: midi/midi.c
	$(CC) $(CFLAGS) -c midi/midi.c


# PITCH DETECTION LIBRARIES
fourier_transform.o: fourier_transform/fourier_transform.c
	$(CC) $(CFLAGS) -c fourier_transform/fourier_transform.c

frequency_bin_typedef.o: frequency_bin_typedef/frequency_bin_typedef.c
	$(CC) $(CFLAGS) -c frequency_bin_typedef/frequency_bin_typedef.c

peaks_analyser.o: peaks_analyser/peaks_analyser.c
	$(CC) $(CFLAGS) -c peaks_analyser/peaks_analyser.c

peaks_correlation.o: peaks_correlation/peaks_correlation.c
	$(CC) $(CFLAGS) -c peaks_correlation/peaks_correlation.c

pitch_detection.o: pitch_detection/pitch_detection.c
	$(CC) $(CFLAGS) -c pitch_detection/pitch_detection.c


# TESTS
reharmoniser.test.o: reharmoniser/tests/reharmoniser.test.c
	$(CC) $(CFLAGS) -c reharmoniser/tests/reharmoniser.test.c

int_complex.test.o: int_complex/tests/int_complex.test.c
	$(CC) $(CFLAGS) -c int_complex/tests/int_complex.test.c

double_complex.test.o: double_complex/tests/double_complex.test.c
	$(CC) $(CFLAGS) -c double_complex/tests/double_complex.test.c

pitch_detection.test.o: pitch_detection/tests/pitch_detection.test.c
	$(CC) $(CFLAGS) -c pitch_detection/tests/pitch_detection.test.c


# VERIFY ARDUINO SKETCHES

arduinoIntComplex: int_complex/tests/int_complex.test/int_complex.test.ino
	$(ARDUINO) $(BOARD) -o arduinoIntComplex int_complex/tests/int_complex.test/int_complex.test.ino

arduinoDoubleComplex: double_complex/tests/double_complex.test/double_complex.test.ino
	$(ARDUINO) $(BOARD) -o arduinoDoubleComplex double_complex/tests/double_complex.test/double_complex.test.ino

arduinoPitchDetection: pitch_detection/tests/pitch_detection.test/pitch_detection.test.ino
	$(ARDUINO) $(BOARD) -o arduinoPitchDetection pitch_detection/tests/pitch_detection.test/pitch_detection.test.ino

# MISC

.PHONY: all, clean, submodules, objects, c-tests, arduino-tests

all: $(EXECUTABLES) $(ARDUINO_SKETCHES)

clean:
	rm -v $(EXECUTABLES) *.o *.elf *.hex *.wav

submodules:
	make --directory=$(WAVE_FILE_DIR) objects

c-tests: $(EXECUTABLES)
	./run_test_scripts.sh $(EXECUTABLES)

arduino-tests:
	make $(ARDUINO_SKETCHES)
	