#include <iostream>
using namespace std;

class VideoService
{
public:
    virtual ~VideoService() = default;
    virtual void generateVideo() = 0;
};

class ActualVideoService : public VideoService
{
public:
    void generateVideo()
    {
        cout << "Generating video..." << "\n";
    }
};

class VideoProxy : public VideoService
{
private:
    ActualVideoService vd;

public:
    void generateVideo() override
    {
        // authentication check
        // logging
        vd.generateVideo();
    }
};

int main(){
    VideoProxy p;
    p.generateVideo();
    return 0;
}