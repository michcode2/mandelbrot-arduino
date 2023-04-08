double x = -1.779826;
double x_radius = 0.00002;

double y = 0.0;
double y_radius = 0.00002;

double zoom = 8000000.0;

int gamma = 80;

class Linspace {
    public:
        double start;
        double finish;
        double stride;
        int num;
        double current;

    double * linspace() {
        double output[this -> num];

      
        for (int i = 0; i < this-> num; i++) {
            output[i] = i * this -> stride + this -> start;
        }
        double* memory = (double*)malloc(this -> num * sizeof(double ) + 1);
        memcpy(memory, &output, this -> num *sizeof(double) + 1);
      
        return memory;
    }

    double next() {
        this -> current = this -> current + this -> stride;

        return this -> current;
    }

    Linspace(double Start, double End, double Num) {
        start = Start;
        finish = End;
        num = Num;
        stride = (End - Start) / Num;
        current = Start;
    }

};


void setup() {
    Serial.begin(3000000);
    double low_x = x - x_radius;
    double high_x = x + x_radius;

    double low_y = y - y_radius;
    double high_y = y + y_radius;

    int width = 2 * x_radius * zoom;
    int height = 2 * y_radius * zoom;

    Serial.print(height);
    Serial.print(F(" "));
    Serial.println(width);

    using_iterators(low_x, high_x, width, low_y, high_y, height);
    
    Serial.println(F("done"));
}

void using_iterators(float low_x, float high_x, int width, float low_y, float high_y, int height) {
    Linspace reals = Linspace(low_x, high_x, width);


    for (int i = 0; i < width; i++){
        Linspace imags = Linspace(low_y, high_y, height);
        float x = reals.next();
        for (int j = 0; j < height; j++){
            float y = imags.next();

            int result = bounded(x, y, 768);
           
            Serial.println(result);
            
        }

    }
}

int bounded (double c_real, double c_imag, int bound) {
    double z_real = 0.0;
    double z_imag = 0.0;

    double top = 1000.0;

    for(int i = 0; i < bound; i++){
        double temp_real = z_real + c_real;
        double temp_imag = z_imag + c_imag;

        z_real = (temp_real * temp_real) - (temp_imag * temp_imag);
        z_imag = 2 * temp_real * temp_imag;

        if ((z_real * z_real) + (z_imag * z_imag) > top * top){
            return i;
        }
    }
    return 0;

}
void loop() {
  // put your main code here, to run repeatedly:

}
