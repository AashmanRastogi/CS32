//
//  event.cpp
//  Homework_3
//
//  Created by Aashman Rastogi on 5/7/23.
//

class Event
{
public:
    Event(string name);
    virtual ~Event(){};
    virtual string name() const;
    virtual string need() const = 0;
    virtual bool isSport() const = 0;
private:
    string m_name;
};


class BasketballGame : public Event
{
public:
    BasketballGame(string name);
    virtual ~BasketballGame();
    virtual string need() const;
    virtual bool isSport() const {return true;};
};


class HockeyGame : public Event
{
public:
    HockeyGame(string name);
    virtual ~HockeyGame();
    virtual string need() const;
    virtual bool isSport() const {return true;};
};


class Concert : public Event
{
public:
    Concert(string name, string type);
    virtual ~Concert();
    virtual string need() const;
    virtual bool isSport() const {return false;};
    string kind() const;
private:
    string m_type;
};

//Event constructor

Event::Event(string name): m_name(name) {}
string Event::name() const
{
    return m_name;
}

// Basketball
BasketballGame::BasketballGame(string name):Event(name){}
string BasketballGame::need() const
{
    return "hoops";
}
BasketballGame::~BasketballGame()
{
    cout << "Destroying the " << name() << " basketball game"<< endl;
}

//Hockeygame
HockeyGame::HockeyGame(string name):Event(name){}
string HockeyGame::need() const
{
    return "ice";
}
HockeyGame::~HockeyGame()
{
    cout << "Destroying the " << name() << " hockeyGame game"<< endl;
}

// Concert
Concert::Concert(string name, string type):Event(name),m_type(type){}
string Concert::need() const
{
    return "a stage";
}
string Concert::kind() const
{
    return m_type;
}
Concert::~Concert()
{
    cout << "Destroying the " << name() << " " << m_type << " concert"<< endl;
}


