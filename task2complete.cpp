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