
#include "MainLoop.hpp"

uint Main::ncapture = 0;
/*================Main================*/
//Constucteur
Main::Main(const Solution* sol) :
    Loop(), instance(Solution::instance), solution(sol), targets(), spacing(20)
{ }
//Destructeur
Main::~Main()
{
    //Screenshot
    sf::RenderTexture renderTex;
    renderTex.create(w, h);
    sf::Image image;

    renderTex.clear(sf::Color::White);
    renderTex.draw(targets);
    renderTex.display();
    
    image = renderTex.getTexture().copyToImage();
    image.saveToFile("capture_" + std::to_string(Main::ncapture) + ".jpg");
    Main::ncapture++;
}

void Main::gesEvent()   
{
    targets.gesEvent(event, window);

}
void Main::update() { }
void Main::draw()
{
    window.clear(sf::Color::White);

    window.draw(targets);

    window.display();
}

bool Main::notdone() const { return true; }
bool Main::abortCondition() const { return false; }

int Main::init()
{
    spacing = targets.createTargets(instance, solution);
    return 0;
}
void Main::createWindows()
{
    w = instance->Grid_size() * spacing + spacing;
    h = instance->Grid_size() * spacing + spacing;
    Loop::createWindows();

    window.setFramerateLimit(30);
}
