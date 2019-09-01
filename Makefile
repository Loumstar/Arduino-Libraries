CC = gcc
CFLAGS = -v
INCLUDES = -I./double_complex/ -I./int_complex/ -I./unittest/ \
-I./fourier_transform/ -I./frequency_bin_typedef/ \
-I./peaks_analyser/ -I./peaks_correlation/ -I./pitch_detection/

BINARIES = testIntComplex testDoubleComplex testPitchDetection

# EXECUTABLES

testIntComplex: int_complex.test.o int_complex.o unittest.o
	$(CC) $(CFLAGS) $(INCLUDES) -o testIntComplex int_complex.test.o unittest.o int_complex.o

testDoubleComplex: double_complex.test.o double_complex.o unittest.o
	$(CC) $(CFLAGS) $(INCLUDES) -o testDoubleComplex double_complex.test.o double_complex.o unittest.o

testPitchDetection: pitch_detection.test.o pitch_detection.o peaks_correlation.o peaks_analyser.o \
fourier_transform.o frequency_bin_typedef.o int_complex.o double_complex.o unittest.o
	$(CC) $(CFLAGS) $(INCLUDES) -o testPitchDetection pitch_detection.test.o pitch_detection.o peaks_correlation.o \
	peaks_analyser.o fourier_transform.o frequency_bin_typedef.o int_complex.o double_complex.o unittest.o


# OBJECT FILES

# BASIC LIBRARIES
int_complex.o: int_complex/int_complex.c
	$(CC) $(CFLAGS) $(INCLUDES) -c int_complex/int_complex.c

double_complex.o: double_complex/double_complex.c
	$(CC) $(CFLAGS) $(INCLUDES) -c double_complex/double_complex.c

unittest.o: unittest/unittest.c
	$(CC) $(CFLAGS) $(INCLUDES) -c unittest/unittest.c


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
int_complex.test.o: int_complex/tests/int_complex.test.c
	$(CC) $(CFLAGS) $(INCLUDES) -c int_complex/tests/int_complex.test.c

double_complex.test.o: double_complex/tests/double_complex.test.c
	$(CC) $(CFLAGS) $(INCLUDES) -c double_complex/tests/double_complex.test.c

pitch_detection.test.o: pitch_detection/tests/pitch_detection.test.c
	$(CC) $(CFLAGS) $(INCLUDES) -c pitch_detection/tests/pitch_detection.test.c


# MISC

.PHONY: clean

clean:
	rm -v $(BINARIES) *.o
