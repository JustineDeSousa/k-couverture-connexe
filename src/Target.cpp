#include "../include/Target.h"




/*================Target================*/
//Constucteur
Target::Target() : target(radius), captor(radius), com(radius),
                   r(radius), rcom(radius), rcapt(radius),
                   state(state::normal), manager(NULL)
{

}
Target::Target(TargetManager* TargetManager) : 
    target(radius), captor(radius), com(radius),
    r(radius), rcom(radius), rcapt(radius),
    state(state::normal), manager(TargetManager)
{
    target.setFillColor(sf::Color::White);
    target.setOutlineThickness(2.0f);
    target.setOutlineColor(sf::Color::Black);

    captor.setFillColor(sf::Color::Transparent);
    captor.setOutlineThickness(2.0f);
    captor.setOutlineColor(sf::Color::Transparent);

    com.setFillColor(sf::Color::Transparent);
    com.setOutlineThickness(2.0f);
    com.setOutlineColor(sf::Color::Transparent);
}

void Target::set(vec2f position, float Rcom, float Rcapt, float spacing)
{
    target.setPosition(position - vec2f(r, r));

    rcom = Rcom * spacing;
    com.setRadius(rcom);
    com.setPosition(position - vec2f(rcom, rcom));

    rcapt = Rcapt * spacing - 1.0f;
    captor.setRadius(rcapt);
    captor.setPosition(position - vec2f(rcapt, rcapt));

}

//Destructeur   
Target::~Target()
{
}

bool Target::gesEvent(sf::Event& e, sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    bool mouseInMiniature = mousePosition.x >= target.getPosition().x //- r
        && mousePosition.x <= target.getPosition().x + 2*r
        && mousePosition.y >= target.getPosition().y //- r
        && mousePosition.y <= target.getPosition().y + 2*r;

    if (e.type == sf::Event::MouseMoved)
    {
        if (mouseInMiniature)
            setState(state::hovered);
        else
            setState(state::normal);
    }
    return mouseInMiniature;
}
void Target::draw(sf::RenderTarget& theTarget, sf::RenderStates states) const
{
    theTarget.draw(target, states);
    theTarget.draw(captor, states);
    theTarget.draw(com, states);
}

void Target::setState(uint s)
{

    switch(s)
    {
    case state::normal:
            state = s;
            //target.setOutlineColor(sf::Color::Black);
            captor.setOutlineColor(sf::Color::Transparent);
            com.setOutlineColor(sf::Color::Transparent);
            break;
    case state::cible:
        state = s;
        target.setFillColor(sf::Color::Red);
        captor.setOutlineColor(sf::Color::Transparent);
        com.setOutlineColor(sf::Color::Transparent);
        break;
    case state::isCapted:
        state = s;
        target.setOutlineColor(sf::Color::Green);
        break;
    case state::hovered:
        state = s;
        captor.setOutlineColor(sf::Color::Black);
        com.setOutlineColor(sf::Color::Red);
        break;
    default:
        break;
    }

};

/*================Link================*/
//Constucteur
Link::Link() : manager(NULL)
{ }
Link::Link(TargetManager* TargetManager) : manager(TargetManager)
{ }

void Link::set(vec2f a, std::vector<vec2f> b)
{
    points.resize( b.size());
    uint v1, v2;
    for (uint i = 0; i < b.size(); i++)
        points[i] = sfLine(a, b[i], sf::Color::Red, 3.0f);
}

//Destructeur   
Link::~Link()
{ }
void Link::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (uint i = 0; i < points.size(); i++)
        target.draw(points[i], states);
}

/*================TargetManager================*/

TargetManager::TargetManager() : clicked(false), switchGraph(false)
{ }
TargetManager::~TargetManager()
{
    for (uint i(0); i != Targets.size(); i++)
    {
        if (Targets[i] != NULL)
            delete Targets[i];
    }
    Targets.resize(0);
}

Target* TargetManager::createTarget()
{
    Target* target = new Target(this);
    return target;
}
Link* TargetManager::createLink()
{
    Link* link = new Link(this);
    return link;
}

float TargetManager::createTargets(const Instance* instance, const Solution* solution)
{
    float m(10);
    for (uint i = 0; i < instance->size(); i++)
    {
        for(uint j = 0 ; j < (*instance)[i].size(); j++)
            if( i != j)
                m = min(m, (*instance)[i][j] );
    }
    float spacing = 20 / m;
    cout << m << endl;
    spacing = 30;

    for (uint i = 0; i < instance->size(); i++)
    {
        pair<float, float> myPair = instance->getPosition(i);
        vec2f pos(spacing * myPair.first + spacing, spacing+ spacing * myPair.second);

        if (i >= Targets.size())
            Targets.push_back(createTarget());

        Targets[i]->set(pos, instance->getRcom(), instance->getRcapt(), spacing );
    }
    for (uint i = 0; i < solution->size(); i++)
    {
        if ((*solution)[i])
            Targets[i]->setState(state::cible);
    }

    for (uint i = instance->size(); i < Targets.size(); i++)
        Targets.pop_back();


    Linkscom.resize(0);
    Graph capt = solution->get_graph_com();
    set<int> sommets;
    vector<sf::Vector2f> myVec;
    pair<float, float> pos;
    uint n = 0;
    for (uint i = 0; i < capt.size(); i++)
    {
        sommets = capt[i];
        if (sommets.size() > 0)
        {
            myVec.resize(0);
            for (int s : sommets)
            {
                pos = instance->getPosition(s);
                myVec.push_back(vec2f(spacing * pos.first + spacing, spacing + spacing * pos.second));
            }

            pos = instance->getPosition(i);

            Linkscom.push_back(createLink());
            Linkscom[n]->set(vec2f(spacing * pos.first + spacing, spacing + spacing * pos.second), myVec);
            n++;
        }
    }

    capt = solution->get_graph_capt();
    for (uint i = 0; i < capt.size(); i++)
    {

        if (capt[i].size() >= instance->k())
            Targets[i]->setState(state::isCapted);
    }    

    return(spacing);
}

void TargetManager::gesEvent(sf::Event& e, sf::RenderWindow& window)
{
    if (e.type == sf::Event::MouseButtonPressed)
    {
        if (e.mouseButton.button == sf::Mouse::Left)
            clicked = true;
    }

    if (e.type == sf::Event::MouseButtonReleased)
    {
        if (e.mouseButton.button == sf::Mouse::Left)
            clicked = false;

        if (e.mouseButton.button == sf::Mouse::Right)
            switchGraph = !switchGraph;
    }

    for (uint i = 0; i < Targets.size(); i++)
        Targets[i]->gesEvent(e, window);
}

void TargetManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    for (uint i = 0; i < Targets.size(); i++)
    {
        if(!Targets[i] -> isHovered())
            target.draw(*Targets[i], states);
    }

    for (uint i = 0; i < Targets.size(); i++)
    {
        if (Targets[i]->isHovered())
            target.draw(*Targets[i], states);
    }

    if (switchGraph)
    {
        for (uint i = 0; i < Linkscom.size(); i++)
            target.draw(*Linkscom[i], states);
    }

}

bool TargetManager::getClicked() { return clicked; }
