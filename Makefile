CC = gcc
CFLAGS = -Wall -pedantic

BINARIES = testReharmoniser testIntComplex testDoubleComplex testPitchDetection

ARDUINO = arduino-cli compile
BOARD = --fqbn arduino:avr:mega:cpu=atmega2560

ARDUINO_SKETCHES = arduinoIntComplex arduinoDoubleComplex arduinoPitchDetection

WAVE_FILE_DIRECTORY =  ./reharmoniser/tests/Write-WAV-File/
_WAVE_FILE_OBJECT_FILES = endianness.o wave_header.o wave.o wave_file.o
WAVE_FILE_OBJECT_FILES = $(patsubst %,$(WAVE_FILE_DIRECTORY)/%,$(_WAVE_FILE_OBJECT_FILES))

WAVE_FILE_INCLUDES = -I$(WAVE_FILE_DIRECTORY) \
					 -I$(WAVE_FILE_DIRECTORY)scripts/

INCLUDES = -I./reharmoniser/ \
		   -I./int_complex/ \
		   -I./double_complex/ \
		   -I./unittest/ \
		   -I./midi/ \
		   -I./fourier_transform/ \
		   -I./frequency_bin_typedef/ \
		   -I./peaks_analyser/ \
		   -I./peaks_correlation/ \
		   -I./pitch_detection/

# BINARIES

testReharmoniser: reharmoniser.test.o reharmoniser.o midi.o
	make --directory=$(WAVE_FILE_DIRECTORY) objects
	$(CC) $(CFLAGS) -o testReharmoniser $(WAVE_FILE_OBJECT_FILES) reharmoniser.test.o reharmoniser.o midi.o

testIntComplex: int_complex.test.o int_complex.o unittest.o
	$(CC) $(CFLAGS) -o testIntComplex int_complex.test.o unittest.o int_complex.o

testDoubleComplex: double_complex.test.o double_complex.o unittest.o
	$(CC) $(CFLAGS) -o testDoubleComplex double_complex.test.o double_complex.o unittest.o

testPitchDetection: pitch_detection.test.o pitch_detection.o peaks_correlation.o peaks_analyser.o fourier_transform.o frequency_bin_typedef.o int_complex.o double_complex.o unittest.o
	$(CC) $(CFLAGS) -o testPitchDetection pitch_detection.test.o pitch_detection.o peaks_correlation.o peaks_analyser.o fourier_transform.o frequency_bin_typedef.o int_complex.o double_complex.o unittest.o


# OBJECT FILES

# BASIC LIBRARIES
reharmoniser.o: reharmoniser/reharmoniser.c
	$(CC) $(CFLAGS) $(INCLUDES) -c reharmoniser/reharmoniser.c

int_complex.o: int_complex/int_complex.c
	$(CC) $(CFLAGS) $(INCLUDES) -c int_complex/int_complex.c

double_complex.o: double_complex/double_complex.c
	$(CC) $(CFLAGS) $(INCLUDES) -c double_complex/double_complex.c

unittest.o: unittest/unittest.c
	$(CC) $(CFLAGS) $(INCLUDES) -c unittest/unittest.c

midi.o: midi/midi.c
	$(CC) $(CFLAGS) $(INCLUDES) -c midi/midi.c


# PITCH DETECTION LIBRARIES
fourier_transform.o: fourier_transform/fourier_transform.c
	$(CC) $(CFLAGS) $(INCLUDES) -c fourier_transform/fourier_transform.c

frequency_bin_typedef.o: frequency_bin_typedef/frequency_bin_typedef.c
	$(CC) $(CFLAGS) $(INCLUDES) -c frequency_bin_typedef/frequency_bin_typedef.c

peaks_analyser.o: peaks_analyser/peaks_analyser.c
	$(CC) $(CFLAGS) $(INCLUDES) -c peaks_analyser/peaks_analyser.c

peaks_correlation.o: peaks_correlation/peaks_correlation.c
	$(CC) $(CFLAGS) $(INCLUDES) -c peaks_correlation/peaks_correlation.c

pitch_detection.o: pitch_detection/pitch_detection.c
	$(CC) $(CFLAGS) $(INCLUDES) -c pitch_detection/pitch_detection.c


# TESTS
reharmoniser.test.o: reharmoniser/tests/reharmoniser.test.c
	$(CC) $(CFLAGS) $(INCLUDES) $(WAVE_FILE_INCLUDES) -c reharmoniser/tests/reharmoniser.test.c

int_complex.test.o: int_complex/tests/int_complex.test.c
	$(CC) $(CFLAGS) $(INCLUDES) -c int_complex/tests/int_complex.test.c

double_complex.test.o: double_complex/tests/double_complex.test.c
	$(CC) $(CFLAGS) $(INCLUDES) -c double_complex/tests/double_complex.test.c

pitch_detection.test.o: pitch_detection/tests/pitch_detection.test.c
	$(CC) $(CFLAGS) $(INCLUDES) -c pitch_detection/tests/pitch_detection.test.c


# VERIFY ARDUINO SKETCHES

arduinoIntComplex: int_complex/tests/int_complex.test/int_complex.test.ino
	$(ARDUINO) $(BOARD) -o arduinoIntComplex int_complex/tests/int_complex.test/int_complex.test.ino

arduinoDoubleComplex: double_complex/tests/double_complex.test/double_complex.test.ino
	$(ARDUINO) $(BOARD) -o arduinoDoubleComplex double_complex/tests/double_complex.test/double_complex.test.ino

arduinoPitchDetection: pitch_detection/tests/pitch_detection.test/pitch_detection.test.ino
	$(ARDUINO) $(BOARD) -o arduinoPitchDetection pitch_detection/tests/pitch_detection.test/pitch_detection.test.ino


# MISC

.PHONY: all, clean, c-tests, arduino-tests, arduinoIntComplex, arduinoDoubleComplex, arduinoPitchDetection

all: $(BINARIES) $(ARDUINO_SKETCHES)

clean:
	rm -v $(BINARIES) $(WAVE_FILE_OBJECT_FILES) *.o *.elf *.hex *.wav

c-tests:
	make $(BINARIES)
	./run_test_scripts.sh $(BINARIES)
	rm $(BINARIES) *.o

arduino-tests:
	make $(ARDUINO_SKETCHES)
	rm *.elf *.hex
	