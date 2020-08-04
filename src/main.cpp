#include <Arduino.h>



// #include <mainFFT.h>

// Defino el tamanio de la captura de datos. // ! Este valor siempre debe ser una potencia de 2
const uint8_t size = 64;

#include <arduinoFFT.h>
arduinoFFT FFT = arduinoFFT();


#include <SPI.h>
#include <SD.h>
#include <vector.h>
Vector vectorR(size), vectorI(size);

void setup(){
    Serial.begin(230400);
    _delay_ms(1000);
    Serial.println(F("Iniciado!"));


    // Cargo los valores en el el vector
    const int a = analogRead(0);
    while(a == analogRead(0));
    Serial.println(F("Recording"));
    
    for (uint8_t i = 0; i < size; i++)
    {
        vectorR.push((double)analogRead(0));
        delay(5);
    }

    Serial.println(F("\nDatos de entrada"));
    // Muestro el vector
    vectorR.print();
    vectorR.printToSDFile("raw_data.csv");

    // Transformada de fourier
    FFT.Windowing(vectorR.data, size, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vectorR.data, vectorI.data, size, FFT_FORWARD); /* Compute FFT */


    // Muestro el vector transformado
    Serial.println(F("\nTransformado"));
    vectorR.println();
    vectorR.printToSDFile("fft_data.csv");
    
    Serial.println(F("CAPTURA DE DATOS FINALIZADA"));

    for(;;);
}


void loop(){
}