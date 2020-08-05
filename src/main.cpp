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

    pinMode(chipSelect, OUTPUT);
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH); // Desactivar Ethernet
    digitalWrite(chipSelect, LOW);   // Activar SD
    if (!SD.begin(chipSelect)) {
        Serial.println(F("SD card failed, or not present"));
        while (1);
    }
    Serial.println(F("SD card initialized."));

    if (SD.exists("dataset.csv"))
        SD.remove("dataset.csv");

    File dataFile = SD.open("dataset.csv", FILE_WRITE);

    Serial.println(F("Iniciado!"));




    if (dataFile) {
        double f31;
        double f17;
        double f61;
        for(uint8_t i=0; i < 250; i++)
        {
            f31=0;
            f17=0;
            f61=0;
            vectorR.clear();
            vectorI.clear();

            // Espero que el joystick se mueva
            const int a = (analogRead(0)/5);
            while(a == (analogRead(0)/5));

            // Cargo los valores en el el vector
            Serial.print(F("Recording "));  
            Serial.println(i);
            for (uint8_t i = 0; i < size; i++)
            {
                vectorR.push((double)analogRead(0));
                delay(5);
            }

            Serial.println(F("\nDatos de entrada"));
            // Muestro el vector
            // vectorR.printToSDFile("raw_data.csv");

            // Transformada de fourier
            FFT.Compute(vectorR.data, vectorI.data, size, FFT_FORWARD); /* Compute FFT */
            vectorR.print();
            
            f31 = vectorR.data[31];
            f17 = vectorR.data[17];
            f61 = vectorR.data[61];

            // dataFile
            dataFile.print(f31);
            dataFile.print(F(",\t"));
            dataFile.print(f17);
            dataFile.print(F(",\t"));
            dataFile.println(f61);
        }
    }
    else
        Serial.println(F("Error abriendo el archivo"));

    dataFile.close();

    /* // Muestro el vector transformado
    Serial.println(F("\nDatos transformados"));
    vectorR.printToSDFile("fft_data.csv");
    vectorR.println();
    
    Serial.println(F("CAPTURA DE DATOS FINALIZADA"));

    for(;;); */
}


void loop(){
}