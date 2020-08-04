
#ifndef MI_VECTOR_H
#define MI_VECTOR_H

/* 
 * Esta mini Clase permite crear un vector de longitud fija que se puede manipular con metodos tipicos como .push(val) y .pop(val)
 * 
 @ by github.com/Rafdal
 */


typedef double formato_t;
const int chipSelect = 4; // pin CS del modulo SD o ethernet con SD 


// Vector de longitud fija
class Vector
{
private:
    uint8_t _size;

public:
    formato_t* data; // puntero del array de datos

    // Constructor de la clase
    Vector(uint8_t size) {
        _size = size;
        data = new formato_t[size];
        for (uint8_t i = 0; i < size; i++)
        {
            // Inicio todo en cero
            data[i] = 0; 
        }
    }
    // Destructor de la clase
    ~Vector() {
        if(data)
            delete[] data;
    }

    // Agrego un valor al final de la cadena y corro todos los valores una posicion hacia la izquierda
    void push(formato_t newValue) {
        for (uint8_t i = 0; i < _size-1; i++)
        {
            data[i] = data[i+1];
        }
        data[_size-1] = newValue;
    }

    // Agrego un valor al principio de la cadena y corro todos los valores una posicion hacia la derecha
    void pop(formato_t newValue) {
        for (uint8_t i = _size; i > 0; i--)
        {
            data[i] = data[i-1];
        }
        data[0] = newValue;
    }

    // Imprime todos los valores del vector
    void print() {
        for (uint8_t i = 0; i < _size; i++)
        {
            #if formato_t == double
                Serial.print(String(data[i]));
                Serial.print(F(", "));
            #elif formato_t == uint8_t
                char buf[8];
                sprintf(buf, "%u,", (uint8_t)data[i]);
            Serial.print(buf);
            #endif
        }
        Serial.println();
    }


    // Imprime todos los valores del vector, pero en vertical y con su indice
    void println() {
        for (uint8_t i = 0; i < _size; i++)
        {
            #if formato_t == double
                Serial.print(i);
                Serial.print('\t');
                Serial.println(String(data[i]));
            // #elif formato_t == uint8_t
            //     char buf[8];
            //     sprintf(buf, "%u,", (uint8_t)data[i]);
            //     Serial.print(buf);
            #endif
        }
    }


    #ifdef __SD_H__
    void printToSDFile(const char* filepath, bool eliminar = true) {

        pinMode(chipSelect, OUTPUT);
        pinMode(10, OUTPUT);
        digitalWrite(10, HIGH); // Desactivar Ethernet
        digitalWrite(chipSelect, LOW);   // Activar SD


        if (!SD.begin(chipSelect)) {
            Serial.println(F("SD card failed, or not present"));
            while (1);
        }
        Serial.println(F("SD card initialized."));

        if (SD.exists(filepath) && eliminar)
        {
            SD.remove(filepath);
            Serial.println(F("Archivo eliminado"));
        }

        File dataFile = SD.open(filepath, FILE_WRITE);

        if (dataFile) {
            for (unsigned long i = 0; i < _size; i++)
                dataFile.println(data[i], 2);
        }
        else
            Serial.println(F("Error abriendo el archivo"));

        dataFile.close();
    }

    #endif

};

#endif