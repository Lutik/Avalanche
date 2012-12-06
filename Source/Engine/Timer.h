#ifndef AvalancheTimerH
#define AvalancheTimerH

class CTimer
{
public:
    void Start()
    {
        start = SDL_GetTicks();
    }

    float GetTime(bool reset = false)
    {
        current = SDL_GetTicks();
        float time = float(current - start) / 1000.0f;
        if(reset) start = current;
        return time;
    }

private:
    Uint32 start;
    Uint32 current;
};

#endif