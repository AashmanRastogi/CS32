
void listAll(const MenuItem* m, string path)  // two-parameter overload
{
    if (m->name() != "")
    {
        cout << path << m->name() << endl;
    }
    
    if (m->menuItems() == nullptr || m->menuItems()->size() == 0)
    {
        return;
    }

    if (m->name() != "")
    {
        path += m->name() + "/";
    }
    for (vector<MenuItem*>::const_iterator p = m->menuItems()->begin(); p!=m->menuItems()->end(); p++)
    {
        listAll(*p, path);
    }
}

