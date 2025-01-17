#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

//std::vector<std::vector<Circle>> checkCollisions(std::vector<Circle> circles);
class Circle{
    public:
    sf::CircleShape shape;
    int size;
    int mass;
    float velocity;
    float px,py,sx,sy;

    Circle(int tsize) {
        size = tsize;
        shape.setRadius(tsize);
        shape.setFillColor(sf::Color(rand()%256,rand()%256,rand()%256));
        mass = size*size;
        px = rand()%(800 - 2*size);
        py = rand()%(650 - 2*size);
        shape.setPosition(px,py);
        sx = rand()%9 - 4;
        sy = rand()%9 -4;
        velocity = sqrt(sx*sx + sy*sy);
    }
    void move(){
        px += sx;
        py += sy;
        shape.setPosition(px,py);
    }
    void border(){
        if ((px < 0) || (px + 2*size > 800)) {
            sx*=-1;
        }
        if((py < 0) || (py + 2*size > 650)) {
            sy*=-1;
        }
    }
};


int main()
{ 
    float wWidth = 800;
    float wHeight = 650;
     std::cout << "Number of circles: \n";
    int x;
    std::cin >> x;
    std::vector<Circle> circles;
    srand(time(0));
    for(int i = 0; i < x; ++i) {
        Circle circleObj(rand()%21 + 10);
        circles.push_back(circleObj);
    }
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "First game");
    
    window.setFramerateLimit(60);


    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
           
            
        }
       for(auto& circle : circles) {
        circle.border();
        circle.move();
       }

        window.clear();
        for (auto& circle : circles) {
            window.draw(circle.shape);
        }
        window.display();
    }

    return 0;
}
//std::vector<std::vector<Circle>> checkCollisions(std::vector<Circle> circles){
//    std::vector<std::vector<float>> collisions;
    
//}
