#include "Write-WAV-File/wave_file.h"
#include "Write-WAV-File/scripts/wave.h"

#include "reharmoniser.h"
#include "midi.h"

int main(void){
    char a_note_filename[] = "./reharmoniser/tests/a_note.wav";
    char chord_filename[] = "c_major.test.wav";

    uint16_t bits_per_sample = 24;

    int32_t* a_note_array = NULL;
    int32_t* chord_array = NULL;

    Wave a_note = read_wave(a_note_filename);

    printf("Metadata read from %s:\n", a_note_filename);
    print_metadata(&a_note);

    if(a_note.data){
        a_note_array = malloc(a_note.numberof_samples * sizeof(int32_t));
        chord_array = malloc(a_note.numberof_samples * sizeof(int32_t));
    }

    read_wave_data_to_array(&a_note, a_note_array);

    double bit_depth_ratio = pow(2, bits_per_sample - a_note.header.bits_per_sample);

    int numberof_voices = 4;

    note notes[MAX_VOICES] = {
        {40, 261.6, 128},
        {44, 329.6, 128},
        {47, 392.0, 128},
        {51, 493.9, 100}
    };

    for(size_t i = 0; i < a_note.numberof_samples; i++){
        a_note_array[i] = (int32_t) (a_note_array[i] * bit_depth_ratio / numberof_voices);
    }

    for(size_t i = 0; i < a_note.numberof_samples; i++){
        chord_array[i] = get_reharmonised_wave_amplitude(a_note_array, notes, 440.0, i, a_note.numberof_samples);
    }

    write_array_to_wav_file(chord_filename, chord_array, a_note.numberof_samples, 2, a_note.header.sample_rate, bits_per_sample);

    free(a_note_array);
    free(chord_array);

    return 0;
}
