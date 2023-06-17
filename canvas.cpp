#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Canvas{
    private:
        int width;
        int height;
        char emptyPixel;
        std::vector<std::vector<char>> canvas;

    public:
    
        Canvas(int w, int h, char c) : width(w), height(h), emptyPixel(c){
            canvas.resize(height + 2, std::vector<char>(width + 2, ' '));
            for(int y = 0; y < height + 2; y++){
                for(int x = 0; x < width + 2; x++){
                    if(x == 0 || x == width + 1){
                        canvas[y][x] = '|';
                    }
                    else if(y == 0 || y == height + 1){
                        canvas[y][x] = '=';
                    }
                    else{
                        canvas[y][x] = emptyPixel;
                    }
                }
            }
        }
        
        void drawPixel(int x, int y, char c){
            if(x >= 0 && x <= width + 2 && y >= 0 && y <= height + 2){
                canvas[x + 1][y + 1] = c;
            }
        }

        void toFile(std::ofstream& file){
            for(const auto& row : canvas){
                for(const auto &pixel : row){
                    file << pixel;
                }
                file << std::endl;
            }
        }
        
};

class Figure{
    public:
        virtual void draw(Canvas& canvas) = 0;
};

class Rectangle : public Figure{
    private:
        int x;
        int y;
        int a;
        int b;
        char pixel;
    public:
        Rectangle(int x, int y, int a, int b, char c) : x(x), y(y), a(a), b(b), pixel(c){}
        ~Rectangle(){}
        virtual void draw(Canvas &canvas) override {
            for(int i = x; i < x + a; i++){
                for(int j = y; j < y + b; j++){
                    canvas.drawPixel(j, i, pixel);
                }
            }
        }
};

class Square : public Rectangle{
    public:
        Square(int x, int y, int a, char c) : Rectangle(x, y, a, a, c){}

};

class Circle : public Figure{
    private:
        int x;
        int y;
        int r;
        char pixel;

        bool isInside(int m, int n){
            int dx = m - x;
            int dy = n - y;
            return dx*dx + dy*dy <= r*r;
        }
    public:
        Circle(int x, int y, int r, char c) : x(x), y(y), r(r), pixel(c){}

        void draw(Canvas &canvas) override {
           for(int i = y - r; i <= y + r; i++){
                for(int j = x - r; j <= x + r; j++){
                    if(isInside(i, j)){
                        canvas.drawPixel(i, j, pixel);
                    }
                }
           } 
        }
};

void figureFromFile(std::vector<std::string> info, Canvas &canvas){
    if(info[0] == "rectangle"){
        int x = stoi(info[1]);
        int y = stoi(info[2]);
        int a = stoi(info[3]);
        int b = stoi(info[4]);
        char pixel = info[5][0];

        Rectangle r(x, y, a, b, pixel);
        r.draw(canvas);
    }

    else if(info[0] == "square"){
        int x = stoi(info[1]);
        int y = stoi(info[2]);
        int a = stoi(info[3]);
        char pixel = info[4][0];

        Square s(x, y, a, pixel);
        s.draw(canvas);       
    }
    else if(info[0] == "circle"){
        int x = stoi(info[1]);
        int y = stoi(info[2]);
        int r = stoi(info[3]);
        char pixel = info[4][0];

        Circle c(x, y, r, pixel);
        c.draw(canvas);

    }
}

void drawFromFile(std::ifstream &configFile){
    std::vector<std::string> data;
    std::string line;

    if(configFile){
        while(getline(configFile, line)){
            std::string temp = "";
            for(int i = 0; i < line.length(); i++){
                if(line[i] != '-'){
                    temp += line[i];
                }
                else i = line.length();
            }
            data.push_back(temp);
        }
    }

    int width = stoi(data[0]);
    int height = stoi(data[1]);
    char emptyPixel = data[3][0];
    Canvas canvas(width, height, emptyPixel);

    for(int i = 4; i < data.size(); i++){
        std::vector<std::string> info;
        std::string temp = "";
        
        for(int j = 0; j < data[i].length(); j++){
            if(data[i][j] != ' '){
                temp += data[i][j];
            }
            else{
                info.push_back(temp);
                temp = "";
            }
        }
        figureFromFile(info, canvas);

        info.clear();

    }

    std::string saveFileName = data[2] + ".txt";
    std::ofstream saveFile(saveFileName.c_str());
    canvas.toFile(saveFile);
    saveFile.close();
}

int main(int argc, char **argv){

    if(argc < 2){
        std::cerr << "brak pliku\n";
        return 1;
    }

    std::ifstream configFile(argv[1]);

    drawFromFile(configFile);

    configFile.close();

    return 0;
}