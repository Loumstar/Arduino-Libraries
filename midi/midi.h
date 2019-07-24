#define LATENCY pow(10, -3) // 1 milisecond samples
#define SAMPLE_RATE 44100 // standard 44.1kHz sample rate
#define SAMPLE_FRAMES (size_t) round(SAMPLE_RATE * LATENCY)

#define MAX_VOICES 10

typedef double note[3]; // first element is note number, second is frequency, third is volume

double note_frequency(int n){
    return pow(2, (n - 69) / 12) * 440.0;
}

void note_off(int n, note* notes){
    for(size_t i = 0; i < MAX_VOICES; i++){
        if((int) notes[i][0] == n){
            notes[i][0] = 0;
            notes[i][1] = 0;
            notes[i][2] = 0;
            break;
        }
    }
}

void note_on(int n, int vol, note* notes){
    for(size_t i = 0; i < MAX_VOICES; i++){
        if(notes[i][0] == 0.0){
            notes[i][0] = n;
            notes[i][1] = note_frequency(n);
            notes[i][2] = vol / 128.0;
            break;
        }
    }
}

void handle_midi(int* msg, note* notes){
    if(msg[0] < 0xA0){ // only handle note on/off messages
        if(msg[0] < 0x90){
            note_off(msg[1], notes);
        } else {
            note_on(msg[1], msg[2], notes);
        }
    }
}

int* read_midi(int* msg, Stream &midiDevice){
    size_t msg_length = midiDevice.available();
    size_t i = 0;

    while(i < msg_length){
        msg[i] = midiDevice.read(); //need to check for status byte
        i++;
    }
}

double playback_amplitude(double* sample, size_t frame, double f, note* notes){
    int a = 0;
    size_t j;
    for(size_t i = 0; i < MAX_VOICES; i++){
        j = notes[i][1] / f;
        a += sample[j] * notes[i][2];
    }
    return a;
}