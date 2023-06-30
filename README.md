# codesmells

### Завдання 1. Рішення задач узагальнення
```
class Animal
{
public:
    Animal() {}
    ...
    };
class Dog : public Animal
{
public:
    Dog(int age) : Animal()
    {
        m_age = age;
    }
    int GetAge() { return m_age; }
    ...
private:
    int m_age;
};

class Cat : public Animal
{
public:
    Cat (int age) : Animal()
    {
    m_age = age;
    }
    int GetAge() { return m_age; }
    ...
private:
    int m_age;
};
```
Помічені "запахи коду":
```
class Animal
{
public:
    Animal() {}
    ...
    };
class Dog : public Animal
{
public:
    Dog(int age) : Animal() // "Забруднювачі - Дублювання Коду"
    {
        m_age = age; 
    }
    int GetAge() { return m_age; } // "Забруднювачі - Дублювання Коду"
    ...
private:
    int m_age; // "Забруднювачі - Дублювання Коду"
};

class Cat : public Animal
{
public:
    Cat (int age) : Animal() // "Забруднювачі - Дублювання Коду"
    {
    m_age = age; 
    }
    int GetAge() { return m_age; } // "Забруднювачі - Дублювання Коду"
    ...
private:
    int m_age; // "Забруднювачі - Дублювання Коду"
};
```
Рефакторинг:
1. Підйом поля m_age у суперклас;
2. Підйом метода GetAge() у суперклас;
3. Підйом конструкторау суперклас та виклик його з конструктора підкласів.
```
class Animal
{
public:
    Animal(int age) {
        m_age = age;
    }
    int GetAge() { 
        return m_age; 
    }
private:
    int m_age;
};

class Dog : public Animal
{
public:
    using Animal::Animal;
};

class Cat : public Animal
{
public:
    using Animal::Animal;
};

```

### Завдання 2. Рефакторинг на рівні окремих операторів
```
int getSpeed()
{
    int result = 0;
    if (isTransport())
    {
        if(isCar)
        {
            result = getCarSpeed();
        }
        else
        {
            if(isPlane)
            {
                for (int i = 0; i < m_planes.Length; i++)
                {
                    result += getPlaneSpeed(m_planes[i]);
                }
                if (m_planes.Length > 0)
                {
                    result = result / m_planes.Length;
                }
            }
            else
            {
                if(isBoat)
                {
                    result = getBoatSpeed();
                }
            }
        }
    }
    else
    {
        result = getManSpeed();
    }
    return result;
}
```
Помічені "запахи коду":
```
int getSpeed()
{
    int result = 0; // "Забруднювач коду" мертва зміни для збереження граничного результату
    if (isTransport())
    {
        if(isCar)
        {
            result = getCarSpeed();
        }
        else
        {
            if(isPlane) // "Роздувач коду" вкладенні умовні оператори
            {
                for (int i = 0; i < m_planes.Length; i++) // "Роздувач коду" довгий метод
                {
                    result += getPlaneSpeed(m_planes[i]);
                }
                if (m_planes.Length > 0)
                {
                    result = result / m_planes.Length;
                }
            }
            else
            {
                if(isBoat)  // "Роздувач коду" вкладенні умовні оператори
                {
                    result = getBoatSpeed();
                }
            }
        }
    }
    else
    {
        result = getManSpeed();
    }
    return result;
}
```
Рефакторинг:
1. Прибрати метрву зміну result та замінити її граничним оператором return;
2. Винести код обочислення PlaneSpeed у окремий метод;
3. Замнити вкладенні умовні оператори послідовними.
```
int getPlanesSpeed() 
{
    int result = 0;
    for (int i = 0; i < m_planes.Length; i++)
        {
            result += getPlaneSpeed(m_planes[i]);
        }
        if (m_planes.Length > 0)
        {
            result = result / m_planes.Length;
        }
    return 0;
}

int getSpeed()
{
    if (!isTransport())
    {
        return getManSpeed();
    }
    else if(isCar)
    {
        return getCarSpeed();
    }
    else if(isPlane)
    {
        return getPlanesSpeed();
    }
    else if(isBoat)
    {
        return getBoatSpeed();
    }

    return 0;
}
```

