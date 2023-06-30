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
